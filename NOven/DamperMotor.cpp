#pragma hdrstop

#include "DamperMoter.h"
#include "HelperFunctions.h"
#include "SerialPortManager.h"
#include "Chamber.h"

#pragma package(smart_init)

DamperMoter::DamperMoter(BaseChamber *chamber, PORTINFO portInfo, bool createPort)
    : SerialDevice(chamber, portInfo, createPort)
{
}
__fastcall DamperMoter::~DamperMotor()
{
}
