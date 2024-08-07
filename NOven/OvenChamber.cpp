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

    case STEP_O2_PURGE:
    {
        if (IsHold == false)
        {
            if (FMainTempController->Hold() == false)
            {
                RaiseAlarm(ERR_TEMP_CONTROLLER_HOLD_FAIL);
                SetStep(STEP_IDLE);
                break;
            }
            Sleep(1000);
            break;
        }

        if (Options.O2Function.CheckO2DensityValid(O2Valid, IsO2Valid))
        {
            SetStep(STEP_CURE_START);
            break;
        }

        if (Options.O2Function.IsO2DensityTimeout())
        {
            RaiseAlarm(ERR_O2_DENSITY_ALARM);
            SetStep(STEP_IDLE);
            break;
        }
    }
    break;

    case STEP_CURE_START:
    {
        if (IsHold)
        {
            if (FMainTempController->Resume() == false)
            {
                RaiseAlarm(ERR_TEMP_CONTROLLER_RESUME_FAIL);
                SetStep(STEP_IDLE);
                break;
            }
            Sleep(100);
            break;
        }
        SetStep(STEP_RAMPUP);
        Sleep(1000);
    }
    break;

    case STEP_RAMPUP:
    {
        if (IsForcedCureStopped())
        {
            SetStep(STEP_DONE);
            break;
        }
        if (IsRun == false)
        {
            RaiseAlarm(ERR_TEMP_CONTROLLER_NOT_RUN);
        }

        bool useO2Analyzer = GetManager()->Options.FactorySetting.UseO2Analyzer;
        bool purgeFirst = Options.O2Function.CureStartOnTargetDensity;
        if (useO2Analyzer)
        {
            if (purgeFirst)
            {
                if (Options.O2Function.CheckO2DensityValid(O2Value, IsO2Valid) == false)
                {
                    RaiseAlarm(ERR_O2_DENSITY_ALARM);
                }
            }
            else
            {
                Options.O2Function.CheckO2DensityValid(O2Value, IsO2Valid);
                if (Options.O2Function.IsO2DensityTimeout())
                {
                    RaiseAlarm(ERR_O2_DENSITY_ALARM);
                }
            }
        }
        break;
    }
    case STEP_RUNNING:
    {
        if (IsForcedCureStopped())
        {
            SetStep(STEP_IDLE);
            break;
        }
        if (IsRun == false)
        {
            RaiseAlarm(ERR_TEMP_CONTROLLER_NOT_RUN);
        }

        bool useO2Analyzer = GetManager()->Options.FactorySetting.UseO2Analyzer;
        if (useO2Analyzer)
        {
            if (Options.O2Function.CheckO2DensityValid(O2Value, IsO2Valid) == false)
            {
                RaiseAlarm(ERR_O2_DENSITY_ALARM);
            }
        }

        if (IsCoolingEventOn == false)
        {
            break;
        }
        SetStep(STEP_COOLING);
    }
    break;

    case STEP_GOTO_COOLING:
    {
        while (SegNo != 3)
        {
            GotoNextSeg();
            Wait(2);
        }

        if (IsCoolingEventOn == false)
        {
            break;
        }
        SetStep(STEP_COOLING);
    }
    break;

    case STEP_COOLING:
    {
        if (IsForcedCureStopped())
        {
            SetStep(STEP_IDLE);
            break;
        }

        if (FMainTempController->RamainingTime > 1)
        {
            if (IsRun == false)
            {
                RaiseAlarm(ERR_TEMP_CONTROLLER_NOT_RUN);
            }
        }

        int shutdownTemp = Options.General.ShutdownTemp;
        if (IsReset || PV < (double)shutdownTemp)
        {
            SetStep(STEP_DONE);
        }
    }
    break;

    case STEP_CURE_STOP:
    {
        if (DoCureStop(FORCED_STOP))
        {
            SetStep(STEP_DONE);
        }
    }
    break;

    case STEP_DONE:
    {
        RearManualDoorUnlock();
        CoolingBufferDoorUnlock();
        DeleteStateFile();
    }
    break;
    }
}

