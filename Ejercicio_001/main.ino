/// Bot de Telegram que lee temperatura y humedad con el censor DHT11 ///
///librerias////
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
///////////////////////////////////////////////////////////////////
#define WIFI_SSID "#####"
#define WIFI_PASSWORD "#####"
#define BOT_TOKEN "#########" // el token se octiene en  (Botfather)
//////////////////////////////////////////////////////////////////
const unsigned long BOT_MTBS = 1000; // tienpo de escaneo de mensajes
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client); // pasando datos hacia libreria
unsigned long bot_lasttime;          // última vez que se realizó el escaneo de mensajes
bool Start = false;
/////////////////////////////////////////////////////////////////
void manejarNuevosMensajes (int numNuevosMensajes)
{
  Serial.println("manejarNuevosMensajes");
  Serial.println(String(numNuevosMensajes));

  for (int i = 0; i < numNuevosMensajes; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/send_test_action")
    {
      bot.sendChatAction(chat_id, "typing"); el estado actual del bot
      delay(4000);
      bot.sendMessage(chat_id, "?????????"); ??????


      //typing mensajes de texto
      //upload_photo para fotos
      //record_video para videos
      //record_audio para audio
      //upload_document para documentos
      //find_location ???

      //Guia en  - https://core.telegram.org/bots/api#sendchataction
    }

    if (text == "/start")
    {
      String welcome = "BOT para saber la Temperatura y la Humedad.\n\n"; //mensaje de bienvenida
      welcome += from_name + " comienza diciendo /Hola o /hola";
      bot.sendMessage(chat_id, welcome); 
    }

    if (text == "/hola"){
      String hola = (String) dht.readTemperature(); //obteniendo datos del sensor
      hola += " Grados Centígrados."; 
      bot.sendMessage(chat_id, hola);

      String holaa = (String) dht.readHumidity();
      holaa += " % De Humedad.";
      bot.sendMessage(chat_id, holaa);
      }

      if (text == "/Hola"){
      String hola = (String) dht.readTemperature();
      hola += " Grados Centígrados.";
      bot.sendMessage(chat_id, hola);

      String holaa = (String) dht.readHumidity();
      holaa += " % De Humedad.";
      bot.sendMessage(chat_id, holaa);
      }
  }
}
////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  Serial.println();
  dht.begin();
/////////////////////////////////////////////////////////////
  // conectarse al wifi:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // ????? api.telegram.org
  
  ///mostrar datos dela coneccion wifi cuando sea exitosa
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}
/////////////////////////////////////////////////////////////////
//////////loop para leer mensajes/////////
////se deve mejorar ya que el el esp 32 entra en reposo y deja de funcionar////
///////no se aprobecha todos los nucleos del esp32/////
void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS) //a la espera de mensajes
  {
    int numNuevosMensajes = bot.getUpdates(bot.last_message_received + 1); 

    while (numNuevosMensajes) 
    {
      Serial.println("got response"); //solo es para ver si contesta 
      manejarNuevosMensajes (numNuevosMensajes); //llamada ala funcion
      numNuevosMensajes = bot.getUpdates(bot.last_message_received + 1); 
    }
    bot_lasttime = millis();
  }
}
