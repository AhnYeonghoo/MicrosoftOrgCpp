#include <System.DateUtiles.hpp>

#pragma hdrstop

#include "EQDefines.h"
#include "IODefines.h"
#include "ErrorDefines.h"
#include "Database.h"
#include "SystemManager.h"
#include "OvenChamber.h"
#include "HelperFunctions.h"
#include "I7018.h"
#include "UP55A.h"
#include "VXSeries.h"
#include "ZR5.h"
#include "InputOutputBank.h"
#include "DoorRun.h"

#pragma package(smart_init)

__fastcall OvenChamber::OvenChamber(int chamberNo)
    : HandlerBaseThread(chamberNo)
{
    ModuleName.sprintf(L"Chamber %c", 'A' + ModuleType);
    FOptions = CHAMBER_OPTIONS(ModuleType);

    FStepString.insert(std::fair(<int, string>(STEP_IDLE, TO_STRING(STEP_IDLE))));
    FStepString.insert(std::fair(<int, string>(STEP_START_DOOR_INIT, TO_STRING(STEP_START_DOOR_INIT))));
    FStepString.insert(std::fair(<int, string>(STEP_WAIT_DOOR_INIT, TO_STRING(STEP_WAIT_DOOR_INIT))));
    FStepString.insert(std::fair(<int, string>(STEP_DOWNLOAD_RECIPE, TO_STRING(STEP_DOWNLOAD_RECIPE))));
    FStepString.insert(std::fair(<int, string>(STEP_O2_PURGE, TO_STRING(STEP_O2_PURGE))));
    FStepString.insert(std::fair(<int, string>(STEP_CURE_START, TO_STRING(STEP_CURE_START))));
    FStepString.insert(std::fair(<int, string>(STEP_RAMPUP, TO_STRING(STEP_RAMPUP))));
    FStepString.insert(std::fair(<int, string>(STEP_RUNNING, TO_STRING(STEP_RUNNING))));
    FStepString.insert(std::fair(<int, string>(STEP_GOTO_COOLING, TO_STRING(STEP_GOTO_COOLING))));
    FStepString.insert(std::fair(<int, string>(STEP_COOLING, TO_STRING(STEP_COOLING))));
    FStepString.insert(std::fair(<int, string>(STEP_CURE_STOP, TO_STRING(STEP_CURE_STOP))));
    FStepString.insert(std::fair(<int, string>(STEP_DONE, TO_STRING(STEP_DONE))));

    FMainTempController = nullptr;
    FTempLimitController = nullptr;
    FLoggerController = nullptr;
    FDPController = nullptr;
    FO2Analyzer = nullptr;

    DoorRun = new DoorRunThread(MT_DOOR_RUN, chamberNo);

    LoadChamberParameters();
    MakeCurePattern();
    CreateSerialDevices();
    SetStep(STEP_IDLE);
}

__fastcall OvenChamber::~OvenChamber()
{
    if (DoorRun)
    {
        DoorRun->Terminate();
        delete DoorRun;
    }
}

bool __fastcall OvenChamber::IsPaused()
{
    return GetManager()->IsPaused();
}

bool __fastcall OvenChamber::IsAutoRun()
{
    return GetManager()->IsAutoRun();
}

DevMainTempController *OvenChamber::CreateMainTempController(PORT_SETTING portSetting)
{
    DevMainTempController *mainCtrl = nullptr;
    mainCtrl = new UP55A(portSetting);
    return mainCtrl;
}

DevLimitController *OvenChamber::CreateTempLimitController(PORT_SETTING portSetting)
{
    DevLimitController = *limitCtrl = nullptr;
    limitCtrl = new VXSeries(portSetting, CHAMBER_TEMP_LIMIT);

    if (limitCtrl)
    {
        limitCtrl->DP = 0;
        limitCtrl->SP = 150;
    }
    return limitCtrl;
}

