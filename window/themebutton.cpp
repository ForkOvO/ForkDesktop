#include "themebutton.h"
#include "publiccache.h"

#include <QPainter>

ThemeButton::ThemeButton(QWidget *parent, QString name, int size)
    : QPushButton(parent)
{
    setsize(size);
    setname(name);
    PublicCache* cache = PublicCache::instance();
    cache->addWidget(this);
}

ThemeButton::~ThemeButton()
{
    PublicCache* cache = PublicCache::instance();
    cache->removeWidget(this);
}

void ThemeButton::paintEvent(QPaintEvent *event)
{
    setFixedSize(m_size, m_size);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    PublicCache* cache = PublicCache::instance();
    if (cache->get("theme") == "dark")
    {
        QPixmap pixmap(":/res/" + m_name + "_white.png");
        painter.drawPixmap(rect(), pixmap);
    }
    else
    {
        QPixmap pixmap(":/res/" + m_name + "_black.png");
        painter.drawPixmap(rect(), pixmap);
    }
}
