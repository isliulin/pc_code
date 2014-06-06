#include "qprogectmanager.h"
#include "mainwindow.h"
#include <fstream>
#include <string>
#include <iostream>
#include <QProcess>
#include "Macro/macro.h"
#include "Frame/TreeCtrlDlg/schedulers.h"
using namespace std;
#define  DATARECIPE_NAME            "recipe.dat"
extern MainWindow *pwnd;
/**************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: Keyboard class implementation.
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2011-6-29        Tang             Edit.
 *************************************************************/
#define MAX_CTL_BY_BIT_LIST           200
#define MAX_HMI_PROTECT_LIST          10
#define MAX_HISTORY_SAMPLE_LIST       32
#define MAX_PLC_COMMU_LIST            5
#define MAX_INIT_MARO_LIST            64
#define MAX_GLOBAL_MARO_LIST          128
#define MAX_DATA_TRANS_LIST           200
#define MAX_DIGITAL_ALARM_LIST        64
#define MAX_ANALOG_ALARM_LIST         64
#define MAX_KEYBOARD_LIST             100

Keyboard::Keyboard()
{
    nConnectType = 0;
    nPlcRegTypeIndex = 0;
    nPlcStationIndex = 0;
    nAddrType = 0;
    sShowAddr = "LB0";
    sPlcAddrValue = "";
    sPlcRegTypeStr = "LB";
    Length = 1;
}
Keyboard& Keyboard::operator =(const int n)
{
    if(n==0)
    {
        nConnectType = 0;
        nPlcRegTypeIndex = 0;
        nPlcStationIndex = 0;
        nAddrType = 0;
        sShowAddr = "LB0";
        sPlcAddrValue = "";
        sPlcRegTypeStr = "LB";
        sPlcName = "";
        Length = 1;
    }
return *this;
}
Keyboard& Keyboard::operator=(const Keyboard &souceObj)
{
    if(this == &souceObj) return *this;
    nConnectType = souceObj.nConnectType;
    nPlcRegTypeIndex = souceObj.nPlcRegTypeIndex;
    nPlcStationIndex = souceObj.nPlcStationIndex;
    nAddrType = souceObj.nAddrType;
    sShowAddr = souceObj.sShowAddr;
    sPlcAddrValue = souceObj.sPlcAddrValue;
    sPlcRegTypeStr = souceObj.sPlcRegTypeStr;
    Length = souceObj.Length;
    sPlcName = souceObj.sPlcName;
    return *this;
}

