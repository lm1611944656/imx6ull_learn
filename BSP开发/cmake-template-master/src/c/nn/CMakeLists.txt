# 设置最低要求的CMake版本
cmake_minimum_required(VERSION 3.12)

# 收集当前目录下的所有源文件
aux_source_directory(. NN_SRC)

# 在控制台输出源文件列表的消息
message("NN_SRC: ${NN_SRC}")

# 使用收集到的源文件创建一个名为 'nn' 的静态库
add_library(nn STATIC ${NN_SRC})
