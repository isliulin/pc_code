#include "compilethrd.h"
#include "Frame\mainwindow.h"
#include "Frame/qprogectmanager.h"

#define  DATABASE_NAME              "sd.dat"
#define  CONECT_NAME                "samkoonAndroidDatabase"

extern MainWindow *pwnd;
CompileThrd::CompileThrd()
{
    eType = COMPILE_ONLY;
    bDatabaseClosed = true;
    connect(this,SIGNAL(finished()),this,SLOT(threadfinished()));
}

void CompileThrd::threadfinished ()
{
    pwnd->undoAction->setEnabled(pwnd->undoStack->canUndo());
    pwnd->redoAction->setEnabled(pwnd->undoStack->canRedo());
    qDebug() <<"CompileThrd::finished";
}
void CompileThrd::run()
{
    pwnd->is_NeedCompiled = true;
    pwnd->undoAction->setEnabled(false);
    pwnd->redoAction->setEnabled(false);
    if(eType == SIMULATOR_OFF)
    {
        emit SignalStartsimulator();
    }
    emit message(tr("��ʼ����..."), MSG_NORMAL);

    QSqlDatabase androidDb;
    if(false == clearDataBaseData())
    {
        message(tr("������� :ɾ�������ݿ����"), MSG_ERROR);
        pwnd->isCompiled = false;
        QFile::remove("gEKip");
        return ;
    }
    if(QFile::exists("recipe.dat"))
    {
        if(false == QFile::remove("recipe.dat"))
        {
            message(tr("������� :ɾ�������ݿ����"), MSG_ERROR);
            pwnd->isCompiled = false;
            QFile::remove("gEKip");
            return;
        }
    }
    if(false == openDataBase(androidDb))
    {
        message(tr("������� :�½����ݿ����"), MSG_ERROR);
        pwnd->isCompiled = false;
        QFile::remove("gEKip");
        return ;
    }
    bDatabaseClosed = false;
    QTime before = QTime::currentTime();
    if(!pwnd->USBCompile(androidDb,(eType == SIMULATOR_OFF)))
    {
        androidDb.close();
        pwnd->isCompiled = false;
        if(pwnd->pSimDlg) //wxy ģ���������Ի���
        {
            pwnd->pSimDlg->accept();
            pwnd->pSimDlg = NULL;
        }
        bDatabaseClosed = true;
        return;
    }
    QTime after = QTime::currentTime();
    ExecuteQuerys(androidDb);
    qDebug() << " TTTTTTTT" << before.secsTo(after);
    if(!androidDb.commit())
    {
        message(tr("������� :�����������"), MSG_ERROR);;
    }
    androidDb.close();
    bDatabaseClosed = true;
    switch(eType)
    {
	case DOWNLOAD:
        emit SignalStartDownload();
        eType = COMPILE_ONLY;
		break;
	case SIMULATOR_OFF:
        {
            //wxy��һ����֪ͨ��λ�������
            QString vdisk = QDir::currentPath();
            vdisk += "/vdisk/prepare.ini";
            vdisk.replace("\\","/");
            QSettings *readIni = new QSettings(vdisk, QSettings::IniFormat, 0);
            readIni->setValue("Prepare", "true");
            delete readIni;
            //wxy�ڶ������ȴ���λ׼�����֪ͨ
            while(1)
            {
                vdisk = QDir::currentPath();
                vdisk += "/vdisk/prepare_OK.ini";
                if(QFile::exists(vdisk))
                {
                    removeDirectory("vdisk/Udisk");
                    QFile::remove("vdisk/prj.bin");
                    QFile::remove("vdisk/upLoad.akr");
                    QFile::remove("vdisk/prepare_OK.ini");
                    break;
                }
                else
                {
                    msleep(100);
                }
            }
            //wxy�����������ļ�������vDiskĿ¼
            emit SignalCompileEnd();
            eType = COMPILE_ONLY;
            break;
        }
    }
    pwnd->isCompiled = false;
    pwnd->is_NeedCompiled = false;

//    pwnd->is_Save=true;
//    pwnd->ui->action_save->setDisabled(true);
//    pwnd->is_SaveAS=false;
//    pwnd->setCurrentFile(file.fileName());//����򿪵��ĵ�
}
void CompileThrd::SetDownload(COMPILE_TYPE type)
{
    eType = type;
}
/*�����ݿ�*/
bool CompileThrd::openDataBase(QSqlDatabase &dataBase)
{
    //message(tr("openDataBase"));
    dataBase = QSqlDatabase::addDatabase("QSQLITE",CONECT_NAME);
    dataBase.setDatabaseName(DATABASE_NAME);

    if(false == dataBase.open()) return false;
    if(!dataBase.transaction()) return false;

    //message(tr("dataBase.open()"));
    QStringList tableList = dataBase.tables();
    if(tableList.isEmpty())
    {
        if(false == createDataBase(dataBase))
        {
            dataBase.close();
            return false;
        }
    }
    return true;
}

/*ɾ�����ݿ����������*/
bool CompileThrd::clearDataBaseData()
{
    bool bSuccess = false;
    QFile dataFile;
    QSqlDatabase  db = QSqlDatabase ::database("sd.dat");
    db.close();
    QSqlDatabase::removeDatabase(CONECT_NAME);
    if(dataFile.exists(DATABASE_NAME))
    {
        bSuccess = dataFile.remove(DATABASE_NAME);
        if(!bSuccess) return false;
    }

    QSqlDatabase  recipedb = QSqlDatabase ::database("recipe.dat");
    recipedb.close();
    QSqlDatabase::removeDatabase("recipe.dat");
    if(dataFile.exists("recipe.dat"))
    {
        bSuccess = dataFile.remove("recipe.dat");
        if(!bSuccess) return false;
    }
    return true;
}

