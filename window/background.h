#ifndef BACKGROUND_H
#define BACKGROUND_H

// 渐变背景

#include <QWidget>
#include "stdinit.h"

class QSSManager;

class Background : public QWidget
{
    Q_OBJECT
    STD_PROPERTY(QString, qssTemplate) // qss模板
    STD_PROPERTY(QString, leftDark) // 左侧暗色
    STD_PROPERTY(QString, rightDark) // 右侧暗色
    STD_PROPERTY(QString, leftLight) // 左侧亮色
    STD_PROPERTY(QString, rightLight) // 右侧亮色
public:
    explicit Background(QWidget *parent = nullptr);

    void setColor(QString leftDark, QString rightDark, QString leftLight, QString rightLight);
};

#endif // BACKGROUND_H
