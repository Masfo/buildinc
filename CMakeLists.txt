#
cmake_minimum_required (VERSION 3.25)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

# buildinc.exe buildnumber.h $(ProjectName)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(SetupMSVC)
include(Buildinc)


set(PROJECT_VERSION 1.0.0)




project(buildinc VERSION ${PROJECT_VERSION} LANGUAGES CXX)



# Buildinc
add_executable (buildinc)
setup_piku_executable_msvc(buildinc "")
target_include_directories(buildinc PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)


add_subdirectory(src)

target_compile_options(buildinc PRIVATE 
       
    /wd5039 # pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc.
    
    /wd5262 # implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]] when a break 
                    # statement is intentionally omitted between cases
    /wd4710 # function not inlined
    /wd4711 # function selected for automatic inline expansion
    /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
)

run_buildinc(buildinc)

