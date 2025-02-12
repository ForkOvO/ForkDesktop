#ifndef PUBLICCACHE_H
#define PUBLICCACHE_H

// 单例模式 公共缓存

#include "stdinit.h"
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <mutex>
#include <QWidget>

class PublicCache : public QObject
{
    Q_OBJECT
    STD_PROPERTY(QString, cachePath) // 缓存文件路径
public:
    // 单例模式 禁止拷贝构造和赋值操作
    PublicCache(const PublicCache&) = delete;
    PublicCache& operator=(const PublicCache&) = delete;

    static PublicCache* instance(); // 获取单例实例

    void set(QString key, QJsonValue value); // 修改缓存
    QJsonValue get(QString key); // 获取缓存数据

    void addWidget(QWidget *widget); // 添加需要更新的控件
    void removeWidget(QWidget *widget); // 移除需要更新的控件
    void updateAllWidgets(); // 更新所有控件

private:
    explicit PublicCache();
    static std::atomic<PublicCache*> m_instance; // 单例实例指针
    static std::mutex m_mutex; // 保证线程安全

    QJsonObject m_cache; // 缓存数据
    QList<QWidget*> m_widgets; // 需要更新的控件
};

#endif // PUBLICCACHE_H
