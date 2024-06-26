// AUTOMATICALLY GENERATED BY BUILDINC v0.2.352 TOOL
// LAST BUILD (CMAKE): 2024-04-30 21:26:34

#pragma once

#ifndef BUILDINC_BUILDNUMBER_HEADER_H
#define BUILDINC_BUILDNUMBER_HEADER_H

#include <cstdint>

namespace BuildInc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 2;

	 // Do not modify these
	constexpr uint32_t build = 354;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0x25ec93c45ac96e0d;
	
	constexpr char version_string[] = "v0.2.354";
	constexpr char build_time_string[] = "2024-04-30 21:26:34";
	constexpr char phrase[] = "sprawl-vividness-tattered";
	constexpr char calver[] = "2024.18.354";
	constexpr char uuid[] = "07188708-A441-4126-B7D5-EB6740A79BCB";

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
#endif // BUILDINC_BUILDNUMBER_HEADER_H

