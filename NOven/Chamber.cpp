#pragma hdrstop

#include <System.DateUtils.hpp>
#include "Chamber.h"
#include "HelperFunctions.h"
#include "MainTempController.h"
#include "LimitController.h"
#include "Database.h"
#include "SystemManager.h"
#include "Defines.h"

#pragma package(smart_init)

BaseChamber::BaseChamber(int chamberNo)
    : TThread(false)
{
    FChamberID = chamberNo;
    FEnabled = true;
    FErrorString = "";
    FStep = -1;
    for (int i = 0; i < MAX_ALARM_COUNT; i++)
    {
        FAlarmStatus[i] = false;
    }
    FNewAlarm = false;
}

BaseChamber::~BaseChamber()
{
    StepChanged = false;
}

void __fastcall BaseChamber::Execute()
{
    while (!terminated)
    {
        WaitForSingleObject((void *)Handle, THREAD_WAIT_TIME);
        DoWorkSequence();
    }
}

void BaseChamber::DelayTime(unsigned int milliSeconds, bool workInThread)
{
    TDateTime now = Now();
    while (1)
    {
        if (workInThread)
        {
            WaitForSingleObject((void *)Handle, THREAD_WAIT_TIME);
        }
        else
        {
            Application->ProcessMessages();
            Sleep(THREAD_WAIT_TIME);
        }
        if (MilliSecondsBetween(now, Now()) >= milliSeconds)
        {
            break;
        }
    }
}

void BaseChamber::SetStep(int step)
{
    FStep = step;
    StepChanged = true;
}

bool BaseChamber::SetAlarm(unsigned int alarmCode)
{
    std::vector<unsigned int>::iterator i;
    for (i = Alarms.begin(); i != Alarms.end(); i++)
    {
        if (*i == alarmCode)
        {
            return false;
        }
    }

    FNewAlarm = true;
    Alarms.push_back(alarmCode);
    return true;
}

unsigned int BaseChamber::GetAlarm(int idx)
{
    return Alarms[idx];
}

void BaseChamber::ClearAlarm(unsigned int alarmCode)
{
    std::vector<unsigned int>::iterator i;
    for (i = Alarms.begin(); i != Alarms.end(); i++)
    {
        if (*i == alarmCode)
        {
            Alarms.erase(i);
            FAlarmStatus[alarmCode] = false;
            break;
        }
    }
}

void BaseChamber::ClearAlarmAll()
{
    Alarms.Clear();
    for (int i = 0; i < MAX_ALARM_COUNT; i++)
    {
        FAlarmStatus[i] = false;
    }
}

bool BaseChamber::GetAlarmStatus(int idx)
{
    if (idx >= 0 && idx < MAX_ALARM_COUNT)
    {
        return FAlarmStatus[idx];
    }
    return false;
}

void BaseChamber::SetAlarmStatus(int idx, bool status)
{
    if (idx >= 0 && idx < MAX_ALARM_COUNT)
    {
        FAlarmStatus[idx] = status;
    }
}

OvenChamber::OvenChamber(int chamberNo)
    : BaseChamber(chamberNo)
{
    FMainTempControllerType = TEMPCTRL_UP550;
    FLimitControllerType = LIMIT_ST;
    FMainTempController = nullptr;
    FChamberTempLimitController = nullptr;
    FHeaterTempLimitController = nullptr;
    FPressureLimitController = nullptr;
    for (int i = 0; i < MAX_LOGGER_COUNT; i++)
    {
        FLoggerController[i] = nullptr;
    }

    ProgressValue = 0;
    for (int i = 0; i < MAX_LOGGERPOINT_COUNT; i++)
    {
        FLoggerOffset[i] = 0;
        FUseChannel[i] = FALSE;
    }
    FDoorOpenConditionTemp = 0;
}

OvenChamber::~OvenChamber()
{
    StepChanged = false;
}

OvenChamber::LogStepChanged()
{
    if (StepChanged)
    {
        StepChanged = false;
        String str;
        str.sprintf(L"Step = %s", StatusStr[FStep].c_str());
        GetOvenDB()->SaveLog(str, MESSAGE, FChamberID);
    }
}

I7018 *OvenChamber::GetLoggerController(int idx)
{
    if (idx >= 0 && idx < MAX_LOGGER_COUNT)
    {
        return FLoggerController[idx];
    }
    return nullptr;
}

void OvenChamber::SetLoggerController(int idx, I7018 *logger)
{
    if (idx >= 0 && idx < MAX_LOGGER_COUNT)
    {
        FLoggerController[idx] = logger;
    }
}

double OvenChamber::GetLoggerOffset(int idx)
{
    if (idx >= 0 && idx < MAX_LOGGERPOINT_COUNT)
    {
        return (double)((double)FLoggerOffset[idx] / (double)DEFAULT_SCALEFACTOR);
    }
    return 0;
}

