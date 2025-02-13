#ifndef SIDEBAR_H
#define SIDEBAR_H

// 侧边栏

#include "stdinit.h"
#include <QWidget>

class QPropertyAnimation;

class Sidebar : public QWidget
{
    Q_OBJECT
    STD_PROPERTY(QStringList, btnNameList)
    STD_PROPERTY(QStringList, btnDescList)
    STD_PROPERTY_INIT(int, currBackPos, 0)
public:
    explicit Sidebar(QWidget *parent = nullptr);

signals:
    void btnClicked(int index);

private slots:
    void onBtnClicked(int index);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPropertyAnimation* m_foldAnimation = nullptr; // 折叠动画
    QPropertyAnimation* m_clickAnimation = nullptr; // 点击动画
};

#endif // SIDEBAR_H