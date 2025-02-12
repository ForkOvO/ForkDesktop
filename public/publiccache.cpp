#include "publiccache.h"

#include <QCoreApplication>
#include <QFile>

std::atomic<PublicCache*> PublicCache::m_instance = nullptr;
std::mutex PublicCache::m_mutex;

PublicCache *PublicCache::instance()
{
    PublicCache* instance = m_instance.load(); // 获取单例
    if (!instance) // 如果单例不存在，则创建单例
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        instance = m_instance.load(); // 再次获取单例
        if (!instance) // 双重检查，确保单例不存在
        {
            instance = new PublicCache();
            m_instance.store(instance); // 存储单例
        }
    }
    return instance;
}

void PublicCache::set(QString key, QJsonValue value)
{
    // 修改缓存并保存
    m_cache[key] = value;
    QJsonDocument jsonDoc;
    jsonDoc.setObject(m_cache);
    QFile cacheFile(m_cachePath);
    if (!cacheFile.open(QFile::WriteOnly))
    {
        STD_DEBUG(PublicCache.cpp) << "Failed to open cache file";
        return;
    }
    QTextStream wirteStream(&cacheFile);
    wirteStream.setEncoding(QStringConverter::Utf8);
    wirteStream << jsonDoc.toJson();
    cacheFile.close();

    if (key == "theme") updateAllWidgets(); // 如果修改了主题，更新所有控件
}

QJsonValue PublicCache::get(QString key)
{
    return m_cache[key];
}

void PublicCache::addWidget(QWidget *widget)
{
    m_widgets.append(widget);
}

void PublicCache::removeWidget(QWidget *widget)
{
    m_widgets.removeAll(widget);
}

void PublicCache::updateAllWidgets()
{
    STD_DEBUG(PublicCache.cpp) << "Update all widgets";
    for (QWidget* widget : m_widgets)
    {
        widget->update();
    }
}

PublicCache::PublicCache()
{
    setcachePath(QCoreApplication::applicationDirPath() + "/cache.json"); // 设置缓存文件路径

    // 检查缓存文件是否存在
    QFile file(m_cachePath);
    if (!file.exists())
    {
        file.open(QFile::WriteOnly);
        file.close();
    }

    // 加载缓存文件
    QFile cacheFile(m_cachePath);
    if (!cacheFile.open(QFile::ReadOnly))
    {
        STD_DEBUG(PublicCache.cpp) << "Failed to open cache file";
        return;
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(cacheFile.readAll());
    cacheFile.close();
    m_cache = jsonDoc.object();
}
