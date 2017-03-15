cmake_minimum_required(VERSION 3.6)
project(ic2)

find_package(CURL)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Xml)
find_package(Qt5Network)
find_package(Qt5WebKit)
find_package(Qt5WebKitWidgets)




include_directories({Qt5WebKitWidgets_DIRS})
include_directories({Qt5Webkit_INCLUDE_DIRS})
include_directories({Qt5Network_INCLUDE_DIRS})
include_directories({Qt5Widgets_INCLUDE_DIRS})
include_directories({Qt5Xml_INCLUDE_DIRS})
include_directories({Qt5Core_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)


message(STATUS ${CURL_found})
add_executable(main main.cpp)

target_link_libraries( main Qt5::Core Qt5::Widgets Qt5::Xml Qt5::Network Qt5::WebKitWidgets)
target_link_libraries(main ${CURL_LIBRARIES})


add_executable(ic2 ${SOURCE_FILES})