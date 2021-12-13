cmake_minimum_required(VERSION 3.18)
project(Revive VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Revive Revive.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(cryptoTools REQUIRED)

target_link_libraries(Revive oc::cryptoTools)
target_link_libraries(Revive -lglpk)

