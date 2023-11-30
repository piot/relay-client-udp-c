/*----------------------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved. https://github.com/piot/relay-client-udp-c
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------------------*/
#include <relay-client-udp/client.h>
#include <udp-client/udp_client.h>
#include <imprint/allocator.h>

static int udpClientSocketInfoSend(void* _self, const uint8_t* data, size_t size)
{
    RelayClientUdpSocketInfo* self = (RelayClientUdpSocketInfo*)_self;

    return udpClientSend(self->clientSocket, data, size);
}

static ssize_t udpClientSocketInfoReceive(void* _self, uint8_t* data, size_t size)
{
    RelayClientUdpSocketInfo* self = (RelayClientUdpSocketInfo*)_self;

    return udpClientReceive(self->clientSocket, data, size);
}

int relayClientUdpInit(RelayClientUdp* self, const char* name, uint16_t port,
    const RelaySerializeUserSessionId guiseUserSessionId, MonotonicTimeMs now,
    struct ImprintAllocator* allocator, Clog log)
{
    (void) now;
    self->transport.receive = udpClientSocketInfoReceive;
    self->transport.send = udpClientSocketInfoSend;
    self->transport.self = &self->socketInfo;

    udpClientInit(&self->socket, name, port);

    self->socketInfo.clientSocket = &self->socket;

    tc_snprintf(self->subLog, 32, "%s/relay", log.constantPrefix);
    Clog relayClientLog;
    relayClientLog.config = log.config;
    relayClientLog.constantPrefix = self->subLog;

    return relayClientInit(&self->relayClient, guiseUserSessionId, self->transport, allocator,
        "prefix", relayClientLog);
}

/// Updates the client
/// @param self client
/// @param now the current monotonic time
/// @return negative on error
int relayClientUdpUpdate(RelayClientUdp* self, MonotonicTimeMs now)
{
    return relayClientUpdate(&self->relayClient, now);
}
