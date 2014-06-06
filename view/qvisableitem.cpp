#include "qvisableitem.h"
#include "Frame/mainwindow.h"
extern MainWindow *pwnd;

QVisableItem::QVisableItem(QGraphicsItem *parent):QItemGroup(parent)
{
}

QGraphicsItem *QVisableItem::Clone()
{
    //return QItemGroup::Clone();

    //需要在派生类实例化对象，复制部分无法重用基类代码
	return 0;
}

//编译权限页面到数据库 db
//nSceneId位当前item所在的场景的数据表ID
//count 数据表计数器 作为ID分配给需要自己设定ID的表，并在分配之后+1
void QVisableItem::compile(QSqlDatabase &db, int nSceneId,int &count,int index)
{
    int itemId = count;
    QItemGroup::compile(db,nSceneId,count, index);
    //count++;
    int nTable = 0 ;
    QMap<QString,QVariant> mapQuery;
//	QSqlQuery sqlquery(db);
//	sqlquery.prepare("INSERT INTO touchProp(nItemId,bTouchByAddr,eCtlAddrType,nValidStatus,nAddrId,"
//		"nWordPosition,bTouchByUser,nGroupValueF,nGroupValueL,nPressTime,"
//		"bTimeoutCancel,bNoticAddr,eDataType,nNoticeId,nNoticValue)"
//		"VALUES (:nItemId,:bTouchByAddr,:eCtlAddrType,:nValidStatus,:nAddrId,"
//		":nWordPosition,:bTouchByUser,:nGroupValueF,:nGroupValueL,:nPressTime,"
//		":bTimeoutCancel,:bNoticAddr,:eDataType,:nNoticeId,:nNoticValue)");
    mapQuery.insert(":nItemId",QVariant(itemId));
    if(sPro.enableTouch)
    {
        mapQuery.insert(":bTouchByAddr",QVariant(!sPro.byGroups_T));

        mapQuery.insert(":bTouchByUser",QVariant(sPro.byGroups_T));
        if(!sPro.byGroups_T)                                                //选择了受地址控制
        {
            nTable++;
            mapQuery.insert(":eCtlAddrType",QVariant(sPro.addrType_T+1));
            int nTmp = 0;
            if(sPro.condition_T == 0)
            {
                nTmp = 1;
            }
            else
                nTmp = 0;
            mapQuery.insert(":nValidStatus",QVariant(nTmp));
            mapQuery.insert(":nAddrId",QVariant(count+nTable));
            //在这里加入插入地址表的代码
			ADDR_PARAMENTS stParams;
			stParams.id = count+nTable;
			stParams.itemId = itemId;
			stParams.eType = OBJ_ITEM;
			stParams.addrNum = -1;
            stParams.eRWtype = SCENE_CONTROL_LOOP_R;
            sPro.address_T.compile(db,stParams);
            mapQuery.insert(":nWordPosition",QVariant(sPro.bitIndex_T));
        }
        else
        {
            int valueF = (int)GetUserGroupT();
            int valueL = GetUserGroupT()>>32;
            mapQuery.insert(":nGroupValueF",QVariant(valueF));
            mapQuery.insert(":nGroupValueL",QVariant(valueL));
            mapQuery.insert(":nAddrId",QVariant(-1));
        }


    }
    else
    {
        mapQuery.insert(":bTouchByAddr",QVariant(false));

        mapQuery.insert(":bTouchByUser",QVariant(false));
    }

    mapQuery.insert(":bTimeoutCancel",QVariant(sPro.bDelay));
    if(sPro.bDelay)
    {
        mapQuery.insert(":nPressTime",QVariant(sPro.time));
    }

    mapQuery.insert(":bNoticAddr",QVariant(sPro.bNotice));
	if(sPro.bNotice)
	{
		nTable++;
		//在这里加入插入地址表的代码
		ADDR_PARAMENTS stParams;
		stParams.id = count+nTable;
		stParams.itemId = itemId;
		stParams.eType = OBJ_ITEM;
		stParams.addrNum = -1;
		stParams.eRWtype = SCENE_CONTROL_LOOP_R;
		sPro.addrNotice.compile(db,stParams);
        mapQuery.insert(":nNoticeId",QVariant(count+nTable));


        mapQuery.insert(":eDataType",QVariant(sPro.datatype+1));
        mapQuery.insert(":nNoticValue",QVariant(sPro.noticeValue));
	}
	else
        mapQuery.insert(":nNoticValue",QVariant(0));

    if(sPro.enableTouch || sPro.bNotice || sPro.bDelay)
    {
        pwnd->inSertDbQuery("touchProp",mapQuery);
        //bool result = false;
        //result = sqlquery.exec();
        //qDebug() << "insert touchPro table :"<<result;
    }


    if(sPro.enableVisable)
    {
//        sqlquery.prepare("INSERT INTO showProp(nItemId ,bShowByAddr ,eAddrType ,nValidStatus ,nAddrId ,"
//                            "nBitPosition ,bShowByUser ,nGroupValueF ,nGroupValueL ) "
//                            "VALUES (:nItemId ,:bShowByAddr ,:eAddrType ,:nValidStatus ,:nAddrId ,"
//                         ":nBitPosition ,:bShowByUser ,:nGroupValueF ,:nGroupValueL )");
        mapQuery.clear();
        mapQuery.insert(":nItemId",QVariant(itemId));
        mapQuery.insert(":bShowByAddr",QVariant(!sPro.byGroups_V));

        mapQuery.insert(":bShowByUser",QVariant(sPro.byGroups_V));
        if(!sPro.byGroups_V)                                                //选择了受地址控制
        {
            nTable++;
            int nTmp = 0;
            if(sPro.condition_V == 0)
            {
                nTmp = 1;
            }
            else
                nTmp = 0;
            mapQuery.insert(":eAddrType",QVariant(sPro.addrType_V+1));
            mapQuery.insert(":nValidStatus",QVariant(nTmp));
            mapQuery.insert(":nAddrId",QVariant(count+nTable));
            //在这里加入插入地址表的代码

			ADDR_PARAMENTS stParams;
			stParams.id = count+nTable;
			stParams.itemId = itemId;
			stParams.eType = OBJ_ITEM;
			stParams.addrNum = -1;
            stParams.eRWtype = SCENE_CONTROL_LOOP_R;
            sPro.address_V.compile(db,stParams);
            mapQuery.insert(":nBitPosition",QVariant(sPro.bitIndex_V));
            mapQuery.insert(":nGroupValueL",QVariant(0));//默认值
        }
        else
        {
            int valueF = (int)GetUserGroupV();
            int valueL = GetUserGroupV()>>32;
            mapQuery.insert(":nGroupValueF",QVariant(valueF));
            mapQuery.insert(":nGroupValueL",QVariant(valueL));
            mapQuery.insert(":nAddrId",QVariant(-1));
        }
        pwnd->inSertDbQuery("showProp",mapQuery);
        //bool result = false;
        //result = sqlquery.exec();
        //qDebug() << "insert showPro table :"<<result;
    }

}
qint64 QVisableItem::GetUserGroupT()
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
            //按位计算
			int index = groups.indexOf(sPro.groups_T[i]);
            value = value|((qint64)pow(2.0,index));
        }
    }
    return value;
}

