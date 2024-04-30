module;
#include <cstdint>

export module moduleVersion;

export namespace moduleVersion
{
	// You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	// Do not modify these
	constexpr uint32_t build = 1'2000;

	constexpr uint32_t version     = major * 100 + minor * 10 + build;
	constexpr uint64_t random_seed = 0xdd57'3015'6a2c'4050;

	constexpr char version_string[]    = "v0.0.1";
	constexpr char build_time_string[] = "2023-04-30 21:12:49";
	constexpr char phrase[]            = "abacus-abacus-abacus";
	constexpr char calver[]            = "2023.17.1";
	constexpr char uuid[]              = "AAF42AE5-77B8-4AA6-AAE8-3C9DAE7C2614";

	// Copy paste to import to your project
	/*
		constexpr auto major = moduleVersion::major;
		constexpr auto minor = moduleVersion::minor;
		constexpr auto build = moduleVersion::build;
		constexpr auto version = moduleVersion::version;
		constexpr auto random_seed = moduleVersion::random_seed;

		constexpr auto version_string = moduleVersion::version_string;
		constexpr auto build_time_string = moduleVersion::build_time_string;
		constexpr auto phrase = moduleVersion::phrase;
		constexpr auto calver = moduleVersion::calver;
		constexpr auto uuid = moduleVersion::uuid;
	*/
} // namespace moduleVersion
