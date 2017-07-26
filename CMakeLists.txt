cmake_minimum_required(VERSION 2.6)
project(JetbotTest)

#set(CMAKE_BUILD_TYPE "Release")

include_directories("asp/inc" "uart/inc")

FILE(GLOB sourcefiles "asp/src/*.c" "uart/src/*.cpp")
add_executable( test ${sourcefiles} "JetbotTest.cpp")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable( test_dbus ${sourcefiles} "JetbotDBusTest.cpp")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
