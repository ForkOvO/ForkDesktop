#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

// 主体窗口

#include <QWidget>

// 自定义
class FoldWindow; // 折叠窗口
class Background; // 渐变背景
class SearchBox; // 搜索框
class Sidebar; // 侧边栏
class SkinPage; // 皮肤页面
class GamePage; // 游戏页面
class ThemeButton; // 主题按钮

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);

private:
    void onPageIndexChanged(int index); // 页面索引改变

private:
    FoldWindow* m_parent = nullptr; // 折叠窗口
    Background* m_background = nullptr; // 背景
    SearchBox* m_searchBox = nullptr; // 搜索框
    Sidebar* m_sidebar = nullptr; // 侧边栏
    SkinPage* m_skinPage = nullptr; // 皮肤页面
    GamePage* m_gamePage = nullptr; // 游戏页面

    ThemeButton* m_foldSwitchBtn = nullptr; // 折叠开关
    ThemeButton* m_themeSwitchBtn = nullptr; // 主题切换
    ThemeButton* m_githubBtn = nullptr; // GitHub
    ThemeButton* m_bilibiliBtn = nullptr; // Bilibili
};

#endif // CENTRALWIDGET_H
