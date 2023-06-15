module;
#include <cstdint>

export module BuildInc;
export namespace BuildInc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	 // Do not modify these
	constexpr uint32_t build = 309;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0xdbaf9394f6eb01f3;
	
	constexpr char version_string[] = "v0.2.309";
	constexpr char build_time_string[] = "2023-06-15 15:31:24";
	constexpr char phrase[] = "disjoin-bullion-create";
	constexpr char calver[] = "2023.24.309";
	constexpr char uuid[] = "84FC179B-25ED-4454-9B4B-A97FAC5C54A3";

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
