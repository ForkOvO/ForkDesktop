#include "foldwindow.h"
#include "centralwidget.h"

#include <QScreen>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QMouseEvent>

FoldWindow::FoldWindow(QWidget *parent)
    : QWidget(parent)
{
    // 折叠展开数据
    setfullRect(QGuiApplication::primaryScreen()->availableGeometry()); // 全屏不包含任务栏
    setfoldRect(QRect(m_fullRect.width() - 50, m_fullRect.height() / 2 - 25, 50, 50)); // 右方居中
    m_foldAnimation = new QPropertyAnimation(this, "geometry"); // 折叠动画
    m_foldAnimation->setDuration(300);

    // 设置窗口属性
    setWindowTitle("Fork桌面 - 十_OvO脱发开发中"); // 设置窗口标题
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint); // 无边框 | 窗口置底
    setAttribute(Qt::WA_TranslucentBackground); // 透明
    setGeometry(m_fullRect); // 初始窗口大小

    // 主窗口
    m_centralWidget = new CentralWidget(this);
    m_centralWidget->setGeometry(m_fullRect);
}

void FoldWindow::changeFoldStatus()
{
    setisFold(!m_isFold); // 切换折叠状态
    m_foldAnimation->setStartValue(this->geometry());
    m_foldAnimation->setEndValue(m_isFold ? m_foldRect : m_fullRect);
    m_foldAnimation->start(); // 开始动画
}

void FoldWindow::mousePressEvent(QMouseEvent *event)
{
    if (m_isFold && (event->buttons() & Qt::RightButton)) // 折叠状态右键开始移动
    {
        setstartPos(event->globalPosition().toPoint() - frameGeometry().topLeft());
    }
}

void FoldWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isFold && (event->buttons() & Qt::RightButton)) // 移动窗口并存储位置
    {
        move(event->globalPosition().toPoint() - m_startPos);
        setfoldRect(geometry());
    }
}
