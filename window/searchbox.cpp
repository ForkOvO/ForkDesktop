#include "searchBox.h"
#include "qssmanager.h"

#include <QFile>
#include <QLineEdit>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QListWidget>

SearchBox::SearchBox(QWidget *parent)
    : QWidget(parent)
{
    // qss管理
    m_qssManager = QSSManager::instance();

    resize(300, 50); // 设置大小
    setAttribute(Qt::WA_StyledBackground); // 启用qss
    setAttribute(Qt::WA_TranslucentBackground); // 设置背景透明

    // get请求
    m_networkAccessManager = new QNetworkAccessManager(this);
    connect(m_networkAccessManager, &QNetworkAccessManager::finished, this, &SearchBox::replyFinished);

    // 搜索框
    m_searchLineEdit = new QLineEdit(this);
    m_searchLineEdit->setObjectName("searchLineEdit");
    m_searchLineEdit->setPlaceholderText("搜索");
    m_searchLineEdit->setGeometry(0, 0, 250, 50);
    connect(m_searchLineEdit, &QLineEdit::returnPressed, this, [&](){ search(m_searchLineEdit->text()); }); // 回车搜索
    connect(m_searchLineEdit, &QLineEdit::textChanged, this, &SearchBox::onSearchLineEditTextChanged); // 输入搜索

    // 搜索按钮
    m_searchBtn = new QPushButton(this);
    m_searchBtn->setObjectName("searchBtn");
    m_searchBtn->setGeometry(250, 0, 50, 50);
    connect(m_searchBtn, &QPushButton::clicked, this, [&](){ search(m_searchLineEdit->text()); }); // 点击搜索

    // 搜索建议列表
    m_searchListWidget = new QListWidget(this);
    m_searchListWidget->setObjectName("searchListWidget");
    m_searchListWidget->setGeometry(0, 50, 300, 100);
    m_searchListWidget->setFrameStyle(QFrame::NoFrame); // 不显示边框
    m_searchListWidget->setFocusPolicy(Qt::NoFocus); // 不获取焦点
    connect(m_searchListWidget, &QListWidget::itemClicked, this, [&](QListWidgetItem *item){ search(item->text()); }); // 点击搜索建议

    // 加载qss
    QFile file(":/qss/searchbox.qss");
    file.open(QFile::ReadOnly);
    QString qss = file.readAll();
    file.close();
    m_qssManager->input(this, QString(qss).replace("{{theme}}", "white"), QString(qss).replace("{{theme}}", "black"));
}

void SearchBox::search(const QString & text)
{
    QUrl url("https://cn.bing.com/search?q=" + text); // bing搜索
    QDesktopServices::openUrl(url);
}

void SearchBox::replyFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) // 请求失败
    {
        qDebug() << "searchBox.cpp" << __LINE__ << "请求失败" << reply->errorString();
        reply->deleteLater();
        return;
    }
    
    QString str = reply->readAll();
    qDebug() << "searchBox.cpp" << __LINE__ << "请求建议成功";

    // 获取双引号中的内容
    QRegularExpression re("\".*?\"");
    QRegularExpressionMatchIterator i = re.globalMatch(str);
    i.next(); // 第一个双引号为问题本身，跳过
    while (i.hasNext()) // 把建议添加到搜索建议列表中
    {
        QRegularExpressionMatch match = i.next();
        QString matchStr = match.captured(0);
        matchStr = matchStr.mid(1, matchStr.size() - 2); // 去掉双引号
        if (matchStr == "") continue;
        QListWidgetItem *item = new QListWidgetItem(matchStr);
        item->setSizeHint(QSize(300, 50));
        m_searchListWidget->addItem(item);
    }
    m_searchListWidget->setGeometry(0, 50, 300, 50 * m_searchListWidget->count());
    resize(300, 50 + 50 * m_searchListWidget->count());
    reply->deleteLater();
}

void SearchBox::onSearchLineEditTextChanged(QString text)
{
    m_searchListWidget->clear(); // 清空搜索建议列表
    m_searchListWidget->setGeometry(0, 50, 300, 50 * m_searchListWidget->count());
    resize(300, 50 + 50 * m_searchListWidget->count());
    if (text == "") return;
    QUrl url("https://suggestion.baidu.com/su?p=3&ie=UTF-8&cb=&wd=" + text); // 百度搜索建议接口
    m_networkAccessManager->get(QNetworkRequest(url));
}
