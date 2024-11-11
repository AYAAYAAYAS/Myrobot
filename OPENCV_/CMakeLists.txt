cmake_minimum_required(VERSION 3.0)
project(OPENCV_)

set(CMAKE_CXX_STANDARD 17)

set(OpenCV_DIR F:\\opencv\\opencv\\x64\\vc16\\lib)  # 替换为您的 OpenCV 安装路径
find_package(OpenCV REQUIRED)


# 将源文件添加到此项目的可执行文件
add_executable(OPENCV_ main.cpp)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(OPENCV_ ${OpenCV_LIBS})




