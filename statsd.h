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
private:
  void _send(char *msg);
  IPAddress _ip;
  int _port;
  int _localPort;
};

#endif
