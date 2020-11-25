cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ex2 main.cpp timeseries.cpp anomaly_detection_util.cpp SimpleAnomalyDetector.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
