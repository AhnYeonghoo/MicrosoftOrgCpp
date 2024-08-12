#include <memory>

#pragma hdrstop

#include "EQDefines.h"
#include "HelperFunctions.h"
#include "SystemManager.h"
#include "Database.h"
#include "TowerLampControl.h"
#include "LogWriter.h"
#include "ComiEtherCatIOManager.h"
#include "ComizoaEtherCatIOModule.h"
#include "InputOutputBank.h"
#include "HandlerBase.h"
#include "ComiEthercatMotorCtrl.h"
#include "WatchIOThread.h"
#include "OvenChamber.h"
#include "DoorRun.h"

#pragma package(smart_init)

SystemManager::SystemManager()
{
    FTowerLampOption = new TowerLampControl();
    FIOManager = nullptr;
    FOperationMode = OM_READY;
    FInitStarted = false;
    FInitStopped = false;
    FIsBlink = false;
    FIsTestMode = false;
    UserID = L"Operator";

    int ComiDioModuleCount = IO_COUNT / MAX_IO_COUNT32_PER_MODULE;
    ComiDeviceAddr.push_back(0x201);
    ComiDeviceAddr.push_back(0x202);
    ComiDeviceAddr.push_back(0x203);
    ComiDeviceAddr.push_back(0x204);
    ComiDeviceAddr.push_back(0x215);
    for (int i = 0; i < MOTOR_COUNT; i++)
    {
        ComiDeviceAddr.push_back(i + 1);
    }

    GetIOBank();
#ifdef _DEBUG
    LoginLevel = LV_DEVELOPER;
#else
    LoginLevel = LV_OPERATOR;
#endif
}

SystemManager::~SystemManager()
{
    if (FTowerLampOption)
    {
        delete FTowerLampOption;
        FTowerLampOption = nullptr;
    }

    DestroyHandler();
    DestroyLogWriter();
    DestroyIOManager();
    DestroyMotors();

    if (Options.FactorySetting.IOType == IT_COMIZOA)
    {
        ComiEtherCatIOManager::UnloadLibrary();
    }
}

void __fastcall CreateFolder(String folder)
{
    if (CreateDir(folder) == false)
    {
        String msg;
        String str = GetResStr(L"MESSAGE", L"FileCreateFail");
        msg.sprintf(str.c_str(), folder.c_str());
        SetMessageStr(msg);
        ShowMessageDlg();
    }
}

void __fastcall SystemManager::InitManager()
{
    String title = UpperCase(Application->Title);
    InitDirectory(title);
    LoadLanguageStr();
    GetDB()->ConnectDB();
    GetDB()->ConnectErrDB();

    LoadSystemParameters();
    OptionItem<int> language = Options.General.Language;
    Options.General.Language = language;

    CreateLogWriter();
    if (Options.FactorySetting.IOType == IT_COMIZOA)
    {
        String str;
        if (ComiEtherCatIOManager::LoadLibrary(str) == false)
        {
            SetMessageStr(str);
            ShowMessageDlg();
        }
    }

    LoadIOSettings();
    LoadTowerLampValue();
    CreateIOManager();
    CreateMotors();
    CreateChamber();
    ClearAlarmAll();
    LoadMotionSettings();
    CreateHandler();

    if (GetManager()->GetDoor()->IsServoMCOn() == false)
    {
        GetManager()->GetDoor()->ServoMCOn();
    }

    String str;
    str = GetResStr(L"UI", L"Home");
    HomeSensorTypeStr.push_back(str);
    str = GetResStr(L"UI", L"PositiveLimit");
    HomeSensorTypeStr.push_back(str);
    str = GetResStr(L"UI", L"NegativeLimit");
    HomeSensorTypeStr.push_back(str);

    str = GetResStr(L"UI", L"NegativeDir");
    HomeSensorDirStr.push_back(str);
    str = GetResStr(L"UI", L"PositiveDir");
    HomeSensorDirStr.push_back(str);
}