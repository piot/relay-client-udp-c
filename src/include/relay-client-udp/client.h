/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/relay-client-udp-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#ifndef RELAY_CLIENT_UDP_H
#define RELAY_CLIENT_UDP_H

#include <clog/clog.h>
#include <datagram-transport/transport.h>
#include <relay-client/client.h>
#include <udp-client/udp_client.h>

struct ClvSerializeRoomCreateOptions;
struct ImprintAllocator;

typedef struct RelayClientUdpSocketInfo {
    struct UdpClientSocket* clientSocket;
} RelayClientUdpSocketInfo;

typedef struct RelayClientUdp {
    RelayClient relayClient;
    DatagramTransport transport;
    RelayClientUdpSocketInfo socketInfo;
    UdpClientSocket socket;
    char subLog[32];
    Clog log;
} RelayClientUdp;

int relayClientUdpInit(RelayClientUdp* self, const char* name, uint16_t port,
    RelaySerializeUserSessionId guiseUserSessionId, MonotonicTimeMs now,
    struct ImprintAllocator* allocator, Clog log);
int relayClientUdpUpdate(RelayClientUdp* self, MonotonicTimeMs now);
int relayClientUdpCreateRoom(
    RelayClientUdp* self, const struct ClvSerializeRoomCreateOptions* roomOptions);

#endif
