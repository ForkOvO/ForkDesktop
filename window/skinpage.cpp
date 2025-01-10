#include "skinpage.h"
#include "qssmanager.h"
#include "background.h"
#include "cachemanager.h"

#include <QFile>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QColor>

SkinPage::SkinPage(Background* background, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground); // 启用qss
    resize(600, 400);

    m_background = background; // 背景

    dataInit(); // 初始化数据
    uiInit(); // 初始化UI
}

void SkinPage::dataInit()
{
    // 背景颜色数据
    m_skinList = { // 左暗 右暗 左亮 右亮
        {"#456EA6", "#8A5A91", "#B2D4FE", "#E8C5F5"},
        {"#735C16", "#38323F", "#FFDF92", "#EFE5F9"},
        {"#3F612F", "#4F3242", "#A8F688", "#FBFBF7"},
        {"#4A4873", "#2A4129", "#DDD7FD", "#BDF9B2"},
        {"#653E61", "#174241", "#FCC9F0", "#4DFCF3"},    
        {"#604962", "#0C1824", "#FFF3FF", "#D8EAFF"},
        {"#111111", "#111111", "#F2F2F2", "#F2F2F2"},
        {"#628D9B", "#82AFC2", "#D0F3FF", "#FEFEFF"},
        {"#E9A276", "#F68F64", "#EEC0A2", "#FFE9B3"},
        {"#85707A", "#798967", "#FFDDEF", "#F4FEE7"},
        {"#776E78", "#597171", "#F7CEC5", "#B4EAB2"},
        {"#5EB57D", "#6A9377", "#82E8A3", "#B6FAB7"},
    };

    // 自定义背景颜色数据
    CacheManager* cacheManager = CacheManager::instance();
    cacheManager->loadCache("theme.json");
    QJsonValue colors = cacheManager->getCache("theme.json", "customBackColor");
    if (!colors.isNull()) // 如果有自定义背景颜色数据
    {
        m_leftDarkColor = colors["leftDark"].toString();
        m_leftLightColor = colors["leftLight"].toString();
        m_rightDarkColor = colors["rightDark"].toString();
        m_rightLightColor = colors["rightLight"].toString();
    }
}

