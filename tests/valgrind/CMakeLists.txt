cmake_minimum_required(VERSION 3.17)

#Valgrind test
add_custom_target(memcheck-report)

#Valgrind check command
add_custom_command( TARGET memcheck-report
        POST_BUILD
        COMMAND valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 -s --track-fds=yes --suppressions=${CMAKE_BINARY_DIR}/../tests/valgrind/Midi_Parser.suppressions --log-file=${CMAKE_BINARY_DIR}/../tests/valgrind/valgrind_memcheck_${DATE}.log ${CMAKE_BINARY_DIR}/Midi_Parser)
