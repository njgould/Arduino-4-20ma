# Arduino-4-20ma
4-20mA pressure transducer HTTP interface for Arduino Network

Code for Arduino Network to read the output of a 4-20mA 25MPa pressure transducer and publish it as a JSON object over HTTP.
The Arduino measures the voltage drop across a resistor placed in the 4-20mA current loop, to determine the amount of current and therefore the transducer value.  This is converted to a pressure and the arduino runs a small web server to publish the current value as a JSON object over HTTP.

Could easily be adapted to a different type of 4-20mA transducer or a different micro controller.
