#ifndef DoorRunH
#define DoorRunH

#include "HandlderBase.h"

enum
{
    REQ_DOOR_NONE,
    REQ_DOOR_OPEN,
    REQ_DOOR_CLOSE,
} DOOR_REQ;

class OvenChamber;
class DoorRunThread : public HandlderBaseThread
{
protected:
    enum STEP
    {
        STEP_INIT = STEP_INITIALIZE,
        STEP_READY,

        STEP_OPEN_START,
        STEP_MOVE_TO_TARGET_DOOR_FOR_OPEN,
        STEP_GRIPPER_FWD_FOR_OPEN,
        STEP_GRIP,
        STEP_GRIPPER_BWD_FOR_OPEN,
        STEP_MOVE_TO_AVOID,

        STEP_CLOSE_START,
        STEP_MOVE_TO_TARGET_DOOR_FOR_CLOSE,
        STEP_GRIPPER_FWD_FOR_CLOSE,
        STEP_UNGRIP,
        STEP_GRIPPER_BWD_FOR_CLOSE,

        STEP_COUNT
    };

protected:
    int ChamberID;
    Motor *DoorZ;
    int CuurentOpenedDoor;
    int DoorRequest;
    int RequestedDoorIndex;
    int FDoorOpened[DOOR_COUNT];

protected:
    virtual bool __fastcall IsAutoRun() override { return false; }
    virtual bool __fastcall IsPaused() override { return false; }
    virtual bool __fastcall IsStepIdle() override { return false; }
    virtual bool __fastcall InitializeCylinder() override;
    virtual void __fastcall DoWorkSequence();

    void __fastcall CheckDoorState();

    int __fastcall GetDoorOpened(int idx);
    void __fastcall SetDoorOpened(int idx, int val);

protected:
    __property int IsDoorOpened[int idx] = {read = GetDoorOpened, write = SetDoorOpened};

public:
    __fastcall DoorRunThread(const int moduleType, const int chamberId);
    __fastcall ~DoorRunThread();

    bool __fastcall IsDoorReady() { return Step == STEP_READY; }
    bool __fastcall CheckDoorOpen(int doorIdx, const bool raiseAlarm = true, const int delayTime = 0);

    bool __fastcall IsDoorClampLeftOpened(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampRightOpened(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampLeftClosed(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampRightClosed(const bool raiseAlarm = true, const int delayTime = 0);

    bool __fastcall IsDoorClampOpened(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampRightOpened(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampLeftClosed(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampRightClosed(const bool raiseAlarm = true, const int delayTime = 0);

    bool __fastcall IsDoorClampOpened(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampClosed(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampBackward(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClampForward(const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorClosed(const int doorNo, const bool raiseAlarm = true, const int delayTime = 0);
    bool __fastcall IsDoorDetectedInClamp(const bool raiseAlarm = true, const int dealyTime = 0);
    bool __fastcall IsDoorNotDetectedInClamp(const bool raiseAlarm = true, const int delayTime = 0);

    bool __fastcall DoorClampOpen(bool workInThread = true);
    bool __fastcall DoorClampClose(bool workInThread = true);
    bool __fastcall DoorClampBackward(bool workInThread = true);
    bool __fastcall DoorClampForward(bool workInThread = true);

    void __fastcall RequestDoorOpen(int doorIdx);
    void __fastcall RequestDoorClose(int doorIdx);

    bool __fastcall IsRearDoorClosed();
    bool __fastcall RearDoorLock();
    bool __fastcall MoveToDoorPos(int doorNo, bool monitorDoorDetect, bool workInThread = true);
    bool __fastcall MoveToAvoidDoorPos(int doorNo, bool workInThread = true);

    bool __fastcall IsServoMCOn();
    void __fastcall ServoMCOn(const bool on = true);
};
#endif