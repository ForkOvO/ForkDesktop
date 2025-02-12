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
    STD_PROPERTY_INIT(QString, content, "欢迎使用Fork桌面^_^") // 内容
public:
    Notification(QWidget *parent);
    ~Notification();

    // 显示通知 (默认暗色 3秒后自动销毁)
    static void showNotification(QWidget *parent, QString content = "欢迎使用Fork桌面^_^", int ms = 3000);

    void startDestroyTimer(int ms = 3000); // 启动销毁定时器

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QTimer* m_destroyTimer = nullptr; // 销毁定时器
};

#endif // NOTIFICATION_H