//count ������id
//itemId ����item��id
void Keyboard::compile(QSqlDatabase &db,ADDR_PARAMENTS paraments)
{
    //QMap<QString,QVariant> mapQuery;
    //qDebug() << "compile" << sShowAddr;
	QStringList variables = pwnd->m_LocalReg.keys(); 
	if (variables.contains(sShowAddr,Qt::CaseInsensitive))
	{
		QString regStr;
		foreach(QString sReg,variables)
		{
			if(sReg.compare(sShowAddr,Qt::CaseInsensitive) == 0)
			{
				regStr = sReg;
				break;
			}
		}
		Keyboard kb;
		pwnd->CheckString(kb,pwnd->m_LocalReg.value(regStr),nAddrType);
        kb.Length = Length;
		kb.compile(db,paraments);
		return ;
	}
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO addr(eItemType ,nAddrId,nItemId ,nAddrNum ,eConnectType,nUserPlcId ,sPlcProtocol ,"
                        "nPlcStationIndex ,nPlcRegIndex ,nPlcStartAddr ,nAddrLen , eRwLevel)"
                        "VALUES (:eItemType,:nAddrId,:nItemId,:nAddrNum ,:eConnectType ,:nUserPlcId,:sPlcProtocol ,"
                        ":nPlcStationIndex,:nPlcRegIndex,:nPlcStartAddr,:nAddrLen, :eRwLevel)");
    sqlquery.bindValue(":eItemType",QVariant(paraments.eType));// ����item����
    sqlquery.bindValue(":nAddrId",QVariant(paraments.id));// �� id
    sqlquery.bindValue(":nItemId",QVariant(paraments.itemId));// ����item id
    sqlquery.bindValue(":nAddrNum",QVariant(paraments.addrNum));
    sqlquery.bindValue(":eRwLevel",QVariant(paraments.eRWtype));//��д����
    
    

    QStringList addrs;
    addrs << "LB" << "LW" <<"RWI"<<"LS";
    int index = 0;
    QString sPlc;
	stConnect cConnect;//��ǰ������
	stProtocol cModel;// ��ǰ��Э��
	int value;
    int nPlcIndex = 0;
    int regIndex = 0;
    if(nConnectType == 0)
    {
        regIndex = addrs.indexOf(sPlcRegTypeStr.toUpper());
        sqlquery.bindValue(":sPlcProtocol",QVariant("local"));// PLC����
		value = sPlcAddrValue.toInt();
        sqlquery.bindValue(":nPlcStationIndex",QVariant(1));
        sqlquery.bindValue(":eConnectType",QVariant(1));//��������
        sqlquery.bindValue(":nUserPlcId",QVariant(0));//Э���
    }
    else
    {
		bool bExist = false;
		

		foreach (stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
        {
			foreach(stProtocol ptl,cnt.vProtocols)
			{
				nPlcIndex++;
				if (ptl.sName.compare(sPlcName,Qt::CaseInsensitive) == 0)
				{
					bExist = true;
					cModel = ptl;
					break;
				}
			}
			if (bExist)
			{
				cConnect = cnt;
				break;
			}
		}
		int nCom= 0;
		switch (cConnect.eConnectPort)
		{
		case 0:
#ifdef AKPLC
        nCom = 4;
#else
        nCom = 3;
#endif
			break;
		case 1:
			nCom = 4;
			break;
		case 2:
            nCom = 5;
			break;
        case 3:
            nCom = 8;
            break;
        case 4:
            nCom = 14;
            break;
        case 5:
            nCom = 15;
            break;
		}
        sqlquery.bindValue(":eConnectType",QVariant(nCom));//��������

                
        index = cModel.mPlc.regs.indexOf(sPlcRegTypeStr);
        sqlquery.bindValue(":sPlcProtocol",QVariant(cModel.sProtocolName));// PLC����
        regIndex = index;
        value = getAddrValue(cModel,regIndex);
        sqlquery.bindValue(":nPlcStationIndex",QVariant(cModel.nPlcNo));// PLCջ��
        sqlquery.bindValue(":nUserPlcId",QVariant(nPlcIndex));//Э���

		//���ַ�ռ�vector����ӵ�ǰ��ַ����Ϣ
		addrTargetProp addrPrarm;
		addrPrarm.nUserPlcId = nPlcIndex;
		addrPrarm.nAddrValue = value;
		addrPrarm.nRegIndex = index;
		addrPrarm.nPlcStationIndex = cModel.nPlcNo;
		addrPrarm.nAddrLen = Length;
        addrPrarm.eAddrRWprop = paraments.eRWtype;
        switch(paraments.eRWtype)
        {
        case SCENE_CONTROL_ONCE_W:
        case SCENE_CONTROL_LOOP_W:
        case GLOBAL_ONCE_W:
        case GLOBAL_LOOP_W:
        case MACRO_ONCE_W:
        case MACRO_LOOP_W:
            break;
        default:
            if (paraments.eType != OBJ_RECIPE && paraments.eType != OBJ_OTHER)
			{
				pwnd->addrsInScene.insert(sPlcName,addrPrarm);
			}
            
            break;
        }
		
    }
	

    sqlquery.bindValue(":nPlcRegIndex",QVariant(regIndex));//��Ҫת��
	
    sqlquery.bindValue(":nPlcStartAddr",QVariant(value));// PLC��ʼ��ַ
    sqlquery.bindValue(":nAddrLen",QVariant(Length));// ��ַ����
    bool result = false;
    result = sqlquery.exec();
    qDebug() << "insert addr table :"<<result;
    qDebug() << "compile end" << sShowAddr;

	
}
int Keyboard::getAddrValue(stProtocol model,int &index)
{	  
    QString path = "Drivers/qtdll/"+model.sFactoryName +"/"+model.sProtocolName+".dll";
    QLibrary lib(path);
    
    if(index <0)
        return 0;

    if(lib.load())
    {
        typedef bool (*ADDPROC)(ADDR_CHECK_SOURCE_PROP , ADDR_TARGET_PROP &);
        ADDPROC getValue= (ADDPROC)lib.resolve("addrStringToInt");
        if(getValue)
        {
            ADDR_CHECK_SOURCE_PROP spro;
            spro.nAddrLen = Length;
            spro.sRegName = model.mPlc.regs.at(index).toStdString();
            spro.eAddrRWprop = SCENE_CONTROL_ONCE_W;
            spro.nPlcStationIndex = model.nPlcNo;
            spro.sAddrValue = sPlcAddrValue.toStdString();
            ADDR_TARGET_PROP tpro;
            if(getValue(spro,tpro))
            {
                index = tpro.nRegIndex;
                return tpro.nAddrValue;
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}
bool  Keyboard::getCurrentModel(stProtocol &cModel,stConnect &cConnect)
{
	bool bExist = false;
	if (nConnectType != 0)
	{
		foreach (stConnect cnt,pwnd->m_pSamSysParame->m_qvcConnect)
		{
			foreach(stProtocol ptl,cnt.vProtocols)
			{
				if (ptl.sName.compare(sPlcName,Qt::CaseInsensitive) == 0)
				{
					bExist = true;
					cModel = ptl;
					break;
				}
			}
			if (bExist)
			{
				cConnect = cnt;
				break;
			}
		}
	}
	return bExist;
}

void Keyboard::refreshShowAddr()
{
	QString header = "["+sPlcName+"]";
	if (nConnectType == 0)
	{
		header = "";
	}
	QStringList variables = pwnd->m_LocalReg.keys(); 
	if (!variables.contains(sShowAddr,Qt::CaseInsensitive))
	{
		sShowAddr = header+sPlcRegTypeStr+sPlcAddrValue;
	}
	
}
QVector <ADDR_CHECK_SOURCE_PROP> Keyboard::getMultiAddrs(int nInterval,int count)
{
	QStringList variables = pwnd->m_LocalReg.keys(); 
	if (variables.contains(sShowAddr,Qt::CaseInsensitive))
	{
		nInterval = 0;
	}
	QVector <ADDR_CHECK_SOURCE_PROP> vAddrs;
	std::vector <ADDR_CHECK_SOURCE_PROP> std_Vaddrs;
	
	stProtocol model;
	stConnect cnt;

	ADDR_CHECK_SOURCE_PROP spro;
	spro.nAddrLen = Length;
	spro.eAddrRWprop = SCENE_CONTROL_ONCE_W;
	spro.sAddrValue = sPlcAddrValue.toStdString();

	if (nConnectType == 0)//�ڲ���ַ
	{
		QStringList addrs;
		int nValue = sPlcAddrValue.toInt();

		addrs << "LB" << "LW" <<"RWI"<<"LS";
        spro.sRegName = sPlcRegTypeStr.toStdString();
		spro.nPlcStationIndex = 1;

        for (int i=1; i<=count; i++)
		{
			QString sValue;
            int addValue = nValue+i*nInterval;
            if(addValue > 65535)
            {
                addValue = 65535;
            }
            if(addValue < 0)
            {
                addValue = 0;
            }
            sValue = QString::number(addValue);
			spro.sAddrValue = sValue.toStdString();
			vAddrs << spro;
		}
		return vAddrs;
	}
	if (!getCurrentModel(model,cnt))
	{
		vAddrs.resize(count);
		return vAddrs;
	}
	
    QString path = "Drivers/qtdll/"+model.sFactoryName +"/"+model.sProtocolName+".dll";
	QLibrary lib(path);

	int index = model.mPlc.regs.indexOf(sPlcRegTypeStr);
	if(lib.load())
	{
		typedef ADDR_CHECK_ERROR_INFO (*ADDPROC)(ADDR_CHECK_SOURCE_PROP ,
			vector<ADDR_CHECK_SOURCE_PROP > &,int,int);
		ADDPROC getAddrs= (ADDPROC)lib.resolve("addrsMutilCopy");
		if(getAddrs)
		{
            spro.sRegName = sPlcRegTypeStr.toStdString();
			spro.nPlcStationIndex = model.nPlcNo;
			
			getAddrs(spro,std_Vaddrs,nInterval,count);
			vAddrs= vAddrs.fromStdVector(std_Vaddrs);
            ADDR_CHECK_SOURCE_PROP lastOne;
			if (vAddrs.size() >0)
			{
				lastOne = vAddrs.last();
			}
			else
			{
				lastOne.nAddrLen = Length;
				lastOne.eAddrRWprop = SCENE_CONTROL_ONCE_W;
				lastOne.sAddrValue = sPlcAddrValue.toStdString();
			}
            int retSize = vAddrs.size();
            for(int i=retSize; i<count; i++)
            {
                vAddrs << lastOne;
            }
            vAddrs.resize(count);
			return vAddrs;
			
		}
	}

	vAddrs.resize(count);
	return vAddrs;

}

QVector <Keyboard> Keyboard::copyAddrs(int nIntervl,int count)
{
    Keyboard kb = *this;
    QVector <Keyboard> Vaddrs;

    QVector<ADDR_CHECK_SOURCE_PROP> multiAddrs = kb.getMultiAddrs(nIntervl,count);
    foreach(ADDR_CHECK_SOURCE_PROP addrPro,multiAddrs)
    {
        kb.sPlcAddrValue = QString::fromStdString(addrPro.sAddrValue);
        kb.refreshShowAddr();
        Vaddrs<< kb;
    }
    return Vaddrs;
}
QDataStream &operator<<(QDataStream &stream, Keyboard &keyBoard)
{
    stream << keyBoard.sShowAddr << keyBoard.nConnectType;
    stream << keyBoard.nPlcRegTypeIndex << keyBoard.nPlcStationIndex;
    stream << keyBoard.sPlcAddrValue << keyBoard.sPlcRegTypeStr;
    stream << keyBoard.nAddrType;
    stream << keyBoard.Length;
    stream << keyBoard.sPlcName;

    return stream;
}

QDataStream &operator>>(QDataStream &stream, Keyboard &keyBoard)
{
    stream >> keyBoard.sShowAddr >> keyBoard.nConnectType;
    stream >> keyBoard.nPlcRegTypeIndex >> keyBoard.nPlcStationIndex;
    stream >> keyBoard.sPlcAddrValue >> keyBoard.sPlcRegTypeStr;
    stream >> keyBoard.nAddrType;
    stream >> keyBoard.Length;
    stream >> keyBoard.sPlcName;

    return stream;
}

/**************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2010
 *
 * Description: QSamSysParame class implementation.
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2011-6-29        Tang             Edit.
 *************************************************************/
QSamSysParame::~QSamSysParame()
{
    //if(process)
    //{
    //    process->deleteLater();
    //}
    if(schedulers)
    {
        delete schedulers;
    }
}

QSamSysParame::QSamSysParame()
{
    //process = NULL;
    //process = new QProcess();

    nUserDefKeyboardCount = 0;
    /*init FILE_PROTECT_PROP struct*/
    m_fileProtect.bNeedFileProtect = false;
    m_fileProtect.sProtectPWD = "";

    /*init PROJECT_PROP struct*/
    m_projectProp.bAccessOperate = false;
    m_projectProp.bHaveAlarmVoice = false;
    m_projectProp.bHaveTouchVoice = true;
    m_projectProp.bHideMouse = true;
    m_projectProp.bLoadInitScene = false;
    m_projectProp.bNeedUpLoad = false;
    m_projectProp.bNeedUploadCom = true;
    m_projectProp.bScreensaver = false;
    m_projectProp.bTIPicTransparent = false;
    m_projectProp.bTouchInvalidPic = false;
    m_projectProp.bUploadComNeedPWD = false;
    m_projectProp.bAlarmCoruscate = false;
    m_projectProp.bUseHighLevelPWD = false;
    m_projectProp.nDisplayMode = 0;
    m_projectProp.nDefautUserId = 0;
    m_projectProp.nFlickerFqc = 10;
    m_projectProp.nLoadSceneIndex = 0;
    m_projectProp.nLoadSceneTime = 1;
    m_projectProp.nNoDataCharFlag = 0;
    m_projectProp.nNoDataValueFlag = 0;
    m_projectProp.nPicFilePathIndex = 0;
    m_projectProp.nSceneHeight = 600;
    m_projectProp.nSceneWidth = 800;
    m_projectProp.nScreensaverIndex = 0;
    m_projectProp.nScreensaverTimer = 1;
    m_projectProp.nSetFloatProp = 1;//��ʼ��Ϊ1
    m_projectProp.nSetFloatType = 1;//��ʼ��Ϊ1
    m_projectProp.nStartScreenIndex = 0;

    m_projectProp.bClearHisAlarm=1;
    m_projectProp.bStratScreen=1;
    m_projectProp.bClearHisData=1;
    m_projectProp.bDownLoadRecipe=1;
    m_projectProp.nHisdataSave = 0;
    m_projectProp.nHisAlarmSave = 0;
    m_projectProp.nScreenPictureSave = 0;
    m_projectProp.nDownLoadPicCheck = 1;
    m_projectProp.sHisdataPath.clear();
    m_projectProp.sHisAlarmPath.clear();
    m_projectProp.sScreenPicturePath.clear();
    m_projectProp.sHighLevelPWD = "";
    m_projectProp.sPjtFilePath = "";
    m_projectProp.sPjtModel = "";
    m_projectProp.sTIPicPathList.clear();
    m_projectProp.sUploadComPWD = "";
    m_projectProp.mTIPicColor = QColor(0,0,0);
    m_projectProp.cAlarmBackColor = QColor(255,0,0);
    m_projectProp.sBackupForNewVer.clear();
    m_projectProp.sBackupForNewVer.append("0");    //at(0)---"0"��ʾĬ�ϲ��ô�������������1����ʾ���������� add by Dylan 2011-12-12
    m_projectProp.sBackupForNewVer.append("255+255+255");//at(1)---ϵͳ��������ɫ add by Dylan 2011-12-19
    m_projectProp.sBackupForNewVer.append("0+0+0");//at(2)---ϵͳ�����ı���ɫ add by Dylan 2011-12-19
    m_projectProp.sBackupForNewVer.append("����"); //at(3)---ϵͳ�������� add by Dylan 2011-12-19
    m_projectProp.sBackupForNewVer.append("10");//at(4)---ϵͳ���������Сadd by Dylan 2011-12-19
    m_projectProp.sBackupForNewVer.append("0");//at(5)---ϵͳ������ʾ��ʽ 0-ʼ����ʾ 1-������ʾ add by Dylan 2011-12-19
    m_projectProp.sBackupForNewVer.append("0");//at(6)---ϵͳ����������λ�� 0-����  1-�ײ� add by Dylan 2011-12-19
    m_projectProp.sBackupForNewVer.append("0");//at(7)---�Ƿ�ʹ��ϵͳ���� add by Dylan 2011-12-19
    /*init user level*/
    for(int i = 0; i< 8; i++)
    {
        QString sUserId;
        sUserId.setNum(i+1);
        m_projectProp.mUserLevelList[i].bSelect = false;
        m_projectProp.mUserLevelList[i].sUserName =  "user" + sUserId;
        m_projectProp.mUserLevelList[i].sUserPWD = QString("%1%2%3%4").arg(sUserId).
                                                   arg(sUserId).arg(sUserId).arg(sUserId);

        for(int j = 0; j < 8; j++)
        {
            if(j <= i)
            {
                m_projectProp.mUserLevelList[i].bUserLevelList[j] = true;
            }
            else
            {
                m_projectProp.mUserLevelList[i].bUserLevelList[j] = false;
            }
        }
    }
    /*init HMI_PRINTER_PROP struct*/
    m_projectProp.mPrinterProp.bPrintCharModel = false;
    /*...........*/

    //czq
    /*init GlobalVariable struct*/
    //--------����ѡ��
    m_mixGlobalVar.m_strModelName       = "";           //��������
    m_mixGlobalVar.m_eScreenDir         = scrHorizontal;//��Ļ����
    m_mixGlobalVar.m_strModelSize       = "";           //��Ļ�ߴ�
    m_mixGlobalVar.m_strResolution      = "";           //�ֱ���
    m_mixGlobalVar.m_strColor           = "";           //ɫ��
    m_mixGlobalVar.m_strUsermemory      = "";           //�û��ڴ�
    m_mixGlobalVar.m_strNandFlash       = "";           //
    m_mixGlobalVar.m_strPowersupply     = "";           //�����Դ
    m_mixGlobalVar.m_strCom1            = "";           //com1
    m_mixGlobalVar.m_strCom2            = "";           //com2
    m_mixGlobalVar.m_strUsb             = "";           //USB
    m_mixGlobalVar.m_strMaxscreennumber = "";           //��̫��
    m_mixGlobalVar.m_nScreenWidth       = 800;          //�ֱ��ʿ�
    m_mixGlobalVar.m_nScreenHeight      = 480;          //�ֱ��ʸ�
    m_mixGlobalVar.m_strHmiName         = "";           //hmi
    //--------��ʾ����
    m_mixGlobalVar.m_bUseLogo           = false;        //�Ƿ�ʹ������Logo����
    m_mixGlobalVar.m_sLogoNum           = "";            //��������
    m_mixGlobalVar.m_strLogoNum         = "";           //��������Logo���������
    m_mixGlobalVar.m_bStandby           = false;        //�Ƿ����ô���ģʽ
    m_mixGlobalVar.m_bStandbyMode       = true;         //������ʽ,���ʾ��Ļ����
    m_mixGlobalVar.m_sStandbyNum        = "";
    m_mixGlobalVar.m_strStandbyNum      = "";           //��������(�������������) ������
    m_mixGlobalVar.m_eStandbyLight      = LightNull;    //��������
    m_mixGlobalVar.m_nScreenTime        = 1;            //��������ʱ��(��)
    m_mixGlobalVar.m_bStandbyLogin      = false;        //����ע����¼
    m_mixGlobalVar.m_sInitNum           = "";           //��ʼ�������ã�����ţ�
    m_mixGlobalVar.m_nRecipeIndex       = 0;            //��ǰ�䷽��
    m_mixGlobalVar.m_nRecipeNum         = 0;            //��ǰ�䷽��
    m_mixGlobalVar.m_nFlickRate         = 0;            //��˸Ƶ��
    m_mixGlobalVar.m_bLockIcon          = true;
    //--------��������
    m_mixGlobalVar.m_bTouchVoice        = true;         //�Ƿ�����������
    m_mixGlobalVar.m_autoLogin          = false;        //�Ƿ��Զ���¼
    m_mixGlobalVar.m_bMultiVisitor      = false;        //�Ƿ�������˷���Զ�̼��
    m_mixGlobalVar.m_strMonitor         = "";           //�������
    m_mixGlobalVar.m_nMonitorPort       = 743;          //Զ�̼�ض˿ں�
    //--------���ݿ���
    m_mixGlobalVar.m_bCurScreenNum      = false;        //�Ƿ�ǰ������
    m_mixGlobalVar.m_bCurFormulaNum     = false;        //�Ƿ�ǰ�䷽���
    m_mixGlobalVar.m_bCurLanguageNum    = false;        //�Ƿ�ǰ���Ա��
    m_mixGlobalVar.m_bWordAddrScreenNum = false;        //�Ƿ��ֵ�ַ���ƻ����л����
    m_mixGlobalVar.m_bBitSenceExch      = false;        //�Ƿ�λ��ַ��ʾ����
    m_mixGlobalVar.m_vecBitSence.clear();
    Keyboard myKey;
    myKey.sPlcRegTypeStr = "LW";
    myKey.sShowAddr = "LW0";
    m_mixGlobalVar.m_keyCurScreen       = myKey;         //��ǰ�����ַ���
    m_mixGlobalVar.m_keyCurFormula      = myKey;        //��ǰ�䷽��ַ���
    m_mixGlobalVar.m_keyCurLanguage     = myKey;       //��ǰ���Ե�ַ���
    m_mixGlobalVar.m_keyWordAddrScreen  = myKey;    //�ֵ�ַ���ƻ����л����
    //--------�û�Ȩ��
    m_mixGlobalVar.m_vecUser.clear();
    m_mixGlobalVar.m_vecGroup.clear();

    UserPermiss     user0;
    GroupPermiss    group0;

    user0.m_strName     = QObject::tr("Ĭ���û�");
    user0.m_strDescrip  = QObject::tr("���û���ֹɾ��");
    user0.m_strPassword = "";

    group0.m_strName    = QObject::tr("Ĭ����");
    group0.m_strDescrip = QObject::tr("�����ֹɾ��");
    group0.m_bNeedAdmin = false;

    Admin administrator;
    administrator.m_strUser = user0.m_strName;
    administrator.m_bIsAdmin = false;
    group0.m_vecMember.push_back(administrator);

    m_mixGlobalVar.m_vecGroup.push_back(group0);
    m_mixGlobalVar.m_vecUser.push_back(user0);

    //--------��ӡ��
    m_mixGlobalVar.m_ePrinter           = Type_1;       //��ӡ��֧���ͺ�
    //--------����������
    m_mixGlobalVar.m_eDownload          = UsbDownload;  //���ط�ʽ
    m_mixGlobalVar.m_nIp1               = 0;            //IP��ַ
    m_mixGlobalVar.m_nIp2               = 0;            //
    m_mixGlobalVar.m_nIp3               = 0;            //
    m_mixGlobalVar.m_nIp4               = 0;            //
    m_mixGlobalVar.m_nPort              = 8000;         //�˿ں�
    m_mixGlobalVar.m_ePicMode           = SavePicJPEG;  //ͼƬ�����ʽ
    m_mixGlobalVar.m_bStartHMI          = false;        //���غ�����HMI
    m_mixGlobalVar.m_bClearData         = true;        //����ʱ�����ʷ����
    m_mixGlobalVar.m_bClearAlarm        = true;        //����ʱ�����ʷ��������
    m_mixGlobalVar.m_bWriteFormula      = true;        //����ʱд���䷽
    m_mixGlobalVar.m_bUpLoad            = true;        //�Ƿ���������
    m_mixGlobalVar.m_bUploadPassword    = false;        //������Ҫ����
    m_mixGlobalVar.m_strUploadPassword  = "";           //��������
    //--------���ʼ���
    m_mixGlobalVar.m_bEncryAccess       = false;         //�Ƿ����÷��ʼ���
    m_mixGlobalVar.m_strAccessPassword  = "";           //��������
    //--------��Ʒ��Ȩ
    m_mixGlobalVar.m_eAuthMode          = AuthForever;  //��Ʒ��Ȩ��ʽ
    m_mixGlobalVar.m_eTimeStyle         = ATimeOut;     //��Ȩʱ�䷽ʽ
    //m_mixGlobalVar.m_strTimeout         = "";           //��ʱ�����ַ���
    for(int i = 0; i < 5; i++)
    {
        m_mixGlobalVar.m_bIsUseDay[i]          = false;
        m_mixGlobalVar.m_strTimeoutDay[i]      = "";
        m_mixGlobalVar.m_nUseDay[i]            = 0;            //ʹ������
        m_mixGlobalVar.m_sUseDayPassword[i]    = "";           //ʹ����������
    }
    QDateTime date = QDateTime::currentDateTime();
    for(int i = 0; i < 5; i++)
    {
        m_mixGlobalVar.m_bIsUseDate[i]      = false;
        m_mixGlobalVar.m_strTimeoutDate[i]  = "";
        m_mixGlobalVar.m_gDateTime[i]       = date;
        m_mixGlobalVar.m_strDate[i]         = "";
    }
    //--------��������
    m_mixGlobalVar.m_nLanNum            = 1;            //��������
    m_mixGlobalVar.m_nCurLan            = 0;            //��ǰ���Ժ�
    m_mixGlobalVar.m_vecLanguageNameList.clear();       //���������б�
    //m_mixGlobalVar.m_vecLanguageNameList.append("language1");
    m_mixGlobalVar.m_vecLanguageNameList.push_back(QObject::tr("����"));

    /*init WRITE_HMIINFO_TO_PLC struct*/
    Keyboard initKeyboard;
    m_wHmiInfoToPlc.bWCurrLangageId = false;
    m_wHmiInfoToPlc.bWCurrRecipeId = false;
    m_wHmiInfoToPlc.bWCurrSceneId = false;
    m_wHmiInfoToPlc.bWCurrUserId = false;
    m_wHmiInfoToPlc.mLangageIdAddr = initKeyboard;
    m_wHmiInfoToPlc.mRecipeIdAddr = initKeyboard;
    m_wHmiInfoToPlc.mSceneIdAddr = initKeyboard;
    m_wHmiInfoToPlc.mUserIdAddr = initKeyboard;
    m_wHmiInfoToPlc.sBackupForNewVer.clear();

    /*init CTL_BY_PLC struct*/
    m_ctlByPlc.bBitCtlSceneSwitch = false;
    m_ctlByPlc.bCtlCurrUserId = false;
    m_ctlByPlc.bCtlRecipeChange = false;
    m_ctlByPlc.bCtlWriteRecipe = false;
    m_ctlByPlc.bWordCtlSceneSwitch = false;
    m_ctlByPlc.mChangeRecipeAddr = initKeyboard;
    m_ctlByPlc.mCtlUserIdAddr = initKeyboard;
    m_ctlByPlc.mSceneCtlByBitList.clear();;
    m_ctlByPlc.mSceneCtlByWAddr = initKeyboard;
    m_ctlByPlc.mWriteRecipeAddr = initKeyboard;
    m_ctlByPlc.sBackupForNewVer.clear();

    /*init TREE_CLOCK_PROP struct*/
    m_clockProp.bDownLoadTime = false;
    m_clockProp.bRTimeFromPlc = false;
    m_clockProp.bWTimeToPlc = false;
    m_clockProp.mRTimeFromPlc.mCtlAddr = initKeyboard;
    m_clockProp.mRTimeFromPlc.mTriggerAddr = initKeyboard;
    m_clockProp.mRTimeFromPlc.nAddrLen = 7;
    m_clockProp.mRTimeFromPlc.nDataType = 0;
    m_clockProp.mRTimeFromPlc.nStartType = 0;
    m_clockProp.mRTimeFromPlc.nTimeInterval = 60;
    m_clockProp.mRTimeFromPlc.bReset = false;
    m_clockProp.mWTimeToPlc.mCtlAddr = initKeyboard;
    m_clockProp.mWTimeToPlc.mTriggerAddr = initKeyboard;
    m_clockProp.mWTimeToPlc.nAddrLen = 7;
    m_clockProp.mWTimeToPlc.nDataType = 0;
    m_clockProp.mWTimeToPlc.nStartType = 0;
    m_clockProp.mWTimeToPlc.nTimeInterval = 60;
    m_clockProp.mWTimeToPlc.bReset = false;
    m_clockProp.sBackupForNewVer.clear();
    /*init HMI_PROTECT_PROP struct*/
    m_hmiProtectProp.bSelectHMIProtect = false;
    m_hmiProtectProp.nCurrentLevel = 1;
    m_hmiProtectProp.nTotalProtectNum = 1;
    m_hmiProtectProp.mProtectList.clear();
    m_hmiProtectProp.sBackupForNewVer.clear();
    HMI_PROTECT_SET initHmiSet;
    initHmiSet.sUnlockPWD = "0";
    initHmiSet.nProtectSceneId = 0;
    initHmiSet.mProtectDate = QDate::currentDate();
    initHmiSet.mProtectTime = QTime::currentTime();
    initHmiSet.sBackupForNewVer.clear();
    m_hmiProtectProp.mProtectList.push_back(initHmiSet);

    /*init LANGUAGE_PROP struct*/
    //m_languageProp.nTotalNum = 1;
    //m_languageProp.sLanguageNameList.clear();
    //m_languageProp.sLanguageNameList.push_back("language1");

    //czq
    /*init HISTORY_LOG_PROP struct*/
    /*m_historyLogData.bFullNotic = false;
    m_historyLogData.bFullStop = false;
    m_historyLogData.bHistoryDataExist = false;
    m_historyLogData.bAutoOff = false;
    m_historyLogData.sHistoryDataName = "��ʷ�����ռ���0";
    m_historyLogData.nFullNoticPercent = 90;
    m_historyLogData.nSampleLen = 1;
    m_historyLogData.nSampleSize = 1;
    m_historyLogData.nSampleType = 0;
    m_historyLogData.nTimeInterval = 1;
    m_historyLogData.nTriggerTime = 1;
    m_historyLogData.mFullNoticAddr = initKeyboard;
    m_historyLogData.mReadAddr = initKeyboard;
    m_historyLogData.mTriggerAddr = initKeyboard;
    m_historyLogData.mSampleList.clear();
    m_historyLogData.sBackupForNewVer.clear();
    m_historyLogData.sBackupForNewVer.append("22");//�ڴ�������*/

    /*init DATA_SAMPLING struct*/
    m_loadDataSampling.clear();
    m_vecDataSamplingStr.clear();//�������
    /*
    m_loadDataSampling.bContiguousAddr  = true;     //�Ƿ��������ĵ�ַ
    m_loadDataSampling.bFullNotic       = false;    //�Ƿ�ȡ��֪ͨ
    m_loadDataSampling.bAutoReset       = false;    //�Ƿ��Զ���λ
    m_loadDataSampling.bSaveToFile      = false;    //�Ƿ񱣴��ļ�
    m_loadDataSampling.bZeroSupp        = true;     //�Ƿ�������
    m_loadDataSampling.bZoomIn          = false;    //�Ƿ�����
    m_loadDataSampling.bRound           = true;     //�Ƿ���������
    m_loadDataSampling.bAddrCtlSamp     = false;    //λ��ַ�����Ƿ����
    m_loadDataSampling.bSampTime        = true;     //�Ƿ�Ƶ�ʲ���ʱ����Ϊ1��
    m_loadDataSampling.nDataLen         = 5;        //����λ��
    m_loadDataSampling.nDecimalLen      = 0;        //С������
    m_loadDataSampling.nStartHour       = 0;        //��ʼ��ʱ��0-23��
    m_loadDataSampling.nStartMinute     = 0;        //��ʼ�ķ֣�0-60��
    m_loadDataSampling.nEndHour         = 0;        //������ʱ��0-23��
    m_loadDataSampling.nEndMinute       = 0;        //�����ķ֣�0-60��
    m_loadDataSampling.nSampAddrLen     = 1;        //����������(�ֵ�ַ��������)
    m_loadDataSampling.nDigitLen        = 16;       //λ��
    m_loadDataSampling.eSampType        = SampCycle;//��������
    m_loadDataSampling.eDealSampFull    = SFStop;   //ȡ������ʽ
    m_loadDataSampling.eSaveMedium      = SM_Udisk; //�����ý��
    m_loadDataSampling.eDateShowType    = DateYMD;  //���ڸ�ʽ
    m_loadDataSampling.eDataType        = DataInt;  //��������
    //m_loadDataSampling.nTotalSampNum    = 20;       //�����������
    m_loadDataSampling.nSampRate        = 1;        //������Ƶ��
    m_loadDataSampling.nSampTimes       = 1;        //��������
    m_loadDataSampling.nSourceMin       = 0;        //����Դ������Сֵ
    m_loadDataSampling.nSourceMax       = 65535;    //����Դ�������ֵ
    m_loadDataSampling.nTargeMin        = 0;        //����Ŀ��������Сֵ
    m_loadDataSampling.nTargeMax        = 65535;    //����Ŀ���������ֵ
    m_loadDataSampling.strNoticAddrId   = initKeyboard;//��ַ֪ͨ��ID��
    m_loadDataSampling.strCtlSampAddrId = initKeyboard;//���Ʋ����ĵ�ַID��
    m_loadDataSampling.keyAddrBegin     = initKeyboard;//������ַ��ʱ�����ʼ��ַ
    m_loadDataSampling.keyCtlSaveAddr   = initKeyboard;//�����ļ��Ŀ��Ƶ�ַ
    m_loadDataSampling.m_dataTable.clear();         //���ݱ��
    */

    /*init RECIPE_PROP struct*/
    m_recipeProp.bRecipeExist = false;
    m_recipeProp.bRaddrSameWaddr = true;
    m_recipeProp.bRRecipeFromPlc = false;
    m_recipeProp.bWRecipeToPlc = false;
    m_recipeProp.nDataType = 0;
    m_recipeProp.nRecipeLen = 4;
    m_recipeProp.nRecipeTotalNum = 1;
    m_recipeProp.nSourceIdList.clear();
    m_recipeProp.nTargetIdList.clear();
    m_recipeProp.sCurrRecAddrRange = "RW1-RW4";
    m_recipeProp.sDescription = "";
    m_recipeProp.nLanIndex=0;
    m_recipeProp.sRecipeData.clear();
    m_recipeProp.sRecipeName.clear();
    m_recipeProp.sRecipeRegNum = "RWI0";
    m_recipeProp.sRecMemAddrRange = "RW1-RW4";
    m_recipeProp.sRowHeadName.clear();
    m_recipeProp.mRRecipeAddr = initKeyboard;
    m_recipeProp.mWRecipeAddr = initKeyboard;
    m_recipeProp.sBackupForNewVer.clear();
    //ip��ַ
    m_projectProp.nDownLoadType=0;
    m_projectProp.sDowndloadIP="0.0.0.0";
    m_projectProp.sPortNO="8000";
    /*init qvector list*/
    m_qvcPlcCommunicate.clear();
    m_qvcInitMaroProp.clear();
    m_qvcGlobalMaroProp.clear();
    m_qvcdataTransProp.clear();
    m_qvcAlarm.clear();
    m_qvcRecipe.clear();
    m_qRecipe.formula.clear();;
    m_qRecipe.sName = "";
    //pUserKeyboard_vector.clear();
    m_PowerProtect.startLB = 0;
    m_PowerProtect.lengthLB = 0;
    m_PowerProtect.startLW = 0;
    m_PowerProtect.lengthLW = 0;
    schedulers = new Schedulers();
}

void QSamSysParame::compile(QSqlDatabase &db, int &count,bool bSimulator)
{
    dataSamplingCompile(db, count);//���ݲɼ�
    SystemProcCompile(db, count,bSimulator);//ϵͳ����
    LanguageCompile(db, count);//���Ա�
    PasswordCompile(db,count);//�����
    UserRightCompile(db,count);//�û�Ȩ��
    connectCompile(db,count);//����
    alarmCompile(db,count);//����
    recipeCompile(db,count);//�䷽
    globalCompile(db,count);//ȫ�ֺ�
    initCompile(db,count);//��ʼ����
	datatransferCompile(db,count);//���ϴ���
	timesettingCompile(db,count);
    schedulerCompile(db,count);
}

const int DEFAULT_SET       = 0x00000000;//Ĭ������
const int VERTICAL_SHOW     = 0x00000001;//��ֱ��ʾ
const int USE_SAVER         = 0x00000002;//ʹ������
const int LOGOUT            = 0x00000004;//���������˳���¼
const int USE_TOUCH_SOUND   = 0x00000008;//ʹ�ô���������
const int WRITE_SCENE_ID    = 0x00000010;//�ѵ�ǰ����д��PLC
const int WRITE_RECIPE      = 0x00000020;//д��ǰ�䷽��
const int WRITE_LANGUAGE    = 0x00000040;//д��ǰ���Ժ�
const int WORD_CHANGE_SCENE = 0x00000080;//���л�����
const int UP_LOAD           = 0x00000100;//����������̬
const int UP_LOAD_USE_PWD   = 0x00000200;//������Ҫ����
const int HMI_PROTECT       = 0x00000400;//ʹ��ʱЧȨ��
const int AUTO_LOGIN       = 0x00000800;//�Զ���¼Ĭ���û�
const int MULTI_VISITOR     = 0x00001000; //Զ�̿��ƶ��˷���

void QSamSysParame::SystemProcCompile(QSqlDatabase &db,int &count,bool bSimulator)
{
    count++;

    int m_nSetBoolParam = 0x00000000;//����ϵͳ����
    if(m_mixGlobalVar.m_eScreenDir == scrVertical)//��Ļ��ֱ����
    {
        m_nSetBoolParam += VERTICAL_SHOW;
    }
    if(m_mixGlobalVar.m_bStandby)//�Ƿ����ô���ģʽ
    {
        m_nSetBoolParam += USE_SAVER;
    }
    if(m_mixGlobalVar.m_bStandbyLogin)//����ע����¼
    {
        m_nSetBoolParam += LOGOUT;
    }
    if(m_mixGlobalVar.m_bTouchVoice)//�Ƿ�����������
    {
        m_nSetBoolParam += USE_TOUCH_SOUND;
    }
    if(m_mixGlobalVar.m_bCurScreenNum)//�ѵ�ǰ����д��PLC
    {
        m_nSetBoolParam += WRITE_SCENE_ID;
    }
    if(m_mixGlobalVar.m_bCurFormulaNum)//д��ǰ�䷽��
    {
        m_nSetBoolParam += WRITE_RECIPE;
    }
    if(m_mixGlobalVar.m_bCurLanguageNum)//д��ǰ���Ժ�
    {
        m_nSetBoolParam += WRITE_LANGUAGE;
    }
    if(m_mixGlobalVar.m_bWordAddrScreenNum)//���л�����
    {
        m_nSetBoolParam += WORD_CHANGE_SCENE;
    }
    if(m_mixGlobalVar.m_bUpLoad)//����������̬
    {
        m_nSetBoolParam += UP_LOAD;
    }
    if(m_mixGlobalVar.m_bUploadPassword)//������Ҫ����
    {
        m_nSetBoolParam += UP_LOAD_USE_PWD;
    }
    if(m_mixGlobalVar.m_eAuthMode == AuthTime)//ʹ��ʱЧ��Ȩ
    {
        m_nSetBoolParam += HMI_PROTECT;
    }
    if(m_mixGlobalVar.m_autoLogin == true)//----ʹ��ʱЧ��Ȩ
    {
        m_nSetBoolParam += AUTO_LOGIN;
    }
    if(m_mixGlobalVar.m_bMultiVisitor == true)//----���˷���Զ�̼��
    {
        m_nSetBoolParam += MULTI_VISITOR;
    }
    QSqlQuery sqlquery(db);

    bool bSystemSure = false;
    bSystemSure = sqlquery.prepare("INSERT INTO systemProp("
            "nModel,sStartScreen,nScreenTime,bScreensaver,"
            "sScreenIndex,nFlickRate,nBrightness,nSetBoolParam,"
            "kWriteScreenAddr,kRecipeIndexAddr,kWriteLanguageAddr,"
            "kChangeScreenAddr,sUploadPassword,bProtectType,"
            "sProtectValue,nLanguageIndex,nRecipeGroupId,nRecipeIndex,nInitScreenId"
            ",nstartLB,nlengthLB,nstartLW,nlengthLW,bBitScene,bSimulator,bLockIcon,strMonitor,strHmiName,nMonitorPort,nPrinterType)"
      "VALUES(:nModel,:sStartScreen,:nScreenTime,:bScreensaver,"
            ":sScreenIndex,:nFlickRate,:nBrightness,:nSetBoolParam,"
            ":kWriteScreenAddr,:kRecipeIndexAddr,:kWriteLanguageAddr,"
            ":kChangeScreenAddr,:sUploadPassword,:bProtectType,"
            ":sProtectValue,:nLanguageIndex,:nRecipeGroupId,:nRecipeIndex,:nInitScreenId,"
            ":nstartLB,:nlengthLB,:nstartLW,:nlengthLW,:bBitScene,:bSimulator,:bLockIcon,:strMonitor,:strHmiName,:nMonitorPort,:nPrinterType)");

    qDebug() << "sqlquery.prepare " << bSystemSure << endl;

    int temp = count;
    sqlquery.bindValue(":nModel", QVariant(m_mixGlobalVar.m_strModelName));                 //�������ͺ�
    sqlquery.bindValue(":strHmiName", QVariant(m_mixGlobalVar.m_strHmiName));

    //��item���浽pixmap
    int lgNum = 0;
    //int temp = 0;
    int totalSize = pwnd->pSceneSheet.size();
    int X = 0;
    if(m_mixGlobalVar.m_sLogoNum != "" && m_mixGlobalVar.m_bUseLogo)
    {
        for(; X < totalSize; X++)
        {
            if(pwnd->pSceneSheet[X]->nIsSceneOrWindow == 0)
            {
                //temp++;
                if(m_mixGlobalVar.m_sLogoNum == pwnd->pSceneSheet[X]->sNewScreenName)
                {
                    lgNum = X;
                    break;
                }
            }
        }
    }

    if(X == totalSize || m_mixGlobalVar.m_sLogoNum == "" || !m_mixGlobalVar.m_bUseLogo)//��ʱɾ�����⸱����
    {
        sqlquery.bindValue(":sStartScreen", QVariant(""));
    }
    else
    {
        //QProcess *process = new QProcess();
        QString pathW = QDir::currentPath();

        QRectF rect;
        rect.setLeft(0);
        rect.setTop(0);
        rect.setWidth(pwnd->pSceneSheet[lgNum]->width());
        rect.setHeight(pwnd->pSceneSheet[lgNum]->height());
        //rect.setWidth(pwnd->pSceneSheet[m_mixGlobalVar.m_nLogoNum]->width());
        //rect.setHeight(pwnd->pSceneSheet[m_mixGlobalVar.m_nLogoNum]->height());
        QPixmap pixmap(rect.width(),rect.height());
        pixmap.fill(QColor(0,0,0,0));
        QPainter painter(&pixmap);
        QRectF target = QRectF(0,0,rect.width(),rect.height());
        rect = QRectF(rect.x(),rect.y(),rect.width()+1,rect.height()+1);
        //pwnd->pSceneSheet[m_mixGlobalVar.m_nLogoNum]->render(&painter,target,rect,Qt::IgnoreAspectRatio);
        pwnd->pSceneSheet[lgNum]->clearSelection();
        pwnd->pSceneSheet[lgNum]->render(&painter,target,rect,Qt::IgnoreAspectRatio);
        //tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);
        QString strLogo = "logo.png";
        QString newPath = "/data/data/com.android.Samkoonhmi/pictures/" + strLogo;
        QFile::remove("resource/logo.png");

        pixmap.save("resource/"+strLogo, "png");
        //sqlquery.bindValue(":sStartScreen", QVariant(m_mixGlobalVar.m_strLogoNum));             //�����������
        sqlquery.bindValue(":sStartScreen", QVariant(newPath));             //�����������

        QDir dir("usranipro/ani1");
        if(!dir.exists())
        {
            dir.mkdir(dir.absolutePath());
        }

        QString qstr1 = QString::number(m_mixGlobalVar.m_nScreenWidth);
        QString qstr2 = QString::number(m_mixGlobalVar.m_nScreenHeight);
        QString strLine = qstr1 + " "  + qstr2 + " " + "17" + "\n";
        strLine = strLine + "p";//�ڶ��е�һ��
        strLine = strLine + " ";
        strLine = strLine + "0";//�ڶ��еڶ���
        strLine = strLine + " ";
        strLine =  strLine + "0";//�ڶ��е�����
        strLine = strLine + " ";
        strLine = strLine + "ani1\n";
        ofstream fexe("usranipro/desc.txt",ios::binary);
        fexe.clear();
        fexe.write( strLine.toAscii().data(),strLine.length());
        fexe.close();
        qDebug() <<"usranipro/desc.txt1  " <<strLine;



        QFile::remove("usranipro/ani1/logo.png");
        QFile::remove("usranipro\\bootanimation.zip");
        if(!QFile::copy("resource/logo.png", "usranipro/ani1/logo.png"))
        {
            pwnd->information(QObject::tr("����logoͼƬ���Ʋ���ȷ"), MSG_WARNING);
            qDebug() << "error";
        }
        QString cDir = QDir::currentPath();
        cDir += "\\usranipro";
        QProcess process;
        process.setWorkingDirectory(cDir);
        process.start(QString("\"%1\\zip.exe\" -0 bootanimation.zip desc.txt -r ani1 ").arg(cDir));
        process.waitForFinished();

    }

    sqlquery.bindValue(":nScreenTime", QVariant(m_mixGlobalVar.m_nScreenTime));             //��Ļ������ʱ��
    sqlquery.bindValue(":bScreensaver", QVariant(m_mixGlobalVar.m_bStandbyMode));           //������ʾ��ʽ(��ʾָ�����棨true�������ȱ仯��false��

    int sbNum = 0;
    if(m_mixGlobalVar.m_sStandbyNum != "" && m_mixGlobalVar.m_bStandby && m_mixGlobalVar.m_bStandbyMode)
    {
        for(X = 0; X < totalSize; X++)
        {
            if(pwnd->pSceneSheet[X]->nIsSceneOrWindow == 0)
            {
                //temp++;
                if(m_mixGlobalVar.m_sStandbyNum == pwnd->pSceneSheet[X]->sNewScreenName)
                {
                    sbNum = X;
                    break;
                }
            }
        }
    }
    if(X == totalSize || m_mixGlobalVar.m_sStandbyNum == "" || !m_mixGlobalVar.m_bStandby || !m_mixGlobalVar.m_bStandbyMode)
    {
        sqlquery.bindValue(":sScreenIndex", QVariant(""));          //������ʾ�Ļ����
    }
    else
    {
        QRectF rect0;
        rect0.setLeft(0);
        rect0.setTop(0);
        rect0.setWidth(pwnd->pSceneSheet[sbNum]->width());
        rect0.setHeight(pwnd->pSceneSheet[sbNum]->height());
        //rect0.setWidth(pwnd->pSceneSheet[m_mixGlobalVar.m_nStandbyNum]->width());
        //rect0.setHeight(pwnd->pSceneSheet[m_mixGlobalVar.m_nStandbyNum]->height());
        QPixmap pixmap0(rect0.width(),rect0.height());
        pixmap0.fill(QColor(0,0,0,0));
        QPainter painter0(&pixmap0);
        QRectF target0 = QRectF(0,0,rect0.width(),rect0.height());
        rect0 = QRectF(rect0.x(),rect0.y(),rect0.width()+1,rect0.height()+1);
        pwnd->pSceneSheet[sbNum]->clearSelection();
        pwnd->pSceneSheet[sbNum]->render(&painter0,target0,rect0,Qt::IgnoreAspectRatio);
        //tmpScene.render(&painter,target,rect,Qt::IgnoreAspectRatio);
        QString strStandby = "standby.png";
        QString newPath0 = "/data/data/com.android.Samkoonhmi/pictures/" + strStandby;
        pixmap0.save("resource/"+strStandby, "png");
        //sqlquery.bindValue(":sScreenIndex", QVariant(m_mixGlobalVar.m_strStandbyNum));          //������ʾ�Ļ����
        sqlquery.bindValue(":sScreenIndex", QVariant(newPath0));          //������ʾ�Ļ����
    }

    sqlquery.bindValue(":nFlickRate", QVariant(m_mixGlobalVar.m_nFlickRate));               //��˸Ƶ�ʣ���λ��100ms,Ĭ����10*100ms��
    sqlquery.bindValue(":nBrightness", QVariant(m_mixGlobalVar.m_eStandbyLight));           //������������
    sqlquery.bindValue(":nSetBoolParam", QVariant(m_nSetBoolParam));                        //���ֲ������ã��鿴��������
    if(m_mixGlobalVar.m_bCurScreenNum)
    {
        temp++;
        sqlquery.bindValue(":kWriteScreenAddr", QVariant(temp));  //д�뵱ǰ�����ַId
    }
    if(m_mixGlobalVar.m_bCurFormulaNum)
    {
        temp++;
        sqlquery.bindValue(":kRecipeIndexAddr", QVariant(temp));  //д�뵱ǰ�䷽��ַId
    }
    if(m_mixGlobalVar.m_bCurLanguageNum)
    {
        temp++;
        sqlquery.bindValue(":kWriteLanguageAddr", QVariant(temp));//д�뵱ǰ���Ե�ַId
    }
    if(m_mixGlobalVar.m_bWordAddrScreenNum)
    {
        temp++;
        sqlquery.bindValue(":kChangeScreenAddr", QVariant(temp)); //�ֿ��ƻ����л���ַId
    }
    if(m_mixGlobalVar.m_bUploadPassword)
    {
        sqlquery.bindValue(":sUploadPassword", QVariant(m_mixGlobalVar.m_strUploadPassword));   //��������
    }
    else
    {
        sqlquery.bindValue(":sUploadPassword", QVariant(QString("")));   //��������
    }

    if(m_mixGlobalVar.m_eTimeStyle == ATimeOut)
    {
        sqlquery.bindValue(":bProtectType", QVariant(true));//ʱЧ��Ȩ��ʽ(��ʹ��ʱ�䣨true�� ���������ڣ�false��)
    }
    else
    {
        sqlquery.bindValue(":bProtectType", QVariant(false));//ʱЧ��Ȩ��ʽ(��ʹ��ʱ�䣨true�� ���������ڣ�false��)
    }
    sqlquery.bindValue(":sProtectValue", QVariant(""));            //��Ȩ��ֹ����ת�����ַ���
    sqlquery.bindValue(":nLanguageIndex", QVariant(m_mixGlobalVar.m_nCurLan));
    sqlquery.bindValue(":nRecipeGroupId", QVariant(m_mixGlobalVar.m_nRecipeIndex));//��ǰ������
    sqlquery.bindValue(":nRecipeIndex", QVariant(m_mixGlobalVar.m_nRecipeNum));           //��ǰ���䷽��
    sqlquery.bindValue(":bLockIcon", QVariant(m_mixGlobalVar.m_bLockIcon));
    sqlquery.bindValue(":strMonitor", QVariant(m_mixGlobalVar.m_strMonitor));
    sqlquery.bindValue(":nMonitorPort", QVariant(m_mixGlobalVar.m_nMonitorPort));
    //sqlquery.bindValue(":nInitScreenId", QVariant(m_mixGlobalVar.m_nInitNum + 1));//��������Ŵ�0��ʼΪ��ͬ����������ݣ���Ϊ��1��ʼ//��ʼ�����
    int screenNum = pwnd->copyScreen_Item->childCount();//�ܵĻ�����
    int initNum = 0;
    if(m_mixGlobalVar.m_sInitNum != "")
    {
        for(X = 0; X < screenNum; X++)
        {
            if(m_mixGlobalVar.m_sInitNum == pwnd->copyScreen_Item->child(X)->text(0).split(":").at(1))
            {
                initNum = X;
                break;
            }
        }
    }

    if(X == totalSize || m_mixGlobalVar.m_sInitNum == "")
    {
        sqlquery.bindValue(":nInitScreenId", QVariant(1));
        m_mixGlobalVar.m_sInitNum = pwnd->copyScreen_Item->child(0)->text(0).split(":").at(1);
    }
    else
    {
        sqlquery.bindValue(":nInitScreenId", QVariant(initNum + 1));
    }

    sqlquery.bindValue(":nstartLB", QVariant(m_PowerProtect.startLB));
    sqlquery.bindValue(":nlengthLB", QVariant(m_PowerProtect.lengthLB));//��ǰ������
    sqlquery.bindValue(":nstartLW", QVariant(m_PowerProtect.startLW));           //��ǰ���䷽��
    sqlquery.bindValue(":nlengthLW", QVariant(m_PowerProtect.lengthLW));//
    sqlquery.bindValue(":bBitScene", QVariant(m_mixGlobalVar.m_bBitSenceExch));//
    sqlquery.bindValue(":bSimulator", QVariant((short)bSimulator));//

    sqlquery.bindValue(":nPrinterType", QVariant((short)m_mixGlobalVar.m_ePrinter));//��ӡ������
    bool result = false;
    result = sqlquery.exec();
    qDebug() << "-------------qDebug qDebug qDebug :" << result << endl;

    ADDR_PARAMENTS stParams;
    stParams.itemId     = -1;
    stParams.eType      = OBJ_SYSPRARM;
    stParams.eRWtype    = GLOBAL_LOOP_R;
    stParams.addrNum    = -1;
    if(m_mixGlobalVar.m_bCurScreenNum)
    {
        count++;
        stParams.id         = count;
        stParams.itemId     = -1;
        stParams.eType      = OBJ_SYSPRARM;
        stParams.eRWtype    = GLOBAL_LOOP_W;
        stParams.addrNum    = -1;
        m_mixGlobalVar.m_keyCurScreen.compile(db, stParams);
    }

    if(m_mixGlobalVar.m_bCurFormulaNum)
    {
        count++;
        stParams.id         = count;
        stParams.eRWtype    = GLOBAL_LOOP_W;
        m_mixGlobalVar.m_keyCurFormula.Length = 2;
        m_mixGlobalVar.m_keyCurFormula.compile(db, stParams);
    }

    if(m_mixGlobalVar.m_bCurLanguageNum)
    {
        count++;
        stParams.id         = count;
        stParams.eRWtype    = GLOBAL_LOOP_W;
        m_mixGlobalVar.m_keyCurLanguage.compile(db, stParams);
    }

    if(m_mixGlobalVar.m_bWordAddrScreenNum)
    {
        count++;
        stParams.id         = count;
        stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
        m_mixGlobalVar.m_keyWordAddrScreen.compile(db, stParams);
    }

    if(m_mixGlobalVar.m_bBitSenceExch)
    {
        bool XXXX = false;
        XXXX = sqlquery.prepare("INSERT INTO bitScene("
                "nId,nStatus,nAddressId,nSceneId,bReset,bClose)"
                "VALUES(:nId,:nStatus,:nAddressId,:nSceneId,:bReset,:bClose)");
        qDebug() << "+++++++++++++++++++++ :" << XXXX << endl;

        int bitCount = m_mixGlobalVar.m_vecBitSence.size();
        if(0 == bitCount)
        {
            return;
        }
        for(int i = 0; i < bitCount; i++)
        {
            count++;
            sqlquery.bindValue(":nId", QVariant(count));
            sqlquery.bindValue(":nStatus", QVariant(m_mixGlobalVar.m_vecBitSence[i].nCtlStatus));
            sqlquery.bindValue(":nAddressId", QVariant(count + bitCount));

            int nScreenCount = pwnd->pSceneSheet.size();
            int k = 0;
            int senceXX;
            bool bHave = false;
            for(int j = 0; j < nScreenCount; j++)
            {
                if(pwnd->pSceneSheet[j]->nIsSceneOrWindow == 0 || pwnd->pSceneSheet[j]->nIsSceneOrWindow == 1)
                {
                    k++;
                    if(pwnd->pSceneSheet[j]->sNewScreenName == pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].sCtlSceneId)
                    {
                        senceXX = pwnd->pSceneSheet[j]->sNumberName.toInt()%1000;
                        bHave = true;
                        break;
                    }
                }
            }
            if(bHave)
            {
                sqlquery.bindValue(":nSceneId", QVariant(senceXX));
            }
            else
            {
                QString strWaring = pwnd->m_pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].sCtlSceneId;
                pwnd->information(strWaring + QObject::tr("�Ѿ�������..."), MSG_WARNING);
                sqlquery.bindValue(":nSceneId", QVariant(-1));
            }

            sqlquery.bindValue(":bReset", QVariant(m_mixGlobalVar.m_vecBitSence[i].bReset));
            sqlquery.bindValue(":bClose", QVariant(m_mixGlobalVar.m_vecBitSence[i].bClose));

            bool yyyy = false;
            yyyy = sqlquery.exec();
            qDebug() << "+++++++++++++++++++++ :" << yyyy << endl;
        }

        for(int j = 0; j < bitCount; j++)
        {
            count++;
            ADDR_PARAMENTS stParamsA;
            stParamsA.id      = count;
            stParamsA.itemId  = -1;
            stParamsA.eType   = OBJ_SYSPRARM;
            stParamsA.eRWtype = SCENE_CONTROL_LOOP_R;
            stParamsA.addrNum = -1;
            m_mixGlobalVar.m_vecBitSence[j].mCtlSceneAddr.compile(db, stParamsA);
        }
    }
}

void QSamSysParame::PasswordCompile(QSqlDatabase &db,int &count)//�����
{
    if(m_mixGlobalVar.m_eAuthMode == AuthTime)//ֻ����ʱ����Ȩʱ�������Ч
    {
        QSqlQuery sqlquery(db);

        QString strTemp;

        if(m_mixGlobalVar.m_eTimeStyle == AUseTime)//��ʹ��ʱ�����ʱ��
        {
            for(int i = 0; i < 5; i++)
            {
                if(m_mixGlobalVar.m_bIsUseDay[i])
                {
                    count++;

                    bool bDateSure = sqlquery.prepare("INSERT INTO hmiProtect(sPwdStr,sTimeLimit,bIsUse,sTimeOut)VALUES(:sPwdStr,:sTimeLimit,:bIsUse,:sTimeOut)");
                    qDebug() << "sqlquery.prepare " << bDateSure;

                    int temp = m_mixGlobalVar.m_nUseDay[i];
                    sqlquery.bindValue(":sPwdStr", QVariant(m_mixGlobalVar.m_sUseDayPassword[i]));//�ַ�������
                    sqlquery.bindValue(":sTimeLimit", QVariant(QString::number(temp)));
                    sqlquery.bindValue(":bIsUse", QVariant(false));//�ַ�������sTimeOut
                    sqlquery.bindValue(":sTimeOut", QVariant(m_mixGlobalVar.m_strTimeoutDay[i]));

                    bool result = false;
                    result = sqlquery.exec();
                    qDebug() << "0000000000000000:" << result << endl;
                }
            }
        }
        else
        {
            for(int i = 0; i < 5; i++)//����ֹ���ڼ���
            {
                if(m_mixGlobalVar.m_bIsUseDate[i])
                {
                    count++;
                    bool bDateSure = sqlquery.prepare("INSERT INTO hmiProtect(sPwdStr,sTimeLimit,bIsUse,sTimeOut)VALUES(:sPwdStr,:sTimeLimit,:bIsUse,:sTimeOut)");
                    qDebug() << "sqlquery.prepare " << bDateSure;

                    sqlquery.bindValue(":sPwdStr", QVariant(m_mixGlobalVar.m_strDate[i]));
                    strTemp = QString::number(m_mixGlobalVar.m_gDateTime[i].date().year()) + "/"
                            + QString::number(m_mixGlobalVar.m_gDateTime[i].date().month())+ "/"
                            + QString::number(m_mixGlobalVar.m_gDateTime[i].date().day())  + " "
                            + QString::number(m_mixGlobalVar.m_gDateTime[i].time().hour())  + ":"
                            + QString::number(m_mixGlobalVar.m_gDateTime[i].time().minute());// + ":"
                            //+ QString::number(m_mixGlobalVar.m_gDateTime[i].time().second());
                    sqlquery.bindValue(":sTimeLimit", QVariant(strTemp));//�ַ�������
                    sqlquery.bindValue(":bIsUse", QVariant(false));//�ַ�������
                    sqlquery.bindValue(":sTimeOut", QVariant(m_mixGlobalVar.m_strTimeoutDate[i]));

                    bool result = false;
                    result = sqlquery.exec();
                    qDebug() << "-------------qDebug qDebug qDebug :" << result << endl;
                }
            }
        }
    }
}

void QSamSysParame::LanguageCompile(QSqlDatabase &db,int &count)//���Ա�
{
    QSqlQuery sqlquery(db);

    for(int i = 0; i < m_mixGlobalVar.m_nLanNum; i++)
    {
        count++;
        bool bDateSure = sqlquery.prepare("INSERT INTO languageList(sLanguageName)VALUES(:sLanguageName)");
        qDebug() << "sqlquery.prepare " << bDateSure;
        sqlquery.bindValue(":sLanguageName", QVariant(m_mixGlobalVar.m_vecLanguageNameList.at(i)));//�ַ�������

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "-------------qDebug qDebug qDebug :" << result << endl;
    }
}

void QSamSysParame::datatransferCompile(QSqlDatabase &db,int &count)//���ϴ���
{
	QSqlQuery sqlquery(db);
	sqlquery.prepare("INSERT INTO dataTrans"
        "(nGroupId,nTransType,nInterval,nTriggerAddrId,bAutoReset,"
        "nAddrType,nTransLen,bDynLength ,nLengthAddrId ,nSourceAddrId,nTargetAddrId)"
        "VALUES(:nGroupId,:nTransType,:nInterval,:nTriggerAddrId,:bAutoReset,"
        ":nAddrType,:nTransLen,:bDynLength,:nLengthAddrId, :nSourceAddrId, :nTargetAddrId)");
	int groupIndex = 0;
	foreach(DATA_TRANSFER_PROP item,m_qvcdataTransProp)
	{
		ADDR_PARAMENTS stParams;

		stParams.itemId     = -1;
		stParams.eRWtype = GLOBAL_LOOP_R;

		sqlquery.bindValue(":nGroupId", QVariant(groupIndex));//�����
		
		sqlquery.bindValue(":nTransType", QVariant(item.nTriggerType));//������ʽ
		if (item.nTriggerType == 1)//ʱ�䴥��
		{
			sqlquery.bindValue(":nInterval", QVariant(item.nTriggerSpace));//ʱ����
		}
		else//λ��ַ����
		{
			count++;
			stParams.id = count;
            stParams.eType      = OBJ_SYSPRARM;
			stParams.addrNum    = 1;
			item.mTriggerAddr.compile(db, stParams);
			sqlquery.bindValue(":nTriggerAddrId", QVariant(count));//������ַ
		}
		sqlquery.bindValue(":bAutoReset", QVariant((short)item.bAutomatismOff));//�Ƿ��Զ���λ
		sqlquery.bindValue(":nAddrType", QVariant(item.nAddrType+1));//��ַ����1λ 2�� 3˫��
		sqlquery.bindValue(":nTransLen", QVariant(item.nWordBitPos));//����

		count++;
		stParams.id = count;
		stParams.eType      = OBJ_OTHER;

		if (item.nAddrType == 2)
		{
			stParams.addrNum = item.nWordBitPos*2;
		}
		else
		{
			stParams.addrNum = item.nWordBitPos;
		}
		item.mSourceAddr.compile(db,stParams);
		sqlquery.bindValue(":nSourceAddrId", QVariant(count));//Դ��ַ

		count++;
		stParams.id = count;
		item.mTargetAddr.compile(db,stParams);
		sqlquery.bindValue(":nTargetAddrId", QVariant(count));//Ŀ���ַ

        sqlquery.bindValue(":bDynLength", QVariant(item.bDynLength));//Ŀ���ַ
        if(item.bDynLength)
        {
            count++;
            stParams.id = count;
            stParams.addrNum = 1;
            item.mLengthAddr.compile(db,stParams);
            sqlquery.bindValue(":nLengthAddrId", QVariant(count));//���ȵ�ַ
        }
		
		bool result = false;
		result = sqlquery.exec();
		qDebug() << "insert dataTrans table :"<<result;

		groupIndex++;

	}


}

void QSamSysParame::schedulerCompile(QSqlDatabase &db,int &count)
{
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO scheduler( actionIndex ,actionTime ,eTimeType ,weekday ,nTimeAddr ,"
                     "eActionType ,nActionAddr ,eDataType ,eValueType ,nValue  ,nCtlAddr,bControl )"
                     "VALUES(:actionIndex ,:actionTime ,:eTimeType ,:weekday ,:nTimeAddr ,"
                     ":eActionType ,:nActionAddr ,:eDataType ,:eValueType ,:nValue  ,:nCtlAddr,:bControl )");
    foreach(QList<ScheItem> items,schedulers->getItems())
    {
        ADDR_PARAMENTS stParams;
        for(int i = 0; i<items.size(); i++)
        {
            sqlquery.bindValue(":actionIndex", QVariant(i));//���
            if(!items[i].timeType)//ʱ��
            {
                sqlquery.bindValue(":actionTime", QVariant(items[i].time));

            }
            else
            {
                count++;
                stParams.eRWtype = GLOBAL_LOOP_R;
                stParams.eType      = OBJ_SYSPRARM;
                stParams.id = count;
                stParams.addrNum = 1;
                items[i].kTimeAddr.compile(db,stParams);

                sqlquery.bindValue(":nTimeAddr", QVariant(count));
            }
            sqlquery.bindValue(":eTimeType", QVariant((short)items[i].timeType));
            sqlquery.bindValue(":weekday", QVariant((short)items[i].eWeek));
            sqlquery.bindValue(":eActionType", QVariant((short)items[i].eActionType));

            count++;
            stParams.eRWtype = GLOBAL_ONCE_W;
            stParams.eType      = OBJ_SYSPRARM;
            stParams.id = count;
            stParams.addrNum = 1;
            items[i].kActionAddr.compile(db,stParams);
            sqlquery.bindValue(":nActionAddr", QVariant((double)count));

            sqlquery.bindValue(":eDataType", QVariant((short)items[i].eDataType));
            sqlquery.bindValue(":eValueType", QVariant((short)items[i].valueType));

            if(!items[i].valueType)//����
            {
                sqlquery.bindValue(":nValue", QVariant(items[i].nValue));

            }
            else//
            {
                count++;
                stParams.eRWtype = GLOBAL_LOOP_R;
                stParams.eType      = OBJ_SYSPRARM;
                stParams.id = count;
                stParams.addrNum = 1;
                items[i].kValueAddr.compile(db,stParams);

                sqlquery.bindValue(":nValue", QVariant((double)count));
            }

            sqlquery.bindValue(":bControl", QVariant(items[i].bControl));
            if(items[i].bControl)
            {
                count++;
                stParams.eRWtype = GLOBAL_LOOP_R;
                stParams.eType      = OBJ_SYSPRARM;
                stParams.id = count;
                stParams.addrNum = 1;
                items[i].kControlAddr.compile(db,stParams);
                sqlquery.bindValue(":nCtlAddr", QVariant(count));
            }
            bool result = false;
            result = sqlquery.exec();
            qDebug() << "insert scheduler table :"<<result;

        }
    }
}

void QSamSysParame::UserRightCompile(QSqlDatabase &db,int &count)//�û���Ȩ�ޱ�
{
    //sCreateTableCmd = "CREATE TABLE [userList]
    //(id integer NOT NULL PRIMARY KEY AUTOINCREMENT,
    //nGroupId,sGroupName,sGroupDescript,
    //sUserId,sUserName,sUserDescript,sPassword)";

    QSqlQuery sqlquery(db);

    int groupNum    = m_mixGlobalVar.m_vecGroup.size();//����
    int userNum     = m_mixGlobalVar.m_vecUser.size();//�û���
    for(int i = 0; i < groupNum; i++)
    {
        int temp = m_mixGlobalVar.m_vecGroup.at(i).m_vecMember.size();
        if(0 == temp)//�����������
        {
            count++;
            bool bDateSure = sqlquery.prepare("INSERT INTO userList("
                     "nGroupId,sGroupName,sGroupDescript,"
                     "sUserId,sUserName,sUserDescript,sPassword,sMasterSet,sMaster)"
              "VALUES(:nGroupId,:sGroupName,:sGroupDescript,"
                    ":sUserId,:sUserName,:sUserDescript,:sPassword,:sMasterSet,:sMaster)");

            qDebug() << "sqlquery.prepare " << bDateSure;

            sqlquery.bindValue(":nGroupId", QVariant(-1));//����idΪ-1
            sqlquery.bindValue(":sGroupName", QVariant(m_mixGlobalVar.m_vecGroup.at(i).m_strName));
            sqlquery.bindValue(":sGroupDescript", QVariant(m_mixGlobalVar.m_vecGroup.at(i).m_strDescrip));
            sqlquery.bindValue(":sUserId", QVariant(-1));//����û���û�
            sqlquery.bindValue(":sUserName", QVariant(""));
            sqlquery.bindValue(":sUserDescript", QVariant(""));
            sqlquery.bindValue(":sPassword", QVariant(""));
            sqlquery.bindValue(":sMasterSet", QVariant(""));
            sqlquery.bindValue(":sMaster", QVariant(""));

            bool result = false;
            result      = sqlquery.exec();
            qDebug() << "XXXXXXXXXXXXXX:" << result << endl;

            continue;
        }

        int curUser = 0;
        for(int j = 0; j < temp; j++)
        {
            count++;
            bool bDateSure = sqlquery.prepare("INSERT INTO userList("
                     "nGroupId,sGroupName,sGroupDescript,"
                     "sUserId,sUserName,sUserDescript,sPassword,sMasterSet,sMaster)"
              "VALUES(:nGroupId,:sGroupName,:sGroupDescript,"
                    ":sUserId,:sUserName,:sUserDescript,:sPassword,:sMasterSet,:sMaster)");

            qDebug() << "sqlquery.prepare " << bDateSure;

            sqlquery.bindValue(":nGroupId", QVariant(i));
            sqlquery.bindValue(":sGroupName", QVariant(m_mixGlobalVar.m_vecGroup.at(i).m_strName));
            sqlquery.bindValue(":sGroupDescript", QVariant(m_mixGlobalVar.m_vecGroup.at(i).m_strDescrip));
            sqlquery.bindValue(":sMaster", QVariant(m_mixGlobalVar.m_vecGroup.at(i).m_vecMember.at(j).m_bIsAdmin));
            sqlquery.bindValue(":sMasterSet", QVariant(m_mixGlobalVar.m_vecGroup.at(i).m_bNeedAdmin));

            for(int k = 0; k < userNum; k++)
            {
                //���еĵ�ǰ�û����û����е��Ǹ���Ӧ
                if(m_mixGlobalVar.m_vecGroup.at(i).m_vecMember.at(j).m_strUser == m_mixGlobalVar.m_vecUser.at(k).m_strName)
                {
                    curUser = k;
                    break;
                }
            }
            sqlquery.bindValue(":sUserId", QVariant(curUser));
            sqlquery.bindValue(":sUserName", QVariant(m_mixGlobalVar.m_vecUser.at(curUser).m_strName));
            sqlquery.bindValue(":sUserDescript", QVariant(m_mixGlobalVar.m_vecUser.at(curUser).m_strDescrip));
            sqlquery.bindValue(":sPassword", QVariant(m_mixGlobalVar.m_vecUser.at(curUser).m_strPassword));

            bool result = false;
            result = sqlquery.exec();
            qDebug() << "-------------m_strPassword :" << result << endl;
        }
    }
}

void QSamSysParame::dataSamplingCompile(QSqlDatabase &db,int &count)
{
    QSqlQuery sqlquery(db);

    int num         = m_loadDataSampling.size();

	sqlquery.prepare("INSERT INTO dataCollect(nDataSampType ,nGroupId ,sName ,eSampType "
		",nSaveTime ,eDealSampFull ,bFullNotic ,nNoticAddrId ,bAddrCtlSamp ,nCtlSampAddrId,"
		" bAddrCtlTime ,nStartAddr ,nEndAddr ,nStartHour ,nStartMinute ,nEndHour ,nEndMinute ,bAddrCtlRate ,nSampRate ,"
        "bAutoReset  ,nCtlSaveAddrId ,eSaveMedium ,eDateShowType,bAutoSave ,nIntervalTime,bPrint ,bPrintDate ,bPrintTime,bSaveToFile)"
		"VALUES(:nDataSampType ,:nGroupId ,:sName ,:eSampType "
		",:nSaveTime,:eDealSampFull,:bFullNotic,:nNoticAddrId,:bAddrCtlSamp,:nCtlSampAddrId"
		",:bAddrCtlTime ,:nStartAddr ,:nEndAddr ,:nStartHour,:nStartMinute,:nEndHour,:nEndMinute,:bAddrCtlRate,:nSampRate,"
        ":bAutoReset,:nCtlSaveAddrId,:eSaveMedium,:eDateShowType,:bAutoSave ,:nIntervalTime,:bPrint ,:bPrintDate ,:bPrintTime,:bSaveToFile)");


	for (int i=0; i<num; i++)
	{		
		sqlquery.bindValue(":nDataSampType", QVariant(m_loadDataSampling.at(i).nDataSampType));
		int curSampId = 0;
        for(int j = 0; j <i; j++)
		{
			if(m_loadDataSampling.at(i).nDataSampType == m_loadDataSampling.at(j).nDataSampType)
			{
                curSampId++;

			}

		}

		sqlquery.bindValue(":nGroupId", QVariant(curSampId));
		sqlquery.bindValue(":sName", QVariant(m_vecDataSamplingStr.at(i)));//�ַ�������

		sqlquery.bindValue(":eSampType", QVariant(m_loadDataSampling.at(i).eSampType));//������ʽ

		sqlquery.bindValue(":nSaveTime", QVariant(0));
		sqlquery.bindValue(":eDealSampFull", QVariant(m_loadDataSampling.at(i).eDealSampFull));//ȡ������ʽ
		sqlquery.bindValue(":bFullNotic", QVariant((int)m_loadDataSampling.at(i).bFullNotic));//�Ƿ�ȡ��֪ͨ
		
		//�޸ĵ�ַ�������
		ADDR_PARAMENTS stParams;
		
		stParams.itemId     = i;
        stParams.eRWtype = DATA_COLLECT_LOOP_R;
		if(1 == m_loadDataSampling.at(i).nDataSampType)//ʵʱ
		{
			stParams.eType      = OBJ_REALTIME_DATA;
		}
		else//��ʷ
		{
			stParams.eType      = OBJ_HISTORYDATA;
		}
		
		Keyboard kb;
		if (m_loadDataSampling.at(i).bFullNotic)
		{
			count++;
			stParams.id         = count;
			stParams.addrNum    = 1;
			kb = m_loadDataSampling.at(i).strNoticAddrId;
			kb.compile(db,stParams);
			sqlquery.bindValue(":nNoticAddrId", QVariant(count));//ȡ��֪ͨ��ַ
		}
		
		
		sqlquery.bindValue(":bAddrCtlSamp", QVariant((int)m_loadDataSampling.at(i).bAddrCtlSamp));//λ��ַ�����Ƿ����

        if (m_loadDataSampling.at(i).bAddrCtlSamp)
		{
			count++;
			//�޸ĵ�ַ�������
			stParams.id         = count;
			stParams.addrNum    = 1;

			kb = m_loadDataSampling.at(i).strCtlSampAddrId;
			kb.compile(db,stParams);
			sqlquery.bindValue(":nCtlSampAddrId", QVariant(count));
		}
		sqlquery.bindValue(":bAddrCtlTime", QVariant((int)m_loadDataSampling.at(i).bDynTimeRange));//�Ƿ�̬ʱ�䷶Χ
		if(m_loadDataSampling.at(i).bDynTimeRange)
		{
			count++;
			//�޸ĵ�ַ�������
			stParams.id         = count;
			stParams.addrNum    = 1;

			kb = m_loadDataSampling.at(i).startTimeAddr;
                        kb.Length = 2;
			kb.compile(db,stParams);
			sqlquery.bindValue(":nStartAddr", QVariant(count));
			count++;
			//�޸ĵ�ַ�������
			stParams.id         = count;
			stParams.addrNum    = 1;

			kb = m_loadDataSampling.at(i).endTimeAddr;
                        kb.Length = 2;
			kb.compile(db,stParams);
			sqlquery.bindValue(":nEndAddr", QVariant(count));
			
		}
		else
		{
			sqlquery.bindValue(":nStartHour", QVariant(m_loadDataSampling.at(i).nStartHour));//��ʼ��ʱ��0-23��
			sqlquery.bindValue(":nStartMinute", QVariant(m_loadDataSampling.at(i).nStartMinute));//��ʼ�ķ֣�0-60��
			sqlquery.bindValue(":nEndHour", QVariant(m_loadDataSampling.at(i).nEndHour));//������ʱ��0-23��
			sqlquery.bindValue(":nEndMinute", QVariant(m_loadDataSampling.at(i).nEndMinute));//�����ķ֣�0-60��
		}
		
		if (m_loadDataSampling.at(i).bDynSampleRate)
		{
			sqlquery.bindValue(":bAddrCtlRate", QVariant(1));
			count++;
			//�޸ĵ�ַ�������
			stParams.id         = count;
			stParams.addrNum    = 1;

			kb = m_loadDataSampling.at(i).dynRateAddr;
			kb.compile(db,stParams);
			sqlquery.bindValue(":nSampRate", QVariant(count));
		}
		else{
            int times = 0;
            switch(m_loadDataSampling.at(i).nSampRateUnit)
            {
            case 0://200����
                times = 1;
                break;
            case 1://��
                times = 5;
                break;
            case 2://��
                times = 5*60;
                break;
            case 3://Сʱ
                times = 5*60*60;
                break;
            case 4://��
                times = 5*60*60*24;
                break;
            default:break;
            }
            sqlquery.bindValue(":nSampRate", QVariant(m_loadDataSampling.at(i).nSampRate*times));
		}
		sqlquery.bindValue(":bAutoReset", QVariant((int)m_loadDataSampling.at(i).bAutoReset));//�Ƿ��Զ���λ
		

		if (m_loadDataSampling.at(i).bSaveToFile)
		{
			count++;
			//�޸ĵ�ַ�������
			stParams.id         = count;
			stParams.addrNum    = 1;

			kb = m_loadDataSampling.at(i).keyCtlSaveAddr;
			kb.compile(db,stParams);
			sqlquery.bindValue(":nCtlSaveAddrId", QVariant(count));

		}
        sqlquery.bindValue(":eSaveMedium", QVariant(m_loadDataSampling.at(i).eSaveMedium));//�����ý��
        sqlquery.bindValue(":eDateShowType", QVariant(m_loadDataSampling.at(i).eDateShowType));//���ڸ�ʽ
        sqlquery.bindValue(":bAutoSave", QVariant((int)m_loadDataSampling.at(i).bAutoSave));//�Ƿ��Զ������ļ�
        sqlquery.bindValue(":nIntervalTime", QVariant((int)m_loadDataSampling.at(i).nSaveHour));//����ʱ����
		sqlquery.bindValue(":bSaveToFile", QVariant((int)m_loadDataSampling.at(i).bSaveToFile));//�Ƿ񱣴��ļ�
        sqlquery.bindValue(":bPrint", QVariant((int)m_loadDataSampling.at(i).bPrint));//�Ƿ��ӡ
        sqlquery.bindValue(":bPrintDate", QVariant((int)m_loadDataSampling.at(i).bPrintDate));//�Ƿ��ӡ����
        sqlquery.bindValue(":bPrintTime", QVariant((int)m_loadDataSampling.at(i).bPrintTime));//�Ƿ��ӡʱ��
		bool result = sqlquery.exec();
		qDebug() << "insert dataCollect table :"<<result;
        insertSampleAddr(db,count,m_loadDataSampling.at(i).m_dataTable,curSampId,m_loadDataSampling.at(i).nDataSampType);
	}

}
void QSamSysParame::insertSampleAddr(QSqlDatabase &db,int &count,QVector<DATA_ADDRESS_ITEM> m_dataTable,int nGroupId,int sampleType)
{
	QSqlQuery sqlquery(db);

	sqlquery.prepare("INSERT INTO dataCollectAddr(nGroupId ,nDataSampType ,nArrayId ,nAddrId "
        ",eDataType ,nSourceMin ,nSourceMax ,nTargeMin ,nTargeMax,nDecLength,bRound,sName,bDealData)"
		"VALUES(:nGroupId ,:nDataSampType ,:nArrayId ,:nAddrId "
        ",:eDataType ,:nSourceMin ,:nSourceMax ,:nTargeMin ,:nTargeMax,:nDecLength,:bRound,:sName,:bDealData)");
	for (int i=0; i<m_dataTable.size();i++)
	{
		sqlquery.bindValue(":nGroupId", QVariant(nGroupId));
		sqlquery.bindValue(":nDataSampType", QVariant(sampleType));
		sqlquery.bindValue(":nArrayId", QVariant(i));
		count ++;

		ADDR_PARAMENTS stParams;
		switch (m_dataTable.at(i).dataType)
		{
		case POSITIVE_INT_32:
		case INT_32:
		case BCD_32:
		case FLOAT_32:
			stParams.addrNum = 2;
            break;
		default:
			stParams.addrNum = 1;
		}
		
		stParams.id         = count;
		stParams.itemId     = i;
        stParams.eRWtype    = DATA_COLLECT_LOOP_R;
        if(1 == m_loadDataSampling.at(nGroupId).nDataSampType)//ʵʱ
        {
            stParams.eType      = OBJ_REALTIME_DATA;
        }
        else//��ʷ
        {
            stParams.eType      = OBJ_HISTORYDATA;
        }
		

		Keyboard kb = m_dataTable.at(i).keyAddress;
		kb.compile(db,stParams);

		sqlquery.bindValue(":nAddrId", QVariant(count));
        sqlquery.bindValue(":eDataType", QVariant(m_dataTable.at(i).dataType));
		if (m_dataTable.at(i).bZoom)
		{
			sqlquery.bindValue(":nSourceMin", QVariant(m_dataTable.at(i).inputMin));
			sqlquery.bindValue(":nSourceMax", QVariant(m_dataTable.at(i).inputMax));
			sqlquery.bindValue(":nTargeMin", QVariant(m_dataTable.at(i).outputMin));
			sqlquery.bindValue(":nTargeMax", QVariant(m_dataTable.at(i).outputMax));
		}
        sqlquery.bindValue(":nDecLength", QVariant(m_dataTable.at(i).decLen));
        sqlquery.bindValue(":bRound", QVariant((int)m_dataTable.at(i).bRound));
        sqlquery.bindValue(":sName", QVariant(m_dataTable.at(i).name));
        sqlquery.bindValue(":bDealData", QVariant((int)m_dataTable.at(i).bZoom));
		bool result = sqlquery.exec();
		qDebug() << "insert dataCollectAddr table :"<<result;
	}

}
void QSamSysParame::alarmCompile(QSqlDatabase &db,int &count)
{
    QSqlQuery sqlquery(db);

    int i,j;
    bool result = false;
    for(i=0; i<m_qvcAlarm.size(); i++)
    {
        sqlquery.prepare("INSERT INTO alarmGroup(nGroupId , sName ,nTime)"
                            "VALUES (:nGroupId ,:sName ,:nTime)");
        sqlquery.bindValue(":nGroupId", QVariant(i));
        sqlquery.bindValue(":sName", QVariant(m_qvcAlarm[i].alarmName));
        sqlquery.bindValue(":nTime", QVariant(0));
        result = sqlquery.exec();
        qDebug() << "insert alarmGroup table :"<<result;

        for(j=0;j<m_qvcAlarm[i].alarms.size();j++)
        {
            sqlquery.prepare("INSERT INTO alarm(nGroupId ,nAlarmIndex , nAddress, eCondition, eDataType "
                             ",nRangLow,nRangHigh,nTargetPage,nSceneType,bSeneMsg,sPhoneNum,bAddtoDB ,"
                             "bPrint ,bPrintDate ,bPrintTime,bOpenScene )"
                                "VALUES(:nGroupId ,:nAlarmIndex,:nAddress,:eCondition ,:eDataType,"
                                ":nRangLow,:nRangHigh,:nTargetPage,:nSceneType,:bSeneMsg,:sPhoneNum,"
                                ":bAddtoDB ,:bPrint ,:bPrintDate ,:bPrintTime,:bOpenScene)");
            sqlquery.bindValue(":nGroupId", QVariant(i));
            sqlquery.bindValue(":nAlarmIndex", QVariant(j));
            count++;
			ADDR_PARAMENTS stParams;
			stParams.id = count;
			stParams.itemId = i;
			stParams.eType = OBJ_ALARM;
			stParams.addrNum = j;
            stParams.eRWtype    = GLOBAL_LOOP_R;
            m_qvcAlarm[i].alarms[j].addr.compile(db,stParams);
            sqlquery.bindValue(":nAddress", QVariant(count));
            sqlquery.bindValue(":eCondition", QVariant((int)m_qvcAlarm[i].alarms[j].eCondtion));
            sqlquery.bindValue(":eDataType", QVariant((int)m_qvcAlarm[i].alarms[j].dataType));
            sqlquery.bindValue(":nRangLow", QVariant(m_qvcAlarm[i].alarms[j].rangeLow));
            sqlquery.bindValue(":nRangHigh", QVariant(m_qvcAlarm[i].alarms[j].rangeHigh));
            sqlquery.bindValue(":bSeneMsg", QVariant((int)m_qvcAlarm[i].alarms[j].bSeneMsg));

            QString sPhoneNums;
            foreach(QString sPhone,m_qvcAlarm[i].alarms[j].sPhoneNums)
            {
                sPhoneNums += sPhone;
                sPhoneNums += ";";
            }
            sqlquery.bindValue(":sPhoneNum", QVariant(sPhoneNums));

            sqlquery.bindValue(":bAddtoDB", QVariant((int)m_qvcAlarm[i].alarms[j].bAddtoDB));
            sqlquery.bindValue(":bPrint", QVariant((int)m_qvcAlarm[i].alarms[j].bPrint));
            sqlquery.bindValue(":bPrintTime", QVariant((int)m_qvcAlarm[i].alarms[j].bPrintTime));
            sqlquery.bindValue(":bPrintDate", QVariant((int)m_qvcAlarm[i].alarms[j].bPrintDate));

            sqlquery.bindValue(":bOpenScene", QVariant((int)m_qvcAlarm[i].alarms[j].bOpenScene));


            if(m_qvcAlarm[i].alarms[j].bOpenScene)
            {
                int sceneIndex = 0;
                int windowIndex = 0;

                QString sceneName = m_qvcAlarm[i].alarms[j].sceneName;
                for(int num = 0;num<pwnd->pSceneSheet.size();num++)
                {

                    if(pwnd->pSceneSheet[num]->nIsSceneOrWindow == 0)
                    {
                        if(pwnd->pSceneSheet[num]->sNewScreenName == sceneName)
                        {
                            sqlquery.bindValue(":nTargetPage",QVariant(sceneIndex));// ������ַ�� id
                            sqlquery.bindValue(":nSceneType",QVariant(0));// ����
                            break;
                        }
                        sceneIndex++;
                    }
                    if(pwnd->pSceneSheet[num]->nIsSceneOrWindow == 1)
                    {
                        if(pwnd->pSceneSheet[num]->sNewScreenName == sceneName)
                        {
                            sqlquery.bindValue(":nTargetPage",QVariant(windowIndex));// ������ַ�� id
                            sqlquery.bindValue(":nSceneType",QVariant(1));// ����
                            break;
                        }
                        windowIndex++;
                    }
                }
            }

            result = sqlquery.exec();
            qDebug() << "insert alarm table :"<<result;

            alarmMessagesCompile(db,m_qvcAlarm[i].alarms[j].messages,i,j);


        }
    }
}

void QSamSysParame::alarmMessagesCompile(QSqlDatabase &db,QStringList msgs,int GroupId,int AlarmIndex)
{
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO alarmMessage(nGroupId ,nAlarmIndex ,nLanguage ,sMessage )"
                        "VALUES (:nGroupId ,:nAlarmIndex ,:nLanguage ,:sMessage)");
    bool result = false;
    for(int i=0; i<msgs.size();i++)
    {
        sqlquery.bindValue(":nGroupId", QVariant(GroupId));
        sqlquery.bindValue(":nAlarmIndex", QVariant(AlarmIndex));
        sqlquery.bindValue(":nLanguage", QVariant(i));
        sqlquery.bindValue(":sMessage", QVariant(msgs.at(i)));
        result = sqlquery.exec();
        qDebug() << "insert alarmMessage table :"<<result;
    }
}

void QSamSysParame::connectCompile(QSqlDatabase &db,int &count)
{
    QSqlQuery sqlquery(db);
    sqlquery.prepare("INSERT INTO plcConnectProp(nConnectId ,sConnectName ,eConnectPort,bUseRelationPort ,"
                     "eRelationPort ,bMasterScreen,bConnectScreenPort, nSlaveScreenNum, nScreenNo ,nBaudRate ,nDataBits ,nCheckType ,nStopBit ,sIpAddr ,"
                     "nNetPortNum )"
                     "VALUES (:nConnectId ,:sConnectName ,:eConnectPort,:bUseRelationPort ,:eRelationPort ,:bMasterScreen,"
                     ":bConnectScreenPort,:nSlaveScreenNum,:nScreenNo ,:nBaudRate ,:nDataBits ,:nCheckType ,:nStopBit ,:sIpAddr ,"
                        ":nNetPortNum)");

    bool result = false;
    int port = 0;
    int relport = 0;
    int baudrate = 9600;
    int nDataBits = 8;
    int nPlcIndex = 0;
    for(int i=0; i<m_qvcConnect.size(); i++)
    {
        int nCncId = i;
#ifdef AKPLC
        if(nCncId == 0)
        {
            nCncId = 1;
        }
#endif
        sqlquery.bindValue(":nConnectId", QVariant(nCncId));
        sqlquery.bindValue(":sConnectName", QVariant(m_qvcConnect[i].sConnectName));
        switch (m_qvcConnect[i].eConnectPort)
        {
            case 0:
#ifdef AKPLC
        port = 4;
#else
        port = 3;
#endif
                break;
            case 1:
                port = 4;
                break;
            case 2://COM3
                port = 5;
                break;
            case 3://��̫��
                port = 8;
                break;
            case 4://CAN����
                port = 14;
                break;
            case 5://CAN����
                port = 15;
                break;
            default:
                break;
            /*case 0:
                port = 3;
                break;
            case 1:
                port = 4;
                break;
            case 2:
                port = 8;
                break;*/
        }
        switch (m_qvcConnect[i].eRelationPort)
        {
            case 0:
#ifdef AKPLC
        relport = 4;
#else
        relport = 3;
#endif
                break;
            case 1:
                relport = 4;
                break;
            case 2:
                relport = 8;
                break;
        }
        switch (m_qvcConnect[i].nBaudRate)
        {
            case 0:
                baudrate = 1200;
                break;
            case 1:
                baudrate = 2400;
                break;
            case 2:
                baudrate = 4800;
                break;
            case 3:
                baudrate = 9600;
                break;
            case 4:
                baudrate = 19200;
                break;
            case 5:
                baudrate = 38400;
                break;
            case 6:
                baudrate = 57600;
                break;
            case 7:
                baudrate = 115200;
                break;
            case 8:
                baudrate = 230400;
                break;
        }
        switch (m_qvcConnect[i].nDataBits)
        {
            case 0:
                nDataBits = 7;
                break;
            case 1:
                nDataBits = 8;
                break;
        }
        sqlquery.bindValue(":eConnectPort", QVariant(port));
        sqlquery.bindValue(":bUseRelationPort", QVariant(m_qvcConnect[i].bUseRelationPort));
        sqlquery.bindValue(":eRelationPort", QVariant(relport));
        sqlquery.bindValue(":bMasterScreen", QVariant(m_qvcConnect[i].bMasterScreen));
        sqlquery.bindValue(":bConnectScreenPort", QVariant(m_qvcConnect[i].bConnectScreenPort));
        sqlquery.bindValue(":nSlaveScreenNum", QVariant(m_qvcConnect[i].nSlaveScreenNum));
        sqlquery.bindValue(":nScreenNo", QVariant(m_qvcConnect[i].nScreenNo));
		
        sqlquery.bindValue(":nBaudRate", QVariant(m_qvcConnect[i].nBaudRate));
        sqlquery.bindValue(":nDataBits", QVariant(nDataBits));
        sqlquery.bindValue(":nCheckType", QVariant(m_qvcConnect[i].nCheckType));
        sqlquery.bindValue(":nStopBit", QVariant(m_qvcConnect[i].nStopBit));
        sqlquery.bindValue(":sIpAddr", QVariant(m_qvcConnect[i].sIpAddr));
        sqlquery.bindValue(":nNetPortNum", QVariant(m_qvcConnect[i].nNetPortNum));

        protoclCompile(db,m_qvcConnect[i].vProtocols,nCncId,nPlcIndex);
        nPlcIndex +=m_qvcConnect[i].vProtocols.size();

        result = sqlquery.exec();
        qDebug() << "insert plcConnectProp table :"<<result;
    }
}

void QSamSysParame::protoclCompile(QSqlDatabase &db,QVector<stProtocol> protocols,int nConnectId,int nUserPlcIndex)
{
    QSqlQuery sqlquery(db);
    bool result = false;
    result = sqlquery.prepare("INSERT INTO protocolProp(nConnectIndex ,sPlcServiceType ,nUserPlcId,nPlcNo ,nReceiveTimeout ,"
                     "nMaxRWLen ,nRetryTime,nMinCollectCycle,nIntervalTime,sIpAddr ,bIsNetTcp,nNetPortNum)"
                     "VALUES (:nConnectIndex ,:sPlcServiceType ,:nUserPlcId,:nPlcNo ,:nReceiveTimeout ,:nMaxRWLen ,"
                     ":nRetryTime,:nMinCollectCycle ,:nIntervalTime,:sIpAddr ,:bIsNetTcp ,:nNetPortNum)");
    
     result = false;
    for(int i=0; i<protocols.size();i++)
    {
        sqlquery.bindValue(":nConnectIndex", QVariant(nConnectId));
        sqlquery.bindValue(":sPlcServiceType", QVariant(protocols[i].sProtocolName));
        sqlquery.bindValue(":nUserPlcId", QVariant(nUserPlcIndex+i+1));
        sqlquery.bindValue(":nPlcNo", QVariant(protocols[i].nPlcNo));
        sqlquery.bindValue(":nReceiveTimeout", QVariant(protocols[i].nReceiveTimeout));
        sqlquery.bindValue(":nMaxRWLen", QVariant(protocols[i].nMaxRWLen));
        sqlquery.bindValue(":nRetryTime", QVariant(protocols[i].nRetryTime));

        sqlquery.bindValue(":nMinCollectCycle", QVariant(protocols[i].nCycleTime));
        sqlquery.bindValue(":nIntervalTime", QVariant(protocols[i].nIntervalTime));
        sqlquery.bindValue(":sIpAddr", QVariant(protocols[i].ip));
        sqlquery.bindValue(":bIsNetTcp", QVariant(protocols[i].bIsTcpProtocol));
        sqlquery.bindValue(":nNetPortNum", QVariant(protocols[i].port));


        result = sqlquery.exec();
        qDebug() << "insert protocolProp table :"<<result;
    }

}
void QSamSysParame::recipeCompile(QSqlDatabase &db,int &count)
{
    QVector <int> addr;
    addr.clear();
    int nDataType = 0;
    QSqlDatabase androidDb;
    bool bSuccess = false;
    QFile dataFile;
    if(dataFile.exists(DATARECIPE_NAME))
    {
        bSuccess = dataFile.remove(DATARECIPE_NAME);
        if(!bSuccess)
        {
            return;
        }
    }

    androidDb = QSqlDatabase::addDatabase("QSQLITE","RECIPE");

    androidDb.setDatabaseName(DATARECIPE_NAME);
    if(false == androidDb.open()) return;

    if(!androidDb.transaction())
    {
        return;
    }

    QStringList tableList = androidDb.tables();
    if(tableList.isEmpty())
    {
        QSqlQuery sqlQuery(androidDb);
        QString sCreateTableCmd;
        sCreateTableCmd.clear();

        /*1.������ַ��*/
        sCreateTableCmd = "CREATE TABLE [addr] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,eItemType smallint,nAddrId integer,nItemId integer,nAddrNum integer,eConnectType smallint,nUserPlcId smallint,sPlcProtocol varchar,nPlcStationIndex integer,nPlcRegIndex smallint,nPlcStartAddr integer,nAddrLen integer, eRwLevel smallint)";
        bSuccess = sqlQuery.exec(sCreateTableCmd);
        if(!bSuccess) return;

        sCreateTableCmd = "CREATE TABLE [recipeCollectGroup] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,sRecipeGName varchar,sRecipeGDescri varchar,nRecipeNum integer,nRecipeLen integer,nKeyId smallint,nBoardX smallint,nBoardY smallint,eSaveMedia smallint,nContinue smallint,bNeedCtlAddr smallint,mCtlAddrId integer,bCompleteNotic boolean,mComNoticAddrId integer)";
        bSuccess = sqlQuery.exec(sCreateTableCmd);
        if(!bSuccess) return;

        sCreateTableCmd = "CREATE TABLE [recipeNameML] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nRecipeId integer,nLanguageId smallint,sRecipeName varchar, sRecipeDescri varchar)";
        bSuccess = sqlQuery.exec(sCreateTableCmd);
        if(!bSuccess) return;

        sCreateTableCmd = "CREATE TABLE [recipeElemML] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nElemIndex integer,nValueAddrId integer,eDataType smallint,nLanguageId smallint,sElemName varchar)";
        bSuccess = sqlQuery.exec(sCreateTableCmd);
        if(!bSuccess) return;

        for(int i = 0; i < m_qvcRecipe.size(); i++ )
        {
            bSuccess = sqlQuery.prepare("INSERT INTO recipeCollectGroup(nGroupId,sRecipeGName,sRecipeGDescri,nRecipeNum,nRecipeLen,"
                             "nKeyId,nBoardX,nBoardY,eSaveMedia,nContinue,bNeedCtlAddr,"
                             "mCtlAddrId,bCompleteNotic,mComNoticAddrId)"
                             "VALUES (:nGroupId,:sRecipeGName,:sRecipeGDescri,:nRecipeNum,:nRecipeLen,"
                             ":nKeyId,:nBoardX,:nBoardY,:eSaveMedia,:nContinue,:bNeedCtlAddr,"
                             ":mCtlAddrId,:bCompleteNotic,:mComNoticAddrId)");
            qDebug()<<"recipeCollectGroup prepare "<<bSuccess;

            sqlQuery.bindValue(":nGroupId", QVariant(i));
            sqlQuery.bindValue(":sRecipeGName", QVariant(m_qvcRecipe[i].sName));
            sqlQuery.bindValue(":sRecipeGDescri", QVariant(m_qvcRecipe[i].sRecipeGDescri));
            sqlQuery.bindValue(":nRecipeNum", QVariant(m_qvcRecipe[i].formula.size()));
            sqlQuery.bindValue(":nRecipeLen", QVariant(m_qvcRecipe[i].nRecipeLen));
            if(m_qvcRecipe[i].nKeyMark)
            {
                sqlQuery.bindValue(":nKeyId",QVariant(m_qvcRecipe[i].nKeyId +1));
                sqlQuery.bindValue(":nBoardX",QVariant(m_qvcRecipe[i].nBoardX));
                sqlQuery.bindValue(":nBoardY",QVariant(m_qvcRecipe[i].nBoardY));
            }
            else
            {
               sqlQuery.bindValue(":nKeyId",QVariant(-1));
            }
            sqlQuery.bindValue(":eSaveMedia", QVariant(m_qvcRecipe[i].eSaveMedia));
            if(m_qvcRecipe[i].bContniu)
            {
                sqlQuery.bindValue(":nContinue", QVariant(1));//����
            }
            else
            {
                sqlQuery.bindValue(":nContinue", QVariant(0));//���
            }
            sqlQuery.bindValue(":bNeedCtlAddr", QVariant(int(m_qvcRecipe[i].bCtlAddr)));
                    //�޸ĵ�ַ�������
            if(m_qvcRecipe[i].bCtlAddr)
            {
                count++;
                ADDR_PARAMENTS stParams;
                stParams.id = count;
                stParams.itemId = i;
                stParams.eType = OBJ_RECIPE;
                stParams.addrNum = -1;
                stParams.eRWtype = GLOBAL_LOOP_R;
                m_qvcRecipe[i].addrCtl.Length = 2;
                m_qvcRecipe[i].addrCtl.compile(androidDb,stParams);
                sqlQuery.bindValue(":mCtlAddrId", QVariant(count));
            }
            else
            {
                sqlQuery.bindValue(":mCtlAddrId", QVariant(0));
            }
            sqlQuery.bindValue(":bCompleteNotic", QVariant(m_qvcRecipe[i].bCompleteNotic));
            if(m_qvcRecipe[i].bCompleteNotic)
            {
                count++;
                            //�޸ĵ�ַ�������
                ADDR_PARAMENTS stParams;
                stParams.id = count;
                stParams.itemId = i;
                stParams.eType = OBJ_RECIPE;
                stParams.addrNum = -1;
                stParams.eRWtype = GLOBAL_LOOP_R;
                m_qvcRecipe[i].addrNotic.Length = 1;
                m_qvcRecipe[i].addrNotic.compile(androidDb,stParams);
                sqlQuery.bindValue(":mComNoticAddrId", QVariant(count));
            }
            else
            {
                sqlQuery.bindValue(":mComNoticAddrId", QVariant(0));//Ĭ��ֵ
            }

            bSuccess = sqlQuery.exec();
            qDebug()<<"insert into recipeCollectGroup"<<bSuccess;

            //�����䷽���
            sCreateTableCmd = "CREATE TABLE [recipegroup";
            sCreateTableCmd = sCreateTableCmd + QString("%1").arg(i);
            sCreateTableCmd = sCreateTableCmd + "] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nRecipeId integer,elems varchar)";
            bSuccess = sqlQuery.exec(sCreateTableCmd);
            sCreateTableCmd.clear();
            if(!bSuccess)
            {
                androidDb.close();
                return;
            }
            for(int j = 0; j < m_qvcRecipe[i].formula.size(); j++)
            {
                QString sprepare = "INSERT INTO recipegroup";
                sprepare = sprepare + QString("%1").arg(i);
                sprepare = sprepare + "(nRecipeId,elems)"
                           "VALUES (:nRecipeId,:elems)";
                sqlQuery.prepare(sprepare);

                QString sElment;
                sElment.clear();
                for(int k = 0; k < m_qvcRecipe[i].formula[j].elment.size(); k ++)
                {
                    if("" == m_qvcRecipe[i].formula[j].elment[k].sText)
                    {
                        sElment = sElment + "0";
                    }
                    else
                    {
                        sElment = sElment + m_qvcRecipe[i].formula[j].elment[k].sText;
                    }
                    if(k < m_qvcRecipe[i].formula[j].elment.size() - 1)
                    {
                        sElment = sElment + ",";
                    }
                }
                sqlQuery.bindValue(":nRecipeId", QVariant(j));
                sqlQuery.bindValue(":elems", QVariant(sElment));
                bSuccess = sqlQuery.exec();
                qDebug()<<"INSERT INTO recipegroup:"<<bSuccess;

                //�䷽�����Ա�
                for(int n = 0; n < m_qvcRecipe[i].formula[j].RecipeInfo.size(); n++)//�䷽���Ƹ��� �����Ը������
                {
                    bSuccess = sqlQuery.prepare("INSERT INTO recipeNameML(nGroupId,nRecipeId,nLanguageId,sRecipeName,sRecipeDescri)"
                                               "VALUES (:nGroupId,:nRecipeId,:nLanguageId,:sRecipeName,:sRecipeDescri)");
                    sqlQuery.bindValue(":nGroupId", QVariant(i));
                    sqlQuery.bindValue(":nRecipeId", QVariant(j));
                    sqlQuery.bindValue(":nLanguageId", QVariant(m_qvcRecipe[i].formula[j].RecipeInfo[n].nLanguageId));
                    //sqlquery.bindValue(":nRecipeId", QVariant(m_qvcRecipe[i].formula[j].RecipeInfo[n].nRecipeId));
                    sqlQuery.bindValue(":sRecipeName", QVariant(m_qvcRecipe[i].formula[j].RecipeInfo[n].sRecipeName));
                    sqlQuery.bindValue(":sRecipeDescri", QVariant(m_qvcRecipe[i].formula[j].RecipeInfo[n].sRecipeDescri));
                    bSuccess = sqlQuery.exec();
                    qDebug()<<"insert recipeNameML end "<<bSuccess;
                }
                for(int k = 0; k < m_qvcRecipe[i].formula[j].elment.size(); k++)//Ԫ�ظ���
                {
                    for(int n = 0; n < m_qvcRecipe[i].ElmentName[k].count();n++)//Ԫ�����Ƹ��������Ը������
                    {
                        if(j > 0)
                        {
                            break;
                        }
                        bSuccess = sqlQuery.prepare("INSERT INTO recipeElemML(nGroupId,nElemIndex,nValueAddrId,eDataType,nLanguageId,sElemName)"
                                                   "VALUES (:nGroupId,:nElemIndex,:nValueAddrId,:eDataType,:nLanguageId,:sElemName)");
                        sqlQuery.bindValue(":nGroupId", QVariant(i));
                        sqlQuery.bindValue(":nElemIndex", QVariant(k));
                        if(0 == n)//ֻ��Ҫ�����һ���䷽�ĵ�ַ�������䷽���һ���䷽��Ԫ�ص�ַ����ͬ
                        {
                            count++;
                                            //�޸ĵ�ַ�������
                            ADDR_PARAMENTS stParams;
                            stParams.id = count;
                            stParams.itemId = i;
                            stParams.eType = OBJ_RECIPE;
                            stParams.addrNum = k;
                            stParams.eRWtype = RECIPE_ONCE_R;
    //                        if(m_qvcRecipe[i].bContniu)
    //                        {
    //                            QString sType = m_qvcRecipe[i].formula[j].elment[k].sAddrType;
    //                            if(QObject::tr("32λ����") == sType || QObject::tr("32λ������") == sType || QObject::tr("32λ������") == sType || QObject::tr("32λBCD��") == sType)
    //                            {
    //                                m_qvcRecipe[i].formula[j].elment[k].addr.Length = 2 * m_qvcRecipe[i].formula[j].elment.size();
    //                            }
    //                            else
    //                            {
    //                                m_qvcRecipe[i].formula[j].elment[k].addr.Length = m_qvcRecipe[i].formula[j].elment.size();
    //                            }
    //                        }
                            //else
                            {
                                QString sType = m_qvcRecipe[i].formula[j].elment[k].sAddrType;
                                if(QObject::tr("32λ����") == sType || QObject::tr("32λ������") == sType || QObject::tr("32λ������") == sType || QObject::tr("32λBCD��") == sType)
                                {
                                    m_qvcRecipe[i].formula[j].elment[k].addr.Length = 2;
                                }
                                else
                                {
                                    m_qvcRecipe[i].formula[j].elment[k].addr.Length = 1;
                                }
                            }
                            if(0 == j)
                            {
                                m_qvcRecipe[i].formula[j].elment[k].addr.compile(androidDb,stParams);

                            }
                            sqlQuery.bindValue(":nValueAddrId", QVariant(count));
                            addr.append(count);
                        }
                        else
                        {
                            sqlQuery.bindValue(":nValueAddrId", QVariant(addr.at(k)));
                        }
                        sqlQuery.bindValue(":nLanguageId", QVariant(m_qvcRecipe[i].ElmentName[k].at(n).nLanguageId));
                        if(QObject::tr("16λ����") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 2;//16λ����
                        }
                        else if(QObject::tr("16λ������") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 4;//16λ������
                        }
                        else if(QObject::tr("32λ����") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 3;//32λ����
                        }
                        else if(QObject::tr("32λ������") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 5;//32λ������
                        }
                        else if(QObject::tr("32λ������") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 8;//32λ������
                        }
                        else if(QObject::tr("16λBCD��") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 6;//16λBCD
                        }
                        else if(QObject::tr("32λBCD��") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 7;//32λBCD
                        }
                        else if(QObject::tr("λ") == m_qvcRecipe[i].formula[j].elment[k].sAddrType)
                        {
                            nDataType = 1;//λ
                        }
                        else
                        {
                            nDataType = 2;//16λ����
                        }
                        sqlQuery.bindValue(":eDataType", QVariant(nDataType));
                        sqlQuery.bindValue(":sElemName", QVariant(m_qvcRecipe[i].ElmentName[k].at(n).sElemName));

                        bSuccess = sqlQuery.exec();
                        qDebug()<<"insert recipeElemML end "<<bSuccess;
                    }
                }
            }
        }
    }

    androidDb.commit();

    androidDb.close();
    addr.clear();
    return;
}

void QSamSysParame::globalCompile(QSqlDatabase &db,int &count)//ȫ�ֺ�
{
    QSqlQuery sqlquery(db);
    bool result = false;
    result = sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,TimeInterval,"
                     "ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,nCompID,SceneID,scriptCount)"
              "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,:TimeInterval,"
              ":ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,:nCompID,:SceneID,:scriptCount)");

    int scriptCount = m_qvcGlobalMaroProp.size();
    int oldValue = count;
    int k = 1;

    QVector<MacroLib> vecML;
    foreach(Macro lib,pwnd->macros)
    {
        MacroLib ml;
        ml.libName   = lib.libName;
        ml.funcNames = lib.functions;
        vecML.push_back(ml);
    }
    QVector<bool> vecBool;
    int vecNum = vecML.size();
    int canUse = 0;//Ϊ���bool�ĸ���
    for(int i = 0; i < scriptCount; i++)
    {
        bool isExist = false;
        GLOBAL_MARO_PROP script = m_qvcGlobalMaroProp.at(i);
        for(int j = 0; j < vecNum; j++)
        {
            if((script.sLibName == vecML[j].libName))
            {
               isExist = true;
               break;
            }
        }

        if(isExist)
        {
            vecBool.push_back(true);
            canUse++;
        }
        else
        {
            vecBool.push_back(false);
        }
    }

    if(canUse < scriptCount)
    {
        pwnd->information(QObject::tr("ȫ�ֺ겿�ֱ�ɾ��"), MSG_WARNING);
        //QMessageBox::about(this, QObject::tr("����"), QObject::tr("ȫ�ֺ겿�ֱ�ɾ��"));
    }

    if(canUse == 0)
    {
        //pwnd->information(QObject::tr("û�п��õ�ȫ�ֺ����ȫ�ֺ��Ѿ���ɾ��"));
        return;
    }

    for(int i = 0; i < scriptCount; i++)
    {
        if(vecBool[i] == false)
        {
            continue;
        }
        GLOBAL_MARO_PROP script = m_qvcGlobalMaroProp.at(i);

        count++;
        sqlquery.bindValue(":MacroID",QVariant(count));
        sqlquery.bindValue(":MacroLibName",QVariant(script.sLibName));
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));
        if(script.bIfCtrl)
        {
            sqlquery.bindValue(":MacroType",QVariant(2));
        }
        else
        {
            sqlquery.bindValue(":MacroType",QVariant(1));
        }
        sqlquery.bindValue(":TimeInterval",QVariant(script.iRunRate * 100));
        sqlquery.bindValue(":ControlAddrType",QVariant(script.iCtrlType));//λ��ַ
        if(script.bIfCtrl)
        {
            //sqlquery.bindValue(":ControlAddr",QVariant(oldValue + scriptCount + k));
            sqlquery.bindValue(":ControlAddr",QVariant(oldValue + canUse + k));
            k++;
            sqlquery.bindValue(":ExecCondition",QVariant(script.iValue));
        }
        else
        {
            sqlquery.bindValue(":ControlAddr",QVariant(-1));
            sqlquery.bindValue(":ExecCondition",QVariant(-1));
        }

        sqlquery.bindValue(":nCmpFactor",QVariant(0));
        sqlquery.bindValue(":nCompID",QVariant(-1));
        sqlquery.bindValue(":SceneID",QVariant(-1));
        sqlquery.bindValue(":scriptCount",QVariant(script.iScriptCount));
        bool result = false;
        result = sqlquery.exec();
        qDebug() << "----------->>>>>>>>>" << result;
    }

    for(int i = 0; i < scriptCount; i++)
    {
        if(vecBool[i] == false)
        {
            continue;
        }
        GLOBAL_MARO_PROP script = m_qvcGlobalMaroProp.at(i);
        if(script.bIfCtrl)
        {
            count++;
            ADDR_PARAMENTS stParams;
            stParams.id         = count;
            stParams.itemId     = count;
            stParams.eType      = OBJ_MACRO;
            stParams.eRWtype    = SCENE_CONTROL_LOOP_R;
            stParams.addrNum    = -1;
            script.mCtlAddr.compile(db, stParams);
        }
    }
}

