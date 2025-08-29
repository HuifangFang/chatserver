cmake_minimum_required(VERSION 3.10)
project(chat)

# 设置C++标准（muduo库需要C++11及以上）
set(CMAKE_CXX_STANDARD 11)          # 指定C++17标准
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制要求符合标准，否则报错
set(CMAKE_CXX_EXTENSIONS OFF)       # 禁用编译器扩展（如gnu++17）

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 查找muduo库（全局查找，供子项目使用）
find_library(MUDUO_NET muduo_net)
find_library(MUDUO_BASE muduo_base)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#头文件搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server/db)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis)
include_directories(${PROJECT_SOURCE_DIR}/include/server/model)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
# 告诉链接器 MySQL 库所在目录
link_directories(/usr/lib64/mysql)

# 添加子目录
add_subdirectory(src)