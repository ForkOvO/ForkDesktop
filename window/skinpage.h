#ifndef SKINPAGE_H
#define SKINPAGE_H

// 皮肤设置

#include <QWidget>

// 自定义
class Background;
// Qt
class QPushButton;
class QLineEdit;

class SkinPage : public QWidget
{
    Q_OBJECT
public:
    enum ColorDir // 颜色方向
    {
        LeftDark,
        RightDark,
        LeftLight,
        RightLight
    };

public:
    explicit SkinPage(Background* background, QWidget *parent = nullptr);

private:
    void dataInit(); // 初始化数据
    void uiInit(); // 初始化UI

    void onSkinBtnClicked(int index); // 皮肤按钮点击事件
    void onDarkBtnClicked(); // 暗黑模式按钮点击事件
    void onLightBtnClicked(); // 亮色模式按钮点击事件
    void onCustomTextChanged(ColorDir dir); // 自定义颜色文本改变事件
    void onCustomBtnClicked(); // 自定义按钮点击事件
    
private:
    Background* m_background = nullptr; // 背景

    QString m_itemQSS; // 皮肤按钮样式
    QString m_darkQSS; // 暗黑模式按钮样式
    QString m_lightQSS; // 亮色模式按钮样式
    // 左侧暗黑颜色
    QString m_leftDarkColor = "#456EA6";
    QLineEdit* m_leftDarkEdit = nullptr;
    QPushButton* m_leftDarkBtn = nullptr;
    // 右侧暗黑颜色
    QString m_rightDarkColor = "#8A5A91";
    QLineEdit* m_rightDarkEdit = nullptr;
    QPushButton* m_rightDarkBtn = nullptr;
    // 左侧亮色颜色
    QString m_leftLightColor = "#B2D4FE";
    QLineEdit* m_leftLightEdit = nullptr;
    QPushButton* m_leftLightBtn = nullptr;
    // 右侧亮色颜色
    QString m_rightLightColor = "#E8C5F5";
    QLineEdit* m_rightLightEdit = nullptr;
    QPushButton* m_rightLightBtn = nullptr;

    QPushButton* m_darkBtn = nullptr; // 暗黑模式按钮
    QPushButton* m_lightBtn = nullptr; // 亮色模式按钮
    QList<QList<QString>> m_skinList; // 皮肤数据
    QList<QPushButton*> m_skinBtnList; // 皮肤按钮列表
};

#endif // SKINPAGE_H
