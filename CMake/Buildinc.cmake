function(run_buildinc target)

    add_custom_command(TARGET ${target}
        PRE_BUILD
        COMMENT Run BuildInc and copy to tools
        COMMAND buildinc.exe buildnumber.h BuildInc -q
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
        USES_TERMINAL
    )
endfunction()