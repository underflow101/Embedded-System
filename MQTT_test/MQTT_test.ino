

// MQTT Test

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define WFSSID      "luple_2.4g"
#define PASSWORD    "luple123"
//#define mqtt_server "mosquitto.org"
#define mqtt_port   1883
#define mqtt_topic  "1/#"
#define LED 12

IPAddress mqtt_server(192, 168, 0, 18);

const char* mqtt_message = "Hey, I'm from tistory!";
const char* j = 0;


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int val = 0;

void setup() {
    Serial.begin(9600);
    //Serial.setDebugOutput(true);
    Serial.println();

    pinMode(LED, OUTPUT);

    for(uint8_t t = 3; t > 0; t--) {
        Serial.printf("[SETUP] BOOT WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(WFSSID, PASSWORD);
    Serial.print("Connecting to WiFi");
    while(WiFi.status() != WL_CONNECTED) {
        delay(300);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    client.setServer(mqtt_server, mqtt_port);
    
    client.setCallback(callback);
}

void loop() {
    client.loop();
    
    if(!client.connected()) {
        reconnect();
    }
    if(WiFi.status() != WL_CONNECTED) {
        WiFi.begin(WFSSID, PASSWORD);
        Serial.print("Reconnecting WiFi");
        while(WiFi.status() != WL_CONNECTED) {
            Serial.print(".");
        }
        Serial.println();
        Serial.println("WiFi Reconnected");
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");


    String msgText = "=> ";
    
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      msgText += (char)payload[i];
    }
    Serial.println();

    DynamicJsonDocument doc(1000);
 
    // Deserialize the JSON document : Json문서 분석
    DeserializationError error = deserializeJson(doc, payload);
    
    String topic2 = topic;
    String power = doc["body"]["state"];
    
    if(topic2 == "power") {
        if(power == "2") {
            digitalWrite(LED, HIGH);
        } else {
            digitalWrite(LED, LOW);
        }
    }
}


void reconnect() {
    while(!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);
        if(client.connect(clientId.c_str(),"ESP32client", "Connect")) {
            client.subscribe(mqtt_topic);
            Serial.println("DONE connecting!");
        } else {
            Serial.print("failed, rc = ");
            Serial.print(client.state());
            Serial.println(" automatically trying again in 1 second");
            delay(1000);
        }
    }
}
