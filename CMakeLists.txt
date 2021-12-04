cmake_minimum_required(VERSION 3.2)
project(vb01Gui)

cmake_policy(SET CMP0015 NEW)
set(CMAKE_BUILD_TYPE Debug)

include_directories(external/vb01)
include_directories(external/vb01/external/freetype/include)
include_directories(external/vb01/external/glfw/include/GLFW)
link_directories(build/vb01/build)

set(core button.cpp listbox.cpp textbox.cpp checkbox.cpp slider.cpp)

add_library(vb01Gui ${core})
target_link_libraries(vb01Gui vb01)
