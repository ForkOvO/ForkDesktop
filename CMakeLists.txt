cmake_minimum_required(VERSION 3.16) # CMake最小版本要求
project(ForkDesktop VERSION 0.1 LANGUAGES CXX) # 项目名称 版本 语言

set(CMAKE_AUTOUIC ON) # 自动生成UI文件
set(CMAKE_AUTOMOC ON) # 自动生成MOC文件
set(CMAKE_AUTORCC ON) # 自动生成RCC文件

set(CMAKE_CXX_STANDARD 17) # C++标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++标准要求

set(LIB_PATH ${PROJECT_SOURCE_DIR}/bin) # 库文件目录
set(EXEC_PATH ${PROJECT_SOURCE_DIR}/bin) # 可执行文件目录

find_package(Qt6 REQUIRED COMPONENTS # 查找Qt6库
    Widgets
    Network
)

set(EXECUTABLE_OUTPUT_PATH ${EXEC_PATH}) # 可执行文件输出目录

include_directories( # 头文件目录
    ${PROJECT_SOURCE_DIR}/window
    ${PROJECT_SOURCE_DIR}/utils
    ${PROJECT_SOURCE_DIR}/pages
)

# 添加子目录
add_subdirectory(window)
add_subdirectory(utils)

set(PROJECT_SOURCES main.cpp ) # 项目源文件
set(PROJECT_QRCS res.qrc qss.qrc) # 项目资源文件

qt_add_executable(
    ${PROJECT_NAME} # 可执行文件名称
    MANUAL_FINALIZATION # 手动完成
    ${PROJECT_SOURCES} # 项目源文件
    ${PROJECT_QRCS} # 项目资源文件
    res/icon.rc # 输出图标
) # 生成可执行文件

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    # QT
    Qt6::Widgets
    # 自定义
    window
    utils
) # 链接库

# 设置目标属性
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    # 控制台 ON不生成 OFF生成
    WIN32_EXECUTABLE OFF
    # WIN32_EXECUTABLE ON
)

qt_finalize_executable(${PROJECT_NAME}) # 完成可执行文件