void SkinPage::uiInit()
{
    // 皮肤按钮列表
    QVBoxLayout* skinLayout = new QVBoxLayout();
    skinLayout->setContentsMargins(0, 0, 0, 0);
    for(int i = 0; i < m_skinList.size(); i++) // 所有颜色按钮
    {
        QPushButton* btn = new QPushButton;
        btn->setObjectName(QString("skinBtn%1").arg(i));
        btn->setFixedSize(100, 100);
        connect(btn, &QPushButton::clicked, [this, i](){ this->onSkinBtnClicked(i); });
        skinLayout->addWidget(btn);
    }
    // 显示widget
    QWidget * skinListBack = new QWidget;
    skinListBack->setObjectName("skinListBack");
    skinListBack->setLayout(skinLayout);
    // 滚动区域
    QScrollArea * scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("skinArea");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 禁用水平滚动条
    scrollArea->setFixedSize(120, 400);
    scrollArea->setWidget(skinListBack);

    // 自定义背景
    // 按钮
    m_darkBtn = new QPushButton("暗色");
    m_darkBtn->setObjectName("skinBtnDark");
    m_darkBtn->setFixedSize(100, 100);
    m_lightBtn = new QPushButton("亮色");
    m_lightBtn->setObjectName("skinBtnLight");
    m_lightBtn->setFixedSize(100, 100);
    connect(m_darkBtn, &QPushButton::clicked, this, &SkinPage::onDarkBtnClicked);
    connect(m_lightBtn, &QPushButton::clicked, this, &SkinPage::onLightBtnClicked);
    // 列表
    QLabel* leftDarkLabel = new QLabel("暗色左侧");
    m_leftDarkEdit = new QLineEdit(m_leftDarkColor);
    m_leftDarkBtn = new QPushButton;
    connect(m_leftDarkEdit, &QLineEdit::textChanged, this, [this]{ this->onCustomTextChanged(ColorDir::LeftDark); });
    connect(m_leftDarkBtn, &QPushButton::clicked, this, [this]{ this->onCustomBtnClicked(); });
    QLabel* rightDarkLabel = new QLabel("暗色右侧");
    m_rightDarkEdit = new QLineEdit(m_rightDarkColor);
    m_rightDarkBtn = new QPushButton;
    connect(m_rightDarkEdit, &QLineEdit::textChanged, this, [this]{ this->onCustomTextChanged(ColorDir::RightDark); });
    connect(m_rightDarkBtn, &QPushButton::clicked, this, [this]{ this->onCustomBtnClicked(); });
    QLabel* leftLightLabel = new QLabel("亮色左侧");
    m_leftLightEdit = new QLineEdit(m_leftLightColor);
    m_leftLightBtn = new QPushButton;
    connect(m_leftLightEdit, &QLineEdit::textChanged, this, [this]{ this->onCustomTextChanged(ColorDir::LeftLight); });
    connect(m_leftLightBtn, &QPushButton::clicked, this, [this]{ this->onCustomBtnClicked(); });
    QLabel* rightLightLabel = new QLabel("亮色右侧");
    m_rightLightEdit = new QLineEdit(m_rightLightColor);
    m_rightLightBtn = new QPushButton;
    connect(m_rightLightEdit, &QLineEdit::textChanged, this, [this]{ this->onCustomTextChanged(ColorDir::RightLight); });
    connect(m_rightLightBtn, &QPushButton::clicked, this, [this]{ this->onCustomBtnClicked(); });
    // 更新按钮样式
    onCustomTextChanged(ColorDir::LeftDark);
    onCustomTextChanged(ColorDir::RightDark);
    onCustomTextChanged(ColorDir::LeftLight);
    onCustomTextChanged(ColorDir::RightLight);


    // 布局
    // 自定义按钮
    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(m_darkBtn);
    btnLayout->addWidget(m_lightBtn);
    // 自定义列表
    QHBoxLayout* leftDarkLayout = new QHBoxLayout; // 暗色左侧
    leftDarkLayout->addWidget(leftDarkLabel);
    leftDarkLayout->addWidget(m_leftDarkEdit);
    leftDarkLayout->addWidget(m_leftDarkBtn);
    QHBoxLayout* rightDarkLayout = new QHBoxLayout; // 暗色右侧
    rightDarkLayout->addWidget(rightDarkLabel);
    rightDarkLayout->addWidget(m_rightDarkEdit);
    rightDarkLayout->addWidget(m_rightDarkBtn);
    QHBoxLayout* leftLightLayout = new QHBoxLayout; // 亮色左侧
    leftLightLayout->addWidget(leftLightLabel);
    leftLightLayout->addWidget(m_leftLightEdit);
    leftLightLayout->addWidget(m_leftLightBtn);
    QHBoxLayout* rightLightLayout = new QHBoxLayout; // 亮色右侧
    rightLightLayout->addWidget(rightLightLabel);
    rightLightLayout->addWidget(m_rightLightEdit);
    rightLightLayout->addWidget(m_rightLightBtn);
    // 所有自定义
    QVBoxLayout* customLayout = new QVBoxLayout;
    customLayout->addLayout(btnLayout);
    customLayout->addLayout(leftDarkLayout);
    customLayout->addLayout(rightDarkLayout);
    customLayout->addLayout(leftLightLayout);
    customLayout->addLayout(rightLightLayout);
    // 主体布局
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(customLayout);

    // 加载qss
    // 主体
    QFile file(":/qss/skinpage.qss");
    file.open(QFile::ReadOnly);
    QString qss(file.readAll());
    file.close();
    m_darkQSS = QString(qss).replace("{{theme}}", "rgba(255, 255, 255, 128)");
    m_lightQSS = QString(qss).replace("{{theme}}", "rgba(0, 0, 0, 128)");
    // 按钮
    QFile item_file(":/qss/skinpageitem.qss");
    item_file.open(QFile::ReadOnly);
    m_itemQSS = item_file.readAll();
    item_file.close();
    for (int i = 0; i < m_skinList.size(); i++)
    {
        m_darkQSS += QString(m_itemQSS).arg(i).arg(m_skinList[i][0]).arg(m_skinList[i][1]).replace("{{theme}}", "white");
        m_lightQSS += QString(m_itemQSS).arg(i).arg(m_skinList[i][2]).arg(m_skinList[i][3]).replace("{{theme}}", "black");
    }
    onCustomBtnClicked(); // 加载qss
}

