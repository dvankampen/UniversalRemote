// create an HTML button
void htmlButton( char * label, char *name, int nameId, char *value)
{
  client.print(F("<form action='/change/' method='POST'><p><input type='hidden' name='"));
  client.print(name);
  client.print(nameId);
  client.print(F("' value='"));
  client.print(value);
  client.print(F("'><input type='submit' value='"));
  client.print(label);
  client.print(F("'/></form>"));
}

void unknownPage(char *page)
{
  Serial.print(F("Unknown : "));
  Serial.println(F("page"));

  sendHeader("Unknown Page");
  client.println(F("<h1>Unknown Page</h1>"));
  client.println(page);
  client.println(F("</body></html>"));
}

void sendHeader(char *title)
{
  // send a standard http response header
  client.println(F("HTTP/1.1 200 OK"));
  client.println(F("Content-Type: text/html"));
  client.println();
  client.print(F("<html><head><title>"));
  client.println(title);
  client.println(F("</title><body>"));
  client.println("<a href=\"../home/\">HOME</a><br/>");
}
