
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "buildnumber.h"
#include "effwords.h"

using namespace std::string_view_literals;

namespace global
{
	static std::vector<std::string> eff_wordlist;
}

std::vector<std::string> split(const std::string_view str, const std::string_view delims = "\n") noexcept
{
	auto start = str.find_first_not_of(delims, 0);
	auto stop  = str.find_first_of(delims, start);

	std::vector<std::string> tokens;
	while (std::string::npos != stop || std::string::npos != start)
	{
		tokens.emplace_back(str.substr(start, stop - start));
		start = str.find_first_not_of(delims, stop);
		stop  = str.find_first_of(delims, start);
	}
	return tokens;
}

std::string GenerateRandomPhrase() noexcept
{
	size_t eff_wordlist_size = 0;
	if (global::eff_wordlist.empty())
	{
		std::string_view sv{effwords, EFFWORDS_LEN};

		auto splitwords = split(sv);

		global::eff_wordlist.reserve(splitwords.size());
		for (const auto &words : splitwords)
			global::eff_wordlist.emplace_back(split(words, "\t").at(1));

		eff_wordlist_size = global::eff_wordlist.size();
	}

	std::random_device                    rd;
	std::uniform_int_distribution<size_t> dist(0ull, eff_wordlist_size - 1);

	std::vector<std::string> three_words{global::eff_wordlist[dist(rd)], global::eff_wordlist[dist(rd)], global::eff_wordlist[dist(rd)]};
	while (not std::ranges::unique(three_words).size() == 0)
	{
		three_words[0] = global::eff_wordlist[dist(rd)];
		three_words[1] = global::eff_wordlist[dist(rd)];
		three_words[2] = global::eff_wordlist[dist(rd)];
	}


	return std::format("{}-{}-{}", three_words[0], three_words[1], three_words[2]);
}

bool find_variable(std::string_view variable, std::string_view to_find) { return variable.find(to_find) != std::string::npos; }

size_t variable_pos(std::string_view variable, std::string_view to_find) { return variable.find(to_find); }

std::optional<unsigned int> get_variable(std::string_view from, std::string_view what) noexcept
{
	if (find_variable(from, what))
	{
		size_t found = variable_pos(from, "="sv);
		size_t end   = from.find(';');

		const std::string_view number = from.substr(found + 1, (end - found) - 1);
		return {(uint32_t)std::stoi(number.data())};
	}

	return std::nullopt;
}

std::pair<uint32_t, uint32_t> Multiplier(uint32_t buildnum)
{
	size_t width = std::to_string(buildnum).size();

	uint32_t mul = 1;
	while (width--)
		mul *= 10;

	return std::make_pair(mul, mul * 10);
}

char to_up(const char in) noexcept
{
	if (in >= 'a' && in <= 'z')
		return in - ('a' - 'A');

	return in;
}

static std::string ToUpper(const std::string &s)
{
	std::string ret = s;
	std::transform(ret.begin(), ret.end(), ret.begin(), to_up);
	return ret;
}

std::string GetDateString()
{
	auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	return std::format("{:%Y-%m-%d %X}", time);
}

std::string cal_version_string(uint32_t build)
{
	auto const time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
	return std::format("{:%Y.%V}.{}", time, build);
}

