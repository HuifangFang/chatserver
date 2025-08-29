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
    //��ʼ���������������
    ChatServer(
        EventLoop* loop, //�¼�ѭ��
        const InetAddress& listenAddr, //IP+Port
        const string& nameArg   //������������
    );
    //��������
    void start();
private:
    //�ϱ����������Ϣ�Ļص�����
    void onConnection(const TcpConnectionPtr&);
    void onMessage(const TcpConnectionPtr&,
        Buffer*,
        Timestamp);

    TcpServer _server; //#1
    EventLoop* _loop;
};


#endif // !CHATSERVER_H
