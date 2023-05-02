# buildinc (Visual Studio 2022)
Updates build versions automatically. 


Usage example: *buildinc output.h Example*

Generates C++ header file containing version and build numbers. Also included
  - random number seed
  - random code phrase.
  - compile time

Example output: 
  - Header https://github.com/Masfo/buildinc/blob/main/src/buildnumber.h
  - Module: https://github.com/Masfo/buildinc/blob/main/src/buildnumber.ixx


Example: add custom command to your CMake script to update per build.
```cpp
find_program(BUILDINC_TOOL "buildinc" NO_CACHE)

// Header
add_custom_command(TARGET <your_target>
                   PRE_BUILD
                   COMMAND ${BUILDINC_TOOL} ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.h BuildInc -q 
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
                   COMMENT "Increase build number"
)
```

```cpp
find_program(BUILDINC_TOOL "buildinc" NO_CACHE)

// Module
add_custom_command(TARGET <your_target>
                   PRE_BUILD
                   COMMAND ${BUILDINC_TOOL} ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.ixx BuildInc -q -m
                   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
                   COMMENT "Increase build number"
)
```
![Clang-Format check](https://github.com/Masfo/buildinc/actions/workflows/clang-format-check.yml/badge.svg)
