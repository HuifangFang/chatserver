#include"chatserver.hpp"
#include"json.hpp"
#include"chatservice.hpp"
#include<functional>
using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(
    EventLoop* loop, //�¼�ѭ��
    const InetAddress& listenAddr, //IP+Port
    const string& nameArg   //������������
) :_server(loop, listenAddr, nameArg), _loop(loop)
{
    //��������ע���û����ӵĴ����ͶϿ��ص�
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    //��������ע���û���д�¼��ص�
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));
    //���÷������˿ڵ��߳����� 1��I/O�̣߳�����work�߳�
    _server.setThreadNum(4);
}
//�����¼�ѭ��
void ChatServer::start()
{
    _server.start();
}

//�ϱ����������Ϣ�Ļص�����
void ChatServer::onConnection(const TcpConnectionPtr& conn) {
    //�ͻ��˶Ͽ�����
    if (!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}
//ר�Ŵ����û��Ķ�д�¼�
void ChatServer::onMessage(const TcpConnectionPtr& conn,
    Buffer* buffer,
    Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //���ݵķ����л�
    json js = json::parse(buf);
    //�ﵽĿ�ģ���ȫ��������ģ��Ĵ����ҵ��ģ��Ĵ���
    //ͨ��js["msgid"]��ȡ=��ҵ��handler=��conn js time
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
   //�ص���Ϣ�󶨺õ��¼�����������ִ����Ӧ��ҵ����
    msgHandler(conn, js, time);

}