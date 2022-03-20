#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


int BUZZER = D3;
int RELAY = D1;
int Flame_sensor = A0;
int Flame_detected;

BlynkTimer timer;
char auth[] = "9o6KesXz960UvU6qN5WFsvCRY_f-TXsD"; //Auth code sent via Email
char ssid[] = "MiTelefon";
char pass[] = "omer1234";

void notifyOnFire()
{
  Flame_detected = analogRead(Flame_sensor);
  Serial.println(Flame_detected);
  //delay(100);
  if (Flame_detected <200) {
    Serial.println("Sicaklik algilandi");
    Blynk.notify("yangın var!!!");
    digitalWrite(BUZZER, HIGH);
    digitalWrite(RELAY, LOW);
    delay(500);
  }
  else
  {
    Serial.println("atesli degilim");
    digitalWrite(BUZZER, LOW);
    digitalWrite(RELAY, HIGH);
  }
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, HIGH);
  pinMode(Flame_sensor, INPUT_PULLUP);
  timer.setInterval(1000L, notifyOnFire);
}
void loop()
{
  Blynk.run();
  timer.run();
 
}