void QSamSysParame::initCompile(QSqlDatabase &db,int &count)//��ʼ����
{
    QSqlQuery sqlquery(db);
    bool result = false;
    result = sqlquery.prepare("INSERT INTO macro(MacroID,MacroLibName,MacroName,MacroType,TimeInterval,"
                     "ControlAddr,ControlAddrType,ExecCondition,nCmpFactor,nCompID,SceneID,scriptCount)"
              "VALUES(:MacroID,:MacroLibName,:MacroName,:MacroType,:TimeInterval,"
                     ":ControlAddr,:ControlAddrType,:ExecCondition,:nCmpFactor,:nCompID,:SceneID,:scriptCount)");

    QVector<MacroLib> vecML;

    foreach(Macro lib,pwnd->macros)
    {
        MacroLib ml;
        ml.libName   = lib.libName;
        ml.funcNames = lib.functions;
        vecML.push_back(ml);
    }
    int vecNum = vecML.size();

    int scriptCount = m_qvcInitMaroProp.size();
    //int oldValue = count;
    int k = 0;
    for(int i = 0; i < scriptCount; i++)
    {
        INIT_MARO_PROP script = m_qvcInitMaroProp.at(i);

        bool isExist = false;
        for(int j  = 0; j < vecNum; j++)
        {
            if((script.sLibName == vecML[j].libName))
            {
                isExist = true;
                break;
            }
        }
        if(!isExist)
        {
            continue;
        }

        k++;

        count++;
        sqlquery.bindValue(":MacroID",QVariant(count));
        sqlquery.bindValue(":MacroLibName",QVariant(script.sLibName));
        sqlquery.bindValue(":MacroName",QVariant("MACRO_MAIN"));
        sqlquery.bindValue(":MacroType",QVariant(5));
        sqlquery.bindValue(":TimeInterval",QVariant(0));
        sqlquery.bindValue(":ControlAddrType",QVariant(0));//λ��ַ
        sqlquery.bindValue(":ControlAddr",QVariant(-1));
        sqlquery.bindValue(":ExecCondition",QVariant(-1));
        sqlquery.bindValue(":nCmpFactor",QVariant(0));
        sqlquery.bindValue(":nCompID",QVariant(-1));
        sqlquery.bindValue(":SceneID",QVariant(-1));
        sqlquery.bindValue(":scriptCount",QVariant(1));

        bool result = false;
        result = sqlquery.exec();
        qDebug() << "----------->>>>>>>>>" << result;
    }

    if(k < scriptCount)
    {
        pwnd->information(QObject::tr("��ʼ���겿�ֱ�ɾ��"), MSG_WARNING);
        //QMessageBox::about(this, QObject::tr("����"), QObject::tr("��ʼ���겿�ֱ�ɾ��"));
    }
}

