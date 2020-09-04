#include <FastLED.h>
#include <WiFiManager.h>

#include "Config.h"
#include "Colors.h"

#include "OverlayClockPlasma.h"
#include "OverlayClockFire.h"
#include "OverlayClockNeo.h"

#include "TimeService.h"

#define PIN D6
#define NUM_LEDS 256

const char *host = "ChaosUhrRelaoded"; // WLAN Name

const char *const PROGMEM ntpServer[] ={ "fritz.box", "de.pool.ntp.org", "at.pool.ntp.org", "ch.pool.ntp.org", "ptbtime1.ptb.de", "europe.pool.ntp.org" };

CRGB leds[NUM_LEDS];

TimeService timeService;
OverlayClockPlasma overlayClockPlasma;
OverlayClockFire overlayClockFire;
OverlayClockNeo overlayClockNeo;

//std::vector<OverlayClock*> vec;

void setup()
{
    //vec.push_back(new OverlayClockFire);

    FastLED.addLeds<WS2812B, PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(115200);

    WiFiManager wifiManager;
    wifiManager.setBreakAfterConfig(true);

    if (!wifiManager.autoConnect("ChaosUhrReloaded"))
    {
        Serial.println("failed to connect, we should reset as see if it connects");
        delay(5000);
        ESP.restart();
    }
    Serial.println(WiFi.localIP());

    if (WiFi.status() == WL_CONNECTED)
    {
    }

    timeService.initAfterConnectionEstablished(TIMESERVICE_TIMEZONE, TIMESERVICE_NTP_SERVER_1, TIMESERVICE_NTP_SERVER_2, TIMESERVICE_NTP_SERVER_3, 60);

    overlayClockFire.init(leds);
    overlayClockNeo.init(leds);
    overlayClockPlasma.init(leds);
    //vec[0]->init(leds);
}

void loop()
{
    timeService.process();
    FastLED.clearData();
    overlayClockFire.renderFrame(timeService.localtime);
    FastLED.show();
}