
#include <string>
#include <vector>
#include <format>
#include <chrono>
#include <sstream>
#include <random>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "effwords.h"
#include "buildnumber.h"

namespace global
{
    std::vector<std::string> eff_wordlist;
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

    if (global::eff_wordlist.empty())
    {
        std::string_view sv{effwords, EFFWORDS_LEN};

        auto splitwords = split(sv);

        global::eff_wordlist.reserve(splitwords.size());
        for (const auto &words : splitwords)
            global::eff_wordlist.emplace_back(split(words, "\t").at(1));
    }

    static std::random_device             rd;
    std::uniform_int_distribution<size_t> dist(0, global::eff_wordlist.size());

    auto phrase1 = global::eff_wordlist[dist(rd)];
    auto phrase2 = global::eff_wordlist[dist(rd)];
    auto phrase3 = global::eff_wordlist[dist(rd)];

    auto str = std::format("{}-{}-{}", phrase1, phrase2, phrase3);
    return str;
}


bool find_variable(const std::string &variable, const std::string &to_find)
{
    return variable.find(to_find) != std::string::npos;
}

size_t variable_pos(const std::string &variable, const std::string &to_find)
{
    return variable.find(to_find);
}


bool get_variable(const std::string &from, const std::string &what, unsigned int *output)
{

    if (find_variable(from, what))
    {
        size_t found = variable_pos(from, "=");

        size_t end = from.find(';');

        std::string number = from.substr(found + 1, (end - found) - 1);
        *output            = (uint32_t)std::stoi(number);
        return true;
    }

    return false;
}


std::pair<uint32_t, uint32_t> Multiplier(uint32_t buildnum)
{
    size_t width = std::to_string(buildnum).size();

    uint32_t mul = 1;
    while (width--)
        mul *= 10;

    return {mul, mul * 10};
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
    std::stringstream buffer;
    auto              now       = std::chrono::system_clock::now();
    auto              in_time_t = std::chrono::system_clock::to_time_t(now);

    tm nt;
    localtime_s(&nt, &in_time_t);

    buffer << std::put_time(&nt, "%F %T");
    return buffer.str();
}

void WriteHeader(std::filesystem::path &HeaderFile,
                 const std::string &    project_namespace,
                 uint32_t               major,
                 uint32_t               minor,
                 uint32_t               build)
{
    std::random_device                      rd;
    std::uniform_int_distribution<uint64_t> dist;

    auto date = GetDateString();

    std::string modns = project_namespace + "Version";

    std::string generated;
    generated.reserve(1400);

    const auto generated_version = std::format("v{}.{}.{}", major, minor, build);

    generated.append(std::format("// AUTOMATICALLY GENERATED BY BUILDINC {} TOOL\n", generated_version));
    generated.append(std::format("// LAST BUILD: {}\n\n", date));

    generated.append("#pragma once\n\n");

    generated.append(std::format("#ifndef {}_BUILDNUMBER_HEADER_H\n", ToUpper(modns)));
    generated.append(std::format("#define {}_BUILDNUMBER_HEADER_H\n", ToUpper(modns)));

    generated.append("\n#include <cstdint>\n\n");

    generated.append(std::format("namespace {}\n", modns));
    generated.append("{\n");

    generated.append("\t\t // You can modify major and minor\n");

    generated.append(std::format("\t\tconstexpr uint32_t major = {};\n", major));
    generated.append(std::format("\t\tconstexpr uint32_t minor = {};\n", minor));
    generated.append("\n\t\t // Do not modify these\n");

    generated.append(std::format("\t\tconstexpr uint32_t build = {};\n", build));
    generated.append("\t\t\n");

    auto [multi1, multi2] = Multiplier(build);
    generated.append(
        std::format("\t\tconstexpr uint32_t version = major * {} + minor * {} + build;\n", multi2, multi1));
    generated.append(std::format("\t\tconstexpr uint64_t random_seed = {:#0x};\n", dist(rd)));
    generated.append("\t\t\n");


    generated.append(std::format("\t\tconstexpr char version_string[] = \"{}\";\n", generated_version));
    generated.append(std::format("\t\tconstexpr char build_time_string[] = \"{}\";\n", date));
    auto phrase = GenerateRandomPhrase();
    generated.append(std::format("\t\tconstexpr char phrase[] = \"{}\";\n", phrase));
    generated.append("\n");

    generated.append("\t\t// Copy paste to import to your project\n");
    generated.append("\t\t/*\n");

    generated.append(std::format("\t\t\tconstexpr auto major = {}::major;\n", modns));
    generated.append(std::format("\t\t\tconstexpr auto minor = {}::minor;\n", modns));
    generated.append(std::format("\t\t\tconstexpr auto build = {}::build;\n", modns));
    generated.append(std::format("\t\t\tconstexpr auto version = {}::version;\n", modns));
    generated.append(std::format("\t\t\tconstexpr auto random_seed = {}::random_seed;\n", modns));
    generated.append("\t\t\t\n");

    generated.append(std::format("\t\t\tconstexpr auto version_string = {}::version_string;\n", modns));
    generated.append(std::format("\t\t\tconstexpr auto build_time_string = {}::build_time_string;\n", modns));
    generated.append(std::format("\t\t\tconstexpr auto phrase = {}::phrase;\n", modns));


    generated.append("\t\t*/\n");


    generated.append("}\n");

    generated.append(std::format("#endif // {}_BUILDNUMBER_HEADER_H\n", ToUpper(modns)));
    generated.append("\n");
    generated.shrink_to_fit();

    std::ofstream output(HeaderFile);

    output << generated;
    output.flush();
    output.close();
}


int main(int argc, char **argv)
{

    std::cout << "BuildInc v" << BuildIncVersion::version_string << "\n\n";


    std::vector<std::string> commandline(argv + 1, argv + argc);

    if (commandline.size() < 2)
    {
        std::cout << "usage: buildinc <output file> <projectname>\n";
        return 0;
    }

    if (commandline[0].empty())
    {
        std::cout << "No output file\n";
        return -1;
    }

    if (commandline[1].empty())
    {
        std::cout << "No project name set\n";
        return -2;
    }

    std::filesystem::path filename = std::filesystem::current_path() / commandline[0];

    std::string project_namespace = commandline[1];


    uint32_t major = 0;
    uint32_t minor = 0;
    uint32_t build = 0;

    if (!std::filesystem::exists(filename))
        WriteHeader(filename, project_namespace, major, minor, build);


    std::ifstream header(filename);
    if (!header.is_open())
    {
        std::cout << "Cant open header file\n";
        return -3;
    }

    int         count = 0;
    std::string line;

    while (header.good())
    {
        std::getline(header, line);

        unsigned int temp;

        if (count == 3)
        {
            header.close();
            break;
        }

        if (line.empty() || line.size() <= 25 || line.size() > 40 || line[0] == '/')
            continue;


        if (get_variable(line, "major = ", &temp))
        {
            count++;
            major = temp;
            continue;
        }


        if (get_variable(line, "minor = ", &temp))
        {
            count++;
            minor = temp;
            continue;
        }


        if (get_variable(line, "build = ", &temp))
        {
            count++;
            build = temp + 1;
            continue;
        }
    }

    std::cout << "buildinc "
              << " : '" << project_namespace << "' version is " << major << "." << minor << "." << build << "\n ";


    header.close();
    WriteHeader(filename, project_namespace, major, minor, build);


    return 0;
}
