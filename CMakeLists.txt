cmake_minimum_required(VERSION 3.12)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(EmbPythonTest LANGUAGES CXX)

# Find Python
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

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


find_package(pybind11 REQUIRED)

# Add the pybind11 module
pybind11_add_module(my_robot_function src/pybind11_module.cpp)
target_link_libraries(my_robot_function PRIVATE pybind11::pybind11)


# Create an executable
add_executable(emb_pybind11 src/main_py11bind.cpp)

# Include Python headers
target_include_directories(emb_pybind11 PRIVATE ${Python3_INCLUDE_DIRS})

# Link against Python library
target_link_libraries(emb_pybind11 PRIVATE ${Python3_LIBRARIES})

