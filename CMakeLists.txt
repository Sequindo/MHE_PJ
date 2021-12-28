cmake_minimum_required(VERSION 3.0.0)
project(MHE_PJ VERSION 0.1.0)

include(CTest)
enable_testing()

set(MHE_SOURCES main.cpp ga.cpp graph.cpp)
add_executable(MHE_PJ ${MHE_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
