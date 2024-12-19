#ifndef QSSMANAGER_H
#define QSMMANAGER_H

// 单例模式 QSS管理器

#include <QObject>
#include <QMap>
#include <mutex>

struct QSSData
{
    QString dark;
    QString light;
};

class QSSManager : public QObject
{
    Q_OBJECT
public:
    // 单例模式 禁止拷贝构造和赋值操作
    QSSManager(const QSSManager &) = delete;
    QSSManager& operator=(const QSSManager &) = delete;

    static QSSManager* instance(); // 获取单例实例

    void input(QWidget *widget, QString dark, QString light); // 注册控件
    void updateWidget(); // 更新所有已注册的控件
    void changeTheme(); // 切换主题
    QString theme(); // 返回当前主题

private:
    explicit QSSManager() = default;
    static std::atomic<QSSManager*> m_instance; // 单例实例指针
    static std::mutex m_mutex; // 保证线程安全

    bool m_isDark = true; // 默认为暗色模式
    QMap<QWidget*, QSSData> m_qssData;
};

#endif // QSSMANAGER_H