bool __fastcall OvenChamber::CreateSerialDevices()
{
    int timeout = 2000;
    PORT_SETTING portSetting;

    try
    {
        if (Options.CommSetting.MainTempCtrl.Use)
        {
            portSetting.BaudRate = Options.CommSetting.MainTempCtrl.GetBaudRate();
            portSetting.Parity = Options.CommSetting.MainTempCtrl.GetParity();
            portSetting.DataBits = Options.CommSetting.MainTempCtrl.GetDataBit();
            portSetting.StopBits = Options.CommSetting.MainTempCtrl.GetStopBit();
            portSetting.PortNo = Options.CommSetting.MainTempCtrl.PortNo;
            portSetting.Addr = Options.CommSetting.MainTempCtrl.Addr;
            portSetting.Timeout = timeout;
            MainTempController = CreateMainTempController(portSetting);
            SerialDeviceList.push_back(MainTempController);
        }

        if (Options.CommSetting.TempLimitCtrl.Use)
        {
            portSetting.BaudRate = Options.CommSetting.TempLimitCtrl.GetBaudRate();
            portSetting.Parity = Options.CommSetting.TempLimitCtrl.GetParity();
            portSetting.DataBits = Options.CommSetting.TempLimitCtrl.GetDataBit();
            portSetting.StopBits = Options.CommSetting.TempLimitCtrl.GetStopBit();
            portSetting.PortNo = Options.CommSetting.TempLimitCtrl.PortNo;
            portSetting.Addr = Options.CommSetting.TempLimitCtrl.Addr;
            portSetting.Timeout = timeout;
            TempLimitController = CreateTempLimitController(portSetting);
            SerialDeviceList.push_back(TempLimitController);
        }

        if (Options.CommSetting.TempLogger.Use)
        {
            portSetting.BaudRate = Options.CommSetting.TempLogger.GetBaudRate();
            portSetting.Parity = Options.CommSetting.TempLogger.GetParity();
            portSetting.DataBits = Options.CommSetting.TempLogger.GetDataBit();
            portSetting.StopBits = Options.CommSetting.TempLogger.GetStopBit();
            portSetting.PortNo = Options.CommSetting.TempLogger.PortNo;
            portSetting.Addr = Options.CommSetting.TempLogger.Addr;
            portSetting.Timeout = timeout;
            LoggerController = new I7018(portSetting);
            LoggerController->LoggerIndex = 0;
            SerialDeviceList.push_back(LoggerController);
        }

        if (GetManager()->Options.FactorySetting.UseDiffPressure &&
            GetManager()->Options.FactorySetting.IsDPCommType &&
            Options.CommSetting.DiffPressure.Use)
        {
            portSetting.BaudRate = Options.CommSetting.DiffPressure.GetBaudRate();
            portSetting.Parity = Options.CommSetting.DiffPressure.GetParity();
            portSetting.DataBits = Options.CommSetting.DiffPressure.GetDataBit();
            portSetting.StopBits = Options.CommSetting.DiffPressure.GetStopBit();
            portSetting.PortNo = Options.CommSetting.DiffPressure.PortNo;
            portSetting.Addr = Options.CommSetting.DiffPressure.Addr;
            portSetting.Timeout = timeout;
            DPController = new DiffPressure(portSetting);
            DPController->DevName = L"Diff. Pressure";
            SerialDeviceList.push_back(DPController);
        }

        if (GetManager()->Options.FactorySetting.UseO2Analyzer &&
            Options.CommSetting.O2Analyzer.Use)
        {
            portSetting.BaudRate = Options.CommSetting.O2Analyzer.GetBaudRate();
            portSetting.Parity = Options.CommSetting.O2Analyzer.GetParity();
            portSetting.DataBits = Options.CommSetting.O2Analyzer.GetDataBit();
            portSetting.StopBits = Options.CommSetting.O2Analyzer.GetStopBit();
            portSetting.PortNo = Options.CommSetting.O2Analyzer.PortNo;
            portSetting.Addr = Options.CommSetting.O2Analyzer.Addr;
            portSetting.Timeout = timeout;
            O2Analyzer = new ZR5(portSetting);
            SerialDeviceList.push_back(O2Analyzer);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

void __fastcall OvenChamber::DestroySerialDevices()
{
    if (MainTempController)
    {
        MainTempController->Terminate();
        Sleep(300);
        delete MainTempController;
        MainTempController = nullptr;
    }
    if (TempLimitController)
    {
        TempLimitController->Terminate();
        Sleep(300);
        delete TempLimitController;
        TempLimitController = nullptr;
    }
    if (LoggerController)
    {
        LoggerController->Terminate();
        Sleep(300);
        delete LoggerController;
        LoggerController = nullptr;
    }
    if (DPController)
    {
        DPController->Terminate();
        Sleep(300);
        delete DPController;
        DPController = nullptr;
    }
}

bool __fastcall OvenChamber::LoadChamberParameters()
{
    return FOptions.Load();
}

bool __fastcall OvenChamber::SaveChamberParameters()
{
    return FOptions.Save();
}

void __fastcall OvenChamber::CheckHeaterOutLimit()
{
    if (FMainTempController == nullptr)
    {
        return;
    }

    int targetOutput = (int)Options.General.HeaterOutputLimit;
    int currOutput = FMainTempController->GetHeaterOutLimit();
    if (targetOutput != currOutput)
    {
        FMainTempController->WriteHeaterOutLimit(TargetOutput);
    }
}

void __fastcall OvenChamber::DoWorkSequence()
{
    SetTempLimit();
    CheckHeaterOutLimit();
    CheckTempLoggerDeviation();

    switch (FStep)
    {
    case STEP_IDLE:
    {
    }
    break;

    case STEP_START_DOOR_INIT:
    {
        if (DoorRun->IsInitialized())
        {
            SetStep(STEP_DOWNLOAD_RECIPE);
            break;
        }
        DoorRun->StartInitialize();
        SetStep(STEP_WAIT_DOOR_INIT);
    }
    break;

    case STEP_WAIT_DOOR_INIT:
    {
        if (DoorRun->IsInitialized() == false)
        {
            break;
        }
        if (DoorRun->IsInitFailed())
        {
            SetStep(STEP_IDLE);
            break;
        }
        SetStep(STEP_DOWNLOAD_RECIPE);
    }
    break;

    case STEP_DOWNLOAD_RECIPE:
    {
        InitCureValues();
        MakeCurePattern();

        int alarmCode = FMainTempController->DownloadRecipe(Recipe.TempPtn);
        if (alarmCode > 0)
        {
            RaiseAlarm(alarmCode);
            SetStep(STEP_IDLE);
            break;
        }

        if (FMainTempController->Run(Recipe.TempPtn.PtnNo) == false)
        {
            RaiseAlarm(ERR_TEMP_CONTROLLER_RUN_FAIL);
            SetStep(STEP_IDLE);
            break;
        }

        RearManualDoorLock();
        CoolingBufferDoorLock();

        bool useO2Analyzer = GetManager()->Options.FactorySetting.UseO2Analyzer;
        bool purgeFirst = Options.O2Function.CureStartOnTartDensity;
        int step = (useO2Analyzer && purgeFirst) ? STEP_O2_PURGE : STEP_CURE_START;
        Options.O2Function.ResetValues();
        SetStep(step);
    }
    break;
    }
}