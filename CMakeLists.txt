# 指定cmake的最低版本
cmake_minimum_required(VERSION 3.28.3)

# 设置项目名称，参数可以随意指定
project(week_plan)

# 搜索 src 目录下所有的源文件，并将结果列表存储在变量 SRC_DIR 中
aux_source_directory(src SRC_DIR)
aux_source_directory(function_src FUNC_DIR)
aux_source_directory(test_main MAIN_DIR)

# 指定使用源文件${SRC_DIR} ${MAIN_DIR}，生成可执行程序 app , ${变量名} 是取变量的值
add_executable(app ${FUNC_DIR} ${SRC_DIR} ${MAIN_DIR})

# 设置包含的头文件目录
include_directories(inc function_inc)