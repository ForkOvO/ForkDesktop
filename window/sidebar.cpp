#include "sidebar.h"

#include <QPropertyAnimation>
#include <QPushButton>
#include <QLabel>

Sidebar::Sidebar(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground); // 启用qss

    QStringList btnList = {"home", "skin"};
    QStringList btnNameList = {"主页", "主题"};

    resize(50, 50 * btnList.size());

    // 侧边栏折叠动画
    m_foldAnimation = new QPropertyAnimation(this, "geometry");
    m_foldAnimation->setDuration(300);

    // 侧边栏按钮
    for (int i = 0; i < btnList.size(); i++)
    {
        // 按钮
        QPushButton *btn = new QPushButton(btnList[i], this);
        btn->setObjectName(btnList[i]);
        btn->setGeometry(0, 50 * i, 50, 50);
        connect(btn, &QPushButton::clicked, this, [i, this](){btnClicked(i);});
        // 标签
        QLabel *label = new QLabel(btnNameList[i], this);
        label->setAlignment(Qt::AlignCenter);
        label->setGeometry(50, 50 * i, 100, 50);
    }
}

void Sidebar::enterEvent(QEnterEvent *event)
{
    // 鼠标进入时，展开侧边栏
    QRect rect = geometry();
    m_foldAnimation->setStartValue(rect);
    rect.setWidth(150);
    m_foldAnimation->setEndValue(rect);
    m_foldAnimation->start();
}

void Sidebar::leaveEvent(QEvent *event)
{
    // 鼠标离开时，收缩侧边栏
    QRect rect = geometry();
    m_foldAnimation->setStartValue(rect);
    rect.setWidth(50);
    m_foldAnimation->setEndValue(rect);
    m_foldAnimation->start();
}