//ʱ�����ò��ֱ���
void QSamSysParame::timesettingCompile(QSqlDatabase &db,int &count)
{
	QSqlQuery sqlquery(db);
	bool result = false;
	result = sqlquery.prepare("INSERT INTO timesetting(bDownloadTime ,eDataType ,nLength ,"
		"nSynchAddr ,eExeType ,nTime ,nTriggerAddr ,bAutoReset ,eSynchTime)"
		"VALUES(:bDownloadTime ,:eDataType ,:nLength ,"
		":nSynchAddr ,:eExeType ,:nTime ,:nTriggerAddr ,:bAutoReset,:eSynchTime)");

	sqlquery.bindValue(":bDownloadTime",QVariant(m_clockProp.bDownLoadTime));
	int nSynchTime = 0;
	CLOCK_PROP clockPro;
	if (!m_clockProp.bWTimeToPlc && !m_clockProp.bRTimeFromPlc)
	{
            nSynchTime = 0;
	}
	else if (m_clockProp.bWTimeToPlc)
	{
            nSynchTime = 1;
            clockPro = m_clockProp.mWTimeToPlc;
	}
	else if (m_clockProp.bRTimeFromPlc)
	{
            nSynchTime = 2;
            clockPro = m_clockProp.mRTimeFromPlc;
	}
	
        if (nSynchTime != 0)
	{
		
            sqlquery.bindValue(":eDataType",QVariant((int)BCD_16));
            sqlquery.bindValue(":nLength",QVariant(7));

            count++;
            ADDR_PARAMENTS stParams;
            stParams.id         = count;
            stParams.itemId     = 0;
            stParams.eType      = OBJ_SYSPRARM;
            stParams.eRWtype    = GLOBAL_LOOP_R;
            stParams.addrNum    = 7;
            clockPro.mCtlAddr.compile(db, stParams);
            sqlquery.bindValue(":nSynchAddr",QVariant(count));
            sqlquery.bindValue(":eExeType",QVariant(clockPro.nStartType+1));
            if (clockPro.nStartType == 0)
            {
                sqlquery.bindValue(":nTime",QVariant(clockPro.nTimeInterval));
            }
            else//λ����
            {
                count++;
                stParams.id         = count;
                stParams.itemId     = 0;
                stParams.eType      = OBJ_SYSPRARM;
                stParams.eRWtype    = GLOBAL_LOOP_R;
                stParams.addrNum    = 1;
                m_clockProp.mWTimeToPlc.mTriggerAddr.compile(db, stParams);
                sqlquery.bindValue(":nTriggerAddr",QVariant(count));
                sqlquery.bindValue(":bAutoReset",QVariant(clockPro.bReset));
            }
		
	}
	sqlquery.bindValue(":eSynchTime",QVariant(nSynchTime));
	result = false;
	result = sqlquery.exec();
	qDebug() << "insert timesetting table :"<<result;
}

