module;
#include <cstdint>

export module BuildInc;
export namespace BuildInc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	 // Do not modify these
	constexpr uint32_t build = 319;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0x802eafff38e128de;
	
	constexpr char version_string[] = "v0.2.319";
	constexpr char build_time_string[] = "2023-09-26 17:52:56";
	constexpr char phrase[] = "veteran-punk-cottage";
	constexpr char calver[] = "2023.39.319";
	constexpr char uuid[] = "FAB10069-2746-4C28-89B8-BB8E5F50F18F";

	// Copy paste to import to your project
	/*
		constexpr auto major = BuildInc::major;
		constexpr auto minor = BuildInc::minor;
		constexpr auto build = BuildInc::build;
		constexpr auto version = BuildInc::version;
		constexpr auto random_seed = BuildInc::random_seed;
			
		constexpr auto version_string = BuildInc::version_string;
		constexpr auto build_time_string = BuildInc::build_time_string;
		constexpr auto phrase = BuildInc::phrase;
		constexpr auto calver = BuildInc::calver;
		constexpr auto uuid = BuildInc::uuid;
	*/
}
