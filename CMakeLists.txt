cmake_minimum_required(VERSION 3.2)
project(vb01Gui)

cmake_policy(SET CMP0015 NEW)
set(CMAKE_BUILD_TYPE Debug)
set(VB01_DIR ../vb01)

include_directories(external/vb01)
include_directories(external/vb01/external/freetype/include)
include_directories(external/vb01/external/glfw/include/GLFW)
include_directories(${VB01_DIR})

set(core button.cpp listbox.cpp textbox.cpp checkbox.cpp slider.cpp)
set(LIB_NAME vb01Gui)

add_library(vb01Gui ${core})

target_link_directories(${LIB_NAME} PUBLIC ${VB01_DIR})

