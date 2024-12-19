#ifndef FOLDWINDOW_H
#define FOLDWINDOW_H

// 折叠窗口

#include <QWidget>

// 自定义
class TrayIcon;
class CentralWidget;
// Qt
class QPropertyAnimation;

class FoldWindow : public QWidget
{
    Q_OBJECT
public:
    explicit FoldWindow(QWidget *parent = nullptr);

    void changeFoldStatus(); // 切换折叠状态

protected:
    // 右键移动折叠浮窗
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool m_isFold = false; // 是否折叠
    QRect m_foldRect; // 折叠窗口的位置和大小
    QRect m_fullRect; // 全屏窗口的位置和大小
    QPoint m_startPos; // 鼠标按下时的位置

    TrayIcon* m_trayIcon; // 系统托盘
    CentralWidget* m_centralWidget; // 主窗口
    QPropertyAnimation* m_foldAnimation; // 折叠窗口动画
};

#endif // FOLDWINDOW_H
