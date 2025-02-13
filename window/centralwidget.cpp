#include "centralwidget.h"
#include "foldwindow.h"
#include "background.h"
#include "searchbox.h"
#include "notification.h"
#include "sidebar.h"
#include "skinpage.h"
#include "gamepage.h"
#include "publiccache.h"
#include "themebutton.h"

#include <QPushButton>
#include <QFile>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDesktopServices>
#include <QUrl>
#include <QScreen>
#include <QGuiApplication>

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    m_parent = static_cast<FoldWindow*>(parent); // 折叠窗口

    setAttribute(Qt::WA_TranslucentBackground); // 透明背景
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry()); // 屏幕大小

    // 背景
    m_background = new Background(this);

    // 折叠开关按钮
    m_foldSwitchBtn = new ThemeButton(this);
    m_foldSwitchBtn->move(0, 0);
    connect(m_foldSwitchBtn, &QPushButton::clicked, m_parent, &FoldWindow::changeFoldStatus); // 折叠切换

    // 搜索框
    m_searchBox = new SearchBox(this);
    m_searchBox->move(width() - m_searchBox->width(), 0); // 右侧对齐

    // 侧边栏
    m_sidebar = new Sidebar(this);
    m_sidebar->move(0, (height() - m_sidebar->height()) / 2); // 左侧居中
    connect(m_sidebar, &Sidebar::btnClicked, this, &CentralWidget::onPageIndexChanged); // 侧边栏按钮点击

    // 主题切换按钮
    m_themeSwitchBtn = new ThemeButton(this, "theme");
    connect(m_themeSwitchBtn, &QPushButton::clicked, this, [&](){
        PublicCache *cache = PublicCache::instance();
        if (cache->get("theme").toString() == "dark") cache->set("theme", "white");
        else cache->set("theme", "dark");
    }); // 主题切换

    // github按钮
    m_githubBtn = new ThemeButton(this, "github", 25);
    connect(m_githubBtn, &QPushButton::clicked, this, [&](){ QDesktopServices::openUrl(QUrl("https://github.com/ForkOvO/ForkDesktop")); }); // 打开github仓库
    // bilibili按钮
    m_bilibiliBtn = new ThemeButton(this, "bilibili", 25);
    connect(m_bilibiliBtn, &QPushButton::clicked, this, [&](){ QDesktopServices::openUrl(QUrl("https://space.bilibili.com/387426555")); }); // 打开bilibili

    // 布局
    // 底部布局
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_githubBtn);
    bottomLayout->addWidget(m_bilibiliBtn);
    bottomLayout->addWidget(m_themeSwitchBtn);
    // 主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addLayout(bottomLayout);
    mainLayout->setContentsMargins(0, 0, 0, 0); // 设置边距

    // 启动欢迎通知
    Notification::showNotification(this);
}

void CentralWidget::onPageIndexChanged(int index)
{
    STD_DEBUG(CentralWidget.cpp) << "sidebar clicked" << index;

    if (m_gamePage) m_gamePage->hide();
    if (m_skinPage) m_skinPage->hide();

    switch (index)
    {
    case 0:
        break;
    case 1: // 游戏页面
    {
        if (!m_gamePage) m_gamePage = new GamePage(this);
        m_gamePage->move((width() - m_gamePage->width()) / 2, (height() - m_gamePage->height()) / 2); // 居中
        m_gamePage->show();
        break;
    }
    case 2: // 皮肤页面
    {
        if (!m_skinPage) m_skinPage = new SkinPage(m_background, this);
        m_skinPage->move((width() - m_skinPage->width()) / 2, (height() - m_skinPage->height()) / 2); // 居中
        m_skinPage->show();
        break;
    }
    default:
        break;
    }
}
