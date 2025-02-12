#ifndef BACKGROUND_H
#define BACKGROUND_H

// 渐变背景

#include <QWidget>
#include "stdinit.h"

class Background : public QWidget
{
    Q_OBJECT
    STD_PROPERTY_INIT(QString, leftDark, "#604962") // 左侧暗色
    STD_PROPERTY_INIT(QString, rightDark, "#0C1824") // 右侧暗色
    STD_PROPERTY_INIT(QString, leftLight, "#FFF3FF") // 左侧亮色
    STD_PROPERTY_INIT(QString, rightLight, "#D8EAFF") // 右侧亮色

public:
    explicit Background(QWidget *parent = nullptr);
    ~Background();

    void setColor(QString leftDark, QString rightDark, QString leftLight, QString rightLight);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // BACKGROUND_H
