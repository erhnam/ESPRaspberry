#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define light A0

/************************* Punto de acceso WiFi *********************************/

#define WLAN_SSID       "Nombre Wifi a la que se desea conectar"
#define WLAN_PASS       "Password de la Wifi"

/************************* Configurar Adafruit.io *********************************/

#define MQTT_SERVER      "Direccion IP del Servidor (Raspberry)"
#define MQTT_SERVERPORT  1883  // usar 8883 for SSL
#define MQTT_USERNAME    ""    // empty
#define MQTT_KEY         ""    // empty


// Crear una clase ESP8266 WiFiClient para conectar al servidor MQTT.
WiFiClient client;
// Puedes usar WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Configurar el cliente MQTT
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);

Adafruit_MQTT_Publish light_stream = Adafruit_MQTT_Publish(&mqtt, MQTT_USERNAME "/esp/light"); // change the topic

void MQTT_connect();

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(light,INPUT); 

  // Conectar a WiFi.
  Serial.println(); Serial.println();
  Serial.print("Conectando a ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("Conectado a WiFi");
  Serial.println("Dirección IP: "); Serial.println(WiFi.localIP());

}

uint32_t x=0;

void loop() {

  
  MQTT_connect();

  // Obtener valor analog del pin A0
  int light_value = analogRead(light);
  Serial.print("Lectura de Luz: ");
  // Imprime el valor en decimal
  Serial.println(light_value,DEC);
  // Publicar a Raspberry Pi con Topic: "/esp/light"
  light_stream.publish(light_value);
  delay(500);
  
// aquí puedes procesar el dato y actuar como desees

}

// Funcion para conectar y reconectar al servidor MQTT tantas veces como sea necesario.
void MQTT_connect() {
  int8_t ret;

  //Parar si ya se ha conectado
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Conectando a MQTT... ");

  uint8_t retries = 3;
  // Connect devuelve 0 cuando se ha conectado
  while ((ret = mqtt.connect()) != 0) { 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Reintentando conexión MQTT en 5 segundos...");
       mqtt.disconnect();
       // Esperar 5 segundos
       delay(5000);
       retries--;
       if (retries == 0) {
         // Basicamente muere y espera a un WDT para resetear
         while (1);
       }
  }
  Serial.println("! Conectado a MQTT !");
}
