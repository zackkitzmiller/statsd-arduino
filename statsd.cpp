#include "Arduino.h"
#include "Statsd.h"
#include "Ethernet.h"
#include "EthernetUDP.h"
#include "IPAddress.h"
#include "string.h"

EthernetUDP statsd;

StatsD::StatsD(IPAddress ip, int port, int localPort)
{
  _ip = ip;
  _port = port;
  _localPort = localPort;
}

void StatsD::increment(const char *metric) {
  int buffer_len = sizeof(&metric) + 4;
  char buffer[buffer_len];
  strcpy(buffer, metric);
  strcat(buffer,":1|c");
  StatsD::_send(buffer);
}

void StatsD::decrement(const char *metric) {
  int buffer_len = sizeof(&metric) + 4;
  char buffer[buffer_len];
  strcpy(buffer, metric);
  strcat(buffer,":-1|c");
  StatsD::_send(buffer);
}

void StatsD::_send(char *msg) {
  const uint8_t* nmsg = (uint8_t*)msg;
  statsd.beginPacket(_ip, _port);
  statsd.write(nmsg, sizeof(&msg));
  statsd.endPacket();
}
