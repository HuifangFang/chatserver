# ChatServer

## 项目简介
ChatServer 是一个基于 **C++ Muduo 库** 实现的分布式聊天室项目，支持 **服务器集群** 与 **Redis 发布/订阅消息队列**，可以在 **NGINX TCP 负载均衡** 环境下运行。  
该项目旨在提升高并发网络服务的开发能力，同时积累后端实战经验。

## 功能特性
- 支持多客户端同时在线聊天
- 使用 **Redis 发布/订阅** 实现服务器间消息广播，降低耦合度，节省带宽
- **MySQL 数据库**持久化存储用户数据和聊天记录
- 集群部署，支持 **水平扩展**
- 基于 Muduo 库的高性能网络模型，实现 **异步 I/O**
- 提供简单的客户端和服务器端程序，易于测试和扩展

## 技术栈
- **语言**：C++17
- **网络库**：Muduo
- **数据库**：MySQL
- **缓存/消息队列**：Redis
- **构建工具**：CMake
- **操作系统**：Linux

## 项目结构
```

chatserver/
├── build/          # 编译输出目录
├── src/            # 源代码
├── include/        # 头文件
├── CMakeLists.txt  # CMake 构建文件
└── README.md       # 项目说明

````

## 编译与运行
1. 克隆仓库：
```bash
git clone https://github.com/HuifangFang/chatserver.git
cd chatserver
````

2. 编译项目：

```bash
mkdir build && cd build
cmake ..
make
```

3. 配置数据库与 Redis：

* 修改配置文件，填入 MySQL 和 Redis 信息
* 启动 MySQL 和 Redis 服务

4. 运行服务器：

```bash
./chatserver
```

5. 运行客户端：

```bash
./chatclient
```

## 项目亮点

* 支持 **跨服务器通信**，适用于大规模集群
* 异步网络模型，高并发处理能力强
* Redis 发布/订阅降低服务器耦合，提高扩展性
* MySQL 持久化存储，保证数据可靠性


