cmake_minimum_required(VERSION 3.20)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
#if CMAKE_BUILD_TYPE == Debug || CMAKE_BUILD_TYPE == RelWithDebInfo
add_definitions(-DDEBUGGING_ON=1)
#endif

include_directories(src inc)

file(GLOB HEADER_FILES inc/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
