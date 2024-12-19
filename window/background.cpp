#include "background.h"
#include "qssmanager.h"

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

    setColor("#604962", "#0C1824", "#FFF3FF", "#D8EAFF");
}

void Background::setColor(QString topLeftDark, QString bottomRightDark, QString topLeftLight, QString bottomRightLight)
{
    m_topLeftDark = topLeftDark;
    m_bottomRightDark = bottomRightDark;
    m_topLeftLight = topLeftLight;
    m_bottomRightLight = bottomRightLight;

    QString darkQSS = m_qssTemplate.arg(m_topLeftDark).arg(m_bottomRightDark);
    QString lightQSS = m_qssTemplate.arg(m_topLeftLight).arg(m_bottomRightLight);
    m_qssManager->input(this, darkQSS, lightQSS);
}
