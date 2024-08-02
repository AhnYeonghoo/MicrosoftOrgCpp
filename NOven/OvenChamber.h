#ifndef OvenChamberH
#define OvenChamberH

#include <vector>
#include <map>

#include "BaseThread.h"
#include "EQDefines.h"
#include "ChamberOptionDefines.h"
#include "HandlerBase.h"

class DevMainTempController;
class DevLimitController;
class I7018;
class DiffPressure;
class SerialDevice;
class ZR5;
class DoorRunThread;
class OvenChamber : public HandlerBaseThread
{
protected:
    DevMainTempController *FMainTempController;
    DevLimitController *FDevLimitController;
    DiffPressure *FDiffPressure;
    I7018 *FLoggerController;
    ZR5 *FO2Analyzer;

    CHAMBER_OPTIONS FOptions;
    DoorRunThread *FDoorRun;

protected:
    virtual void __fastcall StartInitialize() override {}
    virtual bool __fastcall IsStepIdle() override { return false; }
    virtual bool __fastcall InitializeCylinder() override { return true; }
    virtual bool __fastcall InitializeMotor(Motor *motor) override { return true; }

    virtual bool __fastcall IsPaused() override;
    virtual bool __fastcall IsAutoRun() override;
    virtual void __fastcall DoWorkSequence() override;
    void __fastcall RaiseAlarm(int errorcode, bool setPaused = false) override;

    void __fastcall InitCureValues();
    void __fastcall MakeCurePattern();

    DevMainTempController *CreateMainTempController(PORT_SETTING portSetting);
    DevLimitController *CreateTempLimitController(PORT_SETTING portSetting);

    bool __fastcall DoCureStop(int stopType);

    void __fastcall DoCheckLoggerPVHigh(int segNo);
    void __fastcall DoCheckLoggerPVLow(int segNo);
    void __fastcall RemoveLoggerPVHighAlarm(int loggerIdx);
    void __fastcall RemoveLoggerPVLowAlarm(int loggerIdx);
    void __fastcall RemoveLoggerPVHighAlarmAll();
    void __fastcall RemoveLoggerPVLowAlarmAll();
    void __fastcall RemoveLoggerPVAlarm();

    double __fastcall GetLoggerData(int idx);
    double __fastcall GetLoggerOffset(int idx);
    void __fastcall SetLoggerOffset(int idx, double offset);

    double __fastcall GetPV();
    double __fastcall GetSP();
    double __fastcall GetHeaterOut();
    int __fastcall GetSetNo();
    int __fastcall GetTotalSeg();
    int __fastcall GetOpMode();
    String __fastcall GetOpModeStr();

    bool __fastcall IsMainTempCtrlCoolingEventOn();
    bool __fastcall IsMainTempCtrlRun();
    bool __fastcall IsMainTempCtrlReset();
    bool __fastcall IsMainTempCtrlLocal();
    bool __fastcall IsMainTempCtrlHold();
    bool __fastcall IsMainTempCtrlKeylocked();
    bool __fastcall IsMainTempCtrlAutoMode();

    double __fastcall GetTempLimitPV();
    double __fastcall GetTempLimitSP();

    double __fastcall GetDiffPressure();
    double __fastcall GetO2Density();

    bool __fastcall GetIsMainTempControllerCommFail();
    bool __fastcall GetIsTempLimitControllerCommFail();
    bool __fastcall GetIsTempLoggerCommFail();
    bool __fastcall GetIsDPCommFail();
    bool __fastcall GetIsO2CommFail();
    bool __fastcall GetIsO2Valid();

public:
    __property CHAMBER_OPTIONS Options = {read = FOptions, write = FOptions};

    __property DevMainTempController *MainTempController = {read = FMainTempController, write = FMainTempController};
    __property DevLimitController *TempLimitController = {read = FTempLimitController, write = FTempLimitController};
    __property I7018 *LoggerController = {read = FLoggerController, write = FLoggerController};
    __property DiffPressure *DPController = {read = FDPController, write = FDPController};
    __property ZR5 *O2Analyzer = {read = FO2Analyzer, wirte = FO2Analyzer};
    __property DoorRunThread *DoorRun = {read = FDoorRun, write = FDoorRun};

