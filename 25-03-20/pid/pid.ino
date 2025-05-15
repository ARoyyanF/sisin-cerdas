#include <PID_v1.h>

const int potPin = A0;
// Define Variables
double Setpoint, Input, Output;

// Define PID Tuning Parameters
double Kp = 2;
double Ki = 5;
double Kd = 1;

// Create PID instance
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Simulation variables
unsigned long lastTime;
double simulatedTemp = 25.0; // Starting temperature

void setup()
{
    Serial.begin(9600);

    // Initialize variables
    

    // Turn the PID on
    myPID.SetMode(AUTOMATIC);

    // Set output limits (0-255 for PWM)
    myPID.SetOutputLimits(0, 255);

    lastTime = millis();
}

void loop()s
{
    // Simulate temperature reading (in real application, read from sensor)
    Setpoint = analogRead(potPin);
    simulateProcess();
    Input = simulatedTemp;

    // Compute PID output
    myPID.Compute();

    // Print results every 100ms for serial plotter
    if (millis() - lastTime >= 100)
    {
        // Format: Setpoint,Input,Output
        Serial.print(Setpoint);
        Serial.print(",");
        Serial.print(Input);
        Serial.print(",");
        Serial.println(Output);

        lastTime = millis();
    }
}

void simulateProcess()
{
    // Simulate temperature changes based on heating power (Output)
    // and natural cooling
    double heatingEffect = Output * 0.01;         // Convert PWM to temperature change
    double cooling = (simulatedTemp - 25) * 0.02; // Natural cooling effect

    simulatedTemp += heatingEffect - cooling;
}