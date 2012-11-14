void showHome()
{
  Serial.println(F("home"));
  sendHeader("Home Page");
  client.println("<h1>Welcome to Dave's Universal Remote</h1><br/>");
  
  client.println("<h2>Remote Functions</h2>");
  client.println("<a href=\"../tv/\">TV</a><br/>");
  client.println("<a href=\"../receiver/\">Receiver</a><br/>");
  client.println("<a href=\"../cable/\">Cable</a><br/>");
  
  client.println("<h2>Arduino Functions</h2>");
  client.println("<a href=\"../analog/\">Analog</a><br/>");
  client.println("<a href=\"../digital/\">Digital</a><br/>");
  client.println("<a href=\"../lcd/\">LCD</a><br/>");
  client.println("<a href=\"../change/\">Change</a><br/>");
  client.println("<a href=\"../status/\">Status</a><br/>");
}

void showStatus()
{
  Serial.println(F("status"));
  sendHeader("Status Page");
  client.println("<h1>Welcome to Dave's Universal Remote Status page</h1>");
  // output the value of each analog input pin
  client.println("<h2>Received UDP commands:</h2>");
  client.println(receivedCommands);
}
