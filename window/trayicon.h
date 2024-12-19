#ifndef TRAYICON_H
#define TRAYICON_H

// 系统托盘图标

#include <QSystemTrayIcon>

class QMenu;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit TrayIcon(QWidget *parent);

private:
    QMenu* m_menu; // 菜单
};

#endif // TRAYICON_H
