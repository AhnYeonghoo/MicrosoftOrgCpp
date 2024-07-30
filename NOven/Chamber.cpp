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