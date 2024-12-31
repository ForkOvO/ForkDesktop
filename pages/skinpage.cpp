#include "skinpage.h"
#include "qssmanager.h"

#include <QFile>

SkinPage::SkinPage(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground); // 启用qss

    QFile file(":/qss/skinpage.qss");
    file.open(QFile::ReadOnly);
    QString qss(file.readAll());
    file.close();
    QSSManager* qssManager = QSSManager::instance();
    qssManager->input(this, QString(qss).replace("{{theme}}", "#404040"), QString(qss).replace("{{theme}}", "#D0D0D0"));

    resize(600, 400);
}
