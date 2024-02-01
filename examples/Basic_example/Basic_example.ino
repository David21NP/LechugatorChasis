#include <Ramps.h>

Ramps ramps;

float rpms[] = {10, 30, 20, 30, 20};

//A4988 mot(200, X_DIR, X_STEP, X_EN);

void setup() {
    
    Serial.begin(9600);

    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    ramps.begin();

    pinMode(POWER_ON, OUTPUT);

    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);
    delay(500);
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);

    //mot.begin(100, 1);
    
    digitalWrite(LED, HIGH);

    // stps.moveY((float) -360.0);
    // stps.moveZ((float) -360.0);

    // digitalWrite(POWER_ON, HIGH);

    ramps.m_pwo.setOutputTo(0, 100);

    /* digitalWrite(X_EN, LOW);
    digitalWrite(X_DIR, LOW);
    for (short i = 0; i < 200; i++)
    {
        digitalWrite(X_STEP, HIGH);
        delayMicroseconds(2);
        digitalWrite(X_STEP, LOW);
        delayMicroseconds(1500);
    }
    delay(2000); */

    //digitalWrite(X_EN, HIGH);
}

void loop() {
    // float ti = millis();
    // Serial.println("Begin ----------------------");
    // Serial.print("T passed : "); Serial.println(millis() - ti);
    // Serial.println("End ----------------------\n");
}
