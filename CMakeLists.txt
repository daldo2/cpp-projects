cmake_minimum_required(VERSION 3.20)

project(cpp_projects LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(stack)
add_subdirectory(Stack_cpp)
add_subdirectory(Complex_numbers)
add_subdirectory(lecture_examples)

find_program(VALGRIND_EXECUTABLE valgrind)

if(VALGRIND_EXECUTABLE)
    foreach(program_target IN ITEMS stack_c stack_cpp complex_numbers)
        add_custom_target(valgrind_${program_target}
            COMMAND ${VALGRIND_EXECUTABLE}
                --leak-check=full
                --show-leak-kinds=all
                --track-origins=yes
                --errors-for-leak-kinds=all
                --error-exitcode=1
                $<TARGET_FILE:${program_target}>
            DEPENDS ${program_target}
            USES_TERMINAL
            VERBATIM
        )
    endforeach()
else()
    message(WARNING "Valgrind was not found; valgrind_* targets will not be available")
endif()
