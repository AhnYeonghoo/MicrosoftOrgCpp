#ifndef DefinesH
#define DefinesH

#define INC(x) (((x) == oxFFFFFFFF) ? 0 : (x)++)
#define TO_STRING(name) #name

#define THREAD_WAIT_TIME 10

#define LANGUAGE_INI "Language.ini"
#define IO_INI "IO.ini"
#define SYSTEM_DB "VS.mdb"
#define ERRDEF_DB "ErrDef.mdb"

#define SEC_SYSTEM "SYSTEM"

#define KOR_TAG "_K"
#define ENG_TAG "_E"
#define JPN_TAG "_J"
#define CHN_TAG "_C"

#define MAX_COLOR_COUNT 18

#define GetManager() SystemManager::GetSystemManager()
#define ReleaseManager() SystemManager::ReleaseSystemManager()

enum LANGUAGE
{
    KOR = 0,
    ENG,
    CHN,
    LANG_COUNT
};

enum AUTOMATION_KIND
{
    AK_NONE = 0,
    AK_GEM,
    AK_COUNT,
};

enum USERLEVEL
{
    LV_NONE = 0,
    LV_OPERATOR,
    LV_ENGINEER,
    LV_SUPERVISOR,
    LV_DEVELOPER,
    LV_COUNT
};

enum BUZZERTYPE
{
    BUZZER_SOUND = 0,
    BUZZER_SIREN,
    BUZZERTYPE_CNT
};

typedef struct _PORT_SETTING
{
    unsigned char BaudRate;
    unsigned char DataBits;
    unsigned char StopBits;
    unsigned char Parity;
    int PortNo;
    int Addr;
    int Timeout;

    bool operator==(const _PORT_SETTING &arg) const
    {
        return (BaudRate == arg.BaudRate &&
                DataBits == arg.DataBits &&
                StopBits == arg.StopBits &&
                Parity == arg.Parity &&
                PortNo == arg.PortNo &&
                Addr == arg.Addr &&
                Timeout == arg.Timeout);
    }
} PORT_SETTING;

extern String LangTag;
extern String LangStr[LANG_COUNT];
extern String LevelStr[LV_COUNT];

enum EMOOPTION
{
    KEEP_WORKING = 0,
    STOP_WORKING,
    EMOOPTION_CNT,
};

enum STOPTYPE
{
    NORMAR_STOP = 0,
    FORCED_STOP,
    EMERGENCY_SW_STOP,
    REAR_DOOR_OPEN_STOP,
    STOPTYPE_CNT
};

enum TEMP_CTRL_EVENT
{
    ET_NONE = 0,
    ET_TIMEEVENT1,
    ET_TIMEEVENT2,
    ET_TIMEEVENT3,
    ET_TIMEEVENT4,
    ET_TIMEEVENT5,
    ET_TIMEEVENT6,
    ET_TIMEEVENT7,
    ET_PVHIGHT,
    ET_PVLOW,
    ET_COUNT
};

#define WAIT_ZONE_COUNT 5

typedef struct _STC
{
    int SegCount;
    double Ssp;
    int Stc;
    double Wz[WAIT_ZONE_COUNT];
    int WTm[WAIT_ZONE_COUNT];
    int Rcy, Rst, Ren;

    void __fastcall Empty() { ZeroMemorty(this, sizeof(_STC)); }
    _STC() { Empty(); }
} STC;

typedef struct _DAMPER
{
    int InPercent;
    int OutPercent;
    int DamperCloseO2Density;
} DAMPERINFO;

#define EVENT_COUNT 8

typedef struct _SEG
{
    double Tsp;
    int Time;
    int TmRt;
    int Pid;
    int EvKind[EVENT_COUNT];
    int OnType[EVENT_COUNT];
    int OffPe[EVENT_COUNT];
    int Jc;
    bool KeepTemp;

    DAMPERINFO Damper;

    void __fastcall Empty()
    {
        ZeroMemory(this, sizeof(_SEG));
        Time = -1;
    }

    _SEG() { Empty(); }
} SEG;

typedef struct _PTN
{
    bool IsLoaded;
    bool UseLocalMode;
    int PtnNo;
    double LocalTemp;

    STC Stc;
    SEG Seg[99];

    void __fastcall Empty()
    {
        IsLoaded = false;
        PtnNo = 0;
        UseLocalMode = false;
        LocalTemp = 0;
        Stc.Empty();
        for (int i = 0; i < 99; i++)
        {
            Seg[i].Empty();
        }
    }
    _PTN() { Empty(); }

    int __fastcall GetTotalTime()
    {
        int total = 0;
        for (int i = 0; i < Stc.SegCount; i++)
        {
            total += Seg[i].Time;
        }
        return total;
    }

    double __fastcall GetMaxTemp()
    {
        double max = 0.0;
        for (int i = 0; i < Stc.SegCount; i++)
        {
            if (Seg[i].Tsp > max)
            {
                max = Seg[i].Tsp;
            }
        }
        return max;
    }
} PTN;

const int LOT_COUNT = 20;
typedef struct _LOTINFO
{
    bool UseQuantity;
    int TotalLotCount;
    int LotQuantity[LOT_COUNT];
    String LotID[LOT_COUNT];
    String UserID;

    _LOTINFO()
    {
        TotalLotCount = 0;
        UseQuantity = false;
    }
    String __fastcall ToString()
    {
        String ret = "";
        for (int i = 0; i < TotalLotCount; i++)
        {
            ret += LotID[i];
            if (i < TotalLotCount - 1)
            {
                ret += ","
            }
        }
        return ret;
    }

    void __fastcall Init()
    {
        UseQuantity = false;
        TotalLotCOunt = 0;
        UserID = "";

        for (int i = 0; i < LOT_COUNT; i++)
        {
            LotQuantity[i] = 0;
            LotID[i] = "";
        }
    }

    _LOTINFO &__fastcall operator=(const _LOTINFO &arg)
    {
        TotalLotCount = arg.TotalLotCount;
        for (int i = 0; i < TotalLotCount; i++)
        {
            UseQuantity = arg.UseQuantity;
            LotQuantity[i] = arg.LotQuantity[i];
            LotID[i] = arg.LotID[i];
        }
        return *this;
    }
} LOTINFO;

typedef struct
{
    int ChamberNo;
    String RecipeName;
    TDateTime CureStartTime;
    TDateTime CureEndTime;
    TDateTime OutTime;

    AnsiString MainTempFilename;
    AnsiString LoggerFilename;
    AnsiString LimitFilename;
    AnsiString O2Filename;
    AnsiString DPFilename;

    int StopType;
    bool JobEnd;
    bool IsGemRecipe;

    PTN TempPtn;
} RECIPE;

const int MAX_LOGGER_COUNT = 1;
const int MAX_LOGGER_POINT_COUNT = 5;
const int PV_IDX = 0;
const int SP_IDX = 1;
const int OUT_IDX = 2;

#endif