QDataStream &operator<<(QDataStream &stream, QSamSysParame *pSamSysParame)
{
    if(!pSamSysParame) return stream;

    int nVectorSize = 0;
    stream << pSamSysParame->nUserDefKeyboardCount;
    /*save m_fileprotect data*/
    stream << pSamSysParame->m_fileProtect.bNeedFileProtect;
    stream << pSamSysParame->m_fileProtect.sProtectPWD;

    //czq
    /*save GlobalVariable data*/
    int temp;//ö�ٱ���Ҫ�õ���
    stream << pSamSysParame->m_mixGlobalVar.m_strModelName;
    stream << pSamSysParame->m_mixGlobalVar.m_strHmiName;
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_eScreenDir;
    stream << temp;
    stream << pSamSysParame->m_mixGlobalVar.m_strModelSize;
    stream << pSamSysParame->m_mixGlobalVar.m_strResolution;
    stream << pSamSysParame->m_mixGlobalVar.m_strColor;
    stream << pSamSysParame->m_mixGlobalVar.m_strUsermemory;
    //stream << pSamSysParame->m_mixGlobalVar.m_strNandFlash;
    stream << pSamSysParame->m_mixGlobalVar.m_strPowersupply;
    stream << pSamSysParame->m_mixGlobalVar.m_strCom1;
    stream << pSamSysParame->m_mixGlobalVar.m_strCom2;
    stream << pSamSysParame->m_mixGlobalVar.m_strUsb;
    stream << pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber;
    stream << pSamSysParame->m_mixGlobalVar.m_nScreenWidth;
    stream << pSamSysParame->m_mixGlobalVar.m_nScreenHeight;
    stream << pSamSysParame->m_mixGlobalVar.m_bUseLogo;
    stream << pSamSysParame->m_mixGlobalVar.m_sLogoNum;
    stream << pSamSysParame->m_mixGlobalVar.m_strLogoNum;
    stream << pSamSysParame->m_mixGlobalVar.m_bStandby;
    stream << pSamSysParame->m_mixGlobalVar.m_bStandbyMode;
    stream << pSamSysParame->m_mixGlobalVar.m_sStandbyNum;
    stream << pSamSysParame->m_mixGlobalVar.m_strStandbyNum;
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_eStandbyLight;
    stream << temp;
    stream << pSamSysParame->m_mixGlobalVar.m_nScreenTime;
    stream << pSamSysParame->m_mixGlobalVar.m_bStandbyLogin; 
    stream << pSamSysParame->m_mixGlobalVar.m_sInitNum;
    stream << pSamSysParame->m_mixGlobalVar.m_nRecipeIndex;

    stream << pSamSysParame->m_mixGlobalVar.m_nRecipeNum;
    stream << pSamSysParame->m_mixGlobalVar.m_bLockIcon;
    stream << pSamSysParame->m_mixGlobalVar.m_strMonitor;
    stream << pSamSysParame->m_mixGlobalVar.m_nMonitorPort;

    stream << pSamSysParame->m_mixGlobalVar.m_nFlickRate;
    stream << pSamSysParame->m_mixGlobalVar.m_bTouchVoice;
    stream << pSamSysParame->m_mixGlobalVar.m_autoLogin;
    stream << pSamSysParame->m_mixGlobalVar.m_bMultiVisitor;
    stream << pSamSysParame->m_mixGlobalVar.m_bCurScreenNum;
    stream << pSamSysParame->m_mixGlobalVar.m_bCurFormulaNum;
    stream << pSamSysParame->m_mixGlobalVar.m_bCurLanguageNum;
    stream << pSamSysParame->m_mixGlobalVar.m_bWordAddrScreenNum;
    stream << pSamSysParame->m_mixGlobalVar.m_keyCurScreen;
    stream << pSamSysParame->m_mixGlobalVar.m_keyCurFormula;
    stream << pSamSysParame->m_mixGlobalVar.m_keyCurLanguage;
    stream << pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen;
    stream << pSamSysParame->m_mixGlobalVar.m_bBitSenceExch;
    temp = pSamSysParame->m_mixGlobalVar.m_vecBitSence.size();
    stream << temp;
    for(int i = 0; i < temp; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].bReset;
        stream << pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].mCtlSceneAddr;
        stream << pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].nCtlStatus;
        stream << pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].sCtlSceneId;
        if(pwnd->getProVersion() >= 3313)
        {
            stream << pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].bClose;
        }
    }
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_ePrinter;
    stream << temp;
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_eDownload;
    stream << temp;
    stream << pSamSysParame->m_mixGlobalVar.m_nIp1;
    stream << pSamSysParame->m_mixGlobalVar.m_nIp2;
    stream << pSamSysParame->m_mixGlobalVar.m_nIp3;
    stream << pSamSysParame->m_mixGlobalVar.m_nIp4;
    stream << pSamSysParame->m_mixGlobalVar.m_nPort;
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_ePicMode;
    stream << temp;
    stream << pSamSysParame->m_mixGlobalVar.m_bStartHMI;
    stream << pSamSysParame->m_mixGlobalVar.m_bClearData;
    stream << pSamSysParame->m_mixGlobalVar.m_bClearAlarm;
    stream << pSamSysParame->m_mixGlobalVar.m_bWriteFormula;
    stream << pSamSysParame->m_mixGlobalVar.m_bUpLoad;
    stream << pSamSysParame->m_mixGlobalVar.m_bUploadPassword;
    stream << pSamSysParame->m_mixGlobalVar.m_strUploadPassword;
    stream << pSamSysParame->m_mixGlobalVar.m_bEncryAccess;
    stream << pSamSysParame->m_mixGlobalVar.m_strAccessPassword;
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_eAuthMode;
    stream << temp;
    temp =  (int)pSamSysParame->m_mixGlobalVar.m_eTimeStyle;
    stream << temp;
    stream << pSamSysParame->m_mixGlobalVar.m_strTimeout;

    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_nUseDay[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_bIsUseDay[i];
    }

    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_gDateTime[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_strDate[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_bIsUseDate[i];
    }
    stream << pSamSysParame->m_mixGlobalVar.m_nLanNum;
    stream << pSamSysParame->m_mixGlobalVar.m_nCurLan;

    int lannum = pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.size();
    stream << lannum;
    for(int i = 0; i < lannum; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.at(i);
    }
    //�û�Ȩ��
    int usernum = pSamSysParame->m_mixGlobalVar.m_vecUser.size();
    stream << usernum;
    for(int i = 0; i < usernum; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strDescrip;
        stream << pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strName;
        stream << pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strPassword;
    }
    //�û���Ȩ��
    int groupnum = pSamSysParame->m_mixGlobalVar.m_vecGroup.size();
    stream << groupnum;
    for(int i = 0; i < groupnum; i++)
    {
        stream << pSamSysParame->m_mixGlobalVar.m_vecGroup.at(i).m_strName;
        stream << pSamSysParame->m_mixGlobalVar.m_vecGroup.at(i).m_strDescrip;
        stream << pSamSysParame->m_mixGlobalVar.m_vecGroup.at(i).m_bNeedAdmin;

        int num =  pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember.size();
        stream << num;
        for(int j = 0; j < num; j++)
        {
            stream << pSamSysParame->m_mixGlobalVar.m_vecGroup.at(i).m_vecMember.at(j).m_strUser;
            stream << pSamSysParame->m_mixGlobalVar.m_vecGroup.at(i).m_vecMember.at(j).m_bIsAdmin;
        }
    }

    /*save m_projectProp data*/
    stream << pSamSysParame->m_projectProp.bAccessOperate;
    stream << pSamSysParame->m_projectProp.bHaveAlarmVoice;
    stream << pSamSysParame->m_projectProp.bHaveTouchVoice ;
    stream << pSamSysParame->m_projectProp.bHideMouse ;
    stream << pSamSysParame->m_projectProp.bLoadInitScene ;
    stream << pSamSysParame->m_projectProp.bNeedUpLoad;
    stream << pSamSysParame->m_projectProp.bNeedUploadCom;
    stream << pSamSysParame->m_projectProp.bScreensaver ;
    stream << pSamSysParame->m_projectProp.bTIPicTransparent;
    stream << pSamSysParame->m_projectProp.bTouchInvalidPic ;
    stream << pSamSysParame->m_projectProp.bUploadComNeedPWD;
    stream << pSamSysParame->m_projectProp.bAlarmCoruscate;
    stream << pSamSysParame->m_projectProp.bClearHisAlarm;
    stream << pSamSysParame->m_projectProp.bStratScreen;
    stream << pSamSysParame->m_projectProp.bClearHisData;
    stream << pSamSysParame->m_projectProp.bDownLoadRecipe;
    stream << pSamSysParame->m_projectProp.bUseHighLevelPWD;
    stream << pSamSysParame->m_projectProp.nDisplayMode;
    stream << pSamSysParame->m_projectProp.nDefautUserId ;
    stream << pSamSysParame->m_projectProp.nFlickerFqc;
    stream << pSamSysParame->m_projectProp.nLoadSceneIndex;
    stream << pSamSysParame->m_projectProp.nLoadSceneTime;
    stream << pSamSysParame->m_projectProp.nNoDataCharFlag;
    stream << pSamSysParame->m_projectProp.nNoDataValueFlag;
    stream << pSamSysParame->m_projectProp.nPicFilePathIndex;
    stream << pSamSysParame->m_projectProp.nSceneHeight;
    stream << pSamSysParame->m_projectProp.nSceneWidth ;
    stream << pSamSysParame->m_projectProp.nScreensaverIndex ;
    stream << pSamSysParame->m_projectProp.nScreensaverTimer ;
    stream << pSamSysParame->m_projectProp.nSetFloatProp;
    stream << pSamSysParame->m_projectProp.nSetFloatType ;
    stream << pSamSysParame->m_projectProp.nStartScreenIndex;
    stream << pSamSysParame->m_projectProp.nDownLoadType;
    stream << pSamSysParame->m_projectProp.nHisdataSave;
    stream << pSamSysParame->m_projectProp.nHisAlarmSave;
    stream << pSamSysParame->m_projectProp.nScreenPictureSave;
    stream << pSamSysParame->m_projectProp.nDownLoadPicCheck;
    stream << pSamSysParame->m_projectProp.sHisdataPath;
    stream << pSamSysParame->m_projectProp.sHisAlarmPath;
    stream << pSamSysParame->m_projectProp.sScreenPicturePath;
    stream << pSamSysParame->m_projectProp.sHighLevelPWD ;
    stream << pSamSysParame->m_projectProp.sPjtFilePath;
    stream << pSamSysParame->m_projectProp.sPjtModel ;
    stream << pSamSysParame->m_projectProp.sTIPicPathList;
    stream << pSamSysParame->m_projectProp.sUploadComPWD;
    stream << pSamSysParame->m_projectProp.sDowndloadIP;
    stream << pSamSysParame->m_projectProp.sPortNO;
    stream << pSamSysParame->m_projectProp.mTIPicColor;
    stream << pSamSysParame->m_projectProp.cAlarmBackColor;
    stream << pSamSysParame->m_projectProp.sBackupForNewVer;

    /*save user level data*/
    for(int i = 0; i< 8; i++)
    {
        stream << pSamSysParame->m_projectProp.mUserLevelList[i].bSelect ;
        stream << pSamSysParame->m_projectProp.mUserLevelList[i].sUserName;
        stream << pSamSysParame->m_projectProp.mUserLevelList[i].sUserPWD ;
        stream << pSamSysParame->m_projectProp.mUserLevelList[i].bUserLevelList[0];
        for(int j = 1; j < 8; j++)
        {
            stream << pSamSysParame->m_projectProp.mUserLevelList[i].bUserLevelList[j] ;
        }
    }

    /*save mPrinterProp data*/
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintCharModel;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintCheckError;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintDate;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintDateEx;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintNo;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintPricesTime;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintStandTime;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintTime;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bPrintTimeEx;
    stream << pSamSysParame->m_projectProp.mPrinterProp.bUsePrinter;
    stream << pSamSysParame->m_projectProp.mPrinterProp.nCheckOe;
    stream << pSamSysParame->m_projectProp.mPrinterProp.nDataBit;
    stream << pSamSysParame->m_projectProp.mPrinterProp.nPrintBaud;
    stream << pSamSysParame->m_projectProp.mPrinterProp.nPrinterType;
    stream << pSamSysParame->m_projectProp.mPrinterProp.nPrintPort;
    stream << pSamSysParame->m_projectProp.mPrinterProp.nStopBit;
    stream << pSamSysParame->m_projectProp.mPrinterProp.sBackupForNewVer;

    /*save m_wHmiInfoToPlc data*/
    stream << pSamSysParame->m_wHmiInfoToPlc.bWCurrLangageId;
    stream << pSamSysParame->m_wHmiInfoToPlc.bWCurrRecipeId;
    stream << pSamSysParame->m_wHmiInfoToPlc.bWCurrSceneId;
    stream << pSamSysParame->m_wHmiInfoToPlc.bWCurrUserId;
    stream << pSamSysParame->m_wHmiInfoToPlc.mLangageIdAddr;
    stream << pSamSysParame->m_wHmiInfoToPlc.mRecipeIdAddr;
    stream << pSamSysParame->m_wHmiInfoToPlc.mSceneIdAddr;
    stream << pSamSysParame->m_wHmiInfoToPlc.mUserIdAddr;
    stream << pSamSysParame->m_wHmiInfoToPlc.sBackupForNewVer;

    /*save m_ctlByPlc data*/
    stream << pSamSysParame->m_ctlByPlc.bBitCtlSceneSwitch;
    stream << pSamSysParame->m_ctlByPlc.bCtlCurrUserId;
    stream << pSamSysParame->m_ctlByPlc.bCtlRecipeChange;
    stream << pSamSysParame->m_ctlByPlc.bCtlWriteRecipe;
    stream << pSamSysParame->m_ctlByPlc.bWordCtlSceneSwitch;
    stream << pSamSysParame->m_ctlByPlc.mChangeRecipeAddr;
    stream << pSamSysParame->m_ctlByPlc.mCtlUserIdAddr;
    stream << pSamSysParame->m_ctlByPlc.mSceneCtlByWAddr;
    stream << pSamSysParame->m_ctlByPlc.mWriteRecipeAddr;
    nVectorSize = pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_CTL_BY_BIT_LIST)
    {
        nVectorSize = MAX_CTL_BY_BIT_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        stream << pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.at(i).bReset;
        stream << pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.at(i).nCtlSceneId;
        stream << pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.at(i).nCtlStatus;
        stream << pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].mCtlSceneAddr;
        stream << pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].sBackupForNewVer;
    }
    stream << pSamSysParame->m_ctlByPlc.sBackupForNewVer;

    /*save m_clockProp data*/
    stream << pSamSysParame->m_clockProp.bDownLoadTime;
    stream << pSamSysParame->m_clockProp.bRTimeFromPlc;
    stream << pSamSysParame->m_clockProp.bWTimeToPlc;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.bReset;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.nAddrLen;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.nDataType;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.nTimeInterval;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr;
    stream << pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr;

    stream << pSamSysParame->m_clockProp.mWTimeToPlc.bReset;
    stream << pSamSysParame->m_clockProp.mWTimeToPlc.nAddrLen;
    stream << pSamSysParame->m_clockProp.mWTimeToPlc.nDataType;
    stream << pSamSysParame->m_clockProp.mWTimeToPlc.nStartType;
    stream << pSamSysParame->m_clockProp.mWTimeToPlc.nTimeInterval;
    stream << pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr;
    stream << pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr;
    stream << pSamSysParame->m_clockProp.sBackupForNewVer;


    /*save m_hmiProtectProp data*/
    stream << pSamSysParame->m_hmiProtectProp.bSelectHMIProtect;
    stream << pSamSysParame->m_hmiProtectProp.nCurrentLevel;
    stream << pSamSysParame->m_hmiProtectProp.nTotalProtectNum;
    nVectorSize = pSamSysParame->m_hmiProtectProp.mProtectList.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_HMI_PROTECT_LIST)
    {
        nVectorSize = MAX_HMI_PROTECT_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        stream << pSamSysParame->m_hmiProtectProp.mProtectList.at(i).nProtectSceneId;
        stream << pSamSysParame->m_hmiProtectProp.mProtectList.at(i).sUnlockPWD;
        stream << pSamSysParame->m_hmiProtectProp.mProtectList.at(i).mProtectDate;
        stream << pSamSysParame->m_hmiProtectProp.mProtectList.at(i).mProtectTime;
        stream << pSamSysParame->m_hmiProtectProp.mProtectList.at(i).sBackupForNewVer;
    }
    stream << pSamSysParame->m_hmiProtectProp.sBackupForNewVer;

    /*save m_languageProp data */
    //stream << pSamSysParame->m_languageProp.nTotalNum;
    //stream << pSamSysParame->m_languageProp.sLanguageNameList;

    /*save m_recipeProp data*/
    stream << pSamSysParame->m_recipeProp.bRecipeExist;
    if(pSamSysParame->m_recipeProp.bRecipeExist)
    {
        stream << pSamSysParame->m_recipeProp.bRaddrSameWaddr;
        stream << pSamSysParame->m_recipeProp.bRRecipeFromPlc;
        stream << pSamSysParame->m_recipeProp.bWRecipeToPlc;
        stream << pSamSysParame->m_recipeProp.mRRecipeAddr;
        stream << pSamSysParame->m_recipeProp.mWRecipeAddr;
        stream << pSamSysParame->m_recipeProp.nDataType;
        stream << pSamSysParame->m_recipeProp.nRecipeLen;
        stream << pSamSysParame->m_recipeProp.nLanIndex;
        stream << pSamSysParame->m_recipeProp.nRecipeTotalNum;
        stream << pSamSysParame->m_recipeProp.sCurrRecAddrRange;
        stream << pSamSysParame->m_recipeProp.sDescription;
        stream << pSamSysParame->m_recipeProp.sRecipeRegNum;
        stream << pSamSysParame->m_recipeProp.sRecMemAddrRange;
        stream << pSamSysParame->m_recipeProp.sRecipeName;
        stream << pSamSysParame->m_recipeProp.nSourceIdList;
        stream << pSamSysParame->m_recipeProp.nTargetIdList;
        stream << pSamSysParame->m_recipeProp.sRecipeData;
        stream << pSamSysParame->m_recipeProp.sRowHeadName;
        stream << pSamSysParame->m_recipeProp.sBackupForNewVer;
    }

    /*save m_qvcPlcCommunicate vector data */
    nVectorSize = pSamSysParame->m_qvcPlcCommunicate.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_PLC_COMMU_LIST)
    {
        nVectorSize = MAX_PLC_COMMU_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nHmiLocation;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nAddrType;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nBandRade;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nCheckType;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nCommunicateTime;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nConnectNum;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nConnectPort;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nConnectType;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nDataBits;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nFwConnectType;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nFwFromStationId;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nPlcAddr;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nPlcAddrInterval;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nRetryTime;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nStopBit;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nTouchScreenAddr;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nTimeout1;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).nTimeout2;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sConnectName;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sDiviceModel;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sDiviceType;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sFwIpAddr;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sFwPort;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sInternetIpAddr;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sInternetPort;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sDataBakeup;
        stream << pSamSysParame->m_qvcPlcCommunicate.at(i).sBackupForNewVer;
    }

    /*save m_qvcInitMaroProp vector data*/
    nVectorSize = pSamSysParame->m_qvcInitMaroProp.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_INIT_MARO_LIST)
    {
        nVectorSize = MAX_INIT_MARO_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        stream << pSamSysParame->m_qvcInitMaroProp.at(i).sLibName;
        stream << pSamSysParame->m_qvcInitMaroProp.at(i).sFucName;
    }

    /*save m_qvcGlobalMaroProp vector data*/
    nVectorSize = pSamSysParame->m_qvcGlobalMaroProp.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_GLOBAL_MARO_LIST)
    {
        nVectorSize = MAX_GLOBAL_MARO_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].sLibName;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].sFucName;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].iRunRate;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].bIfCtrl;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].iCtrlType;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].mCtlAddr;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].iValue;
        stream << pSamSysParame->m_qvcGlobalMaroProp[i].iScriptCount;
    }

    /*save m_qvcdataTransProp vector data*/
    nVectorSize = pSamSysParame->m_qvcdataTransProp.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_DATA_TRANS_LIST)
    {
        nVectorSize = MAX_DATA_TRANS_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        stream << pSamSysParame->m_qvcdataTransProp.at(i).nAddrType;
        stream << pSamSysParame->m_qvcdataTransProp.at(i).nTriggerSpace;
        stream << pSamSysParame->m_qvcdataTransProp.at(i).nTriggerType;
        stream << pSamSysParame->m_qvcdataTransProp.at(i).nWordBitPos;
        stream << pSamSysParame->m_qvcdataTransProp.at(i).bAutomatismOff;
        stream << pSamSysParame->m_qvcdataTransProp[i].mSourceAddr;
        stream << pSamSysParame->m_qvcdataTransProp[i].mTargetAddr;
        stream << pSamSysParame->m_qvcdataTransProp[i].mTriggerAddr;
        stream << pSamSysParame->m_qvcdataTransProp[i].sBackupForNewVer;
        stream << pSamSysParame->m_qvcdataTransProp[i].bDynLength;
        stream << pSamSysParame->m_qvcdataTransProp[i].mLengthAddr;
    }

    /*save m_qvcDigitalAlarm vector data*/
    nVectorSize = pSamSysParame->m_qvcAlarm.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_DIGITAL_ALARM_LIST)
    {
        nVectorSize = MAX_DIGITAL_ALARM_LIST;
    }


    /*save Recipe*/
    int nRecipeSize = pSamSysParame->m_qvcRecipe.size();
    stream << nRecipeSize;//�䷽�����
    for(int i = 0; i < nRecipeSize; i++)
    {
        int nFormulaSize = pSamSysParame->m_qvcRecipe[i].formula.size();
        stream << nFormulaSize;//�䷽����
        for(int j = 0; j < nFormulaSize; j++)
        {
            int nElmentSize = pSamSysParame->m_qvcRecipe[i].formula[j].elment.size();
            stream << nElmentSize;//Ԫ�ظ���
            for(int k = 0; k < nElmentSize; k++)
            {
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].addr;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sAddr;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sAddrType;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sName;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sText;
            }
            stream << pSamSysParame->m_qvcRecipe[i].formula[j].nColum;

            int nNameSize = pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo.size();
            stream << nNameSize;
            for(int k = 0; k < nNameSize; k++)
            {
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].nLanguageId;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].nRecipeId;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeDescri;
                stream << pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeName;
            }

            stream << pSamSysParame->m_qvcRecipe[i].formula[j].sFormulaName;
        }
        stream << pSamSysParame->m_qvcRecipe[i].sName;
        stream << pSamSysParame->m_qvcRecipe[i].sRecipeGDescri;
        stream << pSamSysParame->m_qvcRecipe[i].nRecipeNum;
        stream << pSamSysParame->m_qvcRecipe[i].nRecipeLen;
        stream << pSamSysParame->m_qvcRecipe[i].eDataType;
        stream << pSamSysParame->m_qvcRecipe[i].nLanguageId;
        stream << pSamSysParame->m_qvcRecipe[i].bCtlAddr;
        stream << pSamSysParame->m_qvcRecipe[i].sCtlAddrId;
        stream << pSamSysParame->m_qvcRecipe[i].addrCtl;
        //stream << pSamSysParame->m_qvcRecipe[i].bTransRecipe;
        //stream << pSamSysParame->m_qvcRecipe[i].eRecipeTransType;
        stream << pSamSysParame->m_qvcRecipe[i].bCompleteNotic;
        stream << pSamSysParame->m_qvcRecipe[i].sComNoticAddrId;
        stream << pSamSysParame->m_qvcRecipe[i].addrNotic;
        stream << pSamSysParame->m_qvcRecipe[i].eSaveMedia;
        stream << pSamSysParame->m_qvcRecipe[i].bContniu;
        stream << pSamSysParame->m_qvcRecipe[i].sContniuAddr;

        stream << pSamSysParame->m_qvcRecipe[i].nKeyMark;
        stream << pSamSysParame->m_qvcRecipe[i].nKeyId;
        stream << pSamSysParame->m_qvcRecipe[i].sKeyname;
        stream << pSamSysParame->m_qvcRecipe[i].nBoardX;
        stream << pSamSysParame->m_qvcRecipe[i].nBoardY;

        int nElnameSzie = pSamSysParame->m_qvcRecipe[i].ElmentName.size();
        stream << nElnameSzie;
        for(int j = 0; j < nElnameSzie; j++)
        {
            int nLanguageSize = pSamSysParame->m_qvcRecipe[i].ElmentName[j].size();
            stream << nLanguageSize;
            for(int k = 0; k < nLanguageSize; k++)
            {
                stream << pSamSysParame->m_qvcRecipe[i].ElmentName[j].at(k).nElemIndex;
                stream << pSamSysParame->m_qvcRecipe[i].ElmentName[j].at(k).nLanguageId;
                stream << pSamSysParame->m_qvcRecipe[i].ElmentName[j].at(k).nRecipeGroupId;
                stream << pSamSysParame->m_qvcRecipe[i].ElmentName[j].at(k).sElemName;
            }
        }
    }
    /*save m_qvcAnalogAlarm vector data*/

