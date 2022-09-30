# buildinc (Visual Studio 2022)
Updates build versions automatically. 


Usage example: *buildinc output.h Example*

Generates C++ header file containing version and build numbers. Also included
  - random number seed
  - random code phrase.
  - compile time

Example output: https://github.com/Masfo/buildinc/blob/main/src/buildnumber.h


Example: add custom command to your CMake script to update per build.
```cpp
    add_custom_command(TARGET <your target> POST_BUILD
        COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/buildinc.exe buildnumber.h BuildInc -q
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
        )
```