void OvenChamber::SetLoggerOffset(int idx, double offset)
{
    if (idx >= 0 && idx < MAX_LOGGERPOINT_COUNT)
    {
        FLoggerOffset[idx] = (int)(offset * DEFAULT_SCALEFACTOR);
    }
}

double OvenChamber::GetLoggerData(int idx)
{
    if (idx >= 0 && idx < MAX_LOGGERPOINT_COUNT)
    {
        int val = FLoggerData[idx] + FLoggerOffset[idx];
        return (double)(val / (double)DEFAULT_SCALEFACTOR);
    }
    return 0;
}

void OvenChamber::SetLoggerData(int idx, double data)
{
    if (idx >= 0 && idx < MAX_LOGGERPOINT_COUNT)
    {
        FLoggerData[idx] = (int)(data * DEFAULT_SCALEFACTOR);
    }
}

void OvenChamber::SetUseChannel(int idx, bool use)
{
    if (idx >= 0 && idx < MAX_LOGGERPOINT_COUNT)
    {
        FUseChannel[idx] = use;
    }
}

bool OvenChamber::GetUseChannel(int idx)
{
    if (idx >= 0 && idx < MAX_LOGGERPOINT_COUNT)
    {
        return FUseChannel[idx];
    }
    return false;
}

double OvenChamber::GetChamberTempLimitOffset()
{
    return (double)((double)FChamberTempLimitOffset / (double)DEFAULT_SCALEFACTOR);
}

void OvenChamber::SetChamberTempLimitOffset(double offset)
{
    FChamberTempLimitOffset = (int)(offset * (double)DEFAULT_SCALEFACTOR);
    if (FChamberTempLimitController)
    {
        FChamberTempLimitController->LimitOffset = offset;
    }
}

double OvenChamber::GetChamberTempLimitBias()
{
    return (double)((double)FChamberTempLimitBias / (double)DEFAULT_SCALEFACTOR);
}

void OvenChamber::SetChamberTempLimitBias(double bias)
{
    FChamberTempLimitBias = (int)(bias * (double)DEFAULT_SCALEFACTOR);
    if (FChamberTempLimitController)
    {
        FChamberTempLimitController->Bias = bias;
    }
}

double OvenChamber::GetChamberLoggerTempDeviation()
{
    return (double)FChamberLoggerDeviation;
}

void OvenChamber::SetChamberLoggerTempDeviation(double offset)
{
    FChamberLoggerDeviation = offset;
}

void OvenChamber::InitCureValues()
{
    Recipe.StartTime = Now();
    MakeDataFilename();
    Recipe.StopType = NORMAL_STOP;
    Recipe.JobEnd = false;
}

void OvenChamber::MakeDataFilename()
{
    AnsiString file, name, folder;

    name.sprintf("%C_", 'A' + FChamberID);
    name += Recipe.StartTime.FormatString("yyyy_mm_dd_hh_nn_ss");

    folder = GetReportFolder();
    file = folder + "MainTemp_" + name + ".cht";
    Recipe.MainTempFilename = file;

    file = folder + "LIMIT_" + name + ".cht";
    Recipe.LimitFilename = file;

    file = folder + "VACUUM_" + name + ".cht";
    Recipe.VacuumFilename = file;

    file = folder + "HEATER_" + name + ".cht";
    Recipe.HeaterFilename = file;

    file = folder + "PRESS_" + name + ".cht";
    Recipe.PressFilename = file;

    file = folder + "O2_" + name + ".cht";
    Recipe.O2Filename = file;

    file = folder + "LOGGER_" + name + ".cht";
    Recipe.LoggerFilename = file;
}

bool OvenChamber::WriteMainTempData(TDateTime time)
{
    if (MainTempController = nullptr)
    {
        return false;
    }

    AnsiString data, tmp;

    data = (AnsiString)time.FormatString("hh:nn:ss");
    tmp.sprintf(",%.1f,%.1f,%.1f\n",
                PV, SP, HeaterOut);
    data += tmp;

    File *pFile;
    pFile = fopen(Recipe.MainTempFilename.c_str(), "a+t");
    if (pFile == nullptr)
    {
        return false;
    }
    std::fwrite(data.c_str(), data.Length(), 1, pFile);
    fclose(pFile);
    return true;
}

bool OvenChamber::WriteLoggerData(TDateTime time)
{
    AnsiString data, tmp;
    data = (AnsiString)time.FormatString("hh:nn:ss");
    for (int i = 0; i < MAX_LOGGERPOINT_COUNT; i++)
    {
        tmp.sprintf(",%.1f", LoggerData[i]);
        data += tmp;
    }
    data += "\n";
    FILE *pFile;
    pFile = fopen(Recipe.LoggerFilename.c_str(), "a+t");
    if (pFile == nullptr)
    {
        return false;
    }
    std::fwrite(data.c_str(), data.Length(), 1, pFile);
    fclose(pFile);
    return true;
}

