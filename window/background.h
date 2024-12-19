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

    void setColor(QString topLeftDark, QString bottomRightDark, QString topLeftLight, QString bottomRightLight);

private:
    QSSManager* m_qssManager = nullptr;

    QString m_qssTemplate; // qss模板
    QString m_topLeftDark; // 左上角暗色
    QString m_bottomRightDark; // 右下角暗色
    QString m_topLeftLight; // 左上角亮色
    QString m_bottomRightLight; // 右下角亮色
};

#endif // BACKGROUND_H
