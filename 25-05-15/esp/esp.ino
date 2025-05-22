#include <WiFi.h>

// Ganti dengan SSID dan password yang Anda inginkan
const char* ssid = "ESP32-AP";
const char* password = "12345678";

WiFiServer server(80);
String header;

// Contoh pin untuk aksi (bisa diganti sesuai kebutuhan)
#define enA 25 // Example GPIO for ESP32
#define enB 26 // Example GPIO for ESP32
#define IN1 27 // Example GPIO for ESP32
#define IN2 14 // Example GPIO for ESP32
#define IN3 12 // Example GPIO for ESP32
#define IN4 13 // Example GPIO for ESP32

void setup() {
  Serial.begin(115200);

  // Set ESP32 analog read resolution to 10-bit (0-1023) to match Arduino Uno behavior
  // if your thresholds are based on that range.
  // Alternatively, adjust thresholds for ESP32's default 12-bit resolution (0-4095).
  analogReadResolution(10); 

  // pinMode(LED_BUILTIN, OUTPUT); // Note: LED_BUILTIN is set up but not used in the loop.
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  digitalWrite(enA, HIGH);
  digitalWrite(enB, HIGH);

  // Buat Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Kirim header HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // Tangani permintaan
            if (header.indexOf("GET /maju") >= 0) {
              Serial.println("UP");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, HIGH);
            } else if (header.indexOf("GET /mundur") >= 0) {
              Serial.println("DOWN");
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, LOW);
            } else if (header.indexOf("GET /kiri") >= 0) {
              Serial.println("LEFT");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, LOW);
            } else if (header.indexOf("GET /kanan") >= 0) {
              Serial.println("RIGHT");
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, HIGH);
            }
            else if (header.indexOf("GET /STOP") >= 0) {
              Serial.println("RIGHT");
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, LOW);
              digitalWrite(IN3, LOW);
              digitalWrite(IN4, LOW);
            }

            // Kirim halaman HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>ESP32 Kontrol Arah</title>");
            client.println("<style>button{padding:30px;margin:10px;font-size:20px}</style></head>");
            client.println("<body><h1>Kontrol Gerakan</h1>");
            client.println("<a href=\"/maju\"><button>Maju</button></a><br>");
            client.println("<a href=\"/kiri\"><button>Kiri</button></a>");
            client.println("<a href=\"/kanan\"><button>Kanan</button></a><br>");
            client.println("<a href=\"/mundur\"><button>Mundur</button></a>");
            client.println("<a href=\"/STOP\"><button>STOP</button></a><br>");

            client.println("</body></html>");

            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
  }
}
