function(run_buildinc target)

        add_custom_command(TARGET ${target}
                           PRE_BUILD
                           COMMAND buildinc ${CMAKE_CURRENT_SOURCE_DIR}/src/buildnumber.h BuildInc -q 
                           COMMENT "Increase build number"

        )
endfunction()