    __property double LoggerData[int idx] = {read = GetLoggerData};
    __property double LoggerOffset[int idx] = {read = GetLoggerOffset, write = SetLoggerOffset};

    __property double PV = {read = GetPV};
    __property double SP = {read = GetSP};
    __property double HeaterOut = {read = GetHeaterOut};
    __property int SegNo = {read = GetSegNo};
    __property int TotalSeg = {read = GetSegNo};
    __property int OpMode = {read = GetOpMode};
    __property String OpModeStr = {read = GetOpModeStr};
    __property bool IsCoolingEventOn = {read = IsMainTempCtrlCoolingEventOn};
    __property bool IsRun = {read = IsMainTempCtrlRun};
    __property bool IsReset = {read = IsMainTempCtrlReset};
    __property bool IsLocal = {read = IsMainTempCtrlLocal};
    __property bool IsHold = {read = IsMainTempCtrlHold};
    __property bool IsKeyLocked = {read = IsMainTempCtrlKeylocked};
    __property bool IsAutoTuningOn = {read = IsATOn};
    __property bool IsAutoMode = {read = IsMainTempCtrlAutoMode};

    __property double TempLimitPV = {read = GetTempLimitPV};
    __property double TempLimitSP = {read = GetTempLimitSP};

    __property double DPValue = {read = GetDiffPressure};
    __property double O2Value = {read = GetO2Density};

    __property bool IsMainTempControllerCommFail = {read = GetIsMainTempControllerCommFail};
    __property bool IsTempLimitControllerCommFail = {read = GetIsTempLimitControllerCommFail};
    __property bool IsTempLoggerCommFail = {read = GetIsTempLoggerCommFail};
    __property bool IsDPCommFail = {read = GetIsDPCommFail};
    __property bool IsO2CommFail = {read = GetIsO2CommFail};
    __property bool IsO2Valid = {read = GetIsO2Valid};

public:
    enum CHAMBER_STEP
    {
        STEP_IDLE = 0,
        STEP_START_DOOR_INIT,
        STEP_WAIT_DOOR_INIT,
        STEP_DOWNLOAD_RECIPE,
        STEP_O2_PURGE,
        STEP_CURE_START,
        STEP_RAMPUP,
        STEP_RUNNING,
        STEP_GOTO_COOLING,
        STEP_COOLING,
        STEP_CURE_STOP,
        STEP_DONE,
        STEP_COUNT,
    };

    enum CURE_MODE
    {
        CURE_STOPPED = 0,
        CURE_START,
        CURE_COUNT
    };

    RECIPE Recipe;

    std::vector<SerialDevice *> SerialDeviceList;

public:
    __fastcall OvenChamber(int chamberNo);
    __fastcall ~OvenChamber();

    bool __fastcall CreateSerialDevices();
    void __fastcall DestroySerialDevices();

    void __fastcall CheckCommAlarm();
    void __fastcall CheckPVAlarm();
    void __fastcall CheckTempLoggerDeviation();
    void __fastcall CheckHeaterOutLimit();

    bool __fastcall LoadChamberParameters();
    bool __fastcall SaveChamberParameters();
    bool __fastcall SaveCurrentState();
    bool __fastcall LoadCurrentState();
    bool __fastcall DeleteStateFile();

    void __fastcall Start() { SetStep(STEP_START_DOOR_INIT); }
    void __fastcall Stop() { SetStep(STEP_CURE_STOP); }
    void __fastcall Cooling() { SetStep(STEP_GOTO_COOLING); }

    bool __fastcall IsIdleStep();
    bool __fastcall IsDoneStep();
    bool __fastcall IsStopPossibleStep();
    bool __fastcall IsCoolingPossibleStep();
    bool __fastcall IsForcedCureStopped();
    bool __fastcall IsCuring();
};