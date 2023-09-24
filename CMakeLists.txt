cmake_minimum_required(VERSION 3.16.3)
project(TestBox VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)
set(EXECUTABLE_OUTPUT_PATH ../output)

# OpenMP
find_package(OpenMP REQUIRED)

# ncnn
set(NCNN_DIR /QMy-File2/QPackage/ncnn-20220322/install/)
include_directories(${NCNN_DIR}/include/)
link_directories(${NCNN_DIR}/lib/)
set(NCNN_LIBS libncnn.a)

# opencv
set(OpenCV_DIR /QMy-File2/QPackage/opencv-4.8.0/output_host_ubuntu2004/)
include_directories(${OpenCV_DIR}/include/opencv4/)
link_directories(${OpenCV_DIR}/lib/)
set(OpenCV_LIBS libopencv_world.so)

set(LIB_LIST ${NCNN_LIBS} ${OpenCV_LIBS})

include_directories(./)

set(SRC_Net
Net/NetNCNN.cpp
Net/NetRKNN.cpp)

set(SRC_Predictor
Predictor/Predictor.cpp)

set(SRC_PreProcessor
PreProcessor/PreProcessor.cpp)

set(SRC_PostProcessor
PostProcessor/PostProcessor.cpp
PostProcessor/PostUnit.cpp)

set(SRC_LIST main.cpp ${SRC_Net} ${SRC_Predictor} ${SRC_PreProcessor} ${SRC_PostProcessor})

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIB_LIST} OpenMP::OpenMP_CXX)
