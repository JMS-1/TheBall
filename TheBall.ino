#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

// Zum Testen.
#define LED             13

// Konfiguration des LED Rings.
#define LED_CONTROL     11
#define LED_COUNT       7

// Konfiguration der Fernbedienung.
#define REMOTE_PIN      12

IRrecv irrecv(REMOTE_PIN);

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_CONTROL, NEO_RGBW + NEO_KHZ800);

// Aktuelle Visualisierung.
int mode = 1;

void setup() {
    // LED Ring initialisieren.
    leds.begin();

    // Fernbedienung initialisieren.
    irrecv.enableIRIn();

    // Anzeige initialisieren.
    pinMode(LED, OUTPUT);

    // Zum Testen.
    Serial.begin(9600);
    Serial.println("A");
}

void loop() {
    // Fernbedienung auslesen.
    decode_results results;

    // Keine Änderung.
    if (irrecv.decode(&results))
    {
        Serial.println("B");

        // Fernbedienung auswerten.
        switch (results.value)
        {
        default:
            mode = 1;
            break;
        }

        // Weiter machen.
        irrecv.resume();
    }

    // Anzeige.
    switch (mode) {
    case 1:
        showMode1();
        break;
    }
}

void showMode1() {
    for (auto led = 0; led < 7; led++) {
        for (auto what = 0; what < 4; what++) {
            leds.clear();
            leds.setPixelColor(led, Adafruit_NeoPixel::Color(
                (what == 0) ? 255 : 0,
                (what == 1) ? 255 : 0,
                (what == 2) ? 255 : 0,
                (what == 3) ? 255 : 0
            ));
            leds.show();

            delay(1000);
        }
    }

    leds.clear();
    leds.show();

    delay(10000);
}
