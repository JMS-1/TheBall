#include <IRremote.h>
#include <Adafruit_NeoPixel.h>

// Konfiguration des LED Rings.
#define LED_CONTROL     4
#define LED_COUNT       7

// Konfiguration der Fernbedienung.
#define REMOTE_PIN      2

IRrecv irrecv(REMOTE_PIN);

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_COUNT, LED_CONTROL, NEO_GRBW + NEO_KHZ800);

// Aktuelle Visualisierung.
uint32_t COLOR_WHITE = Adafruit_NeoPixel::Color(255, 255, 255, 255);
uint32_t COLOR_RED = Adafruit_NeoPixel::Color(255, 0, 0, 0);
uint32_t COLOR_BLACK = Adafruit_NeoPixel::Color(0, 0, 0, 0);

int mode = 3;

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
        // Weiter machen.
        irrecv.resume();

        // Fernbedienung auswerten.
        switch (results.value)
        {
        case 0xFF4AB5:
            mode = 0;
            break;
        case 0xFF6897:
            mode = 1;
            break;
        case 0xFF9867:
            mode = 2;
            break;
        case 0xFFB04F:
            mode = 3;
            break;
        case 0xFF30CF:
            mode = 4;
            break;
        }
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

    delay(100);
}

void white() {
    for (auto led = LED_COUNT; led-- > 0;) {
        leds.setPixelColor(led, COLOR_WHITE);
    }

    leds.show();

    delay(100);
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
        leds.setPixelColor(led, Adafruit_NeoPixel::Color(30 + random(50), 30 + random(50), 30 + random(50), 0));
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
