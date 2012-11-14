void showTV()
{
  Serial.println(F("tv"));
  sendHeader("TV Page");
  client.println("<h1>TV Page</h1><br/>");
}

void showReceiver()
{
  Serial.println(F("receiver"));
  sendHeader("Receiver Page");
  client.println("<h1>Receiver Page</h1><br/>");
}

void showCable()
{
  Serial.println(F("cable"));
  sendHeader("Cable Page");
  client.println("<h1>Cable Page</h1><br/>");
}
