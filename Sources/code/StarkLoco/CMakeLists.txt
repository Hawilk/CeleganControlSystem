#设置CMake的最小可适用版本
cmake_minimum_required(VERSION 3.16)

##设置target名称
set(TARGET_NAME  StarkLoco)

##设置源代码路径
set(${TARGET_NAME}_SOURCE_DIR "${PROJECT_SOURCE_DIR}/code/${TARGET_NAME}")

##提取所有源文件(include与src区分开)
file(GLOB_RECURSE  ${TARGET_NAME}_HEADER_FILES
    LIST_DIRECTORIES  False  CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.h*"
)
file(GLOB_RECURSE  ${TARGET_NAME}_SRC_FILES
    LIST_DIRECTORIES  False  CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.h*"
    "${${TARGET_NAME}_SOURCE_DIR}/*.c*"
    "${${TARGET_NAME}_SOURCE_DIR}/*.rc"
    "${${TARGET_NAME}_SOURCE_DIR}/*.qrc"
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

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
#生成可执行程序
add_executable(${TARGET_NAME}
    ${${TARGET_NAME}_HEADER_FILES}
    ${${TARGET_NAME}_SRC_FILES}
    ${${TARGET_NAME}_QT_UI_FILES}
    ${${TARGET_NAME}_QT_QRC_FILES}
    "systemInterface.ui"  
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    PROPERTY VS_STARTUP_PROJECT ${TARGET_NAME})

target_include_directories(${TARGET_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/code/SystemUI/inc
)

# 添加Qt库路径
set_target_properties(${TARGET_NAME} PROPERTIES AUTOMOC ON)
set_target_properties(${TARGET_NAME} PROPERTIES AUTOUIC ON)
set_target_properties(${TARGET_NAME} PROPERTIES AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets)

target_link_libraries(${TARGET_NAME}
    PUBLIC  Qt5::Widgets
    PUBLIC  ${PROJECT_NAME}::SystemUI
)