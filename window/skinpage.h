#ifndef SKINPAGE_H
#define SKINPAGE_H

// 皮肤设置

#include <QWidget>

// 自定义
class Background;
// Qt
class QPushButton;

class SkinPage : public QWidget
{
    Q_OBJECT
public:
    explicit SkinPage(Background* background, QWidget *parent = nullptr);

private:
    void onSkinBtnClicked(int index);

private:
    Background* m_background; // 背景

    QList<QList<QString>> m_skinList; // 皮肤数据
    QList<QPushButton*> m_skinBtnList; // 皮肤按钮列表
};

#endif // SKINPAGE_H
