module;
#include <cstdint>

export module BuildInc;
export namespace BuildInc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	 // Do not modify these
	constexpr uint32_t build = 350;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0x2dede943dd837355;
	
	constexpr char version_string[] = "v0.2.350";
	constexpr char build_time_string[] = "2024-04-30 21:19:56";
	constexpr char phrase[] = "voting-liable-gigolo";
	constexpr char calver[] = "2024.18.350";
	constexpr char uuid[] = "39D0713C-2E49-4ECB-A82B-7C738D327D9E";

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
