#include "cachemanager.h"

#include <QCoreApplication>
#include <QFile>
#include <QDir>

std::atomic<CacheManager*> CacheManager::m_instance = nullptr;
std::mutex CacheManager::m_mutex;

CacheManager *CacheManager::instance()
{
    CacheManager* instance = m_instance.load(); // 获取单例
    if (!instance) // 如果单例不存在，则创建单例
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        instance = m_instance.load(); // 再次获取单例
        if (!instance) // 双重检查，确保单例不存在
        {
            instance = new CacheManager();
            instance->m_cacheDirPath = QCoreApplication::applicationDirPath() + "/cache"; // 设置缓存文件夹路径
            m_instance.store(instance); // 存储单例
        }
    }
    return instance;
}

void CacheManager::loadCache(QString filename)
{
    QString filePath = m_cacheDirPath + "/" + filename; // 设置缓存文件路径
    checkCacheExists(filePath); // 检查缓存文件是否存在
    QFile cacheFile(filePath);  // 加载缓存文件
    if (!cacheFile.open(QFile::ReadOnly))
    {
        qDebug() << "cachemanager.cpp:" << __LINE__ << "Failed to open cache file: " << filename;
        return;
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(cacheFile.readAll());
    cacheFile.close();
    QJsonObject cacheJson = jsonDoc.object();
    m_cacheMap[filename] = cacheJson; // 保存缓存
}

void CacheManager::changeCache(QString filename, QString key, QJsonValue value)
{
    QJsonObject cacheJson = m_cacheMap[filename]; // 获取缓存
    cacheJson[key] = value; // 修改缓存

    QJsonDocument jsonDoc;
    jsonDoc.setObject(cacheJson);
    QFile cacheFile(m_cacheDirPath + "/" + filename);

    if (!cacheFile.open(QFile::WriteOnly))
    {
        qDebug() << "cachemanager.cpp:" << __LINE__ << "Failed to open cache file: " << filename;
        return;
    }

    QTextStream wirteStream(&cacheFile);
    wirteStream.setEncoding(QStringConverter::Utf8); // 设置编码 UTF8
    wirteStream << jsonDoc.toJson(); // 写入文件
    cacheFile.close();
}

QJsonValue CacheManager::getCache(QString filename, QString key)
{
    return m_cacheMap[filename][key]; // 返回缓存值
}

void CacheManager::checkCacheExists(QString filePath)
{
    QDir dir;
    if (!dir.exists(m_cacheDirPath)) // 如果缓存文件夹路径不存在则创建
        dir.mkpath(m_cacheDirPath);

    if (!QFile::exists(filePath)) // 如果缓存文件不存在则创建
    {
        QFile file(filePath);
        file.open(QFile::WriteOnly);
        file.write("{}"); // 写入空json
        file.close();
    }
}
