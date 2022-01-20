  #include   <WiFi.h >  // Biblioteca básica de ESP32 WiFi 
  #include   <DNSServer.h >  // Servidor DNS local usado para redirigir todas       
  #include <WiFiManager.h>
  #include <WebServer.h>
  

  const int PIN_AP = 2; // pulsador para volver al modo AP
  void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Modo de configuración ingresado");
  Serial.println(WiFi.softAPIP());
  Serial.println(myEsp32WifiManager->getConfigPortalSSID());
  }
  //flag para salvar datos
  bool shouldSaveConfig = false;
 
  //callback nos notifica guardar config
  void saveConfigCallback () {
  Serial.println("Debería guardar la configuración");
  shouldSaveConfig = true;
  }
/////////////////////////////////////////////////// 
  void setup() {
  Serial.begin(9600);
  pinMode(PIN_AP, INPUT);
  //declaración de objeto wifiManager
  WiFiManager wifiManager;
 
  // utilizando ese comando, como las configuraciones se apagarán en la memoria
  // en caso de que la redacción se conecte automáticamente se apagara.
  // wifiManager.resetSettings();
  //devolución de llamada para cuando entra en el modo de configuración AP
  wifiManager.setAPCallback(configModeCallback);
  //devolución de llamada cuando se conecta a una red, es decir, cuando pasa a trabajar en modo EST
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  //crea una red de nombre ESP_AP con pass 12345678
  wifiManager.autoConnect("ESP_AP", "12345678");
  }
 
  void loop() {
  WiFiManager wifiManager;
  //si el botón se ha presionado
  if ( digitalRead(PIN_AP) == HIGH ) {
  Serial.println("reajustar"); //resetear intenta abrir el portal
  if(!wifiManager.startConfigPortal("ESP_AP", "12345678") ){
  Serial.println("No se pudo conectar");
  delay(2000);
  ESP.restart();
  delay(2000);
  }
  Serial.println("conectado ESP_AP!!!");
  }
  }
