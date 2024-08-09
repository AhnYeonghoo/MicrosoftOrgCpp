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
