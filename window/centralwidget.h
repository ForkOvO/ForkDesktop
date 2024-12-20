#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

// 主体窗口

#include <QWidget>

// 自定义
class FoldWindow; // 折叠窗口
class QSSManager; // QSS管理器
class Background; // 渐变背景
class SearchBox; // 搜索框
class Sidebar; // 侧边栏
// Qt
class QPushButton;

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);

private:
    FoldWindow* m_parent = nullptr; // 折叠窗口
    QSSManager* m_qssManager = nullptr; // QSS管理器
    Background* m_background = nullptr; // 背景
    SearchBox* m_searchBox = nullptr; // 搜索框
    Sidebar* m_sidebar = nullptr; // 侧边栏

    QPushButton* m_foldSwitchBtn = nullptr; // 折叠开关
    QPushButton* m_themeSwitchBtn = nullptr; // 主题切换
    QPushButton* m_githubBtn = nullptr; // GitHub
    QPushButton* m_bilibiliBtn = nullptr; // Bilibili
};

#endif // CENTRALWIDGET_H
