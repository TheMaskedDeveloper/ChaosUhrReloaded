#ifndef TimeService_h
#define TimeService_h

class TimeService
{
public:
    TimeService();
    void initAfterConnectionEstablished(const char* timeZone, const char* timeServer1, const char* timeServer2, const char* timeServer3, long resync_every_seconds);
    void syncTimeWithTimeServer();
    void process();
    struct tm localtime;
private:
    const char* _timeZone;
    const char* _timeServer1;
    const char* _timeServer2;
    const char* _timeServer3;
    long _resync_every_seconds;
    long _nextSync;
};

#endif