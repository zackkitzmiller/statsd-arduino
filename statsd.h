#ifndef Statsd_h
#define Statsd_h

#include "Arduino.h"
#include "IPAddress.h"
#include "Ethernet.h"
#include "EthernetUDP.h"

class StatsD
{
public:
  StatsD(IPAddress ip, int port, int localPort);
  void increment(const char *metric);
  void decrement(const char *metric);
  void timing(const char *metric, int ms);
  void gauge(const char *metric, int gaugeValue);
  void sets(const char *metric, int setsValue);
private:
  void _send(const char *metric, int value, const char *cmd);
  IPAddress _ip;
  int _port;
};

#endif