#if 0
    /*save pUserKeyboard_vector data*/
    nVectorSize = pSamSysParame->pUserKeyboard_vector.size();
    stream << nVectorSize;
    if(nVectorSize > MAX_KEYBOARD_LIST)
    {
        nVectorSize = MAX_KEYBOARD_LIST;
    }
    for(int i = 0; i < nVectorSize; i++)
    {
        SamDrawScene *pScene = pSamSysParame->pUserKeyboard_vector.at(i);
        stream << pScene;
    }
#endif
    //Э��--����
    int connectList=pSamSysParame->m_qvcConnect.size();
    stream << connectList;
    for(int i=0;i<connectList;i++){
        stream << pSamSysParame->m_qvcConnect[i].bUseRelationPort;
        stream << pSamSysParame->m_qvcConnect[i].eConnectPort;
        stream << pSamSysParame->m_qvcConnect[i].eRelationPort;
        stream << pSamSysParame->m_qvcConnect[i].id;
        stream << pSamSysParame->m_qvcConnect[i].nBaudRate;
        stream << pSamSysParame->m_qvcConnect[i].nCheckType;
        stream << pSamSysParame->m_qvcConnect[i].nDataBits;
        stream << pSamSysParame->m_qvcConnect[i].nNetPortNum;
        stream << pSamSysParame->m_qvcConnect[i].nScreenNo;
        stream << pSamSysParame->m_qvcConnect[i].nStopBit;
        stream << pSamSysParame->m_qvcConnect[i].sConnectName;
        stream << pSamSysParame->m_qvcConnect[i].sIpAddr;

        stream << pSamSysParame->m_qvcConnect[i].bMasterScreen;
        stream << pSamSysParame->m_qvcConnect[i].bConnectScreenPort;
        stream << pSamSysParame->m_qvcConnect[i].nSlaveScreenNum;
        //stream << pSamSysParame->m_qvcConnect[i].vProtocols;

        int vProtocolsList=pSamSysParame->m_qvcConnect[i].vProtocols.size();
        stream << vProtocolsList;
        for(int j=0;j<vProtocolsList;j++){
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nIntervalTime;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nMaxRWLen;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nPlcNo;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nReceiveTimeout;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nRetryTime;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.regs;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.sModelName;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nCycleTime;

            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].nIntervalTime;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].nMaxRWLen;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].nPlcNo;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].nReceiveTimeout;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].nRetryTime;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].sFactoryName;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].sName;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].sProtocolName;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].nCycleTime;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].ip;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].port;
            stream << pSamSysParame->m_qvcConnect[i].vProtocols[j].bIsTcpProtocol;
        }
    }
    //������¼
    int nType=0;
    int alarmList=pSamSysParame->m_qvcAlarm.size();
    stream << alarmList;
    for(int i=0;i<alarmList;i++){
        nType = (int)pSamSysParame->m_qvcAlarm[i].dataType;
        stream << nType;
        stream << pSamSysParame->m_qvcAlarm[i].addrType;
        stream << pSamSysParame->m_qvcAlarm[i].alarmName;

        int nAlarm=pSamSysParame->m_qvcAlarm[i].alarms.size();
        stream << nAlarm;
        for(int j=0;j<nAlarm;j++){
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].addr;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].index;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].messages;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].symb;

            nType = (int)pSamSysParame->m_qvcAlarm[i].alarms[j].dataType;
            stream << nType;
            nType = (int)pSamSysParame->m_qvcAlarm[i].alarms[j].eCondtion;
            stream << nType;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].rangeLow;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].rangeHigh;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].bOpenScene;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].sceneName;

            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].bSeneMsg;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].sPhoneNums;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].bAddtoDB;

            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].bPrint;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].bPrintDate;
            stream << pSamSysParame->m_qvcAlarm[i].alarms[j].bPrintTime;

			qDebug() <<"save alarm end" << pSamSysParame->m_qvcAlarm[i].alarms[j].rangeHigh;
        }

    }

    //���ݲɼ�
    int m_vecDataSamplingList=pSamSysParame->m_vecDataSamplingStr.size();
    stream << m_vecDataSamplingList;
    for(int i=0;i<m_vecDataSamplingList;i++){
        stream << pSamSysParame->m_vecDataSamplingStr[i];
    }

    int m_loadDataSampList=pSamSysParame->m_loadDataSampling.size();
    stream << m_loadDataSampList;
    for(int i=0;i<m_loadDataSampList;i++){
        stream << pSamSysParame->m_loadDataSampling[i].bAddrCtlSamp;
        stream << pSamSysParame->m_loadDataSampling[i].bAutoReset;
        stream << pSamSysParame->m_loadDataSampling[i].bContiguousAddr;
        stream << pSamSysParame->m_loadDataSampling[i].bDynSampleRate;
        stream << pSamSysParame->m_loadDataSampling[i].bDynTimeRange;
        stream << pSamSysParame->m_loadDataSampling[i].bFullNotic;
        stream << pSamSysParame->m_loadDataSampling[i].bSaveToFile;
        stream << pSamSysParame->m_loadDataSampling[i].dynRateAddr;
        stream << (int)pSamSysParame->m_loadDataSampling[i].eDateShowType;
        stream << (int)pSamSysParame->m_loadDataSampling[i].eDealSampFull;
        stream << pSamSysParame->m_loadDataSampling[i].endTimeAddr;
        stream << (int)pSamSysParame->m_loadDataSampling[i].eSampType;
        stream << (int)pSamSysParame->m_loadDataSampling[i].eSaveMedium;
        stream << pSamSysParame->m_loadDataSampling[i].keyCtlSaveAddr;
        stream << pSamSysParame->m_loadDataSampling[i].nDataLen;
        stream << pSamSysParame->m_loadDataSampling[i].nDataSampType;
        stream << pSamSysParame->m_loadDataSampling[i].nDecimalLen;
        stream << pSamSysParame->m_loadDataSampling[i].nDigitLen;
        stream << pSamSysParame->m_loadDataSampling[i].nEndHour;
        stream << pSamSysParame->m_loadDataSampling[i].nEndMinute;
        stream << pSamSysParame->m_loadDataSampling[i].nSampCountUnit;
        stream << pSamSysParame->m_loadDataSampling[i].nSampRate;
        stream << pSamSysParame->m_loadDataSampling[i].nSampRateUnit;
        stream << pSamSysParame->m_loadDataSampling[i].nSampTime;
        stream << pSamSysParame->m_loadDataSampling[i].nSampTimes;
        stream << pSamSysParame->m_loadDataSampling[i].nSampUnit;
        stream << pSamSysParame->m_loadDataSampling[i].nStartHour;
        stream << pSamSysParame->m_loadDataSampling[i].nStartMinute;
        stream << pSamSysParame->m_loadDataSampling[i].startTimeAddr;
        stream << pSamSysParame->m_loadDataSampling[i].strCtlSampAddrId;
        stream << pSamSysParame->m_loadDataSampling[i].strNoticAddrId;

        int tableList=pSamSysParame->m_loadDataSampling[i].m_dataTable.size();
        stream << tableList;
        for(int j=0;j<tableList;j++){
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].bZoom;
            stream << (int)pSamSysParame->m_loadDataSampling[i].m_dataTable[j].dataType;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].inputMax;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].inputMin;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].keyAddress;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].nAddrNumber;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].outputMax;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].outputMin;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].decLen;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].bRound;
            stream << pSamSysParame->m_loadDataSampling[i].m_dataTable[j].name;
			qDebug() <<"save end" <<pSamSysParame->m_loadDataSampling[i].m_dataTable[j].outputMin;
        }
        stream << pSamSysParame->m_loadDataSampling[i].bAutoSave;
        stream << pSamSysParame->m_loadDataSampling[i].nSaveHour;

        stream << pSamSysParame->m_loadDataSampling[i].bPrint;
        stream << pSamSysParame->m_loadDataSampling[i].bPrintDate;
        stream << pSamSysParame->m_loadDataSampling[i].bPrintTime;
    }
    //��������洢������
    stream << pSamSysParame->m_PowerProtect.startLB;
    stream << pSamSysParame->m_PowerProtect.lengthLB;
    stream << pSamSysParame->m_PowerProtect.startLW;
    stream << pSamSysParame->m_PowerProtect.lengthLW;

    //����������
    stream << pSamSysParame->m_VarRecord.size();
    foreach(VarRecord rcd,pSamSysParame->m_VarRecord)
    {
        stream << rcd.sVarName;
        stream << rcd.mAddr;
        stream << (int)rcd.mType;

    }

    //����ʱ���
    QVector<QList<ScheItem> > sItems;
    sItems = pSamSysParame->schedulers->getItems();
    stream << sItems.size();
    qDebug() << "save weekly size :"<< sItems.size();
    int weekday = 0;
    foreach(QList<ScheItem> itemlst,sItems)
    {

        stream << itemlst.size();
        qDebug() << "weekday: "<< weekday;
        qDebug() << "save ScheItem size :"<< itemlst.size();
        foreach(ScheItem item,itemlst)
        {
            stream << item.timeType;
            stream << item.time;
            stream << item.kTimeAddr;
            stream << (int)item.eWeek;
            stream << (int)item.eActionType;
            stream << item.kActionAddr;
            stream << item.eDataType;
            stream << item.valueType;
            stream << item.nValue;
            stream << item.kValueAddr;
            stream << item.bControl;
            stream << item.kControlAddr;
        }
        weekday++;
    }

    return stream;
}

