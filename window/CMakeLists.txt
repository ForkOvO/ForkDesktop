cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(window) # 项目名称

set(LIBRARY_OUTPUT_PATH ${LIB_PATH}) # 设置库输出路径

aux_source_directory(./ SRC) # 查找当前目录下所有源文件
add_library(${PROJECT_NAME} SHARED ${SRC}) # 生成动态库

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    utils
)
