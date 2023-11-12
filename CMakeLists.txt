cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(EmbPythonTest)

# Find Python
find_package(Python3 REQUIRED COMPONENTS Development)

# Add your C++ source files
set(SOURCES
    src/main2.cpp
)

# Create an executable
add_executable(emb_p ${SOURCES})

# Include Python headers
target_include_directories(emb_p PRIVATE ${Python3_INCLUDE_DIRS})

# Link against Python library
target_link_libraries(emb_p PRIVATE ${Python3_LIBRARIES})

