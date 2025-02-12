#ifndef THEMEBUTTON_H
#define THEMEBUTTON_H

#include "stdinit.h"
#include <QPushButton>

class ThemeButton : public QPushButton
{
    Q_OBJECT
    STD_PROPERTY_INIT(int, size, 50)
    STD_PROPERTY_INIT(QString, name, "ten_OvO")
public:
    explicit ThemeButton(QWidget *parent = nullptr, QString name = "ten_OvO", int size = 50);
    ~ThemeButton();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // THEMEBUTTON_H
