#ifndef _MAN_COM_CONFIG_H
#define _MAN_COM_CONFIG_H

// This file is managed by the user of ManCom.
// It defines all the "Compile-Time" Man Com Channels

typedef enum {
  MAN_COM_INIT_LEVEL_OS          = 0, // Indicates man com has started and loaded the initial configuration from the OS Image
  MAN_COM_INIT_LEVEL_FILE_SYSTEM = 1, // Indicates man com has loaded it's configuration from the file system
} ManComInitLevel;

typedef enum {
    MAN_COM_STATIC_CHANNEL_OMNI            = 0,
    MAN_COM_STATIC_CHANNEL_AUTOBAHN_ENGINE = 1,
} ManComStaticChannel;






#endif