statsd-arduino
==============

Arduino StatsD Client

installation
============

* Create a folder for Arduino Libraries if necessary
* Make new `StatsD` folder
* Copy `statsd.cpp` and `statsd.h` to `StatsD`
* Import StatsD folder from Arduino IDE

example usage
=============

```cpp
#include <Ethernet.h>
#include <SPI.h>

#include <statsd.h>

IPAddress stats_ip(207, 12, 33, 21); // IP Address of StatsD Server
int statsd_port = 8125; // StatsD Port
StatsD statsdc(stats_ip, statsd_port, 8888); // create StatsD Client Instance

IPAddress ip(192, 168, 33, 1); // IP Address of Arduino w/ Ethernet Sheild
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Ethernet Shield MAC

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip); // Setup 

  statsdc.increment("metric");
  statsdc.decrement("metric");
}

void loop()
{
  //
}
```
