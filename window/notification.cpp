#include "notification.h"
#include "centralwidget.h"
#include "publiccache.h"

#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QPainter>

Notification::Notification(QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "notification.cpp" << __LINE__ << "通知窗口创建";

    setscreenRect(parent->geometry()); // 获取父窗口大小
    setGeometry(m_screenRect.width() - 350, m_screenRect.height() - 150, 300, 100); // 设置窗口位置和大小

    update();
}

Notification::~Notification()
{
    qDebug() << "notification.cpp" << __LINE__ << "通知窗口关闭";

    m_destroyTimer->stop();
    m_destroyTimer->deleteLater();
}

void Notification::showNotification(QWidget *parent, QString content, int ms)
{
    Notification *notification = new Notification(parent);
    notification->setcontent(content);
    notification->show();
    if (ms <= 0) return;
    notification->startDestroyTimer(ms);
}

void Notification::startDestroyTimer(int ms)
{
    // 销毁定时器
    m_destroyTimer = new QTimer(this);
    connect(m_destroyTimer, &QTimer::timeout, this, &Notification::deleteLater);
    m_destroyTimer->start(ms);
}

void Notification::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    // 字体
    QFont font("Microsoft YaHei", 15);
    painter.setFont(font);
    // 画笔
    QPen pen;
    pen.setWidth(1);
    PublicCache* cache = PublicCache::instance();
    if (cache->get("theme").toString() == "dark")
    {
        pen.setColor(QColor("#808080"));
        painter.setPen(pen);
        painter.setBrush(QColor("#202020"));
    }
    else
    {
        pen.setColor(QColor("#202020"));
        painter.setPen(pen);
        painter.setBrush(QColor("#EFEFEF"));
    }
    painter.drawRoundedRect(rect(), 5, 5); // 圆角矩形
    painter.drawText(rect(), Qt::AlignCenter, m_content); // 文字
    QWidget::paintEvent(event);
}

void Notification::mousePressEvent(QMouseEvent *event)
{
    m_destroyTimer->stop();
    deleteLater();
}
