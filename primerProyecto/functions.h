//=======================================
//handle function: send webpage to client
//=======================================
void webpage()
{
  server.send(200,"text/html");
}
//=====================================================
//function process event: new data received from client
//=====================================================
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t welength)
{
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);

  if(type == WStype_TEXT) // recibir texto del cliente
  {
    byte separator = payloadString.indexOf('=');
    String var = payloadString.substring(0, separator);
    Serial.print("var= ");
    Serial.println(var);
    String val = payloadString.substring(separator + 1);
    Serial.print("val= ");
    Serial.println(val);
    Serial.println(" ");


    if (var == "LEDonoff")
    {
      LEDonoff = false;
      if (val == "ON") LEDonoff = true;
    }
    
    if (var == "LEDonoff2") // agregar esta parte para manejar LEDonoff2
    {
      LEDonoff2 = false;
      if (val == "ON") LEDonoff2 = true;
    }
  }
}

