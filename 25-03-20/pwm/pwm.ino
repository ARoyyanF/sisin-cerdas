const int potPin = A0;  // Pin connected to the potentiometer
const int motorPin = 9; // Pin connected to the motor

// Variables for PWM timing
unsigned long previousPWMMillis = 0;
const unsigned long PWM_PERIOD = 100; // 10Hz = 100ms period
unsigned long onTime = 0;            // Time motor should be ON within period

// Variables for serial printing
unsigned long previousPrintMillis = 0;
const unsigned long PRINT_INTERVAL = 100;

// PWM state
bool motorState = false;

void setup()
{
    pinMode(motorPin, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    // Read potentiometer and calculate duty cycle
    int potValue = analogRead(potPin);
    int dutyCycle = map(potValue, 0, 1023, 0, 100); // Map to 0-100%
    onTime = (PWM_PERIOD * dutyCycle) / 100;        // Calculate ON time in ms

    // Manual PWM implementation
    unsigned long currentMillis = millis();
    unsigned long elapsedPWM = currentMillis - previousPWMMillis;

    // Reset PWM cycle after period completion
    if (elapsedPWM >= PWM_PERIOD)
    {
        previousPWMMillis = currentMillis;
        elapsedPWM = 0;
        motorState = false;
    }

    // Set motor state based on duty cycle
    if (elapsedPWM < onTime && !motorState)
    {
        digitalWrite(motorPin, HIGH);
        motorState = true;
    }
    else if (elapsedPWM >= onTime && motorState)
    {
        digitalWrite(motorPin, LOW);
        motorState = false;
    }

    // Non-blocking serial print
    if (currentMillis - previousPrintMillis >= PRINT_INTERVAL)
    {
        previousPrintMillis = currentMillis;
        Serial.print("Duty Cycle: ");
        Serial.print(dutyCycle);
        Serial.print("% ON Time: ");
        Serial.println(onTime);
    }
}