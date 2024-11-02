##设置CMake的最小可适用版本
cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME EleganSystem)

##配置项目名称/语言/版本
set(PROJECT_VERSION "1.0.0" CACHE STRING "默认工程版本号")
project(${PROJECT_NAME}
    LANGUAGES CXX C
    VERSION ${PROJECT_VERSION}
)

set(CMAKE_CXX_STANDARD 17)

##配置外部库路径
set(EXTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(OpenCV_DIR D:/Hasuyo/Opencv/opencv480/build)  # opencv340版本的cmake配置与msvc2019不兼容

## 配置本地cmake脚本路径
# list(APPEND CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(${PROJECT_NAME}_PLATFORM_NAME "x64")

message(STATUS "PLATFORM---: ${${PROJECT_NAME}_PLATFORM_NAME}")

##源代码位置
set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

##全局配置(并行编译、设置内联函数展开、关闭警告、启用comdat折叠,Release版本生成PDB)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /Ob2 /W1")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG")
endif()

##禁止RelWithDebInfo的优化，打开警告
option(BUILD_DEVELOPER "Build for developer" ON)
option(BUILD_PACKAGE "Build for package" OFF)

##控制VS工程生成使用"文件夹"组织结构
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(${PROJECT_NAME}_DEVELOPE_MODE  "开发模式" ON)

message(STATUS "PROJECT_PLATFORM---: ${PROJECT_PLATFORM}")

##将动态库\静态库输出路径定位到特定路径,供调试时使用(否则依赖的库分布在各个文件夹)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/pdb)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)  #运行时输出目录（可执行文件和动态库）
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib)  #静态库输出目录
# set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/pdb)

set(CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/data/PanelParameters.ini)
set(INI_DESTINATION_DIR ${CMAKE_BINARY_DIR}/config)
file(COPY ${CONFIG_FILE} DESTINATION ${INI_DESTINATION_DIR})

# 给当前节点添加子目录
add_subdirectory(external)
add_subdirectory(code)

# 设置启动项
set(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
