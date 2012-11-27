//12 bits for sony

void showTV()
{
  Serial.println(F("tv"));
  sendHeader("TV Page");
  client.println("<h1>TV Page</h1><br/>");
  for (int i = 0; i < sizeof(tv_commands)/sizeof(long); i++ ) {
    client.print("<a href=tv_command_");
    client.print(i);
    client.print(">Command: ");
    client.print(i);
    client.println("</a>");
  }
}

void showReceiver()
{
  Serial.println(F("receiver"));
  sendHeader("Receiver Page");
  client.println("<h1>Receiver Page</h1><br/>");
  for (int i = 0; i < sizeof(receiver_commands)/sizeof(long); i++ ) {
    client.print("<a href=recevier_command_");
    client.print(i);
    client.print(">Command: ");
    client.print(i);
    client.println("</a>");
  }
}

void showCable()
{
  Serial.println(F("cable"));
  sendHeader("Cable Page");
  client.println("<h1>Cable Page</h1><br/>");
}
