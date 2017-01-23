#include "Arduino.h"
#include "Statsd.h"
#include "Ethernet.h"
#include "EthernetUDP.h"
#include "IPAddress.h"
#include "string.h"

EthernetUDP statsd;

StatsD::StatsD(IPAddress ip, int port, int localPort) {
  _ip = ip;
  _port = port;
  statsd.begin(localPort);
}

void StatsD::increment(const char *metric) {
  StatsD::_send(metric,1, "c");
}

void StatsD::decrement(const char *metric) {
  StatsD::_send(metric,-1, "c");
}

void StatsD::timing(const char *metric, int ms) {
  StatsD::_send(metric,ms, "ms");
}

void StatsD::gauge(const char *metric, int gaugeValue) {
  StatsD::_send(metric,gaugeValue, "g");
}

void StatsD::sets(const char *metric, int setsValue) {
  StatsD::_send(metric, setsValue, "s");
}

void StatsD::_send(const char *metric, int value, const char *cmd) {
  // Convert the integer to a string (an int's maximum string length is 12 characters [sign(1) + digits(10) + null(1)]) �2,147,483,648 to 2,147,483,647
  char valueString[12];
  itoa(value,valueString,10);

  // Concatenate the parts of the final string
  char buffer[strlen(metric) + strlen(valueString) + strlen(cmd) + 2 + 1]; // +2 for : and | and add +1 for null
  strcpy(buffer, metric);
  strcat(buffer, ":");
  strcat(buffer, valueString);
  strcat(buffer, "|");
  strcat(buffer, cmd);

  const uint8_t* msg = (uint8_t*)buffer;

  statsd.beginPacket(_ip, _port);
  statsd.write(msg, strlen(buffer));
  statsd.endPacket();
}
