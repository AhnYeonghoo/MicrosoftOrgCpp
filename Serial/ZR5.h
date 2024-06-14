
#ifndef ZR5H
#define ZR5H
#include "SerialDevice.h"

class ZR5 : public SerialDevice
{
private:
    enum
    {
        DECODE_DENSITY,
        DECODE_FLOWRATE
    };

    int DecodeMode;
    bool IsValidO2Value;
    bool IsValidFlowRateValue;
    bool FIsValid;
    bool FIsCommandInit;
    double FO2Density;
    double FFlowRate;
    bool FO2PumpStatus;

    void __fastcall DoMonitor();
    void __fastcall DecodeMonitor();
    bool __fastcall IsRxDone();
    void __fastcall GetMonitorCommands(TStringList *list);
    bool __fastcall CheckDoubleValid(AnsiString data);

    void __fastcall DoCommandInit(PARAM *param);

public:
    __fastcall ZR5(PORTINFO portInfo);
    __fastcall ~ZR5();

    __property bool IsValid = {read = FIsValid};
    __property bool IsCommandInit = {read = FIsCommandInit};
    __property
}