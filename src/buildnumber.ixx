module;
#include <cstdint>

export module BuildInc;
export namespace BuildInc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	 // Do not modify these
	constexpr uint32_t build = 307;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0xde699f7af603c0f8;
	
	constexpr char version_string[] = "v0.2.307";
	constexpr char build_time_string[] = "2023-06-15 13:51:54";
	constexpr char phrase[] = "luster-vaguely-unknown";
	constexpr char calver[] = "2023.24.307";
	constexpr char uuid[] = "C1B2DF46-8BC9-40CA-9383-C4416FC1B945";

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
