cmake_minimum_required(VERSION 3.6)
project(Xolra)

set(CMAKE_CXX_STANDARD 11) 

include_directories(libs/include)
link_directories(libs/lib)

# Source files
file(GLOB SOURCES src/*.cpp)

# Executable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
add_executable(Xolra ${SOURCES})

# Link libraries
target_link_libraries(Xolra 
    sfml-graphics-s 
    sfml-window-s 
    sfml-system-s 
    opengl32 
    freetype 
    winmm 
    gdi32 
    sfml-main 
    discord
)

# Set compile flags
set(COMPILEFLAGS "-DSFML_STATIC")
add_definitions(${COMPILEFLAGS})

# Run the program after successful build
add_custom_target(run
    COMMAND Xolra
    DEPENDS Xolra
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    COMMENT "Runs main executable"
)
