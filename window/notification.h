#ifndef NOTIFICATION_H
#define NOTIFICATION_H

// 通知窗口

#include <QWidget>

class QSSManager;
class QLabel;
class QPushButton;
class QTextEdit;

class Notification : public QWidget
{
    Q_OBJECT
public:
    Notification(QString theme = "dark", QWidget *parent = nullptr);
    ~Notification();

    // 显示通知 (默认暗色 3秒后自动销毁)
    static void showNotification(QString title = "", QString content = "", int ms = 3000, QWidget *parent = nullptr, QString theme = "dark");

    void setText(QString title = "", QString content = ""); // 设置标题和内容
    void startDestroyTimer(int ms = 3000); // 启动销毁定时器

private:
    QRect m_screenRect; // 屏幕大小
    
    QLabel* m_title; // 标题
    QTextEdit* m_content; // 内容
    QPushButton* m_closeBtn; // 关闭按钮
    QTimer* m_destroyTimer; // 销毁定时器
};

#endif // NOTIFICATION_H
