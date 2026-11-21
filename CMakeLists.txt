set(CMAKE_LINK_DEPENDS_USE_LINKER FALSE)
project(titd)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_COMPILER "/home/portia_labiata/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-gcc")
set(CMAKE_CXX_COMPILER "/home/portia_labiata/luckfox-pico/tools/linux/toolchain/arm-rockchip830-linux-uclibcgnueabihf/bin/arm-rockchip830-linux-uclibcgnueabihf-g++")

set(OpenCV_DIR "/home/portia_labiata/opencv-mobile-4.10.0-luckfox-pico/lib/cmake/opencv4")
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(titd main.cpp tit.cpp)
target_link_libraries(titd ${OpenCV_LIBS})

add_custom_target(flash
    COMMAND adb push ${CMAKE_CURRENT_BINARY_DIR}/titd /opt
)
