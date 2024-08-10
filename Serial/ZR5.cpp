#include <System.AnsiStrings.hpp>
#pragma hdrstop

#include "ZR5.h"
#include "HelperFunction.h"
#include "SerialPortManager.h"
#pragma package(smart_init)

__fastcall ZR::ZR5(PORTINFO portInfo) : SerialDevice(portInfo)
{
    FIsValid = false;
    FIsCommandInit = false;
    DecodeMode = DECODE_DENSITY;
    OpenSerialPort();
}



__fastcall ZR5::~ZR5() {}