bool OvenChamber::WriteLimitData(TDateTime time)
{
    if (FChamberTempLimitController == nullptr)
    {
        return false;
    }
    AnsiString data, tmp;
    data = (AnsiString)time.FormatString("hh:nn:ss");
    tmp.sprintf(",%.1f,%.1f\n", ChamberLimitPV, ChamberLimitSP);
    data += tmp;
    FILE *pFile;
    pFile = fopen(Recipe.LimitFilename.c_str(), "a+t");
    if (pFile == nullptr)
    {
        return false;
    }
    std::fwrite(data.c_str(), data.Length(), 1, pFile);
    fclose(pFile);
    return true;
}

bool OvenChamber::WritePressData(TDateTime time)
{
    if (FPressureLimitController == nullptr)
    {
        return false;
    }
    AnsiString data, tmp;
    data = (AnsiString)time.FormatString("hh:nn:ss");
    tmp.sprintf(",%.2f,%.2f\n", PressureLimitPV, PressureLimitSP);
    data += tmp;
    FILE *pFile;
    pFile = fopen(Recipe.PressFilename.c_str(), "a+t");
    if (pFile == nullptr)
    {
        return false;
    }
    std::fwrite(data.c_str(), data.Length(), 1, pFile);
    fclose(pFile);
    return true;
}

void OvenChamber::WriteProductData(TDateTime endtime, String mcID, String userID,
                                   String lotid, bool errorCode, String detail)
{
    AnsiString file, cm, name, folder, date = "", data = "";
    String tmp, strValue, ecode = "", eDetail = "";

    cm.sprintf("%C", 'A' + FChamberID);
    if (errorCode = true)
    {
        ecode = "NG";
        name = cm + endtime.FormatString("_yyyymmdd");
    }
    else
    {
        ecode = "OK";
        detail = "";
        name = cm + endtime.FormatString("_yyyymmdd");
    }
    folder = GetProductFolder() + cm + "\\";
    if (DirectoryExists(folder) == false)
    {
        CreateDir(folder);
    }

    unsigned short year, mon, day;
    endtime.DecodeDate(&year, &mon, &day);
    String temptime = endTime.FormatString("hhnn");
    int comparetime = StrToInt(temptime);

    if (comparetime < 730)
    {
        TDateTime tempdate;
        day = day - 1;
        tempdate = RecodeDay(endtime, day);
        name = "Lot ID" + tempdate.FormatString("_yyyymmdd");
    }
    file = folder + name + ".csv";
    date = (AnsiString)Now().FormatString("yyyy/mm/dd,");
    TStringList *LotIDList = new TStringList;
    LotIDList->CommaText = lotid;
    if (LotIDList->Count == 0)
    {
        data += date + Recipe.StartTime.FormatString("yyyy-mm-dd hh:nn:ss,");
        tmp.sprintf(L"%s,%s,NONE,", mcID.c_str(), userID.c_str());
        data += (AnsiString)tmp + endtime.FormatString("yyyy-mm-dd hh:nn:ss");
        data += (AnsiString)ecode + "," + (AnsiString)detail + "\n";
    }
    else
    {
        for (int i = 0; i < LotIDList->Count; i++)
        {
            strValue = LotIDList->Strings[i];
            data += date + Recipe.StartTime.FormatString("yyyy-mm-dd hh:nn:ss,");
            tmp.sprintf(L"%s,%s,%s", mcID.c_str(), userID.c_str(), strValue.c_str());
            data += (AnsiString)tmp + endtime.FormatString("yyyy-mm-dd hh:nn:ss,");
            data += (AnsiString)ecode + "," + (AnsiString)detail + "\n";
        }
    }

    FILE *pFile;

    if (FileExists(file) == false)
    {
        try
        {
            int hFile = FileCreate(file);
            FileClose(hFile);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        AnsiString firstData;
        pFile = fopen(file.c_str(), "a+t");
        if (pFile == nullptr)
        {
            return;
        }
        firstData = "DATE,START TIME,M/C ID, OP ID, LOT ID, END TIME,ERROR CODE,DETAIL\n";
        std::fwrite(firstData.c_str(), firstData.Length(), 1, pFile);
        fclose(pFile);
    }
    pFile = fopen(file.c_str(), "a+t");
    if (pFile == nullptr)
    {
        return;
    }
    std::fwrite(data.c_str(), data.Length(), 1, pFile);
    fclose(pFile);
    return;
}

bool OvenChamber::DeleteStateFile()
{
    String strFile;
    strFile.sprintf(L"%s%s%c\\Current_T.ini", GetRootFolder().c_str(), L"PATTERN_CM_", 'A' + FChamberID);
    if (FileExists(strFile))
    {
        return DeleteFile(strFile);
    }
    return true;
}

bool OvenChamber::IsStateFileExist()
{
    String strFile;
    strFile.sprintf(L"%s%s%c\\Current_T.ini", GetRootFolder().c_str(), L"PATTERN_CM_", 'A' + FChamberID);
    return FileExists(strFile);
}