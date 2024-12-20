#ifndef SIDEBAR_H
#define SIDEBAR_H

// 侧边栏

#include <QWidget>

class QPropertyAnimation;

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);

signals:
    void btnClicked(int index);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QPropertyAnimation* m_foldAnimation; // 折叠动画
};

#endif // SIDEBAR_H