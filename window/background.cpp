#include "background.h"
#include "qssmanager.h"
#include "cachemanager.h"

#include <QFile>
#include <QGuiApplication>
#include <QScreen>

Background::Background(QWidget *parent)
    : QWidget(parent)
{
    // qss管理
    m_qssManager = QSSManager::instance();

    setAttribute(Qt::WA_StyledBackground); // 启用qss
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry());
    
    // 加载qss
    QFile file(":/qss/background.qss");
    file.open(QFile::ReadOnly);
    m_qssTemplate = file.readAll();
    file.close();

    // 加载缓存
    CacheManager* cacheManager = CacheManager::instance();
    cacheManager->loadCache("theme.json");
    QJsonValue colors = cacheManager->getCache("theme.json", "backColor");
    if (colors.isNull()) // 默认主题
    {
        setColor("#604962", "#0C1824", "#FFF3FF", "#D8EAFF");
    }
    else // 加载缓存主题
    {
        QJsonObject obj = colors.toObject();
        setColor(obj["leftDark"].toString(), obj["rightDark"].toString(), obj["leftLight"].toString(), obj["rightLight"].toString());
    }
}

void Background::setColor(QString leftDark, QString rightDark, QString leftLight, QString rightLight)
{
    m_leftDark = leftDark;
    m_rightDark = rightDark;
    m_leftLight = leftLight;
    m_rightLight = rightLight;

    // 更新qss
    QString darkQSS = m_qssTemplate.arg(m_leftDark).arg(m_rightDark);
    QString lightQSS = m_qssTemplate.arg(m_leftLight).arg(m_rightLight);
    m_qssManager->input(this, darkQSS, lightQSS);

    // 更新缓存
    QJsonObject obj;
    obj.insert("leftDark", m_leftDark);
    obj.insert("rightDark", m_rightDark);
    obj.insert("leftLight", m_leftLight);
    obj.insert("rightLight", m_rightLight);
    CacheManager* cacheManager = CacheManager::instance();
    cacheManager->loadCache("theme.json");
    cacheManager->changeCache("theme.json", "backColor", obj);
}
