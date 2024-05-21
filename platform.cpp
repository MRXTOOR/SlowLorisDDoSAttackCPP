#include "platform.h"

bool initializePlatform()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        return false;
    }
#endif
    return true;
}

void cleanupPlatform()
{
#ifdef _WIN32
    WSACleanup();
#endif
}