bool __fastcall OvenChamber::DoCureStop(int stopType)
{
    if (FMainTempController == nullptr)
    {
        return false;
    }

    for (int i = 0; i < 3; i++)
    {
        if (FMainTempController->Reset())
        {
            Sleep(500);
            if (IsReset)
            {
                Recipe.StopType = stopType;
                return true;
            }
        }
    }
    return false;
}

bool __fastcall OvenChamber::SaveCurrentState()
{
    String strFile, str;
    strFile.sprintf(L"%s\\Current_T_%c.ini", GetStatusFolder().c_str(), 'A' + ModuleType);

    std::auto_ptr<TIniFile> statFile(new TIniFile(strFile));
    String sec = "STATE";

    try
    {
        statFile->WriteDateTime(sec, "Last Save Time", Now());
        statFile->WriteInteger(sec, "Step", FStep);
        statFile->WriteString(sec, "Recipe", Recipe.RecipeName);
        statFile->WriteString(sec, "UserID", GetManager()->UserID);
        statFile->WriteDateTime(sec, "Start Time", Recipe.CureStartTime);
        statFile->WriteBool(sec, "Job End", Recipe.JobEnd);
        statFile->WriteInteger(sec, "Stop Type", Recipe.StopType);
    }
    catch (const std::exception &e)
    {
        return false;
    }
    return true;
}

bool __fastcall OvenChamber::LoadCurrentState()
{
    String strFile;
    strFile.sprintf(L"%s\\Current_T_%c.ini", GetStatusFolder().c_str(), 'A' + ModuleType);

    if (FileExists(strFile) == false)
    {
        return false;
    }

    std::auto_ptr<TIniFile> statFile(new TIniFile(strFile));
    String sec = "STATE";

    try
    {
        Step = statFile->ReadInteger(sec, "Step", FStep);
        Recipe.RecipeName = statFile->ReadString(sec, "Recipe", Recipe.RecipeName);
        GetManager()->UserID = statFile->ReadString(sec, "User ID", GetManager()->UserID);
        Recipe.CureStartTime = statFile->ReadDateTime(sec, "Start Time", Recipe.CureStartTime);
        Recipe.JobEnd = statFile->ReadBool(sec, "Job End", Recipe.JobEnd);
        Recipe.StopType = statFile->ReadInteger(sec, "Stop Type", Recipe.StopType);
        MakeDataFilename();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

bool __fastcall OvenChamber::DeleteStateFile()
{
    String strFile;
    strFile.sprintf(L"%s\\Current_T_%c.ini", GetStatusFolder().c_str(), 'A' + ModuleType);

    bool ret = false;

    if (FileExists(strFile))
    {
        ret = DeleteFile(strFile);
    }
    return ret;
}

void __fastcall OvenChamber::MakeDataFilename()
{
    FILE *pFile;
    AnsiString file, name, folder;

    name.sprintf("%c_", 'A' + ModuleType);
    name += Recipe.CureStartTime.FormatString("yyyy_mm_dd_hh_nn_ss");

    folder = GetReportFolder();
    file = folder + "MainTemp_" + name + ".cht";
    pFile = fopen(file.c_str(), "a+t");

    if (pFile != nullptr)
    {
        fclose(pFile);
    }

    Recipe.MainTempFilename = file;

    file = folder + "LIMIT_" + name + ".cht";
    pFile = fopen(file.c_str(), "a+t");

    if (pFile != nullptr)
    {
        fclose(pFile);
    }
    Recipe.LimitFilename = file;

    file = folder + "LOGGER_" + name + ".cht";
    pFile = fopen(file.c_str(), "a+t");

    if (pFile != nullptr)
    {
        fclose(pFile);
    }
    Recipe.LoggerFilename = file;
}