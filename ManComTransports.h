#ifndef _MAN_COM_TRANSPORT_H_
#define _MAN_COM_TRANSPORT_H_

// START WINDOWS VERSION
#include <windows.h>
typedef UINT16 uint16_t;
// END WINDOWS VERSION

typedef enum {
    MAN_COM_STREAM_TRANSPORT_TCP   = 0,
    MAN_COM_STREAM_TRANSPORT_MIPIO = 1,
    MAN_COM_STREAM_TRANSPORT_PIPE  = 2,
} ManComTransport;

typedef struct {
    int placeholder;
} ManComTransportDefinition;

typedef struct {
    ManComTransport type;
    union {
        struct {
            int addressFamily;
            uint16_t port;
        } tcp;
    } data;
} ManComTransportConfig;

typedef struct _ManComTransportConfigNode ManComTransportConfigNode;
struct _ManComTransportConfigNode {
    ManComTransportConfigNode* next;
    ManComTransportConfig config;
};



/*
TCP TRANSPORT


A Transport needs to define a function to parse configuration and a structure to hold that configuration at runtime.

Channel Definition

Address Family
    AF_INET or AF_INET6 or (Some other C define)
IP Address
    0.0.0.0? 127.0.0.1?
Port


The transport configuration parse function should operate on something like a json or xml data structure (think about ASON too).


Example Configuration:

config.ljson (lenient json)
-------------------------------------------
// No need for global '{' '}'
// Map Keys do not need a ':' seperator
Channels [
  {
    ChannelName Http
    Transports [
        Tcp AF_INET 0.0.0.0 80
    ]
-------------------------------------------


config.xml
-------------------------------------------
<Channels>
  <Channel Name="Http">
    <Transport Type="Tcp">
        <AddressFamily>AF_INET</AddressFamily>
        <Port>80</Port>
    </Transport>
  </Channel>
</Channels>
-------------------------------------------




transports.config
-------------------------------------------
Transport Tcp
  Type Stream
  ChannelConfig
    uint16 Port
    optional string Address
    optional string AddressFamily
Transport Mipio
  Type ?
  ChannelConfig
    ??
-------------------------------------------

channels.config
-------------------------------------------
Channel Http
  Transport Tcp AddressFamily=AF_INET Port=80
-------------------------------------------


*/






#endif