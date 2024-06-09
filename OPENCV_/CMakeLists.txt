cmake_minimum_required(VERSION 3.0)
project(OPENCV_)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 设置 OpenCV 的安装路径
set(OpenCV_DIR F:\\opencv\\opencv\\x64\\vc16\\lib)  # 替换为您的 OpenCV 安装路径

# 导入 OpenCV
find_package(OpenCV REQUIRED)

# 包含 OpenCV 的头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

# 将源文件添加到此项目的可执行文件
add_executable(OPENCV_ main.cpp)

# 链接 OpenCV 库到你的应用程序
target_link_libraries(OPENCV_ ${OpenCV_LIBS})
