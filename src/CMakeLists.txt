cmake_minimum_required(VERSION 3.20)

include_directories(src inc)

file(GLOB HEADER_FILES inc/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
