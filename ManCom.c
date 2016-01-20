#include <stdio.h>
#include <string.h>

#include <ManCom.h>

#include <windows.h>

static const char* ManComResultStrings[] = {
   "OK",
   "Bad channel name",
   "Invalid config",
   "Acceptor already started",
   "Out of memory",
};
const char* ManComResultString(ManComResult result)
{
    if(result < sizeof(ManComResultStrings) / sizeof(ManComResultStrings[0])) {
      return ManComResultStrings[result];
    }
    return "Unknown error";
}

//
// ManCom Configuration
//
extern ManComChannelConfig StaticChannelConfig[];
extern unsigned StaticChannelConfigCount;

ManComChannelConfig* LookupChannelConfig(const char* name)
{
    if(name != NULL)
    {
        unsigned i;
        for(i = 0; i < StaticChannelConfigCount; i++)
        {
            //printf("[ManComAddAcceptor] StaticChannelConfig[%d] = '%s'\n", i, StaticChannelConfig[i]);
            if(strcmp(name, StaticChannelConfig[i].name) == 0)
            {
                return &StaticChannelConfig[i];
            }
        }
    }
    
    // TODO: Synchronize then lookup dynamic configuration
    return NULL;
}

typedef struct {
    ManComChannelConfig* config;
} ManComChannel;

typedef struct _ManComAcceptorNode ManComAcceptorNode;
struct _ManComAcceptorNode {
    ManComAcceptor acceptor;
    DWORD processID;
    ManComAcceptorNode* next;
};

ManComAcceptorNode* acceptorHead = 0;

// Assumption: called inside critical section for acceptor list
ManComAcceptorNode* AlreadyLocked_LookupRunningAcceptor(const char* name)
{
    ManComAcceptorNode* next;
    for(next = acceptorHead; next; next = next->next)
    {
        if(strcmp(name, next->acceptor.name) == 0)
        {
            return next;
        }
        next = next->next;
    }
    return NULL;
}

ManComResult ManComStartAcceptor(ManComAcceptor* acceptor)
{
    ManComChannelConfig* config;

    //
    // Validate the acceptor configuration
    //
    if(acceptor->acceptReady == NULL && acceptor->accept == NULL)
    {
        return MAN_COM_RESULT_INVALID_CONFIG;
    }

    //
    // Lookup the acceptor configuration
    //
    config = LookupChannelConfig(acceptor->name);
    if(config == NULL)
    {
        return MAN_COM_RESULT_BAD_CHANNEL_NAME;
    }

    // TODO: SYNCHRONIZE ACCESS TO ACCEPTOR LIST
    {
        //
        // Check if the acceptor has already been started
        //
        ManComAcceptorNode* node = AlreadyLocked_LookupRunningAcceptor(acceptor->name);
        if(node != NULL)
        {
            // TODO: EXIT THREAD SYNCHRONIZATION
            return MAN_COM_RESULT_ACCEPTOR_ALREADY_STARTED;
        }

        node = (ManComAcceptorNode*)malloc(sizeof(ManComAcceptorNode));
        if(node == NULL)
        {
            // TODO: EXIT THREAD SYNCHRONIZATION
            return MAN_COM_RESULT_OUT_OF_MEMORY;
        }
        memcpy(&node->acceptor, acceptor, sizeof(node->acceptor));
        node->processID = GetCurrentProcessId();

        node->next = acceptorHead;
        acceptorHead = node;
    }
    // TODO: EXIT THREAD SYNCHRONIZATION

    //
    // Start the Acceptor
    //
    


    return MAN_COM_RESULT_OK;
}















