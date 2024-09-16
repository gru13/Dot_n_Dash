cmake_minimum_required(VERSION 3.5)
project(Dash_n_Dot VERSION 0.1.0 LANGUAGES C)

set(PDCURSES_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib-win32/pdcurses/include")
set(PDCURSES_LIB_DIR "${CMAKE_SOURCE_DIR}/lib-win32/pdcurses/lib")

# Add the include directories
include_directories(${PDCURSES_INCLUDE_DIR})

# Add the library directory
link_directories(${PDCURSES_LIB_DIR})

# Add the executable
add_executable(Dash_n_Dot src/main.c src/Dot.c src/Dash.c src/Game.c src/dataStructures.c)

# Find and link pthread
# find_package(Threads REQUIRED)
target_link_libraries(Dash_n_Dot PRIVATE pthread)

# Link against the pdcurses library
target_link_libraries(Dash_n_Dot PRIVATE ${PDCURSES_LIB_DIR}/pdcurses.a)

# Set the output directory for the executable
set_target_properties(Dash_n_Dot PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../out"
)

# Include directories for header files
target_include_directories(Dash_n_Dot PRIVATE ${PROJECT_SOURCE_DIR}/src)
