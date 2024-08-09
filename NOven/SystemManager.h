#ifndef SystemManagerH
#define SystemManagerH

#include <vector>
#include "Defines.h"
#include "Singleton.h"
#include "SystemOptionDefine.h"
#include "EQDefines.h"
#include "ErrorDefines.h"

typedef struct _DIO_SETTING
{
    bool Use;
    String Description[LANG_COUNT];
} DIO_SETTING;

typedef struct _ALARM_ITEM
{
    bool IsShown;
    MODULE_TYPE ModuleType;
    unsigned int AlarmCode;

    _ALARM_ITEM()
    {
        Init();
    }

    void __fastcall Init()
    {
        IsShown = false;
    }

    _ALARM_ITEM &__fastcall operator=(const _ALARM_ITEM &arg)
    {
        IsShown = arg.IsShown;
        ModuleType = arg.ModuleType;
        AlarmCode = arg.AlarmCode;
        return *this;
    }

    bool __fastcall operator==(const _ALARM_ITEM &arg)
    {
        return (ModuleType == arg.ModuleType && AlarmCode == arg.AlarmCode);
    }
} ALARM_ITEM;

typedef enum _OPERATION_MODE
{
    OM_READY = 0,
    OM_PAUSED,
    OM_MANUAL_MODE,
    OM_INIT_MODE,
    OM_AUTO_MODE,
    OM_COUNT,
} OPERATION_MODE;

struct LOG_INFO;
class SerialDevice;
class TowerLampControl;
class Motor;
class IOControlManager;
class HandlerBaseThread;
class WatchIOThread;
class OvenChamber;
class DoorRunThread;
class SystemManager : public Singleton<SystemManager>
{
protected:
    OPERATION_MODE FOperationMode;
    bool FInitStarted;
    bool FInitStopped;
    bool FIsBlink;
    bool FIsTestMode;
    int FLoginLevel;
    String FUserID;
    SYSTEM_OPTIONS FOptions;

    TowerLampControl *FTowerLampOption;
    IOCOntrolManager *FIOManager;

    std::vector<ALAMR_ITEM> AlarmStatus;
    std::vector<HandlerBaseThread *> HandlerThreads;
    std::vector<OvenChamber *> Chambers;

protected:
    void __fastcall AddLog(LOG_INFO log);

public:
    __property SYSTEM_OPTIONS Options = {read = FOptions, write = FOptions};
    __property TowerLampControl *TowerLampOption = {read = FTowerLampOption, write = FTowerLampOption};
    __property IOControlManager *IOManager = {read = FIOManager, write = FIOManager};

    __property OPERATION_MODE OperationMode = {read = FOperationMode, write = FOperationMode};
    __property bool InitStarted = {read = FInitStarted, write = FInitStarted};
    __property bool InitStopped = {read = FInitStopped, write = FInitStopped};
    __property int LoginLevel = {read = FLoginLevel, write = FLoginLevel};
    __property String UserID = {read = FUserID, write = FUserID};
    __property bool IsBlink = {read = FIsBlink, write = FIsBlink};
    __property bool IsTestMode = {read = FIsTestMode, write = FIsTestMode};

public:
    std::vector<SerialDevice *> SerialDeviceList;
    std::shared_ptr<TMemIniFile> DIOSetting;
    std::vector<Motor *> ServoMotor;
    std::vector<int> ComiDeviceAddr;

public:
    SystemManager();
    ~SystemManager();

    static SystemManager *GetSystemManager()
    {
        return Singleton<SystemManager>::GetInstance();
    }
    static void ReleaseSystemManager()
    {
        return Singleton<SystemManageer>::ReleaseInstance();
    }

    OvenChamber *__fastcall GetChamber(int chamberNo = CHAMBER_A);
    DoorRunThread *__fastcall GetDoor(int chamberNo = CHAMBER_A);
    HandlerBaseThread *GetHandler(int moduleType);
    WatchIOThread *__fastcall GetWatchIoThread();

    void __fastcall InitManager();
    void __fastcall InitDirectory(String programName);

    bool __fastcall IsAlarmExist();
    bool __fastcall IsNoShowAlarmExist();
    bool __fastcall IsRegisteredAlarm(ALARM_ITEM alarm);
    int __fastcall GetAlarmCount();
    ALARM_ITEM __fastcall GetAlarm(int idx);
    void __fastcall SetAllAlarmShown();

    virtual void __fastcall ClearAlarm(int alarmCode);
    virtual void __fastcall ClearAlarm(int moduleType, int alarmCode);
    virtual void __fastcall ClearAlarmAll();
    virtual bool __fastcall ClearAlarmAll(int moduleType);

    void __fastcall RegisterAlarm(String moduleName, MODULE_TYPE moduleType, unsigned int alarmCode,
                                  bool setPaused = false);
    void __fastcall LoadTowerLampValue();
    void __fastcall SaveTowerLampValue();

    bool __fastcall LoadSystemParameters();
    bool __fastcall SaveSystemParameters();

    bool __fastcall LoadIOSettings();
    bool __fastcall SaveIOSettings();

    bool __fastcall LoadMotionSettings();
    bool __fastcall SaveMotionSettings();

    void __fastcall CreateLogWriter();
    void __fastcall DestroyLogWriter();

    void __fastcall CreateIOManager();
    void __fastcall DestroyIOManager();

    void __fastcall CreateMotors();
    void __fastcall DestroyMotors();

    void __fastcall CreateHandler();
    void __fastcall DestroyHandler();

    void __fastcall CreateChamber();
    void __fastcall DestroyChamber();

    void __fastcall Initialize();
    void __fastcall StopInitialize();
    bool __fastcall Initialized();
    bool __fastcall IsRunnable() { return true; }
    bool __fastcall IsAutoRun() { return (OperationMode == OM_AUTO_MODE); }
    bool __fastcall IsManualRun() { return (OperationMode == OM_MANUAL_MODE); }
    bool __fastcall IsPaused() { return (OperationMode == OM_PAUSED); }
}

#endif