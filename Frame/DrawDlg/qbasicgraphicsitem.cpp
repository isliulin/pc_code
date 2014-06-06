#include "qbasicgraphicsitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QBasicGraphicsItem::QBasicGraphicsItem()
{
    //wxy �ṹ���ʼ����������Ϲ��̳���
    sPro.bNotice = false;
    sPro.bDelay = false;
    sPro.enableTouch = false;
    sPro.enableVisable = false;
}

//����Ȩ��ҳ�浽���ݿ� db
//nSceneIdλ��ǰitem���ڵĳ��������ݱ�ID
//count ���ݱ������ ��ΪID�������Ҫ�Լ��趨ID�ı����ڷ���֮��+1
void QBasicGraphicsItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    int itemId = count;
    //QItemGroup::compile(db,nSceneId,count, index);
    //count++;
    int nTable = 0 ;
        QSqlQuery sqlquery(db);
        sqlquery.prepare("INSERT INTO touchProp(nItemId,bTouchByAddr,eCtlAddrType,nValidStatus,nAddrId,"
                "nWordPosition,bTouchByUser,nGroupValueF,nGroupValueL,nPressTime,"
                "bTimeoutCancel,bNoticAddr,eDataType,nNoticeId,nNoticValue)"
                "VALUES (:nItemId,:bTouchByAddr,:eCtlAddrType,:nValidStatus,:nAddrId,"
                ":nWordPosition,:bTouchByUser,:nGroupValueF,:nGroupValueL,:nPressTime,"
                ":bTimeoutCancel,:bNoticAddr,:eDataType,:nNoticeId,:nNoticValue)");
    sqlquery.bindValue(":nItemId",QVariant(itemId));
    if(sPro.enableTouch)
    {
        sqlquery.bindValue(":bTouchByAddr",QVariant(!sPro.byGroups_T));

        sqlquery.bindValue(":bTouchByUser",QVariant(sPro.byGroups_T));
        if(!sPro.byGroups_T)                                                //ѡ�����ܵ�ַ����
        {
            nTable++;
            sqlquery.bindValue(":eCtlAddrType",QVariant(sPro.addrType_T+1));
            int nTmp = 0;
            if(sPro.condition_T == 0)
            {
                nTmp = 1;
            }
            else
                nTmp = 0;
            sqlquery.bindValue(":nValidStatus",QVariant(nTmp));
            sqlquery.bindValue(":nAddrId",QVariant(count+nTable));
            //�������������ַ��Ĵ���
                        ADDR_PARAMENTS stParams;
                        stParams.id = count+nTable;
                        stParams.itemId = itemId;
                        stParams.eType = OBJ_ITEM;
                        stParams.addrNum = -1;
            stParams.eRWtype = SCENE_CONTROL_LOOP_R;
            sPro.address_T.compile(db,stParams);
            sqlquery.bindValue(":nWordPosition",QVariant(sPro.bitIndex_T));
        }
        else
        {
            int valueF = (int)GetUserGroupT();
            int valueL = GetUserGroupT()>>32;
            sqlquery.bindValue(":nGroupValueF",QVariant(valueF));
            sqlquery.bindValue(":nGroupValueL",QVariant(valueL));
            sqlquery.bindValue(":nAddrId",QVariant(-1));
        }


    }

    sqlquery.bindValue(":bTimeoutCancel",QVariant(sPro.bDelay));
    if(sPro.bDelay)
    {
        sqlquery.bindValue(":nPressTime",QVariant(sPro.time));
    }

    sqlquery.bindValue(":bNoticAddr",QVariant(sPro.bNotice));
        if(sPro.bNotice)
        {
                nTable++;
                //�������������ַ��Ĵ���
                ADDR_PARAMENTS stParams;
                stParams.id = count+nTable;
                stParams.itemId = itemId;
                stParams.eType = OBJ_ITEM;
                stParams.addrNum = -1;
                stParams.eRWtype = SCENE_CONTROL_LOOP_R;
                sPro.addrNotice.compile(db,stParams);
                sqlquery.bindValue(":nNoticeId",QVariant(count+nTable));


                sqlquery.bindValue(":eDataType",QVariant(sPro.datatype+1));
                sqlquery.bindValue(":nNoticValue",QVariant(sPro.noticeValue));
        }
        else
                sqlquery.bindValue(":nNoticValue",QVariant(0));

    if(sPro.enableTouch || sPro.bNotice || sPro.bDelay)
    {
        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert touchPro table :"<<result;
    }


    if(sPro.enableVisable)
    {
        sqlquery.prepare("INSERT INTO showProp(nItemId ,bShowByAddr ,eAddrType ,nValidStatus ,nAddrId ,"
                            "nBitPosition ,bShowByUser ,nGroupValueF ,nGroupValueL ) "
                            "VALUES (:nItemId ,:bShowByAddr ,:eAddrType ,:nValidStatus ,:nAddrId ,"
                         ":nBitPosition ,:bShowByUser ,:nGroupValueF ,:nGroupValueL )");
        sqlquery.bindValue(":nItemId",QVariant(itemId));
        sqlquery.bindValue(":bShowByAddr",QVariant(!sPro.byGroups_V));

        sqlquery.bindValue(":bShowByUser",QVariant(sPro.byGroups_V));
        if(!sPro.byGroups_V)                                                //ѡ�����ܵ�ַ����
        {
            nTable++;
            int nTmp = 0;
            if(sPro.condition_V == 0)
            {
                nTmp = 1;
            }
            else
                nTmp = 0;
            sqlquery.bindValue(":eAddrType",QVariant(sPro.addrType_V+1));
            sqlquery.bindValue(":nValidStatus",QVariant(nTmp));
            sqlquery.bindValue(":nAddrId",QVariant(count+nTable));
            //�������������ַ��Ĵ���

                        ADDR_PARAMENTS stParams;
                        stParams.id = count+nTable;
                        stParams.itemId = itemId;
                        stParams.eType = OBJ_ITEM;
                        stParams.addrNum = -1;
            stParams.eRWtype = SCENE_CONTROL_LOOP_R;
            sPro.address_V.compile(db,stParams);
            sqlquery.bindValue(":nBitPosition",QVariant(sPro.bitIndex_V));
            sqlquery.bindValue(":nGroupValueL",QVariant(0));//Ĭ��ֵ
        }
        else
        {
            int valueF = (int)GetUserGroupV();
            int valueL = GetUserGroupV()>>32;
            sqlquery.bindValue(":nGroupValueF",QVariant(valueF));
            sqlquery.bindValue(":nGroupValueL",QVariant(valueL));
            sqlquery.bindValue(":nAddrId",QVariant(-1));
        }
        bool result = false;
        result = sqlquery.exec();
        qDebug() << "insert showPro table :"<<result;
    }

}