QDataStream &operator>>(QDataStream &stream, QSamSysParame *pSamSysParame)
{
    if(!pSamSysParame) return stream;

    int nVectorSize = 0;
    stream >> pSamSysParame->nUserDefKeyboardCount;
    /*save m_fileprotect data*/
    stream >> pSamSysParame->m_fileProtect.bNeedFileProtect;
    stream >> pSamSysParame->m_fileProtect.sProtectPWD;

    //czq
    /*save GlobalVariable data*/
    int temp=0;
    stream >> pSamSysParame->m_mixGlobalVar.m_strModelName;
    if(pwnd->getProVersion() < 3270)//�ɰ汾
    {
        pSamSysParame->m_mixGlobalVar.m_strHmiName = "";
    }
    else
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_strHmiName;
    }
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_eScreenDir=(ScrDirType)temp;
    stream >> pSamSysParame->m_mixGlobalVar.m_strModelSize;
    stream >> pSamSysParame->m_mixGlobalVar.m_strResolution;
    stream >> pSamSysParame->m_mixGlobalVar.m_strColor;
    stream >> pSamSysParame->m_mixGlobalVar.m_strUsermemory;
    //stream >> pSamSysParame->m_mixGlobalVar.m_strNandFlash;
    stream >> pSamSysParame->m_mixGlobalVar.m_strPowersupply;
    stream >> pSamSysParame->m_mixGlobalVar.m_strCom1;
    stream >> pSamSysParame->m_mixGlobalVar.m_strCom2;
    stream >> pSamSysParame->m_mixGlobalVar.m_strUsb;
    stream >> pSamSysParame->m_mixGlobalVar.m_strMaxscreennumber;
    stream >> pSamSysParame->m_mixGlobalVar.m_nScreenWidth;
    stream >> pSamSysParame->m_mixGlobalVar.m_nScreenHeight;
    stream >> pSamSysParame->m_mixGlobalVar.m_bUseLogo;
    stream >> pSamSysParame->m_mixGlobalVar.m_sLogoNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_strLogoNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_bStandby;
    stream >> pSamSysParame->m_mixGlobalVar.m_bStandbyMode;
    stream >> pSamSysParame->m_mixGlobalVar.m_sStandbyNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_strStandbyNum;
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_eStandbyLight=(LightMode)temp;
    stream >> pSamSysParame->m_mixGlobalVar.m_nScreenTime;
    stream >> pSamSysParame->m_mixGlobalVar.m_bStandbyLogin;
    stream >> pSamSysParame->m_mixGlobalVar.m_sInitNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_nRecipeIndex;

    if(pwnd->getProVersion() < 3270)//�ɰ汾
    {
        pSamSysParame->m_mixGlobalVar.m_bLockIcon = true;
        pSamSysParame->m_mixGlobalVar.m_strMonitor = "";
    }
    else
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_nRecipeNum;
        stream >> pSamSysParame->m_mixGlobalVar.m_bLockIcon;
        stream >> pSamSysParame->m_mixGlobalVar.m_strMonitor;
    }
    if(pwnd->getProVersion() < 3451)
    {
        pSamSysParame->m_mixGlobalVar.m_nMonitorPort = 743;
    }
    else
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_nMonitorPort;
    }

    stream >> pSamSysParame->m_mixGlobalVar.m_nFlickRate;
    stream >> pSamSysParame->m_mixGlobalVar.m_bTouchVoice;

    if(pwnd->getProVersion() < 2053)//�ɰ汾
    {
        pSamSysParame->m_mixGlobalVar.m_autoLogin = false;
    }
    else
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_autoLogin;
        if(pwnd->getProVersion() < 3270)
        {
            pSamSysParame->m_mixGlobalVar.m_autoLogin = false;
        }
    }

    if(pwnd->getProVersion() < 3450)
    {
        pSamSysParame->m_mixGlobalVar.m_bMultiVisitor = false;
    }
    else
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_bMultiVisitor;
    }
    stream >> pSamSysParame->m_mixGlobalVar.m_bCurScreenNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_bCurFormulaNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_bCurLanguageNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_bWordAddrScreenNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_keyCurScreen;
    stream >> pSamSysParame->m_mixGlobalVar.m_keyCurFormula;
    stream >> pSamSysParame->m_mixGlobalVar.m_keyCurLanguage;
    stream >> pSamSysParame->m_mixGlobalVar.m_keyWordAddrScreen;
    stream >> pSamSysParame->m_mixGlobalVar.m_bBitSenceExch;
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_vecBitSence.resize(temp);
    for(int i = 0; i < temp; i++)
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].bReset;
        stream >> pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].mCtlSceneAddr;
        stream >> pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].nCtlStatus;
        stream >> pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].sCtlSceneId;
        if(pwnd->getProVersion() >= 3313)
        {
            stream >> pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].bClose;
        }
        else
        {
            pSamSysParame->m_mixGlobalVar.m_vecBitSence[i].bClose = false;
        }
    }
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_ePrinter=(PrinterType)temp;
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_eDownload=(DownloadMode)temp;
    stream >> pSamSysParame->m_mixGlobalVar.m_nIp1;
    stream >> pSamSysParame->m_mixGlobalVar.m_nIp2;
    stream >> pSamSysParame->m_mixGlobalVar.m_nIp3;
    stream >> pSamSysParame->m_mixGlobalVar.m_nIp4;
    stream >> pSamSysParame->m_mixGlobalVar.m_nPort;
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_ePicMode=(PicSaveMode)temp;
    stream >> pSamSysParame->m_mixGlobalVar.m_bStartHMI;
    stream >> pSamSysParame->m_mixGlobalVar.m_bClearData;
    stream >> pSamSysParame->m_mixGlobalVar.m_bClearAlarm;
    stream >> pSamSysParame->m_mixGlobalVar.m_bWriteFormula;
    stream >> pSamSysParame->m_mixGlobalVar.m_bUpLoad;
    stream >> pSamSysParame->m_mixGlobalVar.m_bUploadPassword;
    stream >> pSamSysParame->m_mixGlobalVar.m_strUploadPassword;
    stream >> pSamSysParame->m_mixGlobalVar.m_bEncryAccess;
    stream >> pSamSysParame->m_mixGlobalVar.m_strAccessPassword;
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_eAuthMode=(AuthorizeMode)temp;
    stream >> temp;
    pSamSysParame->m_mixGlobalVar.m_eTimeStyle=(AuthTimeSet)temp;
    stream >> pSamSysParame->m_mixGlobalVar.m_strTimeout; 

    for(int i = 0; i < 5; i++)
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_nUseDay[i];
    }
    for(int i = 0; i < 5; i++)
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_sUseDayPassword[i];
    }
    if(pwnd->getProVersion() < 2052)
    {
        for(int i = 0; i < 5; i++)
        {
            pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[i] = "";
        }
        for(int i = 0; i < 5; i++)
        {
            pSamSysParame->m_mixGlobalVar.m_bIsUseDay[i] = false;
        }
    }
    else
    {
        for(int i = 0; i < 5; i++)
        {
            stream >> pSamSysParame->m_mixGlobalVar.m_strTimeoutDay[i];
        }
        for(int i = 0; i < 5; i++)
        {
            stream >> pSamSysParame->m_mixGlobalVar.m_bIsUseDay[i];
        }
    }

    if(pwnd->getProVersion() < 2052)
    {
        QDate dt;
        for(int i = 0; i < 5; i++)
        {
            stream >> dt;
        }
    }
    else
    {
        for(int i = 0; i < 5; i++)
        {
            stream >> pSamSysParame->m_mixGlobalVar.m_gDateTime[i];
        }
    }
    for(int i = 0; i < 5; i++)
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_strDate[i];
    }
    if(pwnd->getProVersion() < 2052)
    {
        for(int i = 0; i < 5; i++)
        {
            pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[i] = "";
        }
        for(int i = 0; i < 5; i++)
        {
            pSamSysParame->m_mixGlobalVar.m_bIsUseDate[i] = false;
        }
    }
    else
    {
        for(int i = 0; i < 5; i++)
        {
            stream >> pSamSysParame->m_mixGlobalVar.m_strTimeoutDate[i];
        }
        for(int i = 0; i < 5; i++)
        {
            stream >> pSamSysParame->m_mixGlobalVar.m_bIsUseDate[i];
        }
    }

    stream >> pSamSysParame->m_mixGlobalVar.m_nLanNum;
    stream >> pSamSysParame->m_mixGlobalVar.m_nCurLan;

    int lannum = 0;
    stream >> lannum;
    pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList.resize(lannum);
    for(int i = 0; i < lannum; i++)
    {
        QString str ;
        stream >> str;
        pSamSysParame->m_mixGlobalVar.m_vecLanguageNameList[i]=str;
    }

    int usernum = 0;
    stream >> usernum;
    pSamSysParame->m_mixGlobalVar.m_vecUser.resize(usernum);
    for(int i = 0; i < usernum; i++)
    {
        stream >> pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strDescrip;
        stream >> pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strName;
        stream >> pSamSysParame->m_mixGlobalVar.m_vecUser[i].m_strPassword;
    }

    int groupnum = 0;
    stream >>groupnum;
    pSamSysParame->m_mixGlobalVar.m_vecGroup.resize(groupnum);
    for(int i = 0; i < groupnum; i++)
    {
        QString str;
        stream >> str;
        pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_strName=str;
        stream >> str;
        pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_strDescrip=str;

        if(pwnd->getProVersion() < 3258)//�ɰ汾
        {
            pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_bNeedAdmin = false;
        }
        else
        {
            bool b;
            stream >> b;
            pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_bNeedAdmin = b;
        }

        int num =  0;
        stream >> num;
        pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember.resize(num);

        if(pwnd->getProVersion() < 3258)//�ɰ汾
        {
            for(int j = 0; j < num; j++)
            {
                QString b;
                stream >> b;
                pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember[j].m_strUser = b;
                pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember[j].m_bIsAdmin = false;
            }
        }
        else
        {
            for(int j = 0; j < num; j++)
            {
                QString str;
                bool    bAdmin;
                stream >> str;
                stream >> bAdmin;
                pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember[j].m_strUser = str;
                pSamSysParame->m_mixGlobalVar.m_vecGroup[i].m_vecMember[j].m_bIsAdmin = bAdmin;
            }
        }
    }

    /*save m_projectProp data*/
    stream >> pSamSysParame->m_projectProp.bAccessOperate;
    stream >> pSamSysParame->m_projectProp.bHaveAlarmVoice;
    stream >> pSamSysParame->m_projectProp.bHaveTouchVoice ;
    stream >> pSamSysParame->m_projectProp.bHideMouse ;
    stream >> pSamSysParame->m_projectProp.bLoadInitScene ;
    stream >> pSamSysParame->m_projectProp.bNeedUpLoad;
    stream >> pSamSysParame->m_projectProp.bNeedUploadCom;
    stream >> pSamSysParame->m_projectProp.bScreensaver ;
    stream >> pSamSysParame->m_projectProp.bTIPicTransparent;
    stream >> pSamSysParame->m_projectProp.bTouchInvalidPic ;
    stream >> pSamSysParame->m_projectProp.bUploadComNeedPWD;
    stream >> pSamSysParame->m_projectProp.bAlarmCoruscate;
    stream >> pSamSysParame->m_projectProp.bClearHisAlarm;
    stream >> pSamSysParame->m_projectProp.bStratScreen;
    stream >> pSamSysParame->m_projectProp.bClearHisData;
    stream >> pSamSysParame->m_projectProp.bDownLoadRecipe;
    stream >> pSamSysParame->m_projectProp.bUseHighLevelPWD;
    stream >> pSamSysParame->m_projectProp.nDisplayMode;
    stream >> pSamSysParame->m_projectProp.nDefautUserId ;
    stream >> pSamSysParame->m_projectProp.nFlickerFqc;
    stream >> pSamSysParame->m_projectProp.nLoadSceneIndex;
    stream >> pSamSysParame->m_projectProp.nLoadSceneTime;
    stream >> pSamSysParame->m_projectProp.nNoDataCharFlag;
    stream >> pSamSysParame->m_projectProp.nNoDataValueFlag;
    stream >> pSamSysParame->m_projectProp.nPicFilePathIndex;
    stream >> pSamSysParame->m_projectProp.nSceneHeight;
    stream >> pSamSysParame->m_projectProp.nSceneWidth ;
    stream >> pSamSysParame->m_projectProp.nScreensaverIndex ;
    stream >> pSamSysParame->m_projectProp.nScreensaverTimer ;
    stream >> pSamSysParame->m_projectProp.nSetFloatProp;
    stream >> pSamSysParame->m_projectProp.nSetFloatType ;
    stream >> pSamSysParame->m_projectProp.nStartScreenIndex;
    stream >> pSamSysParame->m_projectProp.nDownLoadType;
    stream >> pSamSysParame->m_projectProp.nHisdataSave;
    stream >> pSamSysParame->m_projectProp.nHisAlarmSave;
    stream >> pSamSysParame->m_projectProp.nScreenPictureSave;
    stream >> pSamSysParame->m_projectProp.nDownLoadPicCheck;
    stream >> pSamSysParame->m_projectProp.sHisdataPath;
    stream >> pSamSysParame->m_projectProp.sHisAlarmPath;
    stream >> pSamSysParame->m_projectProp.sScreenPicturePath;
    stream >> pSamSysParame->m_projectProp.sHighLevelPWD ;
    stream >> pSamSysParame->m_projectProp.sPjtFilePath;
    stream >> pSamSysParame->m_projectProp.sPjtModel ;
    stream >> pSamSysParame->m_projectProp.sTIPicPathList;
    stream >> pSamSysParame->m_projectProp.sUploadComPWD;
    stream >> pSamSysParame->m_projectProp.sDowndloadIP;
    stream >> pSamSysParame->m_projectProp.sPortNO;
    stream >> pSamSysParame->m_projectProp.mTIPicColor;
    stream >> pSamSysParame->m_projectProp.cAlarmBackColor;
    stream >> pSamSysParame->m_projectProp.sBackupForNewVer;
    /*save user level data*/
    for(int i = 0; i< 8; i++)
    {
        stream >> pSamSysParame->m_projectProp.mUserLevelList[i].bSelect ;
        stream >> pSamSysParame->m_projectProp.mUserLevelList[i].sUserName;
        stream >> pSamSysParame->m_projectProp.mUserLevelList[i].sUserPWD ;
        stream >> pSamSysParame->m_projectProp.mUserLevelList[i].bUserLevelList[0];
        for(int j = 1; j < 8; j++)
        {
            stream >> pSamSysParame->m_projectProp.mUserLevelList[i].bUserLevelList[j];
        }
    }
    /*save mPrinterProp data*/
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintCharModel;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintCheckError;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintDate;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintDateEx;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintNo;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintPricesTime;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintStandTime;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintTime;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bPrintTimeEx;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.bUsePrinter;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.nCheckOe;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.nDataBit;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.nPrintBaud;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.nPrinterType;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.nPrintPort;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.nStopBit;
    stream >> pSamSysParame->m_projectProp.mPrinterProp.sBackupForNewVer;

    /*save m_wHmiInfoToPlc data*/
    stream >> pSamSysParame->m_wHmiInfoToPlc.bWCurrLangageId;
    stream >> pSamSysParame->m_wHmiInfoToPlc.bWCurrRecipeId;
    stream >> pSamSysParame->m_wHmiInfoToPlc.bWCurrSceneId;
    stream >> pSamSysParame->m_wHmiInfoToPlc.bWCurrUserId;
    stream >> pSamSysParame->m_wHmiInfoToPlc.mLangageIdAddr;
    stream >> pSamSysParame->m_wHmiInfoToPlc.mRecipeIdAddr;
    stream >> pSamSysParame->m_wHmiInfoToPlc.mSceneIdAddr;
    stream >> pSamSysParame->m_wHmiInfoToPlc.mUserIdAddr;
    stream >> pSamSysParame->m_wHmiInfoToPlc.sBackupForNewVer;

    /*save m_ctlByPlc data*/
    stream >> pSamSysParame->m_ctlByPlc.bBitCtlSceneSwitch;
    stream >> pSamSysParame->m_ctlByPlc.bCtlCurrUserId;
    stream >> pSamSysParame->m_ctlByPlc.bCtlRecipeChange;
    stream >> pSamSysParame->m_ctlByPlc.bCtlWriteRecipe;
    stream >> pSamSysParame->m_ctlByPlc.bWordCtlSceneSwitch;
    stream >> pSamSysParame->m_ctlByPlc.mChangeRecipeAddr;
    stream >> pSamSysParame->m_ctlByPlc.mCtlUserIdAddr;
    stream >> pSamSysParame->m_ctlByPlc.mSceneCtlByWAddr;
    stream >> pSamSysParame->m_ctlByPlc.mWriteRecipeAddr;
    stream >> nVectorSize;
    if(nVectorSize > MAX_CTL_BY_BIT_LIST)
    {
        nVectorSize = MAX_CTL_BY_BIT_LIST;
    }
    pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.clear();
    pSamSysParame->m_ctlByPlc.mSceneCtlByBitList.resize(nVectorSize);
    for(int i = 0; i < nVectorSize; i++)
    {
        stream >> pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].bReset;
        stream >> pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].nCtlSceneId;
        stream >> pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].nCtlStatus;
        stream >> pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].mCtlSceneAddr;
        stream >> pSamSysParame->m_ctlByPlc.mSceneCtlByBitList[i].sBackupForNewVer;
    }
    stream >> pSamSysParame->m_ctlByPlc.sBackupForNewVer;

    /*save m_clockProp data*/
    stream >> pSamSysParame->m_clockProp.bDownLoadTime;
    stream >> pSamSysParame->m_clockProp.bRTimeFromPlc;
    stream >> pSamSysParame->m_clockProp.bWTimeToPlc;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.bReset;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.nAddrLen;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.nDataType;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.nStartType;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.nTimeInterval;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.mCtlAddr;
    stream >> pSamSysParame->m_clockProp.mRTimeFromPlc.mTriggerAddr;

    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.bReset;
    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.nAddrLen;
    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.nDataType;
    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.nStartType;
    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.nTimeInterval;
    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.mCtlAddr;
    stream >> pSamSysParame->m_clockProp.mWTimeToPlc.mTriggerAddr;
    stream >> pSamSysParame->m_clockProp.sBackupForNewVer;

    /*save m_hmiProtectProp data*/
    stream >> pSamSysParame->m_hmiProtectProp.bSelectHMIProtect;
    stream >> pSamSysParame->m_hmiProtectProp.nCurrentLevel;
    stream >> pSamSysParame->m_hmiProtectProp.nTotalProtectNum;
    stream >> nVectorSize;
    if(nVectorSize > MAX_HMI_PROTECT_LIST)
    {
        nVectorSize = MAX_HMI_PROTECT_LIST;
    }
    pSamSysParame->m_hmiProtectProp.mProtectList.clear();
    pSamSysParame->m_hmiProtectProp.mProtectList.resize(nVectorSize);
    for(int i = 0; i < nVectorSize; i++)
    {
        stream >> pSamSysParame->m_hmiProtectProp.mProtectList[i].nProtectSceneId;
        stream >> pSamSysParame->m_hmiProtectProp.mProtectList[i].sUnlockPWD;
        stream >> pSamSysParame->m_hmiProtectProp.mProtectList[i].mProtectDate;
        stream >> pSamSysParame->m_hmiProtectProp.mProtectList[i].mProtectTime;
        stream >> pSamSysParame->m_hmiProtectProp.mProtectList[i].sBackupForNewVer;
    }
    stream >> pSamSysParame->m_hmiProtectProp.sBackupForNewVer;

    /*save m_languageProp data */
    //stream >> pSamSysParame->m_languageProp.nTotalNum;
    //stream >> pSamSysParame->m_languageProp.sLanguageNameList;

    //czq
    /*save m_historyLogData data */
    /*stream >> pSamSysParame->m_historyLogData.bHistoryDataExist;
    if(pSamSysParame->m_historyLogData.bHistoryDataExist)
    {
        stream >> pSamSysParame->m_historyLogData.bFullNotic;
        stream >> pSamSysParame->m_historyLogData.bFullStop;
        stream >> pSamSysParame->m_historyLogData.bAutoOff;
        stream >> pSamSysParame->m_historyLogData.nFullNoticPercent;
        stream >> pSamSysParame->m_historyLogData.nSampleLen;
        stream >> pSamSysParame->m_historyLogData.nSampleSize;
        stream >> pSamSysParame->m_historyLogData.nSampleType;
        stream >> pSamSysParame->m_historyLogData.nTimeInterval;
        stream >> pSamSysParame->m_historyLogData.nTriggerTime;
        stream >> pSamSysParame->m_historyLogData.sHistoryDataName;
        stream >> pSamSysParame->m_historyLogData.mFullNoticAddr;
        stream >> pSamSysParame->m_historyLogData.mReadAddr;
        stream >> pSamSysParame->m_historyLogData.mTriggerAddr;

        stream >> nVectorSize;
        if(nVectorSize > MAX_HISTORY_SAMPLE_LIST)
        {
            nVectorSize = MAX_HISTORY_SAMPLE_LIST;
        }
        pSamSysParame->m_historyLogData.mSampleList.clear();
        pSamSysParame->m_historyLogData.mSampleList.resize(nVectorSize);
        for(int i = 0; i < nVectorSize; i++)
        {
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].bZoom;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].nDataLen;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].nDataPointLen;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].nDataShowType;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].nDataType;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].sAddrName;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].sOffsetStr;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].sZoomStr;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].sNameList;
            stream >> pSamSysParame->m_historyLogData.mSampleList[i].sBackupForNewVer;

        }
    }
    stream >> pSamSysParame->m_historyLogData.sBackupForNewVer;*/

    /*save m_recipeProp data*/
    stream >> pSamSysParame->m_recipeProp.bRecipeExist;
    if(pSamSysParame->m_recipeProp.bRecipeExist)
    {
        stream >> pSamSysParame->m_recipeProp.bRaddrSameWaddr;
        stream >> pSamSysParame->m_recipeProp.bRRecipeFromPlc;
        stream >> pSamSysParame->m_recipeProp.bWRecipeToPlc;
        stream >> pSamSysParame->m_recipeProp.mRRecipeAddr;
        stream >> pSamSysParame->m_recipeProp.mWRecipeAddr;
        stream >> pSamSysParame->m_recipeProp.nDataType;
        stream >> pSamSysParame->m_recipeProp.nRecipeLen;
        stream >> pSamSysParame->m_recipeProp.nLanIndex;
        stream >> pSamSysParame->m_recipeProp.nRecipeTotalNum;
        stream >> pSamSysParame->m_recipeProp.sCurrRecAddrRange;
        stream >> pSamSysParame->m_recipeProp.sDescription;
        stream >> pSamSysParame->m_recipeProp.sRecipeRegNum;
        stream >> pSamSysParame->m_recipeProp.sRecMemAddrRange;
        stream >> pSamSysParame->m_recipeProp.sRecipeName;
        stream >> pSamSysParame->m_recipeProp.nSourceIdList;
        stream >> pSamSysParame->m_recipeProp.nTargetIdList;
        stream >> pSamSysParame->m_recipeProp.sRecipeData;
        stream >> pSamSysParame->m_recipeProp.sRowHeadName;
        stream >> pSamSysParame->m_recipeProp.sBackupForNewVer;
    }

    /*save m_qvcPlcCommunicate vector data */
    stream >> nVectorSize;
    if(nVectorSize > MAX_PLC_COMMU_LIST)
    {
        nVectorSize = MAX_PLC_COMMU_LIST;
    }
    pSamSysParame->m_qvcPlcCommunicate.clear();
    pSamSysParame->m_qvcPlcCommunicate.resize(nVectorSize);
    for(int i = 0; i < nVectorSize; i++)
    {
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nHmiLocation;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nAddrType;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nBandRade;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nCheckType;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nCommunicateTime;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nConnectNum;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nConnectPort;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nConnectType;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nDataBits;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nFwConnectType;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nFwFromStationId;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nPlcAddr;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nPlcAddrInterval;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nRetryTime;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nStopBit;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nTouchScreenAddr;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nTimeout1;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].nTimeout2;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sConnectName;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sDiviceModel;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sDiviceType;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sFwIpAddr;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sFwPort;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sInternetIpAddr;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sInternetPort;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sDataBakeup;
        stream >> pSamSysParame->m_qvcPlcCommunicate[i].sBackupForNewVer;
    }

    /*save m_qvcInitMaroProp vector data*/
    stream >> nVectorSize;
    if(nVectorSize > MAX_INIT_MARO_LIST)
    {
        nVectorSize = MAX_INIT_MARO_LIST;
    }
    pSamSysParame->m_qvcInitMaroProp.clear();
    pSamSysParame->m_qvcInitMaroProp.resize(nVectorSize);
    for(int i = 0; i < nVectorSize; i++)
    {
        stream >> pSamSysParame->m_qvcInitMaroProp[i].sLibName;
        stream >> pSamSysParame->m_qvcInitMaroProp[i].sFucName;
    }

    /*save m_qvcGlobalMaroProp vector data*/
    stream >> nVectorSize;
    if(nVectorSize > MAX_GLOBAL_MARO_LIST)
    {
        nVectorSize = MAX_GLOBAL_MARO_LIST;
    }
    pSamSysParame->m_qvcGlobalMaroProp.clear();
    pSamSysParame->m_qvcGlobalMaroProp.resize(nVectorSize);
    for(int i = 0; i < nVectorSize; i++)
    {
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].sLibName;
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].sFucName;
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].iRunRate;
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].bIfCtrl;
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].iCtrlType;
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].mCtlAddr;
        stream >> pSamSysParame->m_qvcGlobalMaroProp[i].iValue;
        if(pwnd->getProVersion() >= 3448)
        {
            stream >> pSamSysParame->m_qvcGlobalMaroProp[i].iScriptCount;
        }
        else
        {
            pSamSysParame->m_qvcGlobalMaroProp[i].iScriptCount = 0;
        }
    }

    /*save m_qvcdataTransProp vector data*/
    stream >> nVectorSize;
    if(nVectorSize > MAX_DATA_TRANS_LIST)
    {
        nVectorSize = MAX_DATA_TRANS_LIST;
    }
    pSamSysParame->m_qvcdataTransProp.clear();
    pSamSysParame->m_qvcdataTransProp.resize(nVectorSize);
    for(int i = 0; i < nVectorSize; i++)
    {
        stream >> pSamSysParame->m_qvcdataTransProp[i].nAddrType;
        stream >> pSamSysParame->m_qvcdataTransProp[i].nTriggerSpace;
        stream >> pSamSysParame->m_qvcdataTransProp[i].nTriggerType;
        stream >> pSamSysParame->m_qvcdataTransProp[i].nWordBitPos;
        stream >> pSamSysParame->m_qvcdataTransProp[i].bAutomatismOff;
        stream >> pSamSysParame->m_qvcdataTransProp[i].mSourceAddr;
        stream >> pSamSysParame->m_qvcdataTransProp[i].mTargetAddr;
        stream >> pSamSysParame->m_qvcdataTransProp[i].mTriggerAddr;
        stream >> pSamSysParame->m_qvcdataTransProp[i].sBackupForNewVer;
        if (pwnd->getProVersion() < 3449)
        {
            pSamSysParame->m_qvcdataTransProp[i].bDynLength = false;
        }
        else
        {
            stream >> pSamSysParame->m_qvcdataTransProp[i].bDynLength;
            stream >> pSamSysParame->m_qvcdataTransProp[i].mLengthAddr;
        }
    }

    /*save m_qvcDigitalAlarm vector data*/
    stream >> nVectorSize;
    if(nVectorSize > MAX_DIGITAL_ALARM_LIST)
    {
        nVectorSize = MAX_DIGITAL_ALARM_LIST;
    }
    pSamSysParame->m_qvcAlarm.clear();
    pSamSysParame->m_qvcAlarm.resize(nVectorSize);


    /*save m_qvcAnalogAlarm vector data*/

    //load recipe begin
    int nRecipeSize = 0;
    stream >> nRecipeSize;//�䷽�����
    pSamSysParame->m_qvcRecipe.resize(nRecipeSize);
    for(int i = 0; i < nRecipeSize; i++)
    {
        int nFormulaSize = 0;
        stream >> nFormulaSize;//�䷽����
        pSamSysParame->m_qvcRecipe[i].formula.resize(nFormulaSize);
        for(int j = 0; j < nFormulaSize; j++)
        {
            int nElmentSize = 0;
            stream >> nElmentSize;//Ԫ�ظ���
            pSamSysParame->m_qvcRecipe[i].formula[j].elment.resize(nElmentSize);
            for(int k = 0; k < nElmentSize; k++)
            {
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].addr;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sAddr;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sAddrType;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sName;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].elment[k].sText;
            }
            stream >> pSamSysParame->m_qvcRecipe[i].formula[j].nColum;

            int nNameSize = 0;
            stream >> nNameSize;
            pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo.resize(nNameSize);
            for(int k = 0; k < nNameSize; k++)
            {
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].nLanguageId;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].nRecipeId;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeDescri;
                stream >> pSamSysParame->m_qvcRecipe[i].formula[j].RecipeInfo[k].sRecipeName;
            }

            stream >> pSamSysParame->m_qvcRecipe[i].formula[j].sFormulaName;
        }
        stream >> pSamSysParame->m_qvcRecipe[i].sName;
        stream >> pSamSysParame->m_qvcRecipe[i].sRecipeGDescri;
        stream >> pSamSysParame->m_qvcRecipe[i].nRecipeNum;
        stream >> pSamSysParame->m_qvcRecipe[i].nRecipeLen;
        stream >> pSamSysParame->m_qvcRecipe[i].eDataType;
        stream >> pSamSysParame->m_qvcRecipe[i].nLanguageId;
        stream >> pSamSysParame->m_qvcRecipe[i].bCtlAddr;
        stream >> pSamSysParame->m_qvcRecipe[i].sCtlAddrId;
        stream >> pSamSysParame->m_qvcRecipe[i].addrCtl;
        //stream >> pSamSysParame->m_qvcRecipe[i].bTransRecipe;
        //stream >> pSamSysParame->m_qvcRecipe[i].eRecipeTransType;
        stream >> pSamSysParame->m_qvcRecipe[i].bCompleteNotic;
        stream >> pSamSysParame->m_qvcRecipe[i].sComNoticAddrId;
        stream >> pSamSysParame->m_qvcRecipe[i].addrNotic;
        stream >> pSamSysParame->m_qvcRecipe[i].eSaveMedia;
        stream >> pSamSysParame->m_qvcRecipe[i].bContniu;
        stream >> pSamSysParame->m_qvcRecipe[i].sContniuAddr;

        if(pwnd->getProVersion() < 2527)
        {
            pSamSysParame->m_qvcRecipe[i].nKeyMark = false;
            pSamSysParame->m_qvcRecipe[i].nKeyId = 0;
            pSamSysParame->m_qvcRecipe[i].sKeyname = "";
            pSamSysParame->m_qvcRecipe[i].nBoardX = 0;
            pSamSysParame->m_qvcRecipe[i].nBoardY = 0;
        }
        else
        {
            stream >> pSamSysParame->m_qvcRecipe[i].nKeyMark;
            stream >> pSamSysParame->m_qvcRecipe[i].nKeyId;
            stream >> pSamSysParame->m_qvcRecipe[i].sKeyname;
            stream >> pSamSysParame->m_qvcRecipe[i].nBoardX;
            stream >> pSamSysParame->m_qvcRecipe[i].nBoardY;
        }

        int nElnameSzie = 0;
        stream >> nElnameSzie;
        pSamSysParame->m_qvcRecipe[i].ElmentName.resize(nElnameSzie);
        for(int j = 0; j < nElnameSzie; j++)
        {
            int nLanguageSize = 0;
            stream >> nLanguageSize;
            pSamSysParame->m_qvcRecipe[i].ElmentName[j].resize(nLanguageSize);
            for(int k = 0; k < nLanguageSize; k++)
            {
                stream >> pSamSysParame->m_qvcRecipe[i].ElmentName[j][k].nElemIndex;
                stream >> pSamSysParame->m_qvcRecipe[i].ElmentName[j][k].nLanguageId;
                stream >> pSamSysParame->m_qvcRecipe[i].ElmentName[j][k].nRecipeGroupId;
                stream >> pSamSysParame->m_qvcRecipe[i].ElmentName[j][k].sElemName;
            }
        }
    }
    //load recipe end
    //Э��--����
    int connectList=0;
    stream >> connectList;
    pSamSysParame->m_qvcConnect.resize(connectList);
    QStringList sBaudrate;
    sBaudrate<< "1200" << "2400" << "4800" << "9600" << "19200" << "38400" << "57600"
            << "115200" << "230400";//������

    for(int i=0;i<connectList;i++){
        stream >> pSamSysParame->m_qvcConnect[i].bUseRelationPort;
        stream >> pSamSysParame->m_qvcConnect[i].eConnectPort;
        stream >> pSamSysParame->m_qvcConnect[i].eRelationPort;
        stream >> pSamSysParame->m_qvcConnect[i].id;
        stream >> pSamSysParame->m_qvcConnect[i].nBaudRate;
        if (pwnd->getProVersion() < 3224)
        {
            int baudIndex = pSamSysParame->m_qvcConnect[i].nBaudRate;
            if(baudIndex < sBaudrate.size())
            {
                pSamSysParame->m_qvcConnect[i].nBaudRate = sBaudrate.at(baudIndex).toInt();
            }
        }
        stream >> pSamSysParame->m_qvcConnect[i].nCheckType;
        stream >> pSamSysParame->m_qvcConnect[i].nDataBits;
        stream >> pSamSysParame->m_qvcConnect[i].nNetPortNum;
        stream >> pSamSysParame->m_qvcConnect[i].nScreenNo;
        stream >> pSamSysParame->m_qvcConnect[i].nStopBit;
        stream >> pSamSysParame->m_qvcConnect[i].sConnectName;
        stream >> pSamSysParame->m_qvcConnect[i].sIpAddr;

        if (pwnd->getProVersion() < 2699)
        {
            pSamSysParame->m_qvcConnect[i].bMasterScreen = 1;
            pSamSysParame->m_qvcConnect[i].bConnectScreenPort = 0;
            pSamSysParame->m_qvcConnect[i].nSlaveScreenNum = 1;
        }
        else
        {
            stream >> pSamSysParame->m_qvcConnect[i].bMasterScreen;
            stream >> pSamSysParame->m_qvcConnect[i].bConnectScreenPort;
            stream >> pSamSysParame->m_qvcConnect[i].nSlaveScreenNum;
        }

        int vProtocolsList=0;
        stream >> vProtocolsList;
        pSamSysParame->m_qvcConnect[i].vProtocols.resize(vProtocolsList);
        for(int j=0;j<vProtocolsList;j++){
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nIntervalTime;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nMaxRWLen;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nPlcNo;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nReceiveTimeout;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nRetryTime;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.regs;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.sModelName;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].mPlc.nCycleTime;

            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].nIntervalTime;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].nMaxRWLen;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].nPlcNo;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].nReceiveTimeout;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].nRetryTime;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].sFactoryName;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].sName;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].sProtocolName;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].nCycleTime;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].ip;
            stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].port;
            if (pwnd->getProVersion() < 3165)
            {
                pSamSysParame->m_qvcConnect[i].vProtocols[j].bIsTcpProtocol = false;
            }
            else
            {
                stream >> pSamSysParame->m_qvcConnect[i].vProtocols[j].bIsTcpProtocol;
            }
        }
    }
    //������¼
    int nType=0;
    int alarmList=0;
    stream >> alarmList;
    pSamSysParame->m_qvcAlarm.resize(alarmList);
    for(int i=0;i<alarmList;i++){
        stream >> nType;
        pSamSysParame->m_qvcAlarm[i].dataType=(DATA_TYPE)nType;;
        stream >> pSamSysParame->m_qvcAlarm[i].addrType;
        stream >> pSamSysParame->m_qvcAlarm[i].alarmName;

        int nAlarm=0;
        stream >> nAlarm;
        pSamSysParame->m_qvcAlarm[i].alarms.resize(nAlarm);
        for(int j=0;j<nAlarm;j++){
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].addr;
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].index;
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].messages;
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].symb;

            stream >> nType;
            pSamSysParame->m_qvcAlarm[i].alarms[j].dataType = (DATA_TYPE)nType;

            stream >> nType;
            pSamSysParame->m_qvcAlarm[i].alarms[j].eCondtion = (E_ALARM_CONDTION)nType;

            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].rangeLow;
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].rangeHigh;
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].bOpenScene;
            stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].sceneName;

            if(pwnd->getProVersion() >= 3210)//�°汾
            {
                stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].bSeneMsg;
                if(pwnd->getProVersion() >= 3442)//�°汾
                {
                    stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].sPhoneNums;
                }
                else
                {
                    QString sTmp;
                    stream >> sTmp;
                    pSamSysParame->m_qvcAlarm[i].alarms[j].sPhoneNums.clear();
                    pSamSysParame->m_qvcAlarm[i].alarms[j].sPhoneNums.append(sTmp);
                }
            }
            else
            {
                pSamSysParame->m_qvcAlarm[i].alarms[j].bSeneMsg = false;
            }

            if(pwnd->getProVersion() >= 3222)//�°汾
            {
                stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].bAddtoDB;
            }
            else
            {
                pSamSysParame->m_qvcAlarm[i].alarms[j].bAddtoDB = true;
            }

            if(pwnd->getProVersion() >= 3298)//�ɰ汾
            {
                stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].bPrint;
                stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].bPrintDate;
                stream >> pSamSysParame->m_qvcAlarm[i].alarms[j].bPrintTime;
            }
            else
                pSamSysParame->m_qvcAlarm[i].alarms[j].bPrint = false;

			qDebug() <<"load alarm end" << pSamSysParame->m_qvcAlarm[i].alarms[j].rangeHigh;

        }

    }
    //���ݲɼ�
    int num=0;
    int m_vecDataSamplingList=0;
    stream >> m_vecDataSamplingList;
    pSamSysParame->m_vecDataSamplingStr.resize(m_vecDataSamplingList);
    for(int i=0;i<m_vecDataSamplingList;i++){
        stream >> pSamSysParame->m_vecDataSamplingStr[i];
    }

    int m_loadDataSampList=0;
    stream >> m_loadDataSampList;
    pSamSysParame->m_loadDataSampling.resize(m_loadDataSampList);

    for(int i=0;i<m_loadDataSampList;i++){
        stream >> pSamSysParame->m_loadDataSampling[i].bAddrCtlSamp;
        stream >> pSamSysParame->m_loadDataSampling[i].bAutoReset;
        stream >> pSamSysParame->m_loadDataSampling[i].bContiguousAddr;
        stream >> pSamSysParame->m_loadDataSampling[i].bDynSampleRate;
        stream >> pSamSysParame->m_loadDataSampling[i].bDynTimeRange;
        stream >> pSamSysParame->m_loadDataSampling[i].bFullNotic;
        stream >> pSamSysParame->m_loadDataSampling[i].bSaveToFile;
        stream >> pSamSysParame->m_loadDataSampling[i].dynRateAddr;
        stream >> num;
        pSamSysParame->m_loadDataSampling[i].eDateShowType=(SaveDateType)num;
        stream >> num;
        pSamSysParame->m_loadDataSampling[i].eDealSampFull=(SampFullType)num;
        stream >> pSamSysParame->m_loadDataSampling[i].endTimeAddr;
        stream >> num;
        pSamSysParame->m_loadDataSampling[i].eSampType=(SampType)num;
        stream >> num;
        pSamSysParame->m_loadDataSampling[i].eSaveMedium=(SaveMidType)num;
        stream >> pSamSysParame->m_loadDataSampling[i].keyCtlSaveAddr;
        stream >> pSamSysParame->m_loadDataSampling[i].nDataLen;
        stream >> pSamSysParame->m_loadDataSampling[i].nDataSampType;
        stream >> pSamSysParame->m_loadDataSampling[i].nDecimalLen;
        stream >> pSamSysParame->m_loadDataSampling[i].nDigitLen;
        stream >> pSamSysParame->m_loadDataSampling[i].nEndHour;
        stream >> pSamSysParame->m_loadDataSampling[i].nEndMinute;
        stream >> pSamSysParame->m_loadDataSampling[i].nSampCountUnit;
        stream >> pSamSysParame->m_loadDataSampling[i].nSampRate;
        stream >> pSamSysParame->m_loadDataSampling[i].nSampRateUnit;
        stream >> pSamSysParame->m_loadDataSampling[i].nSampTime;
        stream >> pSamSysParame->m_loadDataSampling[i].nSampTimes;
        stream >> pSamSysParame->m_loadDataSampling[i].nSampUnit;
        stream >> pSamSysParame->m_loadDataSampling[i].nStartHour;
        stream >> pSamSysParame->m_loadDataSampling[i].nStartMinute;
        stream >> pSamSysParame->m_loadDataSampling[i].startTimeAddr;
        stream >> pSamSysParame->m_loadDataSampling[i].strCtlSampAddrId;
        stream >> pSamSysParame->m_loadDataSampling[i].strNoticAddrId;

        int tableList=0;
        stream >> tableList;
        pSamSysParame->m_loadDataSampling[i].m_dataTable.resize(tableList);
        for(int j=0;j<tableList;j++){
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].bZoom;
            stream >> num;
            pSamSysParame->m_loadDataSampling[i].m_dataTable[j].dataType=(DATA_TYPE)num;
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].inputMax;
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].inputMin;
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].keyAddress;
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].nAddrNumber;
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].outputMax;
            stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].outputMin;

            if(pwnd->getProVersion() >= 2542)//�°汾
            {
                stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].decLen;
            }
            else
                pSamSysParame->m_loadDataSampling[i].m_dataTable[j].decLen = 0;

            if(pwnd->getProVersion() >= 2543)//�°汾
            {
                stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].bRound;
            }
            else
                pSamSysParame->m_loadDataSampling[i].m_dataTable[j].bRound = true;

            if(pwnd->getProVersion() >= 2850)//�°汾
            {
                stream >> pSamSysParame->m_loadDataSampling[i].m_dataTable[j].name;
            }
            else
            {
                pSamSysParame->m_loadDataSampling[i].m_dataTable[j].name =
                        pSamSysParame->m_loadDataSampling[i].m_dataTable[j].keyAddress.sShowAddr;
            }



        }
        if(pwnd->getProVersion() >= 2564)//�ɰ汾
        {
            stream >> pSamSysParame->m_loadDataSampling[i].bAutoSave;
            stream >> pSamSysParame->m_loadDataSampling[i].nSaveHour;
        }
        else
            pSamSysParame->m_loadDataSampling[i].bAutoSave = false;
        if(pwnd->getProVersion() >= 3298)//�ɰ汾
        {
            stream >> pSamSysParame->m_loadDataSampling[i].bPrint;
            stream >> pSamSysParame->m_loadDataSampling[i].bPrintDate;
            stream >> pSamSysParame->m_loadDataSampling[i].bPrintTime;
        }
        else
            pSamSysParame->m_loadDataSampling[i].bPrint = false;
    }
    for(int i =0; i<pSamSysParame->m_loadDataSampling.size(); i++)
    {
        QVector<DATA_ADDRESS_ITEM> sampleItems = pSamSysParame->m_loadDataSampling[i].m_dataTable;
        QVector<DATA_ADDRESS_ITEM>::iterator iter;
        for(iter = pSamSysParame->m_loadDataSampling[i].m_dataTable.begin();
        iter != pSamSysParame->m_loadDataSampling[i].m_dataTable.end();)
        {
            if((*iter).nAddrNumber > 255)
            {
                iter = pSamSysParame->m_loadDataSampling[i].m_dataTable.erase(iter);
            }
            else
                iter++;
        }
    }


    //�������籣����
    stream >> pSamSysParame->m_PowerProtect.startLB;
    stream >> pSamSysParame->m_PowerProtect.lengthLB;
    stream >> pSamSysParame->m_PowerProtect.startLW;
    stream >> pSamSysParame->m_PowerProtect.lengthLW;
    qDebug() << "load end" <<pSamSysParame->m_PowerProtect.lengthLW;

    pSamSysParame->m_VarRecord.clear();
    if(pwnd->getProVersion() >= 3440)
    {
        int nTemp = 0;
        int nRcdSize = 0;
        stream >> nRcdSize;
        //����������

        for(int i=0; i<nRcdSize; i++)
        {
            VarRecord rcd;
            stream >> rcd.sVarName;
            stream >> rcd.mAddr;
            stream >> nTemp;
            rcd.mType = (DATA_TYPE)nTemp;
            pSamSysParame->m_VarRecord << rcd;
        }
    }


    if(pwnd->getProVersion() >= 3456)
    {
        //����ʱ���
        QVector<QList<ScheItem> > sItems;
        int size;
        stream >> size;
        qDebug() <<"weekly size: "<<size;
        for(int i=0; i<size; i++)
        {
            int lstsize;
            stream >> lstsize;
            qDebug() <<"week day:"<< i;
            qDebug() <<"weekly scheduler size: "<<lstsize;
            QList<ScheItem> itemlst;
            for(int j=0; j<lstsize; j++)
            {
                ScheItem item;
                stream >> item.timeType;
                stream >> item.time;
                stream >> item.kTimeAddr;
                int ntemp;
                stream >> ntemp;
                item.eWeek = (E_WEEKDAY)ntemp;
                stream >> ntemp;
                item.eActionType = (E_ACTION_TYPE)ntemp;

                stream >> item.kActionAddr;
                stream >> item.eDataType;
                stream >> item.valueType;
                stream >> item.nValue;
                stream >> item.kValueAddr;
                stream >> item.bControl;
                stream >> item.kControlAddr;

                itemlst << item;
            }
            sItems << itemlst;
        }
        pSamSysParame->schedulers->setItems(sItems);
    }

    return stream;
}


