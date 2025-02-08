#ifndef NOTIFICATION_H
#define NOTIFICATION_H

// 通知窗口

#include <QWidget>
#include "stdinit.h"

class QSSManager;
class QLabel;
class QPushButton;
class QTextEdit;

class Notification : public QWidget
{
    Q_OBJECT
    STD_PROPERTY(QRect, screenRect) // 屏幕大小
public:
    Notification(QString theme = "dark", QWidget *parent = nullptr);
    ~Notification();

    // 显示通知 (默认暗色 3秒后自动销毁)
    static void showNotification(QString title = "Fork桌面", QString content = "", int ms = 3000, QWidget *parent = nullptr, QString theme = "dark");

    void setText(QString title = "", QString content = ""); // 设置标题和内容
    void startDestroyTimer(int ms = 3000); // 启动销毁定时器

private:
    QLabel* m_title = nullptr; // 标题
    QTextEdit* m_content = nullptr; // 内容
    QPushButton* m_closeBtn = nullptr; // 关闭按钮
    QTimer* m_destroyTimer = nullptr; // 销毁定时器
};

#endif // NOTIFICATION_H
