add_custom_command(TARGET buildinc
    POST_BUILD
    COMMENT Run BuildInc and copy to tools
    COMMAND buildinc.exe buildnumber.h BuildInc -q
    #COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/bin/buildinc.exe E:/tools/global_commands
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
    USES_TERMINAL
)