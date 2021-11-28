
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArrowheadESP.h>
ArrowheadESP Arrowhead;

void setup() {
  Serial.begin(115200);

  Arrowhead.getArrowheadESPFS().loadConfigFile("netConfig.json");

} 

void loop() {

  int httpCode = startTransaction("0x0C42D7781A442D7C0c49bF7529FD34FB09aF7205");
  if (httpCode == 200) {
    Serial.println("Provide Data");
  } else {
    Serial.println("Refuse request");
  }
  delay(30000);
  yield();
  
}
int startTransaction(String address)
{
  HTTPClient http;
  WiFiClient client;
  Serial.print("start");
  http.begin("vm.smallville.cloud.bme.hu:20999");
  http.addHeader("Content-Type", "application/json");

  String data = "{\"jsonrpc\":\"2.0\",\"method\":\"eth_sendTransaction\",\"id\":420,\"params\":[{\"from\":\"0x1488B50fB31AE2C87D93bFab4bc1e018828CFF26\",\"to\":\""+ address +"\",\"data\":\"0xf207564e0000000000000000000000000000000000000000000000000000000000000001\"}]}";
  http.addHeader("Content-Length", "0");
  int httpCode = http.POST(data);

  String payload = http.getString();
  Serial.println("http code: " + httpCode);
  Serial.println("payload: " + payload);
  Serial.print("end");
  
  return httpCode;
}
