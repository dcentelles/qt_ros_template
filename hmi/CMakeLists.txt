cmake_minimum_required(VERSION 3.1.0)
project(hmi)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  std_srvs
  actionlib
  actionlib_msgs
  hmi_msgs
)
#http://doc.qt.io/qt-5/cmake-manual.html
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
#SET(CMAKE_AUTOUIC ON)

set(Qt5Core_DIR "~/programming/Qt/5.9.2/gcc_64/lib/cmake/Qt5Core")
set(Qt5Gui_DIR "~/programming/Qt/5.9.2/gcc_64/lib/cmake/Qt5Gui")
set(Qt5Widgets_DIR "~/programming/Qt/5.9.2/gcc_64/lib/cmake/Qt5Widgets")
set(Qt5_DIR "~/programming/Qt/5.9.2/gcc_64/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE "~/programming/Qt/5.9.2/gcc_64/bin/qmake")

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

generate_messages(DEPENDENCIES
    std_msgs
    actionlib_msgs
    )
add_definitions(-fPIC -std=c++14)

SET(PROJECT_INCLUDE_DIRS
    ${catkin_INCLUDE_DIRS}
    src/include
)

set(HW_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/include/hmi)
set(HW_GUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/gui)

#https://stackoverflow.com/questions/19761767/qt-5-cmake-fails-with-undefined-reference-to-vtable-on-hello-world-with-inc-sr
qt5_wrap_cpp(hmi_SRC
    ${HW_HEADER_DIR}/mainwindow.h
    ${HW_HEADER_DIR}/qrosnode.h
    ${HW_HEADER_DIR}/logger.h
    ${HW_HEADER_DIR}/common.h
    )
qt5_wrap_ui(hmi_UI
    ${HW_GUI_DIR}/mainwindow.ui
    )

set(${PROJECT_NAME}_LIB ${PROJECT_NAME}_lib)

# Tell CMake to create the ${PROJECT_NAME} executable
add_library(${${PROJECT_NAME}_LIB}
        src/mainwindow.cpp
        src/qrosnode.cpp
        src/logger.cpp
        src/common.cpp
        ${hmi_SRC}
        ${hmi_UI}
	)

set(QT_DEPS
        Qt5::Widgets
        Qt5::Core
        )
#message("DETECTED QT VERSION: "${Qt5Core_VERSION})
#message("DETECTED QT LIBRARIES: "${Qt5Core_INCLUDE_DIRS})

target_include_directories(${${PROJECT_NAME}_LIB} PUBLIC ${PROJECT_INCLUDE_DIRS})
target_link_libraries(${${PROJECT_NAME}_LIB}  ${QT_DEPS}  ${catkin_LIBRARIES})

add_executable(${PROJECT_NAME} 
        src/main.cpp
	)

target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIB})

# The following is for force msg dependencies to be compiled before:
#   https://answers.ros.org/question/73048/first-compile-with-messages-messages-not-found/
add_dependencies(${${PROJECT_NAME}_LIB} ${catkin_EXPORTED_TARGETS})

catkin_package(
    CATKIN_DEPENDS
    roscpp std_msgs
    message_runtime
    actionlib_msgs
    hmi_msgs
   DEPENDS
    ${QT_DEPS}
)
