#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArrowheadESP.h>

ArrowheadESP Arrowhead;

const char* systemName = "oliveresp"; // name of the system, must match the common name of the certificate
int port = 8080; // doesn't really matter what number we type in, since it won't listen on it anyway
const char* publicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAvpcNKECuEZxyhGi20KD+" \
"dcUt+wgJeGgMdEefwCEMrU7cSnm4gSky3+IUWxI+v5l0t88+1TElJHGUIhKuDg8J" \
"eRXw1aioybH7Un8PWCTBHdrFxMNC+AZYaClFE5uehRa9AEuUHpFHimg37EbBYsNA" \
"a/dAfOFmL/XzuRJ9k28oLq8+AeaBUNfsGgJLvG3uSL6vKJLwn09DrN60dGizdB2x" \
"pffrALtO94qhWCQcUMPIRhUeXY9GUp03O3yhHkaP6eHDjqLmyg6iuFDdh1j9kgdz" \
"RoKGv6CM1FLjlz7n/gilVK5Tj2gAccjR4AdbUWid+DVyaAQJfQLgcUuJmK3QxKYp" \
"NQIDAQAB";

void setup() {
  Serial.begin(115200);
  Arrowhead.getArrowheadESPFS().loadConfigFile("netConfig.json"); // loads network config from file system
  Arrowhead.getArrowheadESPFS().loadSSLConfigFile("sslConfig.json"); // loads ssl config from file system
  Arrowhead.getArrowheadESPFS().loadProviderConfigFile("providerConfig.json"); // loads provider config from file system
 
  Arrowhead.getArrowheadESPFS().getProviderInfo().serviceRegistryAddress,
  Arrowhead.getArrowheadESPFS().getProviderInfo().serviceRegistryPort
  );

  bool startupSuccess = Arrowhead.begin(); // true of connection to WiFi and loading Certificates is successful
  if(startupSuccess){
    String response = "";
    int statusCode = Arrowhead.serviceRegistryEcho(&response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);
    Serial.println("############################");
    Serial.println();

    String serviceRegistryEntry = "{\"endOfValidity\":\"2022-12-05 12:00:00\",\"interfaces\":[\"HTTP-SECURE-SenML\"],\"providerSystem\":{\"address\":\" "+ Arrowhead.getIP() +"\",\"authenticationInfo\":\""+ publicKey +"\",\"port\":"+ port +",\"systemName\":\""+ systemName +"\"},\"secure\":\"CERTIFICATE\",\"serviceDefinition\":\"Temperature service provider for University purpose\",\"serviceUri\":\"/\",\"version\":1}";  

    response = "";
    statusCode = Arrowhead.serviceRegistryRegister(serviceRegistryEntry.c_str(), &response);
    Serial.print("Status code from server: ");
    Serial.println(statusCode);
    Serial.print("Response body from server: ");
    Serial.println(response);
    Serial.println("############################");
    Serial.println();
  }
} 


void loop() {
  Arrowhead.loop(); 
  yield();
}
