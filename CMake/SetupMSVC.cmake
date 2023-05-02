
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_SYSROOT_FLAG_CODE "list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS ixx)")


# setup_piku_executable(targetname exename)
function(setup_piku_executable_msvc target outputname)

    set_property(TARGET "${target}" PROPERTY CXX_STANDARD          23)
    set_property(TARGET "${target}" PROPERTY CXX_STANDARD_REQUIRED ON)
    set_property(TARGET "${target}" PROPERTY CXX_EXTENSIONS        OFF)

    set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

    if(outputname STREQUAL "")
        set_target_properties(${target} PROPERTIES OUTPUT_NAME "${target}")
    else()
        set_target_properties(${target} PROPERTIES OUTPUT_NAME "${outputname}")
    endif()

    get_target_property(str ${target} OUTPUT_NAME)


    set_target_properties("${target}" PROPERTIES DEBUG_POSTFIX "d")


    set_property(TARGET "${target}" PROPERTY VS_STARTUP_PROJECT  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    set_target_properties("${target}" PROPERTIES 
                          RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/bin
                          RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/bin
    )


    if(MSVC)
        target_compile_definitions("${target}" PRIVATE -DUNICODE)
        target_compile_definitions("${target}" PRIVATE -D_UNICODE)
        #target_compile_definitions("${target}" PRIVATE -D_CRT_SECURE_NO_WARNINGS)
        target_compile_definitions("${target}" PRIVATE -DNOMINMAX)
        target_compile_definitions("${target}" PRIVATE -DWIN32_LEAN_AND_MEAN)


        target_compile_options("${target}" PRIVATE /nologo)
        target_compile_options("${target}" PRIVATE -Zc:__cplusplus /Zc:alignedNew)
        target_compile_options("${target}" PRIVATE /utf-8)
        target_compile_options("${target}" PRIVATE /EHsc)
        #target_compile_options("${target}" PRIVATE /Za)

        target_compile_options("${target}"  PRIVATE /fp:precise)
        target_compile_options("${target}" PRIVATE /diagnostics:caret)


        target_compile_options("${target}" PRIVATE /experimental:module)
        target_compile_options("${target}" PRIVATE /Zc:preprocessor)
        target_compile_options("${target}" PRIVATE /permissive-)
        target_compile_options("${target}" PRIVATE /std:c++latest)

        target_compile_options("${target}" PRIVATE /Wall)
        # target_compile_options("${target}" PRIVATE /WX) # Warnings as errors


        # Debug
        if (${CMAKE_BUILD_TYPE} MATCHES "Debug")

            target_compile_options("${target}"  PRIVATE /JMC)    # Just my debugging
            target_compile_definitions("${target}" PRIVATE -DDEBUG)

            target_compile_options("${target}"  PRIVATE /Od)

            target_compile_options("${target}"  PRIVATE /RTC1)
            target_compile_options("${target}"  PRIVATE /GS)
            target_compile_options("${target}"  PRIVATE /Zi)     # /ZI edit/continue

            target_link_options("${target}" PRIVATE /DEBUG)
            #target_link_options("${target}" PRIVATE /ALIGN:16)
        endif()

        # Release
        if (${CMAKE_BUILD_TYPE} MATCHES "Release")
           #set_target_properties("${target}" PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)

            target_compile_definitions("${target}" PRIVATE -DNDEBUG)
        
            target_compile_options("${target}"  PRIVATE /O2  /Os)
            target_compile_options("${target}"  PRIVATE /GS-)

            target_link_options("${target}" PRIVATE /Release)
            target_link_options("${target}" PRIVATE /INCREMENTAL:NO)


            target_link_options("${target}" PRIVATE /OPT:REF /OPT:ICF)




            # Undocumented options
            target_link_options("${target}" PRIVATE  /emittoolversioninfo:no /emitpogophaseinfo)

            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/stub.bin)
            target_link_options("${target}" PRIVATE  /stub:${CMAKE_CURRENT_SOURCE_DIR}/stub.bin )
            endif()
        endif()




        # Minimum Windows 10.
        # target_compile_definitions(CMakeTest+1 PRIVATE -DWINVER=0x0a00)
        # target_compile_definitions(CMakeTest+1 PRIVATE -D_WIN32_WINNT=0x0a00)

        # Check if has manifest.txt then add one
        target_link_options("${target}" PRIVATE  /MANIFEST:NO)


        target_link_options("${target}" PRIVATE  /MAP:map.txt)


        if(BUILD_SHARED_LIBS)
            # Dynamic
            if (${CMAKE_BUILD_TYPE} MATCHES "Release")
                set_target_properties("${target}"  PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
            else()
                set_target_properties("${target}"  PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
            endif()
        else()
            # Static
            if (${CMAKE_BUILD_TYPE} MATCHES "Release")
                set_target_properties("${target}"  PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
            else()
                set_target_properties("${target}"  PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
            endif()
        endif()


        # Disabled warnings
        target_compile_options("${target}" PRIVATE 
        
            /wd5039 # pointer or reference to potentially throwing function passed to 'extern "C"' function under -EHc.

            /wd5262 # implicit fall-through occurs here; are you missing a break statement? Use [[fallthrough]] when a break 
                    # statement is intentionally omitted between cases
        )

    endif() # MSVC

    find_program(BUILDINC_TOOL "buildinc" NO_CACHE)
    if(BUILDINC_TOOL)
        # Build header version
        add_custom_command(TARGET ${target}
                           PRE_BUILD
                           COMMAND ${BUILDINC_TOOL} ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.h BuildInc -q
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
                           COMMENT "Increase build number (header)")
    # Build module version
        add_custom_command(TARGET ${target}
                       PRE_BUILD
                       COMMAND ${BUILDINC_TOOL} ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.ixx BuildInc -q -m
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
                       COMMENT "Increase build number (module)")
    endif()

endfunction()
