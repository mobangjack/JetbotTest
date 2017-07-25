cmake_minimum_required(VERSION 2.6)
project(JetbotTest)

#set(CMAKE_BUILD_TYPE "Release")

include_directories("asp/inc" "uart/inc")

FILE(GLOB sourcefiles "*.cpp" "asp/src/*.c" "uart/src/*.cpp")
add_executable( test ${sourcefiles} )
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
