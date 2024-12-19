#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H

// 单例模式 缓存管理器

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <mutex>

class CacheManager : public QObject
{
    Q_OBJECT
public:
    // 单例模式 禁止拷贝构造和赋值操作
    CacheManager(const CacheManager&) = delete;
    CacheManager& operator=(const CacheManager&) = delete;

    static CacheManager* instance(); // 获取单例实例

    void loadCache(QString filename); // 加载缓存文件
    void changeCache(QString filename, QString key, QJsonValue value); // 修改缓存
    QJsonValue getCache(QString filename, QString key); // 获取缓存数据

private:
    void checkCacheExists(QString filePath); // 检查缓存文件是否存在

private:
    explicit CacheManager() = default;
    static std::atomic<CacheManager*> m_instance; // 单例实例指针
    static std::mutex m_mutex; // 保证线程安全
    static QString m_cacheDirPath; // 缓存文件夹路径

    QMap<QString, QJsonObject> m_cacheMap; // 缓存数据
};

#endif // CACHEMANAGER_H
