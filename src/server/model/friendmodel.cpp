#include "friendmodel.hpp"
#include "db.h"
//添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    // 1.组装sql语句
    char sql[1024] = { 0 };
    sprintf(sql, "insert into friend values(%d, %d)", userid, friendid);

    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// 返回用户好友列表
vector<User> FriendModel::query(int userid)
{
    // 1. 组装sql语句
    // 定义sql语句缓冲区，初始化为空
    char sql[1024] = { 0 };

    // 构建查询sql：通过内连接查询用户的所有好友信息
    // 关联user表（别名a）和friend表（别名b），条件是好友关系表中的friendid等于用户表的id
    // 查询条件为好友关系表中的userid等于传入的userid（当前查询用户）
    // 查询结果为好友的id、name、state字段
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid = a.id where b.userid=%d", userid);

    // 定义存储好友信息的向量
    vector<User> vec;
    // 创建MySQL数据库操作对象
    MySQL mysql;
    // 尝试连接数据库
    if (mysql.connect())
    {
        // 执行sql查询，获取结果集
        MYSQL_RES* res = mysql.query(sql);
        // 检查结果集是否有效
        if (res != nullptr)
        {
            // 逐行读取结果集中的数据
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                // 创建User对象存储当前好友信息
                User user;
                // 从结果行中获取id（第0列），转换为整数后设置到User对象
                user.setId(atoi(row[0]));
                // 从结果行中获取name（第1列），设置到User对象
                user.setName(row[1]);
                // 从结果行中获取state（第2列），设置到User对象
                user.setState(row[2]);
                // 将当前好友信息添加到向量中
                vec.push_back(user);
            }
            // 释放结果集资源，避免内存泄漏
            mysql_free_result(res);
            // 返回查询到的好友列表
            return vec;
        }
    }
    // 若数据库连接失败或查询无结果，返回空向量
    return vec;
}