void QBasicGraphicsItem::save(QDataStream &stream)
{
    //QItemGroup::save(stream);

    //�ڴ���ӱ���Ȩ��ҳ�����Դ���
    stream << sPro.enableTouch;
    stream << sPro.enableVisable;

    stream << sPro.byGroups_T;
    stream << sPro.byGroups_V;

    stream << sPro.groups_T;
    stream << sPro.groups_V;

    stream << sPro.addrType_T;
    stream << sPro.addrType_V;

    stream << sPro.bitIndex_T;
    stream << sPro.bitIndex_V;

    stream << sPro.condition_T;
    stream << sPro.condition_V;

    stream << sPro.address_T;
    stream << sPro.address_V;

    stream << sPro.bNotice;
    stream << sPro.addrNotice;
    stream << sPro.datatype;
    stream << sPro.noticeValue;

    stream << sPro.bDelay;
    stream << sPro.time;

}


void QBasicGraphicsItem::load(QDataStream &stream)
{
   // QItemGroup::load(stream);

    //�ڴ��������Ȩ��ҳ�����Դ���
    stream >> sPro.enableTouch;
    stream >> sPro.enableVisable;

    stream >> sPro.byGroups_T;
    stream >> sPro.byGroups_V;

    stream >> sPro.groups_T;
    stream >> sPro.groups_V;

    stream >> sPro.addrType_T;
    stream >> sPro.addrType_V;

    stream >> sPro.bitIndex_T;
    stream >> sPro.bitIndex_V;

    stream >> sPro.condition_T;
    stream >> sPro.condition_V;

    stream >> sPro.address_T;
    stream >> sPro.address_V;

    stream >> sPro.bNotice;
    stream >> sPro.addrNotice;
    stream >> sPro.datatype;
    stream >> sPro.noticeValue;

    stream >> sPro.bDelay;
    stream >> sPro.time;
}

void QBasicGraphicsItem::SaveSecurityPro(securityPro *pro)
{
    sPro.enableTouch = pro->enableTouch;
    sPro.enableVisable = pro->enableVisable;

    sPro.byGroups_T = pro->byGroups_T;
    sPro.byGroups_V = pro->byGroups_V;

    sPro.groups_T = pro->groups_T;
    sPro.groups_V = pro->groups_V;

    sPro.addrType_T = pro->addrType_T;
    sPro.addrType_V = pro->addrType_V;

    sPro.bitIndex_T = pro->bitIndex_T;
    sPro.bitIndex_V = pro->bitIndex_V;

    sPro.condition_T = pro->condition_T;
    sPro.condition_V = pro->condition_V;

    sPro.address_T = pro->address_T;
    sPro.address_V = pro->address_V;

    sPro.bNotice = pro->bNotice;
    sPro.addrNotice = pro->addrNotice;
    sPro.datatype = pro->datatype;
    sPro.noticeValue = pro->noticeValue;

    sPro.bDelay = pro->bDelay;
    sPro.time = pro->time;
}

securityPro QBasicGraphicsItem::GetSecurityPro()
{
    return sPro;
}

qint64 QBasicGraphicsItem::GetUserGroupT()
{
    qint64 value = 0;

    QStringList groups;
    foreach(GroupPermiss grp,pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup)
    {
        groups << grp.m_strName;
    }
    int count = sPro.groups_T.size();
    count = (count <64) ?count:64;

    for(int i=0;i<count;i++)
    {
        if(groups.contains(sPro.groups_T[i]))
        {
            //��λ����
                        int index = groups.indexOf(sPro.groups_T[i]);
            value = value|((qint64)pow(2.0,index));
        }
    }
    return value;
}

qint64 QBasicGraphicsItem::GetUserGroupV()
{
    qint64 value = 0;


    QStringList groups;
    foreach(GroupPermiss grp,pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecGroup)
    {
        groups << grp.m_strName;
    }
    int count = sPro.groups_V.size();
    count = (count <64) ?count:64;

    for(int i=0;i<count;i++)
    {
        if(groups.contains(sPro.groups_V[i]))
        {
            //��λ����
                        int index = groups.indexOf(sPro.groups_V[i]);
                        value = value|((qint64)pow(2.0,index));
        }
    }
    return value;
}
