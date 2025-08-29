#include "friendmodel.hpp"
#include "db.h"
//��Ӻ��ѹ�ϵ
void FriendModel::insert(int userid, int friendid)
{
    // 1.��װsql���
    char sql[1024] = { 0 };
    sprintf(sql, "insert into friend values(%d, %d)", userid, friendid);

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// �����û������б�
vector<User> FriendModel::query(int userid)
{
    // 1. ��װsql���
    // ����sql��仺��������ʼ��Ϊ��
    char sql[1024] = { 0 };

    // ������ѯsql��ͨ�������Ӳ�ѯ�û������к�����Ϣ
    // ����user������a����friend������b���������Ǻ��ѹ�ϵ���е�friendid�����û����id
    // ��ѯ����Ϊ���ѹ�ϵ���е�userid���ڴ����userid����ǰ��ѯ�û���
    // ��ѯ���Ϊ���ѵ�id��name��state�ֶ�
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid = a.id where b.userid=%d", userid);

    // ����洢������Ϣ������
    vector<User> vec;
    // ����MySQL���ݿ��������
    MySQL mysql;
    // �����������ݿ�
    if (mysql.connect())
    {
        // ִ��sql��ѯ����ȡ�����
        MYSQL_RES* res = mysql.query(sql);
        // ��������Ƿ���Ч
        if (res != nullptr)
        {
            // ���ж�ȡ������е�����
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                // ����User����洢��ǰ������Ϣ
                User user;
                // �ӽ�����л�ȡid����0�У���ת��Ϊ���������õ�User����
                user.setId(atoi(row[0]));
                // �ӽ�����л�ȡname����1�У������õ�User����
                user.setName(row[1]);
                // �ӽ�����л�ȡstate����2�У������õ�User����
                user.setState(row[2]);
                // ����ǰ������Ϣ��ӵ�������
                vec.push_back(user);
            }
            // �ͷŽ������Դ�������ڴ�й©
            mysql_free_result(res);
            // ���ز�ѯ���ĺ����б�
            return vec;
        }
    }
    // �����ݿ�����ʧ�ܻ��ѯ�޽�������ؿ�����
    return vec;
}