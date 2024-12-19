#include "trayicon.h"

#include <QMenu>
#include <QApplication>

TrayIcon::TrayIcon(QWidget *parent)
{
    // 显示
    QAction* showAction = new QAction("显示");
    connect(showAction, &QAction::triggered, parent, &QWidget::show);
    // 退出
    QAction* exitAction = new QAction("退出");
    connect(exitAction , &QAction::triggered, parent, &QApplication::exit);

    // 初始化菜单并添加项
    m_menu = new QMenu();
    m_menu->addAction(showAction);
    m_menu->addAction(exitAction );

    setIcon(QIcon(":/res/ten_OvO.png")); // 设置图标
    setContextMenu(m_menu); // 设置菜单

    // 双击托盘图标显示主窗口
    connect(this, &QSystemTrayIcon::activated, this, [&](QSystemTrayIcon::ActivationReason reason){
        if (reason == QSystemTrayIcon::DoubleClick) this->show();
    });

    show();
}