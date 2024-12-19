#ifndef SEARCHBOX_H
#define SEARCHBOX_H

// 搜索框

#include <QWidget>

class QSSManager;
class QLineEdit;
class QPushButton;
class QNetworkAccessManager;
class QNetworkReply;
class QListWidget;

class SearchBox : public QWidget
{
    Q_OBJECT
public:
    explicit SearchBox(QWidget *parent = nullptr);

    void search(const QString &text); // 搜索

private slots:
    void replyFinished(QNetworkReply *reply); // 网络请求完成
    void onSearchLineEditTextChanged(QString text); // 搜索框文本改变

private:
    QSSManager* m_qssManager; // QSS管理器
    QLineEdit* m_searchLineEdit; // 搜索框
    QPushButton* m_searchBtn;     // 搜索按钮
    QNetworkAccessManager* m_networkAccessManager; // 网络访问管理器
    QListWidget* m_searchListWidget; // 搜索建议列表
};

#endif // SEARCHBOX_H
