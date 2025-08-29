aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})
# 告诉链接器 MySQL 库所在目录
link_directories(/usr/lib64/mysql)
target_link_libraries(ChatServer 
    muduo_net   # muduo网络库
    muduo_base  # muduo基础库
    mysqlclient
    hiredis
    pthread        # 线程库（muduo依赖）
)  