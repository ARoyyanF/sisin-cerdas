// Variables of the print task.
unsigned long last_print_time;
unsigned long last_blink_time;
unsigned long blink_interval;
bool tock = false;
int print_interval = 1000;
void setup() {
 Serial.begin(115200);
 pinMode(LED_BUILTIN, OUTPUT);
 // Initialize last_time variables.
 last_blink_time = millis();
 last_print_time = millis();
}
void loop() {
 // Check if it is time to run the blink task.
 if (millis() - last_blink_time >= blink_interval) {
 // Update the last blink time.
 last_blink_time += blink_interval;
 // Execute the blink task.
 digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
 }
 // Check if it is time to run the print task.
 if (millis() - last_print_time >= print_interval) {
 // Update the last print time.
 last_print_time += print_interval;
 // Execute the print task.
 if (tock){Serial.println("Tock");tock = 0;} else {Serial.println("Tick");tock = 1;}
 
 }
}