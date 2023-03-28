// AUTOMATICALLY GENERATED BY BUILDINC v0.2.265 TOOL
// LAST BUILD (CMAKE): 2023-03-28 17:40:33

#pragma once

#ifndef BUILDINCVERSION_BUILDNUMBER_HEADER_H
	#define BUILDINCVERSION_BUILDNUMBER_HEADER_H

	#include <cstdint>

namespace BuildIncVersion
{
	// You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	// Do not modify these
	constexpr uint32_t build = 267;

	constexpr uint32_t version     = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0xb27c'591b'aee4'5f52;

	constexpr char version_string[]    = "v0.2.267";
	constexpr char build_time_string[] = "2023-03-28 17:40:33";
	constexpr char phrase[]            = "labored-impulse-array";
	constexpr char calver[]            = "2023.13.267";
	constexpr char uuid[]              = "0F3245FF-ECF1-46C1-BA25-D5F065E8F794";

	// Copy paste to import to your project
	/*
		constexpr auto major = BuildIncVersion::major;
		constexpr auto minor = BuildIncVersion::minor;
		constexpr auto build = BuildIncVersion::build;
		constexpr auto version = BuildIncVersion::version;
		constexpr auto random_seed = BuildIncVersion::random_seed;

		constexpr auto version_string = BuildIncVersion::version_string;
		constexpr auto build_time_string = BuildIncVersion::build_time_string;
		constexpr auto phrase = BuildIncVersion::phrase;
		constexpr auto calver = BuildIncVersion::calver;
		constexpr auto uuid = BuildIncVersion::uuid;
	*/
}
#endif // BUILDINCVERSION_BUILDNUMBER_HEADER_H
