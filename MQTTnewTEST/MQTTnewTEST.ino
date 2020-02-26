#include <WiFi.h>
#include <PubSubClient.h>


// Update these with values suitable for your network.
const char* ssid = "luple_2.4g";
const char* password = "luple123";
const char* mqtt_server = "localhost";
#define mqtt_port 1883
#define MQTT_USER "esp32-user"
#define MQTT_PASSWORD "Connect"
#define MQTT_SERIAL_PUBLISH_CH "test/test"
#define MQTT_SERIAL_RECEIVER_CH "test/test"

WiFiClient wifiClient;

PubSubClient client(wifiClient);

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(200);
      Serial.print(".");
    }
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(),MQTT_USER,MQTT_PASSWORD)) {
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish("test/test", "HI!!! I'm BEAR!!!!");
      // ... and resubscribe
      client.subscribe(MQTT_SERIAL_RECEIVER_CH);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 seconds");
      // Wait 1 seconds before retrying
      delay(1000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");  
    Serial.write(payload, length);
    Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(500);// Set time out for 
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  //reconnect();

  client.connect("esp32client", "TEST!!!!!!", "HEY");
}

void publishSerialData(char *serialData){
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH_CH, serialData);
}
void loop() {
//   client.loop();
//   if (Serial.available() > 0) {
//     char mun[501];
//     memset(mun,0, 501);
//     Serial.readBytesUntil( '\n',mun,500);
//     publishSerialData(mun);
//   }

    client.publish("test/test", "Hello, world");
}
