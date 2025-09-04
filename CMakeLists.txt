cmake_minimum_required(VERSION 3.12)
project(Double_Pendulum_Simulation VERSION 0.1.0 LANGUAGES C CXX)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SRC_FILES CONFIGURE_DEPENDS 
    "${CMAKE_SOURCE_DIR}/*.cpp"
    "${CMAKE_SOURCE_DIR}/*.c"
)

add_executable(Double_Pendulum_Simulation ${SRC_FILES})

# Include Boost
cmake_policy(SET CMP0167 NEW)
find_package(Boost 1.83.0 REQUIRED)
target_include_directories(Double_Pendulum_Simulation PRIVATE ${Boost_INCLUDE_DIRS})

# Include Project Headers
target_include_directories(Double_Pendulum_Simulation
    PRIVATE
        ${CMAKE_SOURCE_DIR}/dependencies/include
)

# Link against glfw and system frameworks
target_link_libraries(Double_Pendulum_Simulation
    PRIVATE
        ${CMAKE_SOURCE_DIR}/dependencies/library/libglfw.3.4.dylib
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
)

# COPY SHADERS TO RUN DIR
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/shaders/" DESTINATION "${CMAKE_BINARY_DIR}/shaders/")