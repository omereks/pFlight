cmake_minimum_required(VERSION 3.0.0)
project(ex4 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(ex4 MainTrain.cpp timeseries.cpp anomaly_detection_util.cpp SimpleAnomalyDetector.cpp HybridAnomalyDetector.cpp minCircle.cpp CLI.cpp Server.cpp) 

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(ex4  -lpthread)
include(CPack)
