#include "background.h"
#include "publiccache.h"

#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QGradient>

Background::Background(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry()); // 设置背景大小
    
    PublicCache *cache = PublicCache::instance();
    cache->addWidget(this);
    QJsonObject backColor = cache->get("backColor").toObject();
    if (!backColor.isEmpty())
    {
        setleftDark(backColor.value("leftDark").toString());
        setrightDark(backColor.value("rightDark").toString());
        setleftLight(backColor.value("leftLight").toString());
        setrightLight(backColor.value("rightLight").toString());
    }
    
    update();
}

Background::~Background()
{
    PublicCache *cache = PublicCache::instance();
    cache->removeWidget(this);
}

void Background::setColor(QString leftDark, QString rightDark, QString leftLight, QString rightLight)
{
    setleftDark(leftDark);
    setrightDark(rightDark);
    setleftLight(leftLight);
    setrightLight(rightLight);
    update();
}

void Background::paintEvent(QPaintEvent *event)
{
    QLinearGradient gradient(0, height(), width(), 0); // 从左下角到右上角
    PublicCache *cache = PublicCache::instance();
    if (cache->get("theme").toString() == "dark")
    {
        gradient.setColorAt(0, QColor(m_leftDark));
        gradient.setColorAt(1, QColor(m_rightDark));
    }
    else
    {
        gradient.setColorAt(0, QColor(m_leftLight));
        gradient.setColorAt(1, QColor(m_rightLight));
    }
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);
    painter.drawRect(rect());
    QWidget::paintEvent(event);
}
