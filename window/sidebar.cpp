#include "sidebar.h"
#include "publiccache.h"
#include "themebutton.h"

#include <QPropertyAnimation>
#include <QFile>
#include <QPainter>

Sidebar::Sidebar(QWidget *parent)
    : QWidget(parent)
{
    setbtnNameList({"home", "game", "skin"}); // 按钮名称
    setbtnDescList({"主页", "游戏", "主题"}); // 按钮描述
    resize(50, 50 * m_btnNameList.size()); // 根据按钮数量设置大小

    // 侧边栏折叠动画
    m_foldAnimation = new QPropertyAnimation(this, "geometry");
    m_foldAnimation->setDuration(300);

    // 点击动画
    m_clickAnimation = new QPropertyAnimation(this, "m_currBackPos");
    m_clickAnimation->setDuration(500);
    connect(m_clickAnimation, &QPropertyAnimation::valueChanged, this, [&]{ update(); });

    // 侧边栏按钮
    for (int i = 0; i < m_btnNameList.size(); i++)
    {
        // 按钮
        ThemeButton *btn = new ThemeButton(this, m_btnNameList[i]);
        btn->move(0, 50 * i);
        connect(btn, &QPushButton::clicked, this, [i, this]{this->onBtnClicked(i);});
    }
}

void Sidebar::onBtnClicked(int index)
{
    emit btnClicked(index);
    // 点击动画移动背景
    m_clickAnimation->setStartValue(m_currBackPos);
    m_clickAnimation->setEndValue(index * 50);
    m_clickAnimation->start();
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

void Sidebar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    // 绘制背景
    painter.setPen(Qt::NoPen); // 无边框
    painter.setBrush(QColor("#80808080")); // 背景色
    painter.drawRoundedRect(0, m_currBackPos, width(), 50, 10, 10); // 圆角矩形
    // 绘制文字
    // 字体
    QFont font("Microsoft YaHei", 16, QFont::Bold);
    painter.setFont(font);
    // 文字颜色
    PublicCache* cache = PublicCache::instance();
    if (cache->get("theme") == "dark") painter.setPen(Qt::white);
    else painter.setPen(Qt::black);
    for (int i = 0; i < m_btnDescList.size(); i++) // 绘制
    {
        painter.drawText(50, 50 * i, 100, 50, Qt::AlignCenter, m_btnDescList[i]);
    }
    
    QWidget::paintEvent(event);
}
