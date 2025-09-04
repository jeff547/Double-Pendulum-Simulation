cmake_minimum_required(VERSION 3.10.0)
project(Double_Pendulum_Simulation VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Double_Pendulum_Simulation
    Ball.cpp
    DoublePendulum.cpp
    DoublePendulumODE.cpp
    Lab.cpp
    RigidBody.cpp
    Rod.cpp
    glad.c
    main.cpp
)

# Dependencies include & library paths
target_include_directories(Double_Pendulum_Simulation
    PRIVATE
        ${CMAKE_SOURCE_DIR}/dependencies/include
        /opt/homebrew/opt/boost/include
)

target_link_directories(Double_Pendulum_Simulation
    PRIVATE
        ${CMAKE_SOURCE_DIR}/dependencies/library
        /opt/homebrew/opt/boost/lib
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