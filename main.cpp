#include <Arduino.h>

// Pini pentru LED-uri simple (L1 = 25%, L2 = 50%, L3 = 75%, L4 = 100%)
const int L1 = 2;
const int L2 = 3;
const int L3 = 4;
const int L4 = 5;

// Pini pentru LED RGB (rosu si verde)
const int ledRed = 7;
const int ledGreen = 8;

// Pini pentru butoane
const int buttonStart = 10;
const int buttonStop = 11;

// Variabile pentru butoane si stari
bool isCharging = false; 
bool isStationFree = true; 
unsigned long lastButtonPress = 0; // Pentru debouncing
const unsigned long debounceDelay = 50; // Intarziere pentru debouncing

// Timpuri pentru controlul clipirii si incarcarii
const unsigned long blinkInterval = 500; 
const unsigned long chargeInterval = 3000; 
const unsigned long blinkSlowInterval = 800; // Interval pentru clipirea lenta de la final

// Declaratiile functiilor inainte de utilizare
void setStationStatus(bool free);
void stopCharging();
void blinkAllLEDsSlow();
void chargingSequence();
void startCharging();
void handleButtons();

// Functia setup
void setup() {
    // Configurare pini LED-uri simple
    pinMode(L1, OUTPUT);
    pinMode(L2, OUTPUT);
    pinMode(L3, OUTPUT);
    pinMode(L4, OUTPUT);

    // Configurare pini pentru LED RGB
    pinMode(ledRed, OUTPUT);
    pinMode(ledGreen, OUTPUT);

    // Configurare pini pentru butoane cu pull-up intern
    pinMode(buttonStart, INPUT_PULLUP);
    pinMode(buttonStop, INPUT_PULLUP);

    // Setare stare initiala (statia este libera, deci RGB verde)
    setStationStatus(true);
}

// Functia pentru setarea statusului statiei (verde = liber, rosu = ocupat)
void setStationStatus(bool free) {
    if (free) {
        digitalWrite(ledGreen, HIGH);
        digitalWrite(ledRed, LOW);
        isStationFree = true;  // Statia este liberă
    } else {
        digitalWrite(ledGreen, LOW);
        digitalWrite(ledRed, HIGH);
        isStationFree = false; // Statia este ocupata
    }
}

// Functia pentru clipirea tuturor LED-urilor de 3 ori
void blinkAllLEDsSlow() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(L1, LOW);
        digitalWrite(L2, LOW);
        digitalWrite(L3, LOW);
        digitalWrite(L4, LOW);
        delay(blinkSlowInterval); // Clipire lenta

        digitalWrite(L1, HIGH);
        digitalWrite(L2, HIGH);
        digitalWrite(L3, HIGH);
        digitalWrite(L4, HIGH);
        delay(blinkSlowInterval); // Clipire lenta

        
    }

    // Stingem toate LED-urile la final
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
}

// Functia pentru secventa de incarcare
void chargingSequence() {

    int leds[] = {L1, L2, L3, L4}; // LED-urile de incarcare

    for (int i = 0; i < 4; i++) {
        unsigned long startBlink = millis();
        while (millis() - startBlink < chargeInterval) {
            if (digitalRead(buttonStop) == LOW) {  // Verificam daca butonul de stop este apasat
                stopCharging(); // Oprire incarcare daca este apasat butonul de stop
                return;
            }
            digitalWrite(leds[i], !digitalRead(leds[i])); // Clipim LED-ul curent
            delay(blinkInterval);
        }
        // Lasam LED-ul aprins după clipire
       
        digitalWrite(leds[i], HIGH);
        delay(700);
       
    }

    // După aprinderea tuturor LED-urilor, ele clipesc de 3 ori lent
    blinkAllLEDsSlow();

    // Finalul procesului de incarcare 
    setStationStatus(true);
}

// Functia pentru pornirea procesului de incarcare
void startCharging() {
    if (!isCharging && isStationFree) {
        isCharging = true;
        setStationStatus(false); // Statia devine ocupata (RGB rosu)
        chargingSequence(); // Incepem secventa de incarcare
        isCharging = false; // Incheiem procesul de incarcare
    }
}

// Functia pentru oprirea procesului de incarcare cu intrerupere
void stopCharging() {
    if (isCharging) {
        isCharging = false; // Oprim incarcarea 
        blinkAllLEDsSlow(); // Clipim LED-urile de 3 ori
        setStationStatus(true); // Statia devine libera
    }
}

// Functia pentru gestionarea butoanelor
void handleButtons() {
    unsigned long currentTime = millis();

    // Debouncing pentru butonul Start
    if (digitalRead(buttonStart) == LOW && currentTime - lastButtonPress > debounceDelay) {
        startCharging(); // Apasare scurta incepe incarcarea doar dacă statia este libera
        lastButtonPress = currentTime;
    }

    // Debouncing pentru butonul Stop
    if (digitalRead(buttonStop) == LOW && currentTime - lastButtonPress > debounceDelay) {
        unsigned long pressStartTime = millis();
        
        // Masuram durata apasarii
        while (digitalRead(buttonStop) == LOW) {
            if (millis() - pressStartTime > 1000) { // Apasare lunga mai mare de 1 secunda
                stopCharging();
                break;
            }
        }
        lastButtonPress = currentTime;
    }
}

// Functia loop pentru actualizarea starii
void loop() {
    handleButtons(); // Gestionam butoanele
}