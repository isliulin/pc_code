#include "akipedit.h"

IpAddressWidget::IpAddressWidget(QWidget *parent /* = 0 */):
        QWidget(parent)
{
    m_Separator = ".";
    //�ĸ����ֵ������QSpinBox
    for(int i=0; i<4; i++)
    {
        m_SpinBox[i] = new QSpinBox(this);
        m_SpinBox[i]->setRange(0, 255);
        m_SpinBox[i]->setButtonSymbols(QAbstractSpinBox::NoButtons);
        m_SpinBox[i]->setAlignment(Qt::AlignCenter);
        m_SpinBox[i]->setFixedWidth(30);
        m_SpinBox[i]->setFixedHeight(18);
        m_SpinBox[i]->installEventFilter(this);
    }
    //�ĸ������֮��ķָ���
    for(int i=0; i<3; i++)
    {
        m_Label[i] = new QLabel(m_Separator, this);
        m_Label[i]->setFixedWidth(10);
        m_Label[i]->setFixedHeight(18);
        m_Label[i]->setAlignment(Qt::AlignCenter);
    }

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);
    for(int i=0; i<3; i++)
    {
        layout->addWidget(m_SpinBox[i]);
        layout->addWidget(m_Label[i]);
    }
    layout->addWidget(m_SpinBox[3]);
    setLayout(layout);
}

IpAddressWidget::~IpAddressWidget()
{

}

//��ȡIP��ַ������õ�ַ���Ϸ����򷵻ؿ��ַ���
QString IpAddressWidget::GetIpAddressString()
{
    QString ipAddress;
    for(int i=0; i<3; i++)
    {
        if( m_SpinBox[i]->text().isEmpty() )
        {
            ipAddress.clear();
            return ipAddress;
        }
        ipAddress += m_SpinBox[i]->text() + m_Separator;
    }
    ipAddress += m_SpinBox[3]->text();
    return ipAddress;
}

bool IpAddressWidget::eventFilter(QObject *object, QEvent *event)
{
    //���object�����ĸ�������򷵻�
    int nowBox = -1;
    for(int i=0; i<4; i++)
    {
        if( object == m_SpinBox[i] )
            nowBox = i;
    }
    if( -1 == nowBox )
        return false;

    QSpinBox *spinBox = dynamic_cast<QSpinBox*>(object);

    //���ĳ�������õ������뽹�㣬��������Ϊȫѡ״̬
    if( QEvent::FocusIn == event->type() )
    {
        spinBox->selectAll();
        return true;
    }
    //���������ڵ��ַ�Ϊ0������ո�����򣨷�ֹ�û�������0��
    else if( QEvent::KeyPress == event->type() )
    {
        QKeyEvent *keyevent = dynamic_cast<QKeyEvent*>(event);
        QString context = spinBox->text();

        if( keyevent->key() == Qt::Key_Tab ||keyevent->key() == Qt::Key_Period)
        {
            qDebug() << keyevent->text();
            m_SpinBox[nowBox+1]->setFocus();
            return true;
        }
        else if( "0" == context )
            spinBox->clear();

        if(keyevent->key() == Qt::Key_Backspace)
        {
            if(spinBox->text().isEmpty() && nowBox > 0)
            {
                m_SpinBox[nowBox-1]->setFocus();
            }
        }


    }
    //���������ڵ����ִ���25�������뽹���Զ�������һ��
    else if( QEvent::KeyRelease == event->type() )
    {
        QKeyEvent *keyevent = dynamic_cast<QKeyEvent*>(event);

        int val = spinBox->value();
        QString sVal = spinBox->text();
        if( (spinBox->value() > 25 ) && nowBox < 3
            &&keyevent->key() != Qt::Key_Tab )
        {
           // m_SpinBox[nowBox+1]->setFocus();
        }


    }
    return false;
}
bool IpAddressWidget::setIp(QString ip)
{
    QStringList ips = ip.split(".");
    if(ips.size() == 4)
    {
        return setIp(ips.at(0),ips.at(1),ips.at(2),ips.at(3));
    }
    else
        return false;
}
bool IpAddressWidget::setIp(QString ip1,QString ip2,QString ip3,QString ip4)
{
    if(isDigitString(ip1) && isDigitString(ip2)
        && isDigitString(ip3) && isDigitString(ip4))
        {
        return setIp(ip1.toInt(),ip2.toInt(),ip3.toInt(),ip4.toInt());
    }
    else
        return false;
}
bool IpAddressWidget::setIp(int ip1,int ip2,int ip3,int ip4)
{
    if((ip1>=0 && ip1 <= 255)&& (ip2>=0 && ip2 <= 255)
        && (ip3>=0 && ip3 <= 255)&& (ip4>=0 && ip4 <= 255))
        {
        QVector<int >ips;
        ips << ip1 << ip2 << ip3 << ip4;
        for(int i=0; i<4; i++)
        {
            m_SpinBox[i]->setValue(ips[i]);
        }
        return true;
    }
    else
        return false;
}
bool IpAddressWidget::isDigitString(const QString& src)
{
    const char *s = src.toUtf8().data();

    while(*s && *s>='0' && *s<='9')s++;

    return !bool(*s);
}

