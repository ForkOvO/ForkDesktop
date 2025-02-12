#include "centralwidget.h"
#include "foldwindow.h"
#include "qssmanager.h"
#include "background.h"
#include "searchbox.h"
#include "notification.h"
#include "sidebar.h"
#include "skinpage.h"
#include "gamepage.h"
#include "publiccache.h"

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

    setAttribute(Qt::WA_StyledBackground); // 启用qss
    setAttribute(Qt::WA_TranslucentBackground); // 透明背景
    setGeometry(QGuiApplication::primaryScreen()->availableGeometry()); // 屏幕大小

    // QSS管理器
    m_qssManager = QSSManager::instance();
    QFile file(":/qss/centralwidget.qss");
    file.open(QFile::ReadOnly);
    QString qss(file.readAll());
    file.close();
    m_qssManager->input(this, QString(qss).replace("{{theme}}", "white"), QString(qss).replace("{{theme}}", "black"));

    // 背景
    m_background = new Background(this);

    // 折叠开关按钮
    m_foldSwitchBtn = new QPushButton(this);
    m_foldSwitchBtn->setObjectName("foldSwitchBtn");
    m_foldSwitchBtn->setGeometry(0, 0, 50, 50);
    connect(m_foldSwitchBtn, &QPushButton::clicked, m_parent, &FoldWindow::changeFoldStatus); // 折叠切换

    // 搜索框
    m_searchBox = new SearchBox(this);
    m_searchBox->move(width() - m_searchBox->width(), 0); // 右侧对齐

    // 侧边栏
    m_sidebar = new Sidebar(this);
    m_sidebar->move(0, (height() - m_sidebar->height()) / 2); // 左侧居中
    connect(m_sidebar, &Sidebar::btnClicked, this, &CentralWidget::onPageIndexChanged); // 侧边栏按钮点击

    // 主题切换按钮
    m_themeSwitchBtn = new QPushButton(this);
    m_themeSwitchBtn->setObjectName("themeSwitchBtn");
    m_themeSwitchBtn->setFixedSize(50, 50);
    // connect(m_themeSwitchBtn, &QPushButton::clicked, m_qssManager, &QSSManager::changeTheme); // 主题切换
    connect(m_themeSwitchBtn, &QPushButton::clicked, this, [&](){
        PublicCache *cache = PublicCache::instance();
        QString theme = cache->get("theme").toString();
        if (theme == "dark")
        {
            cache->set("theme", "white");
        }
        else
        {
            cache->set("theme", "dark");
        }
    }); // 主题切换

    // github按钮
    m_githubBtn = new QPushButton(this);
    m_githubBtn->setObjectName("githubBtn");
    m_githubBtn->setFixedSize(25, 25);
    connect(m_githubBtn, &QPushButton::clicked, this, [&](){ QDesktopServices::openUrl(QUrl("https://github.com/ForkOvO/ForkDesktop")); }); // 打开github仓库
    // bilibili按钮
    m_bilibiliBtn = new QPushButton(this);
    m_bilibiliBtn->setObjectName("bilibiliBtn");
    m_bilibiliBtn->setFixedSize(25, 25);
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
    qDebug() << "centralwidget.cpp" << __LINE__ << "侧边栏点击" << index;

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
