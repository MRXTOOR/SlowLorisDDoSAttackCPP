#ifndef ATTACK_H
#define ATTACK_H

#include <vector>
#include <netinet/in.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

void initialSendSocket(int socketNum);
void spamPartialHeaders(struct sockaddr_in victim, std::vector<int>& socketList);

#endif // ATTACK_H
