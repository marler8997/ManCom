#ifndef _MAN_COM_H
#define _MAN_COM_H

#include <ManComConfig.h>
#include <ManComTransports.h>

typedef unsigned char ManComResult;
#define MAN_COM_RESULT_OK                        0
#define MAN_COM_RESULT_BAD_CHANNEL_NAME          1
#define MAN_COM_RESULT_INVALID_CONFIG            2
#define MAN_COM_RESULT_ACCEPTOR_ALREADY_STARTED  3
#define MAN_COM_RESULT_OUT_OF_MEMORY             4

const char* ManComResultString(ManComResult result);



//
// ManCom Configuration
//



/*
A ManComChannel can have multiple transports.
Their order of preference is the order they are configured.

Transports are defined using an identifier code.
Statically defined transports should be added to the ManComTransport
enum defined in ManComConfig.h.

Dynamically defined transports will have both a code (determined at runtime)
and a name.

ManComChannelConfig

// Header
const char* name; // points to string
unsigned transportCount;
TransportNode transportList; // points to transport config later in the struct

*/
typedef struct {
    const char* name;
    ManComTransportConfigNode* transport;
} ManComChannelConfig;

ManComChannelConfig* LookupChannelConfig(const char* name);

//
// ManCom Acceptors
//
typedef struct _ManComAcceptor ManComAcceptor;

typedef void (*AcceptReady)(const ManComAcceptor* acceptor);
typedef void (*AcceptHandle)(const ManComAcceptor* acceptor);

struct _ManComAcceptor {
    const char* name;        // Name of the managed communication channel

    AcceptReady acceptReady; // Low level hook to override default callback functionality.
                             // Blocking this callback will cause all other acceptors on the same thread
                             // to be blocked as well, so in most cases this callback should NEVER BLOCK.

    AcceptHandle accept;     // Callback when connection is accepted.
                             // Called back on the processes own thread.
};

ManComResult ManComStartAcceptor(ManComAcceptor* acceptor);

// A process does not need to use ManComWaitForInit explicitly.
// If ManCom is not ready, then other functions will block
// such as ManComAddAcceptor.
void ManComWaitForInit(ManComInitLevel level, int timeout);

#endif