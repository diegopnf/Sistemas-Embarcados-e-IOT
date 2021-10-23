#include <ESP8266WiFi.h>
#include <SimpleDHT.h>

const char* ssid = "SSID DA REDE WIFI";
const char* psw = "SENHA DA REDE WIFI";

const char http_site[] = "http://(NOME DNS DO COMPUTADOR)";
const int http_port = 8090; //Porta xamp 

WiFiClient client;
IPAddress server(187,38,143,119); //IP Externo
int pinDHT11 = D2;
SimpleDHT11 dht11;

void setup() {
  delay(30000); 
  Serial.begin(115200);
  Serial.println("NodeMCU - Gravando dados no BD via GET");
  Serial.println("Aguardando conexão");
  
  WiFi.begin(ssid, psw);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay(100);
    Serial.print(".");
  }
  Serial.print("\nWI-FI conectado com sucesso: ");
  Serial.println(ssid);

}

void loop() {
  
  //Leitura do sensor DHT11
  delay(3000); 
  byte temp = 5; //Forçando as leituras 
  byte humid = 3;
  
  Serial.println("Gravando dados no BD: ");
  Serial.print((int)temp); Serial.print(" *C, "); 
  Serial.print((int)humid); Serial.println(" %");

  // Envio dos dados do sensor para o servidor via GET
  if ( !getPage((int)temp,(int)humid) ) {
    Serial.println("GET request failed");
  }
}

// Executa o HTTP GET request no site remoto
bool getPage(int temp, int humid) {
  if ( !client.connect(server, http_port) ) {
    Serial.println("Falha na conexao com o site ");
    return false;
  }
  String param = "?temp=" + String(temp) + "&humid=" + String(humid); //Parâmetros com as leituras
  Serial.println(param);
  client.println("GET /insert_weather.php" + param + " HTTP/1.0"); //insert_weather.php e o arquivo na raiz do htdocs do xamp
  client.println("Host: ");
  client.println(http_site);
  client.println("Connection: close");
  client.println();
  client.println();

    // Informações de retorno do servidor para debug
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  return true;
}
