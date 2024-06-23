# 设置最低要求的CMake版本
cmake_minimum_required(VERSION 3.12)

# 定义项目名称和版本号
project(CMakeTemplate VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "A cmake template project")

##--------------------- 版本文件生成 ---------------------------------------##
# 通过配置文件生成版本文件
#[[
    这行代码会使用输入文件 src/c/cmake_template_version.h.in 中的内容，
    并根据配置信息替换其中的占位符，然后将生成的结果写入
    ${PROJECT_SOURCE_DIR}/src/c/cmake_template_version.h 文件中。
    configure_file 命令会将这些占位符替换为实际的值，并生成最终的头文件。
]]
configure_file(src/c/cmake_template_version.h.in "${PROJECT_SOURCE_DIR}/src/c/cmake_template_version.h")

# 指定语言标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

##---------------------编译选项配置------------------------------------##
# 配置编译选项
add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++11")

# 设置构建类型
# set(CMAKE_BUILD_TYPE Debug)  # Use `cmake -DCMAKE_BUILD_TYPE=Debug` more better
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Debug 变体的编译选项
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Release 变体的编译选项
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

message(STATUS "Compile options for c: ${CMAKE_C_FLAGS}")
message(STATUS "Compile options for c++: ${CMAKE_CXX_FLAGS}")

##---------------------全局宏定义--------------------------------------##
#[[
    这行代码会向编译器添加两个预定义宏：DEBUG 和 REAL_COOL_ENGINEER。
    这意味着在编译源代码时，这两个宏将被定义，
    你可以在你的源代码中使用条件编译来根据它们的定义情况执行不同的代码逻辑。

在源码中使用方式：例如 main.c中

    #ifdef DEBUG
        // 在调试模式下执行的代码
    #endif

    #ifdef REAL_COOL_ENGINEER
        // 如果定义了 REAL_COOL_ENGINEER 宏，则执行的代码
    #endif

]]
add_definitions(-DDEBUG -DREAL_COOL_ENGINEER)

##---------------------包含目录配置--------------------------------##
include_directories(src/c)

##--------------------- 源文件列表 ---------------------------------------##
#[[
    GLOB_RECURSE选项表示递归地获取文件列表，包括指定目录及其子目录中的文件。
    MATH_LIB_SRC是一个变量，它将保存获取到的所有匹配文件的列表。
    src/c/*.c表示获取src/c/目录及其子目录中所有以.c为扩展名的文件。
]]
file(GLOB_RECURSE MATH_LIB_SRC
    src/c/*.c
)

##---------------------构建目标 ---------------------------------------##
# 是否使用预编译库的选项
#[[
    USE_IMPORTED_LIB 是选项的名称，这里表示是否使用预编译库。
    "Use precompiled lib" 是选项的描述，用于在生成CMake配置时提供对该选项的简要说明。
    OFF 是默认值，表示默认情况下不使用预编译库。
    如果用户想启用这个选项，可以在命令行中使用 -D 选项进行设置，例如：-DUSE_IMPORTED_LIB=ON。
    如果用户不显式指定，则默认值为 OFF，即不使用预编译的库。
]]
option(USE_IMPORTED_LIB "Use pre compiled lib" OFF)

# 由于  USE_IMPORTED_LIB == OFF   所以不能进入if
if (USE_IMPORTED_LIB)
    # add_library(math STATIC IMPORTED)
    # set_property(TARGET math PROPERTY IMPORTED_LOCATION "./lib/libmath.a")
    find_library(LIB_MATH_DEBUG mathd HINTS "./lib")
    find_library(LIB_MATH_RELEASE math HINTS "./lib")
    add_library(math STATIC IMPORTED GLOBAL)
    set_target_properties(math PROPERTIES
        IMPORTED_LOCATION "${LIB_MATH_RELEASE}"
        IMPORTED_LOCATION_DEBUG "${LIB_MATH_DEBUG}"
        IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
    )

    add_subdirectory(src/c/nn)

else()
    # 告诉 CMake 进入 src/c/math 目录并执行那个目录下的 CMakeLists.txt 文件。
    add_subdirectory(src/c/math)
    # 告诉 CMake 进入src/c/nn目录并执行那个目录下的 CMakeLists.txt 文件。
    add_subdirectory(src/c/nn)
endif()

# 合并库文件
if (APPLE)
    # 对于苹果系统（macOS），使用libtool静态合并库
    set(MERGE_CMD libtool -static -o)

    # 定义一个自定义命令，将math和nn库合并为libmerge.a
    add_custom_command(OUTPUT libmerge.a
    COMMAND libtool -static -o libmerge.a $<TARGET_FILE:math> $<TARGET_FILE:nn>
    DEPENDS math nn)
else()
    # 对于非苹果系统，使用ar命令创建一个静态库
    # 定义一个自定义命令，将math和nn库合并为libmerge.a
    #[[
        add_custom_command(
        OUTPUT generated_file.txt
        COMMAND echo "Hello, World!" > generated_file.txt
        COMMENT "Generating custom file"
        )
        在这个例子中，add_custom_command 将生成一个名为 generated_file.txt 的文件，
        其中包含文本 "Hello, World!"。
        这个命令将在构建时执行。
    ]]
    add_custom_command(OUTPUT libmerge.a
    COMMAND ar crsT libmerge.a $<TARGET_FILE:math> $<TARGET_FILE:nn>
    DEPENDS math nn)
endif()

add_custom_target(_merge ALL DEPENDS libmerge.a)
add_library(merge STATIC IMPORTED GLOBAL)
set_target_properties(merge PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libmerge.a
)

# 构建 demo 可执行文件
add_executable(demo src/c/main.c)
target_link_libraries(demo PRIVATE merge)

##--------------------- 构建单元测试 -----------------------------------##
option(CMAKE_TEMPLATE_ENABLE_TEST "Whether to enable unit tests" ON)
if (CMAKE_TEMPLATE_ENABLE_TEST)
    message(STATUS "Unit tests enabled")
    enable_testing()
    add_subdirectory(third_party/googletest-release-1.10.0 EXCLUDE_FROM_ALL)
    include_directories(third_party/googletest-release-1.10.0/googletest/include)

    add_executable(test_add test/c/test_add.cc)
    add_executable(test_minus test/c/test_minus.cc)
    add_executable(test_gtest_demo test/c/test_gtest_demo.cc)
    target_link_libraries(test_add math gtest gtest_main)
    target_link_libraries(test_minus math gtest gtest_main)
    target_link_libraries(test_gtest_demo math gtest gtest_main)

    add_test(NAME test_add COMMAND test_add)
    add_test(NAME test_minus COMMAND test_minus)
    add_test(NAME test_gtest_demo COMMAND test_gtest_demo)
endif()

##--------------------- 安装和打包目标 -------------------------##
# Install
if (NOT USE_IMPORTED_LIB)
    install(TARGETS math nn demo
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            PUBLIC_HEADER DESTINATION include)
    file(GLOB_RECURSE MATH_LIB_HEADERS src/c/math/*.h)
    install(FILES ${MATH_LIB_HEADERS} DESTINATION include/math)
endif()

# 打包，这些变量在包含 CPack 模块之前应设置
set(CPACK_GENERATOR "ZIP")
set(CPACK_SET_DESTDIR ON)  # 支持指定安装目录
set(CPACK_INSTALL_PREFIX "RealCoolEngineer")
include(CPack)
