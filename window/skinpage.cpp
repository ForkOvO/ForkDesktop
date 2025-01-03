#include "skinpage.h"
#include "qssmanager.h"
#include "background.h"

#include <QFile>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>

SkinPage::SkinPage(Background* background, QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground); // 启用qss
    resize(600, 400);

    m_background = background; // 背景

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

    QWidget * skinListBack = new QWidget;
    skinListBack->setObjectName("skinListBack");
    skinListBack->setLayout(skinLayout);

    QScrollArea * scrollArea = new QScrollArea(this);
    scrollArea->setObjectName("skinArea");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 禁用水平滚动条
    scrollArea->resize(120, 400);
    scrollArea->setWidget(skinListBack);
    
    // 加载qss
    // 主体
    QFile file(":/qss/skinpage.qss");
    file.open(QFile::ReadOnly);
    QString qss(file.readAll());
    file.close();
    QString qss_dark = QString(qss).replace("{{theme}}", "rgba(255, 255, 255, 128)");
    QString qss_light = QString(qss).replace("{{theme}}", "rgba(0, 0, 0, 128)");
    // 按钮
    QFile item_file(":/qss/skinpageitem.qss");
    item_file.open(QFile::ReadOnly);
    QString item_qss(item_file.readAll());
    item_file.close();
    for (int i = 0; i < m_skinList.size(); i++)
    {
        qss_dark += QString(item_qss).arg(i).arg(m_skinList[i][0]).arg(m_skinList[i][1]);
        qss_light += QString(item_qss).arg(i).arg(m_skinList[i][2]).arg(m_skinList[i][3]);
    }
    QSSManager* qssManager = QSSManager::instance();
    qssManager->input(this, qss_dark, qss_light);
}

void SkinPage::onSkinBtnClicked(int index)
{
    qDebug() << "skinpage.cpp" << __LINE__ << "点击按钮" << index;
    m_background->setColor(m_skinList[index][0], m_skinList[index][1], m_skinList[index][2], m_skinList[index][3]); // 设置背景颜色
}
