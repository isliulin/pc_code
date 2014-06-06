#ifndef AKIPEDIT_H
#define AKIPEDIT_H
#include <QtGui>
//IP地址输入框
class IpAddressWidget : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *m_SpinBox[4];
    QLabel *m_Label[3];
    QString m_Separator;        //四个数字之间的分隔符
protected:
    bool eventFilter(QObject *object, QEvent *event);
public:
    IpAddressWidget(QWidget *parent = 0);
    ~IpAddressWidget();
    bool setIp(QString ip);
    bool setIp(QString ip1,QString ip2,QString ip3,QString ip4);
    bool setIp(int ip1,int ip2,int ip3,int ip4);
    bool isDigitString(const QString& src);
    QString GetIpAddressString();
    void SetSeparator(const QString &separator);
};

#endif // AKIPEDIT_H
