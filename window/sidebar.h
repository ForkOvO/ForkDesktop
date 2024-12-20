#ifndef SIDEBAR_H
#define SIDEBAR_H

// 侧边栏

#include <QWidget>

// Qt
class QPropertyAnimation;
// 自定义
class QSSManager;

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit Sidebar(QWidget *parent = nullptr);

signals:
    void btnClicked(int index);

private slots:
    void onBtnClicked(int index);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QPropertyAnimation* m_foldAnimation; // 折叠动画
    QPropertyAnimation* m_clickAnimation; // 点击动画
    QSSManager* m_qssManager; // QSS管理器
    QWidget* m_background; // 背景
};

#endif // SIDEBAR_H