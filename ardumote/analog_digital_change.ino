void showAnalog()
{
  Serial.println(F("analog"));
  sendHeader("Multi-page example-Analog");
  client.println("<h1>Analog Pins</h1>");
  // output the value of each analog input pin

    client.println(F("<table border='1' >"));
  for (int i = 0; i < 6; i++) {
    client.print(F("<tr><td>analog pin "));
    client.print(i);
    client.print(F(" </td><td>"));
    client.print(analogRead(i));
    client.println(F("</td></tr>"));
  }
  client.println(F("</table>"));
  client.println(F("</body></html>"));
}

// mime encoded data for the led on and off images:
// see: http://www.motobit.com/util/base64-decoder-encoder.asp
P(led_on) =  "<img src=\"data:image/jpg;base64,"
"/9j/4AAQSkZJRgABAgAAZABkAAD/7AARRHVja3kAAQAEAAAAHgAA/+4ADkFkb2JlAGTAAAAAAf/b"
"AIQAEAsLCwwLEAwMEBcPDQ8XGxQQEBQbHxcXFxcXHx4XGhoaGhceHiMlJyUjHi8vMzMvL0BAQEBA"
"QEBAQEBAQEBAQAERDw8RExEVEhIVFBEUERQaFBYWFBomGhocGhomMCMeHh4eIzArLicnJy4rNTUw"
"MDU1QEA/QEBAQEBAQEBAQEBA/8AAEQgAGwAZAwEiAAIRAQMRAf/EAIIAAAICAwAAAAAAAAAAAAAA"
"AAUGAAcCAwQBAAMBAAAAAAAAAAAAAAAAAAACBAUQAAECBAQBCgcAAAAAAAAAAAECAwARMRIhQQQF"
"UWFxkaHRMoITUwYiQnKSIxQ1EQAAAwYEBwAAAAAAAAAAAAAAARECEgMTBBQhQWEiMVGBMkJiJP/a"
"AAwDAQACEQMRAD8AcNz3BGibKie0nhC0v3A+teKJt8JmZEdHuZalOitgUoHnEpQEWtSyLqgACWFI"
"nixWiaQhsUFFBiQSbiMvvrmeCBp27eLnG7lFTDxs+Kra8oOyium3ltJUAcDIy4EUMN/7Dnq9cPMO"
"W90E9kxeyF2d3HFOQ175olKudUm7TqlfKqDQEDOFR1sNqtC7k5ERYjndNPFSArtvnI/nV+ed9coI"
"ktd2BgozrSZO3J5jVEXRcwD2bbXNdq0zT+BohTyjgPp5SYdPJZ9NP2jsiIz7vhjLohtjnqJ/ouPK"
"co//2Q=="
"\"/>";

P(led_off) = "<img src=\"data:image/jpg;base64,"
"/9j/4AAQSkZJRgABAgAAZABkAAD/7AARRHVja3kAAQAEAAAAHgAA/+4ADkFkb2JlAGTAAAAAAf/b"
"AIQAEAsLCwwLEAwMEBcPDQ8XGxQQEBQbHxcXFxcXHx4XGhoaGhceHiMlJyUjHi8vMzMvL0BAQEBA"
"QEBAQEBAQEBAQAERDw8RExEVEhIVFBEUERQaFBYWFBomGhocGhomMCMeHh4eIzArLicnJy4rNTUw"
"MDU1QEA/QEBAQEBAQEBAQEBA/8AAEQgAHAAZAwEiAAIRAQMRAf/EAHgAAQEAAwAAAAAAAAAAAAAA"
"AAYFAgQHAQEBAQAAAAAAAAAAAAAAAAACAQQQAAECBQAHBQkAAAAAAAAAAAECAwAREhMEITFhoSIF"
"FUFR0UIGgZHBMlIjM1MWEQABAwQDAQEAAAAAAAAAAAABABECIWESA1ETIyIE/9oADAMBAAIRAxEA"
"PwBvl5SWEkkylpJMGsj1XjXSE1kCQuJ8Iy9W5DoxradFa6VDf8IJZAQ6loNtBooTJaqp3DP5oBlV"
"nWrTpEouQS/Cf4PO0uKbqWHGXTSlztSvuVFiZjmfLH3GUuMkzSoTMu8aiNsXet5/17hFyo6PR64V"
"ZnuqfqDDDySFpNpYH3E6aFjzGBr2DkMuFBSFDsWkilUdLftW13pWpcdWqnbBzI/l6hVXKZlROUSe"
"L1KX5zvAPXESjdHsTFWpxLKOJ54hIA1DZCj+Vx/3r96fCNrkvRaT0+V3zV/llplr9sVeHZui/ONk"
"H3dzt6cL/9k="
"\"/>";
;

void showDigital()
{
  Serial.println(F("digital"));
  sendHeader("Multi-page example-Digital");
  client.println(F("<h2>Digital Pins</h2>"));
  // show the value of digital pins
  client.println(F("<table border='1'>"));
  for (int i = 2; i < 8; i++) {
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // turn on pull-ups
    client.print(F("<tr><td>digital pin "));
    client.print(i);
    client.print(F(" </td><td>"));
    if(digitalRead(i) == LOW)
      printP(led_off);
    else
      printP(led_on);
    client.println(F("</td></tr>"));
  }
  client.println(F("</table>"));

  client.println(F("</body></html>"));
}

void showChange(boolean isPost)
{
  Serial.println(F("change"));
  if(isPost)
  {
    Serial.println("isPost");
    client.find("\n\r"); // skip to the body
    // find parameters starting with "pin" and stop on the first blank line
    Serial.println(F("searching for parms"));
    while(client.findUntil("pinD", "\n\r")){
      int pin = client.parseInt();       // the pin number
      int val = client.parseInt();       // 0 or 1
      Serial.print(pin);
      Serial.print("=");
      Serial.println(val);
      pinMode(pin, OUTPUT);
      digitalWrite(pin, val);
    }
  }
  sendHeader("Multi-page example-change");
  // table with buttons from 2 through 9
  // 2 to 5 are inputs, the other buttons are outputs

  client.println(F("<table border='1'>"));

  // show the input pins
  for (int i = 2; i < 6; i++) {  // pins 2-5 are inputs
    pinMode(i, INPUT);
    digitalWrite(i, HIGH); // turn on pull-ups
    client.print(F("<tr><td>digital input "));
    client.print(i);
    client.print(F(" </td><td>"));

    client.print(F("&nbsp </td><td>"));
    client.print(F(" </td><td>"));
    client.print(F("&nbsp </td><td>"));


    if(digitalRead(i) == LOW)
      //client.print("Low");
      printP(led_off);
    else
      //client.print("high");
      printP(led_on);
    client.println("</td></tr>");
  }

  // show output pins 6-9
  // note pins 10-13 are used by the ethernet shield 
  for (int i = 6; i < 10; i++) {
    client.print(F("<tr><td>digital output "));
    client.print(i);
    client.print(F(" </td><td>"));
    htmlButton( "On", "pinD", i, "1");
    client.print(F(" </td><td>"));
    client.print(F(" </td><td>"));
    htmlButton("Off", "pinD", i, "0");
    client.print(F(" </td><td>"));

    if(digitalRead(i) == LOW)
      //client.print("Low");
      printP(led_off);
    else
      //client.print("high");
      printP(led_on);
    client.println(F("</td></tr>"));
  }
  client.println(F("</table>"));
}

void showLCD() {
  Serial.println(F("lcd"));
  sendHeader("LCD Page");
  client.println("<h1>LCD Page</h1><br/>");
}