/**************************************************************
 *                        SAMKOON TECHNOLOGY CORP.
 *                          COPYRIGHT (C) 2011
 *
 * Description: QNewPro class implementation.
 *
 * Functions: None.
 *
 * Modification Log:
 * Date             Name             Description Of Change
 * 2011-1-10        Tang             Creation.
 *************************************************************/
QDataStream &operator<<(QDataStream &stream, QNewPro *pNewPro)
{
    stream << pNewPro->newprowizard_path << pNewPro->newprowizard_name;
    stream << pNewPro->newprowizard_model << pNewPro->newprowizard_showmodel;
    stream << pNewPro->newprowizard_showmodel_maxscreennum;
    stream << pNewPro->newlinkwizard_connection;
    stream << pNewPro->newlinkwizard_linkname;
    stream << pNewPro->newlinkwizard_linktype;
    stream << pNewPro->newlinkwizard_linkdevice;
    stream << pNewPro->newlinkwizard_linkserver;
    stream << pNewPro->newlinkwizard_plcaddress;
    stream << pNewPro->newscreenwizard_name;
    stream << pNewPro->newscreenwizard_bk;
    stream << pNewPro->newscreenwizard_frontcolor;
    stream << pNewPro->newscreenwizard_style;
    stream << pNewPro->newscreenwizard_picturepath;
    stream << pNewPro->ischeck_slience;
    stream << pNewPro->ischeck_picture;
    stream << pNewPro->nSeleteType;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QNewPro *pNewPro)
{
    stream >> pNewPro->newprowizard_path >> pNewPro->newprowizard_name;
    stream >> pNewPro->newprowizard_model >> pNewPro->newprowizard_showmodel;
    stream >> pNewPro->newprowizard_showmodel_maxscreennum;
    stream >> pNewPro->newlinkwizard_connection;
    stream >> pNewPro->newlinkwizard_linkname;
    stream >> pNewPro->newlinkwizard_linktype;
    stream >> pNewPro->newlinkwizard_linkdevice;
    stream >> pNewPro->newlinkwizard_linkserver;
    stream >> pNewPro->newlinkwizard_plcaddress;
    stream >> pNewPro->newscreenwizard_name;
    stream >> pNewPro->newscreenwizard_bk;
    stream >> pNewPro->newscreenwizard_frontcolor;
    stream >> pNewPro->newscreenwizard_style;
    stream >> pNewPro->newscreenwizard_picturepath;
    stream >> pNewPro->ischeck_slience;
    stream >> pNewPro->ischeck_picture;
    stream >> pNewPro->nSeleteType;
    return stream;
}

