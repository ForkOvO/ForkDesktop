#include "qssmanager.h"
#include "cachemanager.h"

#include <QWidget>

std::atomic<QSSManager*> QSSManager::m_instance = nullptr;
std::mutex QSSManager::m_mutex;
CacheManager* QSSManager::m_cacheManager = nullptr;
bool QSSManager::m_isDark = true;

QSSManager *QSSManager::instance()
{
    QSSManager* instance = m_instance.load(); // 获取单例
    if (!instance) // 如果单例不存在，则创建单例
    {
        std::lock_guard<std::mutex> lock(m_mutex); // 加锁
        instance = m_instance.load(); // 再次获取单例
        if (!instance) // 双重检查，确保单例不存在
        {
            instance = new QSSManager;
            m_instance.store(instance); // 存储单例
            m_cacheManager = CacheManager::instance(); // 创建缓存管理器
            m_cacheManager->loadCache("theme.json");
            if (m_cacheManager->getCache("theme.json", "theme") != "dark")
            {
                m_isDark = false;
            }
        }
    }
    return instance;
}

void QSSManager::input(QWidget *widget, QString dark, QString light)
{
    m_qssData[widget] = {dark, light};
    updateWidget();
}

void QSSManager::updateWidget()
{
    for (auto it = m_qssData.begin(); it != m_qssData.end(); ++it)
    {
        if (m_isDark) it.key()->setStyleSheet(it.value().dark); // 暗色主题
        else it.key()->setStyleSheet(it.value().light); // 亮色主题
    }
}

void QSSManager::changeTheme()
{
    m_isDark = !m_isDark;
    m_cacheManager->changeCache("theme.json", "theme", m_isDark ? "dark" : "light");
    qDebug() << "qssmanager.cpp" << __LINE__ << "修改主题为:" << (m_isDark ? "暗色" : "亮色");
    updateWidget();
}

QString QSSManager::theme()
{
    if (m_isDark) return "dark";
    return "light";
}