std::string uuid_string() noexcept
{
	static std::random_device                      rd;
	static std::uniform_int_distribution<uint64_t> dist(0);
	uint64_t                                       ab = (dist(rd) & 0xFFFF'FFFF'FFFF'0FFFULL) | 0x0000'0000'0000'4000ULL;
	uint64_t                                       cd = (dist(rd) & 0x3FFF'FFFF'FFFF'FFFFULL) | 0x8000'0000'0000'0000ULL;

	return std::format("{:08X}-{:04X}-{:04X}-{:04X}-{:012X}",
					   (ab >> 32) & 0xFFFF'FFFF,
					   (ab >> 16) & 0xFFFF,
					   (ab >> 00) & 0xFFFF,
					   (cd >> 48) & 0xFFFF,
					   (cd >> 00) & 0xFFFF'FFFF'FFFF);
}

void AppendCommon(std::string &generated, uint32_t major, uint32_t minor, uint32_t build, const std::string modns)
{
	std::random_device                      rd;
	std::uniform_int_distribution<uint64_t> dist;

	auto date = GetDateString();


	generated.append("\t // You can modify major and minor\n");

	generated.append(std::format("\tconstexpr uint32_t major = {};\n", major));
	generated.append(std::format("\tconstexpr uint32_t minor = {};\n", minor));
	generated.append("\n\t // Do not modify these\n");

	generated.append(std::format("\tconstexpr uint32_t build = {};\n", build));
	generated.append("\t\n");

	const auto [multi1, multi2] = Multiplier(build);
	generated.append(std::format("\tconstexpr uint32_t version = major * {} + minor * {} + build;\n", multi2, multi1));
	generated.append(std::format("\tconstexpr uint64_t random_seed = {:#0x};\n", dist(rd)));
	generated.append("\t\n");

	const auto generated_version = std::format("v{}.{}.{}", major, minor, build);
	generated.append(std::format("\tconstexpr char version_string[] = \"{}\";\n", generated_version));

	generated.append(std::format("\tconstexpr char build_time_string[] = \"{}\";\n", date));
	auto phrase = GenerateRandomPhrase();
	generated.append(std::format("\tconstexpr char phrase[] = \"{}\";\n", phrase));
	// Cal-ver
	generated.append(std::format("\tconstexpr char calver[] = \"{}\";\n", cal_version_string(build)));
	// uuid
	generated.append(std::format("\tconstexpr char uuid[] = \"{}\";\n", uuid_string()));


	generated.append("\n");

	generated.append("\t// Copy paste to import to your project\n");
	generated.append("\t/*\n");

	generated.append(std::format("\t\tconstexpr auto major = {}major;\n", modns));
	generated.append(std::format("\t\tconstexpr auto minor = {}minor;\n", modns));
	generated.append(std::format("\t\tconstexpr auto build = {}build;\n", modns));
	generated.append(std::format("\t\tconstexpr auto version = {}version;\n", modns));
	generated.append(std::format("\t\tconstexpr auto random_seed = {}random_seed;\n", modns));
	generated.append("\t\t\t\n");

	generated.append(std::format("\t\tconstexpr auto version_string = {}version_string;\n", modns));
	generated.append(std::format("\t\tconstexpr auto build_time_string = {}build_time_string;\n", modns));
	generated.append(std::format("\t\tconstexpr auto phrase = {}phrase;\n", modns));
	generated.append(std::format("\t\tconstexpr auto calver = {}calver;\n", modns));
	generated.append(std::format("\t\tconstexpr auto uuid = {}uuid;\n", modns));
	generated.append("\t*/\n");
}

void WriteModule(std::filesystem::path &HeaderFile, const std::string &project_namespace, uint32_t major, uint32_t minor, uint32_t build)
{

	std::string modns = project_namespace;

	std::string generated;
	generated.reserve(1400);

	generated.append("module;\n");
	generated.append("#include <cstdint>\n\n");

	generated.append(std::format("export module {};\n", modns));
	generated.append(std::format("export namespace {}\n", modns));
	generated.append("{\n");


	AppendCommon(generated, major, minor, build, modns + "::");

	generated.append("}\n");


	// Write
	generated.shrink_to_fit();

	std::ofstream output(HeaderFile);
	output << generated;
	output.flush();
	output.close();
}

void WriteHeader(std::filesystem::path &HeaderFile, const std::string &project_namespace, uint32_t major, uint32_t minor, uint32_t build)
{
	std::uniform_int_distribution<uint64_t> dist;

	auto date = GetDateString();

	const std::string &modns = project_namespace;

	std::string generated;
	generated.reserve(1400);


	generated.append(std::format("// AUTOMATICALLY GENERATED BY BUILDINC {} TOOL\n", BuildInc::version_string));
	generated.append(std::format("// LAST BUILD (CMAKE): {}\n\n", date));

	generated.append("#pragma once\n\n");

	generated.append(std::format("#ifndef {}_BUILDNUMBER_HEADER_H\n", ToUpper(modns)));
	generated.append(std::format("#define {}_BUILDNUMBER_HEADER_H\n", ToUpper(modns)));

	generated.append("\n#include <cstdint>\n\n");

	generated.append(std::format("namespace {}\n", modns));
	generated.append("{\n");

	AppendCommon(generated, major, minor, build, modns + "::");


	generated.append("}\n");

	generated.append(std::format("#endif // {}_BUILDNUMBER_HEADER_H\n", ToUpper(modns)));
	generated.append("\n");
	generated.shrink_to_fit();

	std::ofstream output(HeaderFile);

	output << generated;
	output.flush();
	output.close();
}

void Write(bool module, std::filesystem::path &HeaderFile, const std::string &project_namespace, uint32_t major, uint32_t minor,
		   uint32_t build)
{
	if (!module)
		WriteHeader(HeaderFile, project_namespace, major, minor, build);
	else
		WriteModule(HeaderFile, project_namespace, major, minor, build);
}

int main(int argc, char *argv[])
{

	std::vector<std::string> commandline(argv + 1, argv + argc);

	bool quiet        = !commandline.empty() ? std::ranges::find(commandline, "-q") != commandline.end() : false;
	bool write_module = !commandline.empty() ? std::ranges::find(commandline, "-m") != commandline.end() : false;


	if (!quiet)
		std::cout << std::format("BuildInc {}\n\n", BuildInc::version_string);

	if (commandline.size() < 2)
	{
		if (!quiet)
		{
			std::cout << "usage: buildinc <output file> <projectname> [-q][-m]\n";
			std::cout << "\t-q  Quiet\n";
			std::cout << "\t-m  Generate module version\n";
		}

		return 0;
	}

	if (commandline[0].empty())
	{
		if (!quiet)
			std::cout << "No output file\n";
		return -1;
	}

	if (commandline[1].empty())
	{
		if (!quiet)
			std::cout << "No project name set\n";
		return -2;
	}

	std::filesystem::path filename = std::filesystem::current_path() / commandline[0];

	std::string project_namespace = commandline[1];


	uint32_t major = 0;
	uint32_t minor = 0;
	uint32_t build = 0;

	if (!std::filesystem::exists(filename))
		Write(write_module, filename, project_namespace, major, minor, build);


	std::ifstream header(filename);
	if (!header.is_open())
	{
		if (!quiet)
			std::cout << "Cant open header file\n";
		return -3;
	}

	int         count = 0;
	std::string line;

	while (header.good())
	{
		std::getline(header, line);


		if (count == 3)
		{
			header.close();
			break;
		}

		if (line.empty() || line.size() <= 25 || line.size() > 40 || line[0] == '/')
			continue;


		if (auto temp = get_variable(line, "major = "); temp)
		{
			count++;
			major = *temp;
			continue;
		}


		if (auto temp = get_variable(line, "minor = "); temp)
		{
			count++;
			minor = *temp;
			continue;
		}


		if (auto temp = get_variable(line, "build = "); temp)
		{
			count++;
			build = *temp + 1;
			continue;
		}
	}
	std::cout << std::format("buildinc : '{}' version is {}.{}.{}\n", project_namespace, major, minor, build);

	header.close();
	Write(write_module, filename, project_namespace, major, minor, build);

	return 0;
}