void SkinPage::onSkinBtnClicked(int index)
{
    qDebug() << "skinpage.cpp" << __LINE__ << "点击按钮" << index;
    m_background->setColor(m_skinList[index][0], m_skinList[index][1], m_skinList[index][2], m_skinList[index][3]); // 设置背景颜色
}

void SkinPage::onDarkBtnClicked()
{
    qDebug() << "skinpage.cpp" << __LINE__ << "点击暗色按钮";
    QSSManager* qssManager = QSSManager::instance();
    if (qssManager->theme() != "dark") qssManager->changeTheme(); // 切换为暗色
    m_background->setColor(m_leftDarkColor, m_rightDarkColor, m_leftLightColor, m_rightLightColor); // 设置背景颜色
}

void SkinPage::onLightBtnClicked()
{
    qDebug() << "skinpage.cpp" << __LINE__ << "点击亮色按钮";
    QSSManager* qssManager = QSSManager::instance();
    if (qssManager->theme() != "light") qssManager->changeTheme(); // 切换为亮色
    m_background->setColor(m_leftDarkColor, m_rightDarkColor, m_leftLightColor, m_rightLightColor); // 设置背景颜色
}

void SkinPage::onCustomTextChanged(ColorDir dir)
{
    qDebug() << "skinpage.cpp" << __LINE__ << "自定义颜色改变" << dir;

    auto setColor = [&](QString color, QString& m_color, QPushButton* btn) {
        if (QColor(color).isValid()) // 颜色有效
        {
            m_color = color;
            btn->setStyleSheet(QString("background-color: %1;").arg(color));
        }
    };

    switch (dir)
    {
    case ColorDir::LeftDark:
        setColor(m_leftDarkEdit->text(), m_leftDarkColor, m_leftDarkBtn);
        break;
    case ColorDir::RightDark:
        setColor(m_rightDarkEdit->text(), m_rightDarkColor, m_rightDarkBtn);
        break;
    case ColorDir::LeftLight:
        setColor(m_leftLightEdit->text(), m_leftLightColor, m_leftLightBtn);
        break;
    case ColorDir::RightLight:
        setColor(m_rightLightEdit->text(), m_rightLightColor, m_rightLightBtn);
        break;
    default:
        break;
    }
}

void SkinPage::onCustomBtnClicked()
{
    qDebug() << "skinpage.cpp" << __LINE__ << "更新自定义按钮";
    
    // 更新自定义按钮
    QSSManager* qssManager = QSSManager::instance();
    QString darkBtnDarkQSS = QString(m_itemQSS).arg("Dark").arg(m_leftDarkColor).arg(m_rightDarkColor).replace("{{theme}}", "white");
    QString darkBtnLightQSS = QString(m_itemQSS).arg("Dark").arg(m_leftDarkColor).arg(m_rightDarkColor).replace("{{theme}}", "black");
    QString lightBtnLightQSS = QString(m_itemQSS).arg("Light").arg(m_leftLightColor).arg(m_rightLightColor).replace("{{theme}}", "black");
    QString lightBtnDarkQSS = QString(m_itemQSS).arg("Light").arg(m_leftLightColor).arg(m_rightLightColor).replace("{{theme}}", "white");
    qssManager->input(this, m_darkQSS + darkBtnDarkQSS +lightBtnDarkQSS, m_lightQSS + darkBtnLightQSS + lightBtnLightQSS);

    // 更新缓存
    QJsonObject obj;
    obj.insert("leftDark", m_leftDarkColor);
    obj.insert("rightDark", m_rightDarkColor);
    obj.insert("leftLight", m_leftLightColor);
    obj.insert("rightLight", m_rightLightColor);
    CacheManager* cacheManager = CacheManager::instance();
    cacheManager->loadCache("theme.json");
    cacheManager->changeCache("theme.json", "customBackColor", obj);
}
