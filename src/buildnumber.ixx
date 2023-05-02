module;
#include <cstdint>

export module BuildInc;
export namespace BuildInc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	 // Do not modify these
	constexpr uint32_t build = 298;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0xcc95d41e842450b3;
	
	constexpr char version_string[] = "v0.2.298";
	constexpr char build_time_string[] = "2023-05-02 22:24:08";
	constexpr char phrase[] = "lemon-passably-talon";
	constexpr char calver[] = "2023.18.298";
	constexpr char uuid[] = "79C0CD61-1326-4999-A8C8-24D92F73F754";

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
