SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

#include "oled-wing-adafruit.h"
//pin D2 is the counter incrementer
//pin D3 is the interrupt button

volatile int counter = 0;
volatile bool interruptsOn = false;

OledWingAdafruit display;

void setup()
{
    display.setup();
    
    Serial.begin(9600);
    refreshDisplay();
    display.display();
    pinMode(D2, INPUT_PULLUP);
    pinMode(D3, INPUT_PULLUP);
    attachInterrupt(D2, isr, FALLING);
}
void loop()
{
    display.loop();
    refreshDisplay();
    display.println(counter);
    Serial.println(counter);
    display.display();

    if(digitalRead(D3) == LOW)
    {
        interruptsOn = !interruptsOn;
        if(interruptsOn)
            noInterrupts(); // disable interrupts
        else
        {
            interrupts(); //enable interrupts
        }
        delay(500);
    }
    
    
}
void refreshDisplay()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
}
void isr()
{
    counter++;
}