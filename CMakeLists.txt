cmake_minimum_required(VERSION 3.5)
project(Dash_n_Dot VERSION 0.1.0 LANGUAGES C)

# Add the executable
add_executable(Dash_n_Dot src/main.c src/Dot.c src/Dash.c src/Game.c src/dataStructures.c)

# Link against the ncurses library
target_link_libraries(Dash_n_Dot ncurses pthread)

# Set the output directory for the executable
set_target_properties(Dash_n_Dot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../out"
)

# Include directories for header files
target_include_directories(Dash_n_Dot PRIVATE ${PROJECT_SOURCE_DIR}/src)
