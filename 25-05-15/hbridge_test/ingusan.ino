#include <WiFi.h>

// Ganti dengan SSID dan password yang Anda inginkan
const char* ssid = "ESP32-AP";
const char* password = "12345678";

WiFiServer server(80);
String header;

// Contoh pin untuk aksi (bisa diganti sesuai kebutuhan)
#define PIN_MAJU   14
#define PIN_MUNDUR 27
#define PIN_KIRI   26
#define PIN_KANAN  25

void setup() {
  Serial.begin(115200);

  // Set pin sebagai output
  pinMode(PIN_MAJU, OUTPUT);
  pinMode(PIN_MUNDUR, OUTPUT);
  pinMode(PIN_KIRI, OUTPUT);
  pinMode(PIN_KANAN, OUTPUT);

  // Matikan semua aksi awal
  digitalWrite(PIN_MAJU, LOW);
  digitalWrite(PIN_MUNDUR, LOW);
  digitalWrite(PIN_KIRI, LOW);
  digitalWrite(PIN_KANAN, LOW);

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
              digitalWrite(PIN_MAJU, HIGH);
              delay(500);
              digitalWrite(PIN_MAJU, LOW);
            } else if (header.indexOf("GET /mundur") >= 0) {
              digitalWrite(PIN_MUNDUR, HIGH);
              delay(500);
              digitalWrite(PIN_MUNDUR, LOW);
            } else if (header.indexOf("GET /kiri") >= 0) {
              digitalWrite(PIN_KIRI, HIGH);
              delay(500);
              digitalWrite(PIN_KIRI, LOW);
            } else if (header.indexOf("GET /kanan") >= 0) {
              digitalWrite(PIN_KANAN, HIGH);
              delay(500);
              digitalWrite(PIN_KANAN, LOW);
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