//ִ�е�ַ����������
bool CompileThrd::ExecuteQuerys(QSqlDatabase &dataBase)
{
    bool result = true;
    QMap<QString ,QSqlQuery>mQuerys;
    typedef QMap<QString,QVariant> MAP_QUERY;

    QSqlQuery addrQuery(dataBase);
    addrQuery.prepare("INSERT INTO addr(eItemType ,nAddrId,nItemId ,nAddrNum ,eConnectType,nUserPlcId ,sPlcProtocol ,"
                        "nPlcStationIndex ,nPlcRegIndex ,nPlcStartAddr ,nAddrLen , eRwLevel)"
                        "VALUES (:eItemType,:nAddrId,:nItemId,:nAddrNum ,:eConnectType ,:nUserPlcId,:sPlcProtocol ,"
                        ":nPlcStationIndex,:nPlcRegIndex,:nPlcStartAddr,:nAddrLen, :eRwLevel)");

    //mQuerys.insert("addr",addrQuery);

    QSqlQuery switchQuery(dataBase);
    switchQuery.prepare("INSERT INTO switchButton(nItemId,nSceneId,eButtonType,eWatchType,nLp,nTp,nWidth,nHeight,"
                "nShowLp,nShowTp,nShowWidth,nShowHeight,nSwitchFunId,bSameLanguage,bSlid,bIsStartStatement,"
                " nStatementId,bIsStartStatementUp,nStatementIdUp,eWatchDataType ,nStatTotal,nWatchAddr,nAddrType,nBitIndex,nCondition,"
                "nZvalue,nCollidindId) "
                "VALUES (:nItemId,:nSceneId,:eButtonType,:eWatchType,:nLp,:nTp,:nWidth,:nHeight ,:nShowLp,"
                ":nShowTp,:nShowWidth,:nShowHeight,:nSwitchFunId,:bSameLanguage ,:bSlid,:bIsStartStatement,"
                ":nStatementId,:bIsStartStatementUp,:nStatementIdUp,:eWatchDataType,:nStatTotal,:nWatchAddr,:nAddrType,:nBitIndex,"
                ":nCondition,:nZvalue ,:nCollidindId )");
    mQuerys.insert("switchButton",switchQuery);

    QSqlQuery touchQuery(dataBase);
    touchQuery.prepare("INSERT INTO touchProp(nItemId,bTouchByAddr,eCtlAddrType,nValidStatus,nAddrId,"
        "nWordPosition,bTouchByUser,nGroupValueF,nGroupValueL,nPressTime,"
        "bTimeoutCancel,bNoticAddr,eDataType,nNoticeId,nNoticValue)"
        "VALUES (:nItemId,:bTouchByAddr,:eCtlAddrType,:nValidStatus,:nAddrId,"
        ":nWordPosition,:bTouchByUser,:nGroupValueF,:nGroupValueL,:nPressTime,"
        ":bTimeoutCancel,:bNoticAddr,:eDataType,:nNoticeId,:nNoticValue)");
    mQuerys.insert("touchProp",touchQuery);

    QSqlQuery showQuery(dataBase);
    showQuery.prepare("INSERT INTO showProp(nItemId ,bShowByAddr ,eAddrType ,nValidStatus ,nAddrId ,"
     "nBitPosition ,bShowByUser ,nGroupValueF ,nGroupValueL ) "
      "VALUES (:nItemId ,:bShowByAddr ,:eAddrType ,:nValidStatus ,:nAddrId ,"
     ":nBitPosition ,:bShowByUser ,:nGroupValueF ,:nGroupValueL )");
    mQuerys.insert("showProp",showQuery);

    QSqlQuery userQuery(dataBase);
    userQuery.prepare("INSERT INTO userGroup(nItemId ,nSceneId ,sPath ,nLp ,"
        "nTp ,nWidth ,nHeight ,nZvalue , nCollidindId )"
        "VALUES(:nItemId ,:nSceneId ,:sPath ,:nLp ,"
        ":nTp ,:nWidth ,:nHeight ,:nZvalue ,:nCollidindId)");
    mQuerys.insert("userGroup",userQuery);

    QSqlQuery kbandItemQuery(dataBase);
    kbandItemQuery.prepare("INSERT INTO kbAndItem(nKeyBoardId , nItemId ,nId,nItemTableType ) "
                           "VALUES (:nKeyBoardId ,:nItemId ,:nId,:nItemTableType)");
    mQuerys.insert("kbAndItem",kbandItemQuery);

    QSqlQuery sceneandItemQuery(dataBase);
    sceneandItemQuery.prepare("INSERT INTO sceneAndItem(nSceneId,nItemId,nId,nItemTableType)"
                     "VALUES(:nSceneId,:nItemId,:nId,:nItemTableType)");
    mQuerys.insert("sceneAndItem",sceneandItemQuery);

    QSqlQuery bitQuery(dataBase);
    bitQuery.prepare("INSERT INTO bitSwitch(nItemId,eOperType ,bDownZero,nBitAddress,nTimeout, bConfirm)"
        "VALUES (:nItemId ,:eOperType, :bDownZero,:nBitAddress,:nTimeout,:bConfirm)");
    mQuerys.insert("bitSwitch",bitQuery);

    QSqlQuery wordQuery(dataBase);
    wordQuery.prepare("INSERT INTO wordSwitch(nItemId,eOperType,nAddress,nDataType,"
        "bCycle ,nMax ,nMin ,nFinalValue,bDynamicControl,nAddressConst)"
        "VALUES (:nItemId,:eOperType,:nAddress,:nDataType,"
        ":bCycle ,:nMax ,:nMin ,:nFinalValue, :bDynamicControl, :nAddressConst)");
    mQuerys.insert("wordSwitch",wordQuery);

    QSqlQuery screenswitchQuery(dataBase);
    screenswitchQuery.prepare("INSERT INTO screenSwitch(nItemId, eOperScene,nSlideStyle,nTargetPage ,bLogout ,nSceneType)"
                     "VALUES (:nItemId, :eOperScene,:nSlideStyle,:nTargetPage ,:bLogout,:nSceneType)");
    mQuerys.insert("screenSwitch",screenswitchQuery);

    QSqlQuery funswitchQuery(dataBase);
    funswitchQuery.prepare("INSERT INTO funSwitch(nItemId,ePeculiarType ,nActionId ,nWindowID, bX, bY)"
                     "VALUES (:nItemId,:ePeculiarType, :nActionId,:nWindowID,:bX,:bY)");
    mQuerys.insert("funSwitch",funswitchQuery);

    QSqlQuery switchstatusQuery(dataBase);
    switchstatusQuery.prepare("INSERT INTO switchStatusProp(nItemId ,statusValue,nStatusIndex,eflick ,nAlpha,nColor,eLib ,sPath)"
        "VALUES (:nItemId ,:statusValue,:nStatusIndex,:eflick ,:nAlpha ,:nColor,:eLib ,:sPath)");
    mQuerys.insert("switchStatusProp",switchstatusQuery);

    QSqlQuery textQuery(dataBase);
    textQuery.prepare("INSERT INTO textProp(nItemId,nStatusIndex,nLangIndex,sFont,sText,nSize,nColor,nShowProp)"
                 "VALUES (:nItemId ,:nStatusIndex ,:nLangIndex,:sFont,:sText,:nSize,:nColor,:nShowProp)");
    mQuerys.insert("textProp",textQuery);

    QSqlQuery macroQuery(dataBase);
    macroQuery.prepare("INSERT INTO macro(MacroID , MacroLibName , MacroName , MacroType ,"
        "TimeInterval ,ControlAddr ,ControlAddrType ,ExecCondition , nCmpFactor , "
        "nCompID , SceneID , scriptCount)"
        "VALUES (:MacroID , :MacroLibName , :MacroName , :MacroType ,"
        ":TimeInterval ,:ControlAddr ,:ControlAddrType ,:ExecCondition , :nCmpFactor ,"
        ":nCompID , :SceneID , :scriptCount)");
    mQuerys.insert("macro",macroQuery);

    QSqlQuery numberQuery(dataBase);
    numberQuery.prepare("INSERT INTO number(nItemId, nAddress, bIsInput, bIsScale, eNumberType,"
     "nByteLength, eSourceArea, nSourceMax, nSourceMin, nShow,"
     "bRound, nShowMax, nShowMin, nAllbytelength,"
     "eDecimalType, nDecimalLength, eShowStyle, nFontColor, nBackColor,"
     "nHightColor, nLowerColor, eInputTypeId, nKeyId, sBitAddress,bAutoChangeBit,"
     "eInputAreaType,nInputMax,nInputMin,bInputSign,nBoardX,nBoardY,nLowerNumber,"
     "nHightNumber,bInputIsShow,nInputAddr,bShowExp ,nShowExpId ,nInputExpId ,bInputExp)"
     "VALUES(:nItemId,:nAddress,:bIsInput,:bIsScale,:eNumberType,"
     ":nByteLength,:eSourceArea,:nSourceMax,:nSourceMin,:nShow,"
     ":bRound,:nShowMax,:nShowMin,:nAllbytelength,"
     ":eDecimalType,:nDecimalLength,:eShowStyle,:nFontColor,:nBackColor,"
     ":nHightColor,:nLowerColor,:eInputTypeId,:nKeyId,:sBitAddress,:bAutoChangeBit,"
     ":eInputAreaType,:nInputMax,:nInputMin,:bInputSign,:nBoardX,:nBoardY,:nLowerNumber,"
     ":nHightNumber,:bInputIsShow,:nInputAddr,:bShowExp ,:nShowExpId ,:nInputExpId ,:bInputExp)");
    mQuerys.insert("number",numberQuery);

    QSqlQuery expressQuery(dataBase);
    expressQuery.prepare("INSERT INTO express(nItemId ,nFirstSign ,nFirstNumberType ,"
                         "nFirstNumber ,nSecondSign ,nSecondNumberType ,nSecondNumber ,"
                         "nThirdNumberType ,nThirdNumber, nThirdSign )"
                         "VALUES (:nItemId ,:nFirstSign ,:nFirstNumberType ,"
      ":nFirstNumber ,:nSecondSign ,:nSecondNumberType ,:nSecondNumber ,"
      ":nThirdNumberType ,:nThirdNumber, :nThirdSign)");
    mQuerys.insert("express",expressQuery);

    QSqlQuery datashowQuery(dataBase);
    datashowQuery.prepare("INSERT INTO dataShow(nItemId, nSceneId, eItemType, nStartX, nStartY, nWidth,"
      "nHeight, nTextStartX, nTextStartY, nTextWidth, nTextHeight,"
      "sShapId, nTransparent,sFontStyle, nFontSize, eFontCss, bIsStartStatement, nScriptId, nOffsetAddrID,nZvalue, nCollidindId, nShowPropId,"
      "nTouchPropId)"
      "VALUES (:nItemId, :nSceneId,:eItemType, :nStartX, :nStartY, :nWidth,"
      ":nHeight, :nTextStartX, :nTextStartY, :nTextWidth, :nTextHeight,"
      ":sShapId, :nTransparent, :sFontStyle, :nFontSize, :eFontCss, :bIsStartStatement, :nScriptId, :nOffsetAddrID,:nZvalue, :nCollidindId, :nShowPropId,"
      ":nTouchPropId)");
    mQuerys.insert("dataShow",datashowQuery);

    QSqlQuery asciiQuery(dataBase);
    asciiQuery.prepare("INSERT INTO ascii(nItemId, nAddress, bIsinput, nLanguageTypeId,"
                          "nShowCharNumber, nShowStyle, nCode, nKeyId, nFontColor,"
                          "eInputTypeId, bInputSign, nBoardX, nBoardY,sBitAddress,bAutoChangeBit,"
                          "nBackColor,bInputIsShow,nInputAddr)"
                          "VALUES (:nItemId, :nAddress, :bIsinput, :nLanguageTypeId,"
                          ":nShowCharNumber, :nShowStyle, :nCode, :nKeyId, :nFontColor,"
                          ":eInputTypeId,:bInputSign,:nBoardX,:nBoardY,:sBitAddress,:bAutoChangeBit,"
                          ":nBackColor,:bInputIsShow,:nInputAddr)");
    mQuerys.insert("ascii",asciiQuery);

    QSqlQuery sqlTimequery(dataBase);
    sqlTimequery.prepare("INSERT INTO time(nItemId, eShowDate, eShowWeek, eShowTime,"
                          "nFontColor, nBackground)"
                          "VALUES (:nItemId, :eShowDate, :eShowWeek, :eShowTime,"
                          ":nFontColor, :nBackground)");
    mQuerys.insert("time",sqlTimequery);

    foreach(DBQuery stDbQuery,pwnd->vAllDbQuery)
    {
        foreach(MAP_QUERY mapQuery,stDbQuery.vDbQuery)
        {
            QSqlQuery sqlQuery = mQuerys.value(stDbQuery.tableName);
            QMap<QString,QVariant>::iterator it=mapQuery.begin();
            while(it!=mapQuery.end())
            {
                sqlQuery.bindValue(it.key(),it.value());
                it++;
            }
            result = result && sqlQuery.exec();
            if(!result)
            {
                //qDebug() << "error: "<<stDbQuery.tableName;
            }
        }
    }
    //    QVector<QMap<QString,QVariant>> vMapQuery;

//    typedef QMap<QString,QVariant> MAP_QUERY;
//    foreach(MAP_QUERY mapQuery,pwnd->vAddrQuery)
//    {
//        QMap<QString,QVariant>::iterator it=mapQuery.begin();
//        while(it!=mapQuery.end())
//        {
//            sqlQuery.bindValue(it.key(),it.value());
//            it++;
//        }

//        result = result && sqlQuery.exec();
//    }
    qDebug() << "sql query result:"<< result;
   return result;
}
bool CompileThrd::createDataBase(QSqlDatabase &dataBase)
{
    // TODO put your implementation here.
    bool bScuccess = false;
    QSqlQuery sqlQuery(dataBase);
    QString sCreateTableCmd;
    sCreateTableCmd.clear();

    //message(tr("������ַ��"));
    /*1.������ַ��*/
    sCreateTableCmd = "CREATE TABLE [addr] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,eItemType smallint,nAddrId integer,nItemId integer,nAddrNum integer,eConnectType smallint,nUserPlcId smallint,sPlcProtocol varchar,nPlcStationIndex integer,nPlcRegIndex smallint,nPlcStartAddr integer,nAddrLen integer, eRwLevel smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*2.����õĵ�ַ��*/
    sCreateTableCmd = "CREATE TABLE [arrangeAddr] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nSceneId smallint,eItemType smallint,eConnectType smallint,nUserPlcId smallint,sPlcProtocol  varchar,nPlcStationIndex integer,nPlcRegIndex smallint,nPlcStartAddr integer,nAddrLen integer,eRwLevel integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*3.�����������Ա�*/
    sCreateTableCmd = "CREATE TABLE [touchProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,bTouchByAddr boolean,eCtlAddrType integer,nValidStatus integer,nAddrId integer,nWordPosition integer,bTouchByUser boolean,nGroupValueF integer,nGroupValueL integer,nPressTime integer,bTimeoutCancel boolean,bNoticAddr boolean,eDataType integer,nNoticeId integer,nNoticValue double)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*4.��������*/
    sCreateTableCmd = "CREATE TABLE [showProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,bShowByAddr boolean,eAddrType smallint,nValidStatus smallint,nAddrId integer,nBitPosition smallint,bShowByUser boolean,nGroupValueF integer,nGroupValueL integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*5.�����ؼ���*/
    sCreateTableCmd = "CREATE TABLE [alarmControl] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nFrameColor integer,nTableColor integer,nTitleBackcolor integer,nTitleColor integer,bShowTime boolean,eTimeFormat smallint,bShowDate boolean,eDateFormat smallint,nFontSize smallint,nTextColor integer,nRowCount smallint,bShowall boolean,sNames varchar,nLeftTopX smallint,nLeftTopY smallint,nWidth smallint,nHeight smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*5.�����ؼ������*/
    sCreateTableCmd = "CREATE TABLE [alarmTitle] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nLanguageIndex integer,nFontSize smallint,sFont varchar,sTime varchar,sDate varchar,sMessage varchar,sClearTime varchar,sClearDate varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*6.�������ݲɼ�-��*/
    sCreateTableCmd = "CREATE TABLE [alarmGroup] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId integer, sName varchar,nTime smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*6.�������ݲɼ�-��������*/
    sCreateTableCmd = "CREATE TABLE [alarm] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId integer,nAlarmIndex integer, nAddress integer, eCondition smallint, eDataType smallint, nRangLow double, nRangHigh double,nTargetPage integer,nSceneType smallint, bSeneMsg smallint,sPhoneNum varchar,bAddtoDB smallint,bPrint smallint,bPrintDate smallint,bPrintTime smallint,bOpenScene smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*6.������Ϣ��*/
    sCreateTableCmd = "CREATE TABLE [alarmMessage] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId integer,nAlarmIndex integer,nLanguage smallint,sMessage varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*7.������*/
    sCreateTableCmd = "CREATE TABLE [alarmSlip] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,sApperIndex varchar,nBackcolor integer,nFramecolor integer,nForecolor integer,nFontSize smallint,nTextColor integer,bSelectall boolean,sNames varchar,nSpeed smallint,eDirection smallint,eSort smallint,nLeftTopX smallint,nLeftTopY smallint,nWidth smallint,nHeight smallint,nTextLeftTopX smallint,nTextLeftTopY smallint,nTextWidth smallint,nTextHeight smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*8.��ʷ������ʾ��*/
    sCreateTableCmd = "CREATE TABLE [hisAlarmShow] (id integer  NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nFrameColor integer,nTableColor integer,bControl boolean,eControlAddr integer,nTitleBackcolor integer,nTitleColor integer,bShowTime boolean,eTimeFormat smallint,bShowDate smallint,eDateFormat smallint,bNumber boolean,nFontSize smallint,nTextColor integer,nRowCount smallint,bClearDate boolean,eClearDateFormat smallint,bClearTime boolean,eClearTimeFormat smallint,nClearColor integer,nConfirmColor integer,nLeftTopX smallint,nLeftTopY smallint,nWidth smallint,nHeight smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*9.�����ؼ�*/
    sCreateTableCmd = "CREATE TABLE [animation] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nLp smallint,nTp smallint,nWidth smallint,nHeight smallint,nTrackType smallint,nBackColor integer,nMoveCondition smallint ,nMoveType smallint,nMoveTimeInterval integer,nStartTrackPoint smallint,nTrackPointTotal integer,mMoveCtrlAddr  integer, mXPosCtrlAddr integer, mYPosCtrlAddr integer,nXMoveStepScale float,nYMoveStepScale float,nAreaOrigXPos smallint,nAreaOrigYPos smallint,nAreaWidth smallint,nAreaHeight smallint,nStateTotal smallint,nChangeCondition smallint,nChangeType smallint,nChangeTimeinterval smallint,nInitState smallint, mChangeCtrlAddr integer,nZvalue integer, nCollidindId integer, nShowPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*9.�����ؼ��켣����*/
    sCreateTableCmd = "CREATE TABLE [animationOrbit] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nOrbitId smallint, nXPos smallint, nYPos smallint, nMCmpFactor smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*10.���ذ�ť*/
    sCreateTableCmd = "CREATE TABLE [switchButton] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,eButtonType smallint, eWatchType smallint,nLp smallint,nTp smallint,nWidth smallint,nHeight smallint, nShowLp smallint, nShowTp smallint, nShowWidth smallint, nShowHeight smallint,nSwitchFunId integer, bSameLanguage boolean,bSlid boolean,bIsStartStatement boolean,nStatementId smallint,bIsStartStatementUp boolean,nStatementIdUp smallint, eWatchDataType smallint,nStatTotal smallint,nWatchAddr integer,nAddrType boolean,nBitIndex smallint,nCondition smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*11.	���غ�ָʾ���е�״̬����*/
    sCreateTableCmd = "CREATE TABLE [switchStatusProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer, statusValue double,nStatusIndex smallint,eflick smallint,nAlpha integer,nColor integer,eLib smallint,sPath varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*11.	���غ�ָʾ���е��ı�����*/
    sCreateTableCmd = "CREATE TABLE [textProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nStatusIndex smallint,nLangIndex smallint,sFont varchar,sText varchar,nSize smallint,nColor integer,nShowProp smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*12.	���������е�λ��������*/
    sCreateTableCmd = "CREATE TABLE [bitSwitch] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,eOperType smallint, bDownZero boolean,nBitAddress integer,nTimeout integer, bConfirm boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*13.	�����е��ֿ������Բ���*/
    sCreateTableCmd = "CREATE TABLE [wordSwitch] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer, eOperType smallint, nAddress integer,nDataType smallint,bCycle boolean,nMax double,nMin double,nFinalValue double,bDynamicControl boolean,nAddressConst integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*14.	���ز����еĻ����л�����*/
    sCreateTableCmd = "CREATE TABLE [screenSwitch] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer, eOperScene smallint,nSlideStyle,nTargetPage integer,bLogout boolean,nSceneType smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*15.	��������Ĺ��ܿ��ز���*/
    sCreateTableCmd = "CREATE TABLE [funSwitch] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, nItemId integer,ePeculiarType smallint, nActionId smallint ,nWindowID integer, bX boolean, bY boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*16.	�̶����Ա�*/
    sCreateTableCmd = "CREATE TABLE [calibration] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nLineColor integer,nTextColor integer,nCalibrationDirection smallint,nNumberIncreaseDirection smallint,nMainNumberCount smallint,nNextNumberCount smallint,bShowText boolean,nMaxNumber double,nMinNumber double,nDecimalCount smallint,nTextSize smallint,nStartX smallint,nStartY smallint,nCalibrationWidth smallint,nCalibrationHeight smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*16.	ʱ������Ա�*/
    sCreateTableCmd = "CREATE TABLE [scheduler] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, actionIndex integer,actionTime time,eTimeType smallint,weekday smallint,nTimeAddr integer,eActionType smallint,nActionAddr integer,eDataType smallint,eValueType smallint,nValue double,nCtlAddr integer,bControl boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*17.	���ؼ�*/
    sCreateTableCmd = "CREATE TABLE [tableShow] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nOrientationCount smallint,nPortraitCount smallint,bShowFrameLine boolean,bShowOrientationLine boolean,bShowPortraitCount boolean,nBackColor integer,nTableWidth smallint,nTableHeight smallint,nLeftTopX smallint,nLeftTopY smallint,nWShowColor integer,eNLineType smallint,nNShowColor integer,nTransparent smallint,nZvalue integer,nCollidindId integer, bHControl boolean, nAddrHControl integer, bVControl boolean, nAddrVControl integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*18.	���ؼ��е��ӱ�������*/
    sCreateTableCmd = "CREATE TABLE [tableProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nIsRow smallint,nNo smallint,nWidth double)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*19.	���������Ա�*/
    sCreateTableCmd = "CREATE TABLE [combobox] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartX smallint,nStartY smallint,nWidth smallint,nHeight smallint,nShowNumber smallint,sFontType varchar,nfontSize smallint,nLanguageTypeId smallint,nFontColor integer,eFontCss integer,nBackColor integer, nTouchPropId integer, nShowPropId integer,nZvalue integer,nCollidindId integer, bUsePic boolean,bIsStartStatement boolean, nScriptId smallint,nAlpha smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*20.	�������ܱ�*/
    //sCreateTableCmd = "CREATE TABLE [comboboxFun] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer, eFunctionType smallint, nFunctionId integer, sFunctionName varchar)";
    sCreateTableCmd = "CREATE TABLE [comboboxFun] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer, eFunctionType smallint, sPath varchar,nFunctionId integer,bSaveIndex boolean, sFunctionName smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*21.	�����ռ� */
    sCreateTableCmd = "CREATE TABLE [dataCollect] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nDataSampType smallint,nGroupId smallint,sName varchar,eSampType smallint,nSaveTime integer,eDealSampFull smallint,bFullNotic smallint,nNoticAddrId integer,bAddrCtlSamp smallint,nCtlSampAddrId integer,bAddrCtlTime smallint,nStartAddr integer,nEndAddr integer,nStartHour smallint,nStartMinute smallint,nEndHour smallint,nEndMinute smallint,bAddrCtlRate smallint,nSampRate integer,bAutoReset smallint,nCtlSaveAddrId integer,eSaveMedium smallint,eDateShowType smallint,bAutoSave smallint,nIntervalTime integer,bPrint smallint,bPrintDate smallint,bPrintTime smallint,bSaveToFile smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

	/*21.	�����ռ���ַ */
    sCreateTableCmd = "CREATE TABLE [dataCollectAddr] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nDataSampType samllint,nArrayId integer,nAddrId integer,eDataType samllint,nSourceMin double,nSourceMax double,nTargeMin double,nTargeMax double,nDecLength integer, bRound smallint,sName varchar,bDealData smallint)";
	bScuccess = sqlQuery.exec(sCreateTableCmd);
	if(!bScuccess) return false;

    /*22.	������ʾ��*/
    sCreateTableCmd = "CREATE TABLE [dataShow] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,eItemType smallint,nStartX smallint,nStartY smallint,nWidth smallint,nHeight smallint,nTextStartX smallint,nTextStartY smallint,nTextWidth smallint,nTextHeight smallint,sShapId varchar,nTransparent smallint,sFontStyle varchar,nFontSize smallint,eFontCss integer,bIsStartStatement boolean, nScriptId integer,nOffsetAddrID smallint,nZvalue integer,nCollidindId integer,nShowPropId integer,nTouchPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*23.	������ʾ�е�Ascii���ֹ������Ա�*/
    sCreateTableCmd = "CREATE TABLE [ascii] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nAddress integer,bIsinput boolean,nLanguageTypeId smallint,nShowCharNumber smallint,nShowStyle smallint,nCode  integer,nKeyId  smallint,nFontColor integer,eInputTypeId smallint,bInputSign boolean,nBoardX integer,nBoardY integer,sBitAddress integer,bAutoChangeBit boolean,nBackColor integer,bInputIsShow boolean,nInputAddr integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*24.	������ʾ�е�ʱ����ʾ����*/
    sCreateTableCmd = "CREATE TABLE [time] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,eShowDate smallint,eShowWeek smallint,eShowTime smallint,nFontColor integer,nBackground integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*25.	������ʾ�е���ֵ��ʾ��������*/
    sCreateTableCmd = "CREATE TABLE [number] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nAddress integer,bIsInput boolean,bIsScale boolean,eNumberType smallint,nByteLength smallint,eSourceArea smallint,nSourceMax double,nSourceMin double,nShow smallint,bRound boolean,nShowMax double,nShowMin double,nAllbytelength smallint,eDecimalType smallint,nDecimalLength smallint,eShowStyle smallint,nFontColor integer,nBackColor integer,nHightColor integer,nLowerColor integer,eInputTypeId smallint,nKeyId smallint,sBitAddress integer,bAutoChangeBit boolean,eInputAreaType smallint,nInputMax double,nInputMin double,bInputSign boolean,nBoardX integer,nBoardY integer,nLowerNumber double,nHightNumber double,bInputIsShow boolean,nInputAddr integer,bShowExp boolean,nShowExpId integer,nInputExpId integer,bInputExp boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*25.	������ʾ�б��ʽ����*/
    sCreateTableCmd = "CREATE TABLE [express] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nFirstSign smallint,nFirstNumberType smallint,nFirstNumber double,nSecondSign smallint,nSecondNumberType smallint,nSecondNumber double,nThirdNumberType smallint,nThirdNumber double,nThirdSign smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*26.	������*/
    sCreateTableCmd = "CREATE TABLE [floawBar] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartX smallint,nStartY smallint,nRectWidth smallint,nRectHeight smallint,nFForeColor integer,nFBackColor integer,nDForeColor integer,nDBackColor integer,nFrameColor integer,eStyle smallint,nTriggerAddress integer,eShowWay smallint,eFlowDirection smallint,bTouchAddress boolean,nTouchAddress integer,nFlowNum smallint,bSideLine boolean,eFlowSpeedType smallint,eFixedFlowSpeed smallint,nTrendFlowSpeed integer,nZvalue integer,nCollidindId integer,nValidState smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*27.	ͼ��ؼ���ʾ*/
    sCreateTableCmd = "CREATE TABLE [graphShow] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,eGraphType smallint,eShapeId smallint,sPic varchar,mAddress integer,eDataType smallint,eDirection smallint,nTextColor integer,nBackcolor integer,nLeftTopX smallint,nLeftTopY smallint,nWidth smallint,nHeight smallint,nMainRuling smallint,bShowRuling boolean,bShowRuleValue boolean,nPointType smallint,nRuling smallint,nRulingColor integer,nShowLeftTopX smallint,nShowLeftTopY smallint,nShowWidth smallint,nShowHigth smallint,nRulerLeftTopX smallint,nRulerLeftTopY smallint,nRulerWidth smallint,nRulerHigth smallint,eRulerDirectio smallint,bAlarm boolean,nType smallint,nMin smallint,nMax smallint,nAlarmTextColor integer,nDesignColor integer,nZvalue integer,nCollidindId integer,nShowPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*28.	ͼ��ؼ��������ͨ����*/
    sCreateTableCmd = "CREATE TABLE [commonGraph] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nBitLength smallint,nStartAngle smallint,nSpanAngle smallint,bSourceMark smallint,nSourceRang smallint,eSourceMin double,eSourceMax double,bShowMark boolean,eShowMin double,eShowMax double,eShapeType smallint,bFill boolean,bHole boolean,nRadius smallint,bStart boolean,nDesign smallint,nDesignColor integer,nFrameColor integer,nTransparent smallint,bShowFrame boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*29.	ͼ��ؼ��е���������*/
    sCreateTableCmd = "CREATE TABLE [meterGraph] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nBitLength smallint,nSourceMark smallint,nSourceRang smallint,eSourceMin double,eSourceMax double,bShowMark boolean,eShowMin double,eShowMax double,nTransparent smallint,bShowFrame boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*30.	��ʷ������ʾ��*/
    sCreateTableCmd = "CREATE TABLE [historyShow] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nAlpha smallint,sGroupName varchar,nForecolor integer,nFrameColor integer,nTitleBackColor integer,nTitleFontColor integer,bShowTime boolean,eTimeFormat smallint,bShowDate boolean,eDateFormat smallint,bShowCode boolean,nTextFontSize smallint,nTextFontColor integer,nLine smallint,nLeftTopX smallint,nLeftTopY smallint,nWidth smallint,nHeight smallint,nZvalue integer,nCollidindId integer,nShowPropId integer,bAddr boolean,mAddress integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    sCreateTableCmd = "CREATE TABLE [historyShowText] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nLanguageId integer,nTitleFontSize integer,sTitleFontType varchar,sTitleTimeName varchar,sTitleDateName varchar,sTitleNumber varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    sCreateTableCmd = "CREATE TABLE [historyShowData] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nLanguageId integer,nCode integer,sTitleDataName varchar,bShowTitleDataName boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*31.	ϵͳ���Ա� */
    sCreateTableCmd = "CREATE TABLE [systemProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nModel varchar,sStartScreen varchar,nScreenTime smallint,bScreensaver boolean,sScreenIndex varchar,nFlickRate smallint,nBrightness smallint,nSetBoolParam integer,kWriteScreenAddr integer,kRecipeIndexAddr integer,kWriteLanguageAddr integer,kChangeScreenAddr integer,sUploadPassword varchar,bProtectType boolean,sProtectValue varchar,nLanguageIndex integer,nRecipeGroupId integer,nRecipeIndex integer,nInitScreenId integer,nstartLB integer,nlengthLB integer,nstartLW integer,nlengthLW integer,bBitScene boolean,bSimulator smallint,bLockIcon boolean,strMonitor varchar,strHmiName varchar,nMonitorPort smallint,nPrinterType smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    sCreateTableCmd = "CREATE TABLE [bitScene] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nId integer,nStatus smallint,nAddressId integer,nSceneId integer,bReset boolean,bClose boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*ʱ������*/
    sCreateTableCmd = "CREATE TABLE [timesetting] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,bDownloadTime boolean,eDataType smallint,nLength integer,nSynchAddr integer,eExeType smallint,nTime integer,nTriggerAddr integer,bAutoReset boolean,eSynchTime smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*32.	Plc���ӵ����Ա�*/
    sCreateTableCmd = "CREATE TABLE [plcConnectProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nConnectId integer,sConnectName varchar,eConnectPort smallint,bUseRelationPort boolean,eRelationPort smallint,bMasterScreen smallint, bConnectScreenPort smallint, nSlaveScreenNum smallint,nScreenNo smallint,nBaudRate integer,nDataBits smallint,nCheckType smallint,nStopBit smallint,sIpAddr varchar,nNetPortNum integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*33.	PLC���������е�Э�鲿������*/
    sCreateTableCmd = "CREATE TABLE [protocolProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nConnectIndex integer,sPlcServiceType varchar,nUserPlcId smallint,nPlcNo smallint,nReceiveTimeout smallint,nMaxRWLen integer,nRetryTime smallint,nMinCollectCycle smallint,nIntervalTime smallint,sIpAddr varchar,bIsNetTcp bool,nNetPortNum integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*34.	�������Ա�*/
    sCreateTableCmd = "CREATE TABLE [languageList] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,sLanguageName varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*35.	HMI�������Ա�*/
    sCreateTableCmd = "CREATE TABLE [hmiProtect] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, sPwdStr varchar,sTimeLimit varchar,bIsUse boolean,sTimeOut varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*36.	ͼƬ��ʾ��*/
    sCreateTableCmd = "CREATE TABLE [imageShow] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nLp smallint,nTp smallint,nWidth smallint,nHeight smallint,nFunType smallint,bUseFlicker boolean,nBackColor integer,nChangeCondition smallint, nWatchAddr integer,nStatusTotal smallint,nTimeInterval smallint, bIsLoopType smallint, nOrigWidth smallint, nOrigHeight smallint,nIsBitCtrl smallint,nValidBit smallint,nCtrlAddr smallint,nRCount integer,nZvalue integer, nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*37.	��ͼƬ��·�������Դ洢��*/
    sCreateTableCmd = "CREATE TABLE [imagePath] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStatusId smallint,nCmpFactor smallint,sPicPath varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*38.	���̿ؼ�*/
    sCreateTableCmd = "CREATE TABLE [keyBoard] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nSceneId integer,skeyName varchar,nkeyWidth smallint,nkeyHeight smallint,ekeyStyle smallint,nkeyBackColor integer,nkeyForeColor integer,eBackType smallint,sPicturePath varchar,nMaxStartX smallint,nMaxStartY smallint,nMaxWidth smallint,nMaxHeight smallint,nMaxFont String,nMaxAlign smallint,nMaxFontSize smallint,nMaxFontPro smallint,nMaxFontColor integer,nMaxStyle smallint,nMaxAlpha smallint,nMaxForeColor integer,nMaxBackColor integer,nMaxAdapt bool,nMinStartX smallint,nMinStartY smallint,nMinWidth smallint,nMinHeight smallint,nMinFont String,nMinAlign smallint,nMinFontSize smallint,nMinFontPro smallint,nMinFontColor integer,nMinStyle smallint,nMinAlpha smallint,nMinForeColor integer,nMinBackColor integer,nMinAdapt bool,nTextStartX smallint,nTextStartY smallint,nTextWidth smallint,nTextHeight smallint,nTextFont String,nTextAlign smallint,nTextFontSize smallint,nTextFontPro smallint,nTextFontColor integer,nTextStyle smallint,nTextAlpha smallint,nTextForeColor integer,nTextBackColor integer,nTextAdapt bool)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*39.	ָʾ��*/
    sCreateTableCmd = "CREATE TABLE [lamp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nLp smallint,nTp smallint,nWidth smallint,nHeight smallint,nTxtAssType smallint,nApeaAssType smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*40.	�������Ա�*/
    sCreateTableCmd = "CREATE TABLE [line] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemNumber integer,nSceneId integer,eLineClass smallint,eLineType smallint,nLineWidth smallint,nLineColor integer,eLineArrow smallint,nAlpha smallint, eLinePointType smallint,nZvalue integer,nCollidindId integer,nStartX smallint,nStartY smallint,nWidth smallint,nHeight smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*41.	����ͼ�������ж���εı�*/
    sCreateTableCmd = "CREATE TABLE [polygon] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId  integer,nSceneId integer,ePolygonClass smallint,eLineType smallint,nLineWidth smallint,nLineColor integer,eStyle smallint,nBackColor integer,nForeColor integer,nAlpha smallint,nPointX smallint,nPointY smallint,nWidth smallint,nHeight smallint,nRadius smallint,eCornerType smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*42.	������Ա�*/
    sCreateTableCmd = "CREATE TABLE [macro] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, MacroID smallint, MacroLibName varchar, MacroName varchar, MacroType smallint,TimeInterval integer,ControlAddr integer,ControlAddrType smallint,ExecCondition smallint, nCmpFactor smallint, nCompID smallint, SceneID integer, scriptCount integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*43.	���б��������Ա�*/
    sCreateTableCmd = "CREATE TABLE [macroProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, sName varchar, nDatatype smallint, nAddrValue integer,bOffset boolean,nOffsetAddr integer,sMacroLibName varchar, nRWPerm smallint,nElemNum integer,nCodetype smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*44.	��Ϣ��ʾ��*/
    sCreateTableCmd = "CREATE TABLE [messageShow] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nAlpha smallint,nLeftTopX smallint,nLeftTopY smallint,nWidth smallint,nHeight smallint,nShowLeftTopX smallint,nShowLeftTopY smallint,nShowWidth smallint,nShowHeight smallint,sShape varchar,eDataType smallint,eAddress integer,nStateCount smallint,bFirstLanguage boolean,bStateZero boolean,nZvalue integer,nCollidindId integer,nShowPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*45.	��Ϣÿ��״̬������*/
    sCreateTableCmd = "CREATE TABLE [msgStatusProp] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nStatusIndex smallint,sFontType varchar,nFontSize smallint,nFontColor integer,eRemove smallint,nFrameColor integer,nForecolor integer,nBackcolor integer,nStyle integer,sStateMessage text,nLanguage smallint,nSpeed smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*46.	������Ա�*/
    sCreateTableCmd = "CREATE TABLE [point] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nPosX smallint,nPosY smallint,nOrder integer,ePointType smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*47.	�䷽�����ռ���*/
//    sCreateTableCmd = "CREATE TABLE [recipeCollectGroup] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,sRecipeGName varchar,sRecipeGDescri varchar,nRecipeNum integer,nRecipeLen integer,eSaveMedia smallint,bNeedCtlAddr smallint,mCtlAddrId integer,bCompleteNotic boolean,mComNoticAddrId integer)";
//    bScuccess = sqlQuery.exec(sCreateTableCmd);
//    if(!bScuccess) return false;

    /*48.	�䷽�����ռ����е����ݲ���*/
//    sCreateTableCmd = "CREATE TABLE [recipeCollectData] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nRecipeId integer,nElemIndex integer,nRecipeValue double)";
//    bScuccess = sqlQuery.exec(sCreateTableCmd);
//    if(!bScuccess) return false;

//    sCreateTableCmd = "CREATE TABLE [recipeNameML] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nRecipeId integer,nLanguageId smallint,sRecipeName varchar, sRecipeDescri varchar)";
//    bScuccess = sqlQuery.exec(sCreateTableCmd);
//    if(!bScuccess) return false;

//    sCreateTableCmd = "CREATE TABLE [recipeElemML] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nElemIndex integer,nValueAddrId integer,eDataType smallint,nLanguageId smallint,sElemName varchar)";
//    bScuccess = sqlQuery.exec(sCreateTableCmd);
//    if(!bScuccess) return false;

    /*49.	�䷽��ʾ��*/
    sCreateTableCmd = "CREATE TABLE [recipeDisplay] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartPosX smallint,nStartPosY smallint,nWidth smallint,nHeight smallint,nRecipeGroupId integer,bShowRecipeID boolean,bShowDescrip boolean,eTextAlignType smallint,nLanguaId smallint,nRowShowNum smallint,nColumShowNum smallint,nHHeadTextColor integer,nHHeadBackColor integer,nHHeadFontSize smallint,sHHeadFontFamily varchar,nVHeadTextColor integer,nVHeadBackColor integer,nVHeadFontSize integer,sVHeadFontFamily varchar,nDataTextColor integer,nDataBackColor integer,nDataFontSize smallint,nLineColor integer,nTransparent smallint,nZvalue integer, nCollidindId integer,nShowPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*50.	�䷽ѡ����*/
    sCreateTableCmd = "CREATE TABLE [recipeSelect] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartPosX smallint,nStartPosY smallint,nWidth smallint,nHeight smallint,eShowType smallint,sShowRecipeId smallint,sFontFamily varchar,nFontSize smallint,nTextColor integer,nBackColor integer,nCurrShowRow smallint,bUseMacro boolean,nMacroId smallint,nTouchPropId integer,nShowPropId integer,nTransparent smallint,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*51.	�������Ա�*/
    sCreateTableCmd = "CREATE TABLE [scene] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nSceneId integer,sScreenName varchar,bLogout boolean,sNumber integer,nSceneWidth smallint,nSceneHeight smallint,eBackType smallint,nBackColor integer,nForeColor integer,eDrawStyle smallint,sPicturePath varchar,bIsAddMenu boolean,bSlide boolean,nTowardLeftId integer,nTowardRIghtId integer,nSlideStyle integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*52.	��������*/
    sCreateTableCmd = "CREATE TABLE [windown] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, nSceneId integer NOT NULL, sScreenName varchar,bLogout boolean,sNumber integer,nShowPosX smallint,nShowPosY smallint,nWindownWidth smallint,nWindownHeight smallint,bShowTitle boolean,bShowShutBtn boolean, sTileName varchar,nBackColor integer,bShowMiddle boolean,eBackType smallint,nForeColor integer,sPicturePath varchar,eDrawStyle smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*53.	�����ʹ��ڸ��ؼ��Ĺ�����*/
    sCreateTableCmd = "CREATE TABLE [sceneAndItem] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, nSceneId integer, nItemId integer,nId integer,nItemTableType integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*54.	�������Ա�*/
    sCreateTableCmd = "CREATE TABLE [keyboardScene] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, sKBName varchar, nSceneWidth smallint, nSceneHeight smallint,eBackType smallint,nBackColor integer,nForeColor integer,eDrawStyle smallint,sPicturePath varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*55.	���̸������ؼ��Ĺ�����*/
    sCreateTableCmd = "CREATE TABLE [kbAndItem] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT, nKeyBoardId integer, nItemId integer,nId integer,nItemTableType integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*56.	�Զ�����̵İ���*/
    sCreateTableCmd = "CREATE TABLE [UDFKkeyBoard] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartX smallint, nStartY  smallint, nWidth smallint, nHeight smallint, nUpFrameColor integer, nUpForeColor integer, nUpBackColor integer, eUpStyle smallint, nDownFrameColor integer, nDownForeColor integer, nDownBackColor integer, eDownStyle smallint,eKeyOperation smallint, sText varchar, nFontSize smallint, nFontColor integer, nFontPro integer, eFontAlign smallint, sImagePath varchar, nShowImage smallint, sASCIIText varchar,sFontFamily varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*57.	���������Ա�*/
    sCreateTableCmd = "CREATE TABLE [sliding] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nWidth smallint,nHeight smallint,nStartX smallint,nStartY smallint,nRectColor integer,nSlideBarColor integer,nFingerBackColor integer,nFingerLineColor integer,nDirection smallint,nPosition smallint,bShowCalibration bool,eDataType smallint,nWirteAddress integer,bShowTrend bool,nMaxTrend double,nMinTrend double,nCalibrationColor integer, nMaxNumber smallint,nMinNumber smallint,bShowShaft bool,nDecimalCount smallint,nTextSize smallint, bShowText bool, nTotalCount smallint, nCalibrationMax double, nCalibrationMin double, nSlideWidth smallint, nSlideHeight smallint ,nZvalue integer, nCollidindId integer, nShowPropId integer,nTouchPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*58.	��̬�ı�*/
    sCreateTableCmd = "CREATE TABLE [staticText] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,sStextStr varchar,sFontFamly varchar,nFontSize smallint,bFristLanguage boolean,nLanguageId smallint,eTextPro integer,sFontSpace smallint,eTextAlign smallint,nFontColor integer,nStylePadding smallint,nAlphaPadding smallint,nBackColorPadding integer,nForeColorPadding integer,nStartX smallint,nStartY smallint,nRectWidth smallint,nRectHeight smallint,nLineWidth smallint,nLineColor integer,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*59.	����ͼ*/
    sCreateTableCmd   = "CREATE TABLE [trends] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nTopLeftX smallint,nTopLeftY smallint,nWidth smallint,nHeight smallint,nCurveX smallint,nCurveY smallint,nCurveWd smallint,nCurveHt smallint,nCurveType smallint,nGroupNum smallint,nChannelNum smallint,nDisplayMax double,nDisplayMin double,nDataSample smallint,nScrollSample smallint,nVertMajorScale smallint,bSelectVertMinor boolean,nVertMinorScale smallint,nHorMajorScale smallint,bSelectHorMinor boolean,nHorMinorScale smallint,bSelectNet boolean,nVertNetColor integer,nHorNetColor integer,nBoradColor integer,nScaleColor integer,nGraphColor integer,sFontType varchar,nFontSize smallint,nFontAttri smallint,nDate smallint,nTime smallint,nMarkColor integer,bXmark boolean,nTimeRange smallint,nRecentYear smallint,nRecentMonth smallint,nRecentDay smallint,nRecentHour smallint,nRecentMinute smallint,nStartYear smallint,nStartMonth smallint,nStartDay smallint,nStartHour smallint,nStartMinute smallint,nEndYear smallint,nEndMonth smallint,nEndDay smallint,nEndHour smallint,nEndMinute smallint,nCurveAlpha integer,nZvalue integer,nCollidindId integer,nShowPropId integer,bMainVer boolean,bMainHor boolean,mFromAddr integer,mToAddr integer,bDate boolean,bTime boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;
    sCreateTableCmd   = "CREATE TABLE [xytrends] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nTopLeftX smallint,nTopLeftY smallint,nWidth smallint,nHeight smallint,nCurveX smallint,nCurveY smallint,nCurveWd smallint,nCurveHt smallint,nAddrLength smallint,nChannelNum smallint, nTrigAddr integer,bAutoReset boolean,eDataType smallint, bDisplayConst smallint,nDisplayMaxX double,nDisplayMinX double,bDisplayConstY smallint, nDisplayMaxY double,nDisplayMinY double,bScale boolean, eNumberTypeX smallint,nSourceMaxX double,nSourceMinX double, eNumberTypeY smallint,nSourceMaxY double,nSourceMinY double,bMainVer boolean,nVertMajorScale smallint, bSelectVertMinor boolean,nVertMinorScale smallint,bMainHor boolean,nHorMajorScale smallint,bSelectHorMinor boolean,nHorMinorScale smallint,bSelectNet boolean,nVertNetColor integer,nHorNetColor integer,nBoradColor integer,nScaleColor integer,nGraphColor integer, nFontSize smallint, nMarkColor integer, nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*60.	����ͼ�е�ͨ�����ò��ֵ�����*/
    sCreateTableCmd = "CREATE TABLE [trendsChannelSet] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nStartAddrX integer,nStartAddrY integer,nNumOfChannel smallint, nDisplayCondition smallint,nDisplayAddr integer,nLineType smallint,nLineThickness smallint,nDisplayColor integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*61.	�û�������Ϣ*/
    sCreateTableCmd = "CREATE TABLE [userList] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,sGroupName varchar,sGroupDescript varchar,sUserId smallint,sUserName varchar,sUserDescript varchar,sPassword varchar,sMasterSet boolean,sMaster boolean)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*62.	��̬����*/
    sCreateTableCmd = "CREATE TABLE [dynamicRect] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nAlpha smallint,nXPos smallint,nYPos smallint,nWidth smallint,nHeight smallint,nFillColor integer,nUseFill smallint,nRimColor integer,nRimWidth smallint,mXDataAddr integer,mYDataAddr integer,nUsePosCtrl smallint,nRefType smallint,mWDataAddr integer,mHDataAddr integer,nUseSizeCtrl smallint,nAreaLp smallint,nAreaTp smallint,nAreaWidth smallint,nAreaHeight smallint,nAreaColor integer,nZvalue integer,nCollidindId integer,nShowPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*63.	��̬Բ*/
    sCreateTableCmd = "CREATE TABLE [dynamicRound] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nAlpha smallint,nCpXpos smallint,nCpYpos smallint,nRadius smallint,nFillColor integer,nUseFill smallint,nRimColor integer,nRimWidth smallint,nUsePosCtrl smallint,mCpXDataAddr integer,mCpYDataAddr integer,mRadiusDataAddr integer,nUseSizeCtrl smallint,nAreaLp smallint,nAreaTp smallint,nAreaWidth smallint,nAreaHeight smallint,nAreaColor integer,nZvalue integer,nCollidindId integer,nShowPropId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*64.	�ؼ�������*/
    sCreateTableCmd = "CREATE TABLE [itemMutilLanguage] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nStatusId smallint, nLanguageId smallint,sText varchar,sFontType varchar, nFontSize smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*65.	font map*/
    sCreateTableCmd = "CREATE TABLE [fontmap] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,sFontType varchar,sFileName varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*66.	���԰�*/
    sCreateTableCmd = "CREATE TABLE [messageBoard] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartX smallint,nStartY smallint,nWidth smallint,nHeight smallint,nAlpha smallint,nLineColor integer,nFillCss smallint,nBackColor integer,nForeColor integer,nFontSize smallint,sFontType varchar,nFontColor integer,nTFontSize smallint,sTFontType varchar,nTFontColor integer,nTBackColor integer,bShowId boolean,bShowTime boolean,nTimeType smallint,bShowDate boolean,nDateType smallint,nRowNumber integer,nZvalue integer,nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*67.	���԰������*/
    sCreateTableCmd = "CREATE TABLE [messageBoardLanguage] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nId integer,nItemId integer,nLanguageIndex integer,sNumber varchar,sDateName varchar,sTimeName varchar,sMessageName varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*68.	������Ϣ*/
    sCreateTableCmd = "CREATE TABLE [messageInfo] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nTime long,sMessage varchar,sTitle varchar)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*69.	������*/
    sCreateTableCmd = "CREATE TABLE [dragdownBox] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartX smallint,nStartY smallint,nWidth smallint,nHeight smallint,nState smallint,eNumberType smallint,nBaseAddrID integer,bScriptSet boolean,nScriptId smallint,sBackgroundImg varchar,nBackgroundColor integer,Alpha smallint,nFirstLan boolean,nCollidindId integer,nZvalue integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*�Զ������*/
    sCreateTableCmd = "CREATE TABLE [userGroup] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,sPath varchar,nLp smallint,nTp smallint,nWidth smallint,nHeight smallint,nZvalue integer, nCollidindId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*���ϴ���*/
    sCreateTableCmd = "CREATE TABLE [dataTrans] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nGroupId smallint,nTransType smallint,nInterval smallint,nTriggerAddrId integer,bAutoReset smallint,nAddrType smallint,nTransLen smallint,bDynLength boolean,nLengthAddrId integer, nSourceAddrId integer, nTargetAddrId integer)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;

    /*�๦�ܰ�ť*/
    sCreateTableCmd = "CREATE TABLE [MFbtn] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nSceneId integer,nStartX smallint,nStartY smallint,nWidth smallint,nHeight smallint, eflick smallint,nAlpha integer,nColor integer,eLib smallint,sPath varchar, nZvalue integer,nCollidindId integer, bIsStartStatement boolean, nScriptId smallint, nStatTotal smallint, nAddrType boolean, nBitIndex smallint, nCondition smallint, eWatchDataType smallint, nWatchAddr integer, eWatchType smallint)";
    bScuccess = sqlQuery.exec(sCreateTableCmd);
    if(!bScuccess) return false;
    /*62.	���ݲɼ�������*/
    //sCreateTableCmd = "CREATE TABLE [dataCollect] (id integer NOT NULL PRIMARY KEY AUTOINCREMENT,nItemId integer,nGroupName varchar,nDataId integer,nData integer,mDate date,mTime time)";
    //bScuccess = sqlQuery.exec(sCreateTableCmd);
    //if(!bScuccess) return false;

    return true;
}


bool CompileThrd::removeDirectory(QString dirName)
{
  QDir dir(dirName);
  QString tmpdir = "";
  if(!dir.exists()){
    return false;
  }

  QFileInfoList fileInfoList = dir.entryInfoList();
  foreach(QFileInfo fileInfo, fileInfoList){
    if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
      continue;

    if(fileInfo.isDir()){
      tmpdir = dirName + ("/") + fileInfo.fileName();
      removeDirectory(tmpdir);
      dir.rmdir(fileInfo.fileName()); /**< �Ƴ���Ŀ¼ */
    }
    else if(fileInfo.isFile()){
      QFile tmpFile(fileInfo.fileName());
      dir.remove(tmpFile.fileName()); /**< ɾ����ʱ�ļ� */
    }
    else{
      ;
    }
  }

//  dir.cdUp();            /**< �����ϼ�Ŀ¼����Ϊֻ�з����ϼ�Ŀ¼���ſ���ɾ�����Ŀ¼ */
//  if(dir.exists(dirName)){
//    if(!dir.rmdir(dirName))
//      return false;
//  }
  return true;
}
