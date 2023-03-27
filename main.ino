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

      /
