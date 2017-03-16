
// N. Gould 16/01/2017

// Connect 4-20mA transducer (~24V) Powersupply GND to Arduino GND.  
// Connect 250 Ohm resistor in series with pressure transducer, with the resistor on the GND side.
// Connect the transducer side of the resistor to A0 on the Arduino, to measure the voltage drop across the resistor.
// For a transducer reading of 0%, the current loop should flow 4mA...  4mA @ 250 Ohm = 1V
// For a transducer reading of 100%, the current loop should flow 20mA... 20mA @ 250 Ohm = 5V

#include <SPI.h>
#include <Ethernet.h>

int init_1 = 0, analog_0, res5 = 1, res10 = 1, res80 = 1, res160 = 1;
float pressure, a_0, v_0;

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,15,150);


// (First argument is the port, port 80 is default for HTTP):
EthernetServer server(80);
 
void setup()
{  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();

  
}
 
void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          

          get_current_pressure();

          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println();


          // Send the pressure as a json-p object
          client.print("{");
          client.print("\"pressure");
          client.print("\":");
          client.print(pressure);
          client.print(",");
          client.print("\"millis");
          client.print("\":");
          client.print(millis());          
          client.println("}");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
} 

// Read A0
void get_current_pressure(){
    analog_0 = analogRead(A0);
    a_0 = float(analog_0);
    // v_0 = (a_0/1023.0) * 5;

    // 250 Bar (25,000kPa) Use 250 Ohm Resistor

    // At 0 kPa there should be 4mA. 4mA @ 250 Ohm = 1V
    // At 25,000 kPa there should be 20mA.  20mA @ 250 Ohm = 5V
    // 
    pressure = ((a_0 - 205.0) / (1023.0-205.0)) * 25000;



