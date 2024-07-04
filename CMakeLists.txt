cmake_minimum_required(VERSION 3.0.0)
project(Dash_n_Dot VERSION 0.1.0 LANGUAGES C)

add_executable(Dash_n_Dot  src/main.c)



include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(Dash_n_Dot ncurses)



# Set the output directory for the executable
set_target_properties(Dash_n_Dot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../out"
)