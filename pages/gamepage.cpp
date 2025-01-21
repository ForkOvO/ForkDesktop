#include "gamepage.h"
#include "qssmanager.h"

#include <QFile>

GamePage::GamePage(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground); // 启用qss
    resize(600, 400);

    // QSS模板
    QFile file(":/qss/gamepage.qss");
    file.open(QFile::ReadOnly);
    QString qss(file.readAll());
    file.close();
    // 应用QSS
    QSSManager* m_qssManager = QSSManager::instance();
    m_qssManager->input(this, QString(qss).replace("{{theme}}", "white"), QString(qss).replace("{{theme}}", "black"));
}