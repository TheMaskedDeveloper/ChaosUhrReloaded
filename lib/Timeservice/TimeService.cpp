#include "Arduino.h"
#include "TimeService.h"
#include <time.h>

TimeService::TimeService()
{
    _nextSync = 0;
}

void TimeService::initAfterConnectionEstablished(const char* timeZone, const char* timeServer1, const char* timeServer2, const char* timeServer3, long resync_every_seconds)
{
    _timeZone = timeZone;
    _timeServer1 = timeServer1;
    _timeServer2 = timeServer2;
    _timeServer3 = timeServer3;
    _resync_every_seconds = resync_every_seconds;

    configTzTime(_timeZone, _timeServer1, _timeServer2, _timeServer3);
}

void TimeService::syncTimeWithTimeServer()
{
    configTzTime(_timeZone, _timeServer1, _timeServer2, _timeServer3);
    time_t now = time(&now);
    _nextSync = now + _resync_every_seconds;
}


void TimeService::process()
{
    time_t now = time(&now);
    if (now > _nextSync) {
        syncTimeWithTimeServer();
    }
    localtime_r(&now, &localtime);
}