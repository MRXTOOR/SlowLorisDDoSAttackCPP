#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#endif

bool initializePlatform();
void cleanupPlatform();

#endif // PLATFORM_H
