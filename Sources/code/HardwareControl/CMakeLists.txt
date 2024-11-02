#设置CMake的最小可适用版本
cmake_minimum_required(VERSION 3.16)

#指定Targer名称
set(TARGET_NAME HardwareControl)

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

#------------ 生成静态库 -------------
##设定生成库文件目录
add_library(${TARGET_NAME} STATIC)
add_library(${PROJECT_NAME}::${TARGET_NAME}  ALIAS  ${TARGET_NAME})

##指定源文件
target_sources(${TARGET_NAME}
    PRIVATE  ${${TARGET_NAME}_SRC_FILES}
    PRIVATE  ${${TARGET_NAME}_HEADER_FILES}
)

# 在此链接opencv
find_package(OpenCV REQUIRED)
##指定包含目录 该目录可以传播到使用该库的库文件
target_include_directories(
    ${TARGET_NAME}
    PUBLIC 
      "${${TARGET_NAME}_SOURCE_DIR}/inc"
      "${${TARGET_NAME}_SOURCE_DIR}/inc/Camera"
      "${${TARGET_NAME}_SOURCE_DIR}/inc/Stage"
      "${EXTERNAL}/PwsStage/inc"
      "${OpenCV_INCLUDE_DIRS}"
)

##指定链接库文件 该库文件同样可以传播到使用该库的库文件
target_link_libraries(${TARGET_NAME}
    PUBLIC  ${OpenCV_LIBS}
    PUBLIC  ${PROJECT_NAME}::Common
    PUBLIC  ${PROJECT_NAME}::PVCam
    PUBLIC  ${EXTERNAL}/PwsStage/lib/SLS_Dll.lib
)

##复制位移台所需要的第三方动态库到运行时路径
set(SLS_DLL_PATH "${EXTERNAL}/PwsStage/lib/SLS_Dll.dll")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SLS_DLL_PATH}"
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}"
)
message("SLS_DLL_PATH: ${SLS_DLL_PATH}")