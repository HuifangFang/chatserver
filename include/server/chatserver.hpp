#ifndef CHATSERVER_H
#define CHATSERVER_H

#include<muduo/net/TcpServer.h>
#include<muduo/net/EventLoop.h>
using namespace std;
using namespace muduo;
using namespace muduo::net;

class ChatServer
{
public:
    //初始化聊天服务器对象
    ChatServer(
        EventLoop* loop, //事件循环
        const InetAddress& listenAddr, //IP+Port
        const string& nameArg   //服务器的名字
    );
    //启动服务
    void start();
private:
    //上报链接相关信息的回调函数
    void onConnection(const TcpConnectionPtr&);
    void onMessage(const TcpConnectionPtr&,
        Buffer*,
        Timestamp);

    TcpServer _server; //#1
    EventLoop* _loop;
};


#endif // !CHATSERVER_H