qint64 QVisableItem::GetUserGroupV()
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
            //按位计算
			int index = groups.indexOf(sPro.groups_V[i]);
			value = value|((qint64)pow(2.0,index));
        }
    }
    return value;
}

int QVisableItem::GroupType()
{
    return 0;
}

void QVisableItem::SetText(QString text)
{
    QSimpleTextItem* pText = dynamic_cast<QSimpleTextItem *>(textItem);
    if(pText)
    {
        pText->SetText(text);
    }
}

void QVisableItem::SetPicture(QString path,EITEM_TYPE bLib,int alpha,QColor color)
{
}

void QVisableItem::redrawForChangeLanguage(int index)
{
}

void QVisableItem::changeItemLanguageAttr(int lanNum)
{
}

void QVisableItem::redrawForChangeStatus(int index, int lan)
{
}

int  QVisableItem::getCurrentState()
{
    return -1;
}

QStringList QVisableItem::getItemStates()
{
    QStringList ls;
    ls.clear();
    return ls;
}

QVector<ADDRPRO> QVisableItem::getAllItemAddr()
{
    kb.clear();
    ADDRPRO Addr;

    if(sPro.enableTouch)
    {
        if(!sPro.byGroups_T)                                                //选择了受地址控制
        {
            Addr.pAddr = &sPro.address_T;
            Addr.str   = getItemName();
            Addr.str  += QObject::tr("-触控权限控制地址");
            Addr.type  = sPro.addrType_T;
            kb << Addr;
        }
        
    }
	if(sPro.bNotice)
	{
                Addr.pAddr = &sPro.addrNotice;
				Addr.str   = getItemName();
		Addr.str += QObject::tr("-解锁通知地址");
                if(sPro.datatype == 0)
                {
                    Addr.type  = 0;
                }
                else
                {
                    Addr.type  = 1;
                }
		kb << Addr;
	}
    if(sPro.enableVisable)
    {
        if(!sPro.byGroups_V)                                                //选择了受地址控制
        {
            Addr.pAddr = &sPro.address_V;
			Addr.str   = getItemName();
            Addr.str   += QObject::tr("-显现权限控制地址");
            Addr.type  = sPro.addrType_V;
            kb << Addr;
        }
    }
    return kb;
}

void QVisableItem::SaveSecurityPro(securityPro *pro)
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

QString  QVisableItem::getItemName()
{
    return QObject::tr("");
}
void QVisableItem::save(QDataStream &stream)
{
    QItemGroup::save(stream);

    //在此添加保存权限页面属性代码
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


void QVisableItem::load(QDataStream &stream)
{
    QItemGroup::load(stream);

    //在此添加载入权限页面属性代码
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
