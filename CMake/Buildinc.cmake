function(run_buildinc target)

        find_program(BUILDINC_TOOL "buildinc" NO_CACHE)

        add_custom_command(TARGET ${target}
                           PRE_BUILD
                           COMMAND ${BUILDINC_TOOL} ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.h BuildInc -q 
                           WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
                           COMMENT "Increase build number"

        )
endfunction()


