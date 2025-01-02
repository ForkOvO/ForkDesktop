#ifndef BACKGROUND_H
#define BACKGROUND_H

// 渐变背景

#include <QWidget>

class QSSManager;

class Background : public QWidget
{
    Q_OBJECT
public:
    explicit Background(QWidget *parent = nullptr);

    void setColor(QString leftDark, QString rightDark, QString leftLight, QString rightLight);

private:
    QSSManager* m_qssManager = nullptr;

    QString m_qssTemplate; // qss模板
    QString m_leftDark; // 左侧暗色
    QString m_rightDark; // 右侧暗色
    QString m_leftLight; // 左侧亮色
    QString m_rightLight; // 右侧亮色
};

#endif // BACKGROUND_H
