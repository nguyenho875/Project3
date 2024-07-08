#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

const char* ssid     = "Telecentro-5401";
const char* password = "Z2NKJZ3WYJFD";

char *server = "192.168.0.43";
int port = 1883;

int ledpin = 23;          // Nuevo pin para el LED
int mqttStatusPin = 21;   // Pin para indicar estado MQTT
int messagePin = 19;      // Pin para indicar que se recibión un mensaje y se reenvió por UART
int var = 0;

#define RXD2 16
#define TXD2 17

void wifiInit() {
    Serial.print("Conectándose a ");
    Serial.print(ssid);
    Serial.print("\n");

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);  
    }
    Serial.print("\n");
    Serial.print("Conectado a WiFi");
    Serial.print("\n");
    Serial.print("Dirección IP: ");
    Serial.print(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
    char payload_string[length + 1];
    memcpy(payload_string, payload, length);
    payload_string[length] = '\0';

    if (strcmp(topic, "ProyectoTranquera/TestMQTT") == 0) {
      int resultI = atoi(payload_string);
      var = resultI;
    }

    Serial.print("Mensaje recibido [");
    Serial.print(topic);
    Serial.print("]: ");
    Serial.print(payload_string);
    Serial.print("\n");

    // Reenviar el mensaje por UART
    Serial2.print(topic);
    Serial2.print(":");
    Serial2.print(payload_string);
    Serial2.print("\n");

    digitalWrite(messagePin, HIGH);
    digitalWrite(messagePin, LOW);   // Hago un pulso cuando envié un mensaje
}

void reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Intentando conectarse MQTT...");
        Serial.print("\n");
        digitalWrite(mqttStatusPin, LOW); // Indicar que está desconectado

        if (mqttClient.connect("ESP32")) {
            Serial.print("Conectado");
            Serial.print("\n");
            digitalWrite(mqttStatusPin, HIGH); // Indicar que está conectado
            mqttClient.subscribe("ProyectoTranquera/TestMQTT");
        } else {
            Serial.print("Fallo, rc=");
            Serial.print(mqttClient.state());
            Serial.print(" intentar de nuevo en 5 segundos");
            Serial.print("\n");
            delay(5000);
        }
    }
}

void setup() {
    pinMode(ledpin, OUTPUT);
    pinMode(mqttStatusPin, OUTPUT); // Configurar el pin de estado MQTT como salida
    pinMode(messagePin, OUTPUT);  // Configurar el pin de mensaje como salida
    Serial.begin(115200);
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // Configuración UART2 a 115200 baudios
    delay(10);
    wifiInit();
    mqttClient.setServer(server, port);
    mqttClient.setCallback(callback);
    digitalWrite(mqttStatusPin, LOW);   // El Pin empieza en LOW
    digitalWrite(messagePin, LOW);   // El Pin empieza en LOW
}

void loop() {
    if (!mqttClient.connected()) {
        reconnect();
    } else {
        digitalWrite(mqttStatusPin, HIGH); // Mantener en HIGH si está conectado
    }
    mqttClient.loop();

    if (var == 0) {
        digitalWrite(ledpin, LOW);
    } else if (var == 1) {
        digitalWrite(ledpin, HIGH);
    }

    if (Serial2.available()) {
        String uartMessage = Serial2.readStringUntil('\n'); // Leer mensaje UART
        int separatorIndex = uartMessage.indexOf(':');
        
        if (separatorIndex != -1) {
            String command = uartMessage.substring(0, separatorIndex);
            String argument = uartMessage.substring(separatorIndex + 1);

            if (command == "subscribe") {
                mqttClient.subscribe(argument.c_str());
                Serial.print("Suscrito a: ");
                Serial.print(argument);
                Serial.print("\n");
                Serial2.print("subscribed:");
                Serial2.print(argument);
                Serial2.print("\n");
                digitalWrite(messagePin, HIGH);
                digitalWrite(messagePin, LOW);   // Hago un pulso cuando envié un mensaje
            } else if (command == "unsubscribe") {
                mqttClient.unsubscribe(argument.c_str());
                Serial.print("Desuscrito de: ");
                Serial.print(argument);
                Serial.print("\n");
                Serial2.print("unsubscribed:");
                Serial2.print(argument);
                Serial2.print("\n");
                digitalWrite(messagePin, HIGH);
                digitalWrite(messagePin, LOW);   // Hago un pulso cuando envié un mensaje
            } else {
                // Publicar mensaje en MQTT
                mqttClient.publish(command.c_str(), argument.c_str());
                Serial.print("Mensaje enviado: ");
                Serial.print("\n");
                Serial.print("Tópico: ");
                Serial.print(command);
                Serial.print(", Mensaje: ");
                Serial.print(argument);
                Serial.print("\n");
            }
        }
    }
}
