#ifndef DefinesH
#define DefinesH

#include <memory>
#include "VaComm.hpp"

#define readwrite_property(DATATYPE, READ, WRITE) __declspec(property(get = READ, put = WRITE)) DATATYPE
#define readonly_property(DATATYPE, READ) __declspec(property(get = READ)) DATATYPE

#define INC(x) (((x) == 0XFFFFFFFF) ? 0 : (x)++)

#define THREAD_WAIT_TIME 1
#define MAX_DIO_COUNT 64
#define MAX_AO_COUNT 4
#define MAX_AI_COUNT 8

#define MAX_ALARM_COUNT 256
#define MAX_CAHMBER_COUNT 4
#define MAX_LOGGER_COUNT 2
#define MAX_POINT_COUNT 8
#define MAX_LOGGERPOINT_COUNT MAX_LOGGER_COUNT *MAX_POINT_COUNT
#define MAX_COLOR_COUNT 18
#define MAX_EVENT_COUNT 10

#define TCARD_COUNT 10

#define LANGUAGEINI "Language.ini"
#define OVENDB "VSOven.mdb"
