#ifndef STDPROPERTY_H
#define STDPROPERTY_H

// 定义标准属性
#define STD_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE m_##NAME READ NAME WRITE set##NAME NOTIFY NAME##Changed) \
public: \
    Q_SIGNAL void NAME##Changed(); \
    inline TYPE NAME() const { return m_##NAME; } \
    void set##NAME(const TYPE &VALUE) \
    { \
        m_##NAME = VALUE; \
        emit NAME##Changed(); \
    } \
private: \
    TYPE m_##NAME;

// 定义标准属性并初始化
#define STD_PROPERTY_INIT(TYPE, NAME, VALUE) \
    Q_PROPERTY(TYPE m_##NAME READ NAME WRITE set##NAME NOTIFY NAME##Changed) \
public: \
    Q_SIGNAL void NAME##Changed(); \
    inline TYPE NAME() const { return m_##NAME; } \
    void set##NAME(const TYPE &NAME) \
    { \
        m_##NAME = NAME; \
        emit NAME##Changed(); \
    } \
private: \
    TYPE m_##NAME = VALUE;

#endif // STDPROPERTY_H