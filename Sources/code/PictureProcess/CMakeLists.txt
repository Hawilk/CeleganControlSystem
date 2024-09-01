#设置CMake的最小可适用版本
cmake_minimum_required(VERSION 3.16)

#指定Targer名称
set(TARGET_NAME PictureProcess)

##设置源代码路径
set(${TARGET_NAME}_SOURCE_DIR "${PROJECT_SOURCE_DIR}/code/${TARGET_NAME}")
set(CMAKE_CXX_STANDARD 17)

##提取所有源文件(include与src区分开)
file(GLOB_RECURSE  ${TARGET_NAME}_HEADER_FILES
    LIST_DIRECTORIES  False  CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.h*"
)
file(GLOB_RECURSE  ${TARGET_NAME}_SRC_FILES
    LIST_DIRECTORIES  False  CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.c*"
)

##为VS设置源代码文件夹
source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Header Files"
    FILES ${${TARGET_NAME}_HEADER_FILES}
)
source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Source Files"
    FILES ${${TARGET_NAME}_SRC_FILES}
)

##生成静态库文件
include_directories(${${TARGET_NAME}_SOURCE_DIR}/inc)

##设定生成库文件目录
add_library(${TARGET_NAME} STATIC)
add_library(${PROJECT_NAME}::${TARGET_NAME}  ALIAS  ${TARGET_NAME})

##指定源文件
target_sources(${TARGET_NAME}
    PRIVATE  ${${TARGET_NAME}_SRC_FILES}
    PRIVATE  ${${TARGET_NAME}_HEADER_FILES}
)