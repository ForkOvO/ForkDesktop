#include "notification.h"
#include "centralwidget.h"

#include <QFile>
#include <QGuiApplication>
#include <QScreen>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>

Notification::Notification(QString theme, QWidget *parent)
    : QWidget(parent)
{
    qDebug() << "notification.cpp" << __LINE__ << "通知窗口创建";

    if (parent) m_screenRect = parent->geometry(); // 获取父窗口大小
    else m_screenRect = QGuiApplication::primaryScreen()->availableGeometry(); // 获取屏幕大小

    setAttribute(Qt::WA_StyledBackground); // 启用qss
    setGeometry(m_screenRect.width() - 350, m_screenRect.height() - 150, 300, 100); // 设置窗口位置和大小

    // 标题
    m_title = new QLabel();
    m_title->setObjectName("title");

    // 关闭按钮
    m_closeBtn = new QPushButton("X");
    m_closeBtn->setObjectName("closeBtn");
    m_closeBtn->setFixedSize(20, 20);
    connect(m_closeBtn, &QPushButton::clicked, this, &Notification::deleteLater);

    // 内容
    m_content = new QTextEdit();
    m_content->setObjectName("content");
    m_content->setReadOnly(true);

    // 布局
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->addWidget(m_title);
    titleLayout->addWidget(m_closeBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(m_content);

    // 加载qss
    QFile file(":/qss/notification.qss");
    file.open(QFile::ReadOnly);
    QString qss = file.readAll();
    file.close();

    if (theme == "dark") // 深色模式
    {
        qss.replace("{{back_color}}", "#202020");
        qss.replace("{{content_color}}", "#808080");
    }
    else // 浅色模式
    {
        qss.replace("{{back_color}}", "#EFEFEF");
        qss.replace("{{content_color}}", "#202020");
    }
    setStyleSheet(qss);
}

Notification::~Notification()
{
    qDebug() << "notification.cpp" << __LINE__ << "通知窗口关闭";

    m_destroyTimer->stop();
    m_destroyTimer->deleteLater();
}

void Notification::showNotification(QString title, QString content, int ms, QWidget *parent, QString theme)
{
    if (title == "") title = "Fork桌面"; // 默认标题
    Notification *notification = new Notification(theme, parent);
    notification->setText(title, content);
    notification->show();
    if (ms <= 0) return;
    notification->startDestroyTimer(ms);
}

void Notification::setText(QString title, QString content)
{
    m_title->setText(title);
    m_content->setText(content);
}

void Notification::startDestroyTimer(int ms)
{
    // 销毁定时器
    m_destroyTimer = new QTimer(this);
    connect(m_destroyTimer, &QTimer::timeout, this, &Notification::deleteLater);
    m_destroyTimer->start(ms);
}
