cmake_minimum_required(VERSION 3.6)
project(midiguitar_pwm_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    midiguitar_pwm_2.ino)

add_executable(midiguitar_pwm_2 ${SOURCE_FILES})