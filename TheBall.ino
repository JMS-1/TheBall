#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

// Konfiguration des LED Rings.
#define LED_CONTROL     11
#define LED_COUNT       7

// Konfiguration der Fernbedienung.
#define REMOTE_PIN      12

IRrecv irrecv(REMOTE_PIN);

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_CONTROL, NEO_GRBW + NEO_KHZ800);

// Aktuelle Visualisierung.
uint32_t COLOR_WHITE = Adafruit_NeoPixel::Color(255, 255, 255, 255);
uint32_t COLOR_RED = Adafruit_NeoPixel::Color(255, 0, 0, 0);
uint32_t COLOR_BLACK = Adafruit_NeoPixel::Color(0, 0, 0, 0);

int mode = 0;

void setup() {
    randomSeed(analogRead(0));

    // LED Ring initialisieren.
    leds.begin();

    // Fernbedienung initialisieren.
    irrecv.enableIRIn();
}

void loop() {
    // Fernbedienung auslesen.
    decode_results results;

    // Keine Änderung.
    if (irrecv.decode(&results))
    {
        // Fernbedienung auswerten.
        switch (results.value)
        {
        default:
            mode = (mode == 2) ? 3 : 2;
            break;
        }

        // Weiter machen.
        irrecv.resume();
    }

    // Anzeige.
    switch (mode) {
    case 0:
        black();
        break;
    case 1:
        white();
        break;
    case 2:
        rotate();
        break;
    case 3:
        search();
        break;
    case 4:
        glitter();
        break;
    }
}

void black() {
    leds.clear();
    leds.show();
}

void white() {
    for (auto led = LED_COUNT; led-- > 0;) {
        leds.setPixelColor(led, COLOR_WHITE);
    }

    leds.show();
}

void rotate() {
    leds.setPixelColor(0, COLOR_RED);

    for (auto count = LED_COUNT; count-- > 1; )
    {
        for (auto led = LED_COUNT; led-- > 1; ) {
            leds.setPixelColor(led, (count == led) ? COLOR_RED : COLOR_BLACK);
        }

        leds.show();

        delay(50);
    }
}

int sequence[] = { 1, 4, 2, 5, 3, 6 };

void glitter() {
    for (auto led = 0; led < LED_COUNT; led++) {
        leds.setPixelColor(led, Adafruit_NeoPixel::Color(50 + random(100), 50 + random(100), 50 + random(100), 0));
        leds.show();
    }

    delay(100);
}

void search() {
    for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
        leds.clear();
        leds.setPixelColor(0, COLOR_RED);
        leds.show();
        delay(120);

        leds.clear();
        leds.setPixelColor(sequence[i], COLOR_RED);
        leds.show();
        delay(120);
    }
}
