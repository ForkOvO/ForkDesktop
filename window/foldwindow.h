#ifndef FOLDWINDOW_H
#define FOLDWINDOW_H

// 折叠窗口

#include <QWidget>
#include "stdinit.h"

class CentralWidget;
class QPropertyAnimation;

class FoldWindow : public QWidget
{
    Q_OBJECT
    STD_PROPERTY_INIT(bool, isFold, false) // 是否折叠
    STD_PROPERTY(QRect, foldRect) // 折叠窗口的位置和大小
    STD_PROPERTY(QRect, fullRect) // 全屏窗口的位置和大小
    STD_PROPERTY(QPoint, startPos) // 鼠标按下时的位置
public:
    explicit FoldWindow(QWidget *parent = nullptr);

    void changeFoldStatus(); // 切换折叠状态

protected:
    // 右键移动折叠浮窗
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    CentralWidget* m_centralWidget = nullptr; // 主窗口
    QPropertyAnimation* m_foldAnimation = nullptr; // 折叠窗口动画
};

#endif // FOLDWINDOW_H
