#include "sidebar.h"
#include "qssmanager.h"

#include <QPropertyAnimation>
#include <QPushButton>
#include <QLabel>
#include <QFile>

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

    // 背景
    m_background = new QWidget(this);
    m_background->setObjectName("sidebarBackground");
    m_background->setGeometry(0, 0, 50, 50);
    // 点击动画
    m_clickAnimation = new QPropertyAnimation(m_background, "geometry");
    m_clickAnimation->setDuration(500);

    // 侧边栏按钮
    for (int i = 0; i < btnList.size(); i++)
    {
        // 按钮
        QPushButton *btn = new QPushButton(this);
        btn->setObjectName(btnList[i] + "SidebarBtn");
        btn->setGeometry(0, 50 * i, 50, 50);
        connect(btn, &QPushButton::clicked, this, [i, this]{this->onBtnClicked(i);});
        // 标签
        QLabel *label = new QLabel(btnNameList[i], this);
        label->setObjectName(btnList[i] + "SidebarLabel");
        label->setAlignment(Qt::AlignVCenter);
        label->setGeometry(50, 50 * i, 100, 50);
    }

    // QSS模板
    m_qssManager = QSSManager::instance();
    QFile file(":/qss/sidebar.qss");
    file.open(QFile::ReadOnly);
    QString qssTemplate(file.readAll());
    file.close();
    // 应用QSS
    QString allQss;
    allQss += "QWidget#sidebarBackground{ background-color:#80808080; border-radius: 10px; }";
    for (QString name: btnList)
    {
        allQss += QString(qssTemplate).replace("{{name}}", name);
    }
    m_qssManager->input(this, QString(allQss).replace("{{theme}}", "white"), QString(allQss).replace("{{theme}}", "black"));
}

void Sidebar::onBtnClicked(int index)
{
    emit btnClicked(index);
    // 点击动画移动背景
    QRect rect = m_background->geometry();
    m_clickAnimation->setStartValue(rect);
    rect.moveTo(0, 50 * index);
    m_clickAnimation->setEndValue(rect);
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
