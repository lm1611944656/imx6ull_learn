# 设置最低要求的CMake版本
cmake_minimum_required(VERSION 3.12)

# 定义项目名称和版本号
project(3_1_led_SDK VERSION 1.0.0 LANGUAGES C CXX ASM DESCRIPTION "imx6ull SDK package management project")

# 增加头文件
include_directories(
        ${PROJECT_SOURCE_DIR}/driver/beep
        ${PROJECT_SOURCE_DIR}/driver/clk
        ${PROJECT_SOURCE_DIR}/driver/delay
        ${PROJECT_SOURCE_DIR}/driver/key
        ${PROJECT_SOURCE_DIR}/driver/led
        ${PROJECT_SOURCE_DIR}/driver/utils
        ${PROJECT_SOURCE_DIR}/imx6ull
        ${PROJECT_SOURCE_DIR}/project

)

# 增加源文件
file(GLOB_RECURSE START_SOURCES
        "${PROJECT_SOURCE_DIR}/startup/*.*"
        "${PROJECT_SOURCE_DIR}/project/*.*"
        "${PROJECT_SOURCE_DIR}/driver/led/*.*"
        "${PROJECT_SOURCE_DIR}/driver/clk/*.*"
        "${PROJECT_SOURCE_DIR}/driver/delay/*.*"
)

# 生成可执行文件
add_executable(${PROJECT_NAME}.elf ${START_SOURCES}
        driver/led/bsp_led.h
        driver/led/bsp_led.c
        driver/delay/bsp_delay.h
        driver/delay/bsp_delay.c
        project/main.h
)



