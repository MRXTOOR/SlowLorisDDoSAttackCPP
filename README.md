# SlowLorisDDoSAttackCPP
C++ implementation of Slow Loris DDoS attack. - Vighnesh Souda


1. Open a terminal in location of the program file slowlorisattackmultithread.cpp.

2. Compile the file with -std=c++0x and -pthread flags set; make sure to create output file:
	Example: g++ slowlorisattackmultithread.cpp -std=c++0x -pthread -o out

3. Execute the output file.
	Example: ./out
	-> Terminal will automatically display correct way of execution upon mishap.

## Ubuntu
Terminal Preview:
```
$ git clone https://github.com/vsouda/SlowLorisDDoSAttackCPP.git
$ cd SlowLorisDDoSAttackCPP
$ g++ slowlorisattackmultithread.cpp -std=c++0x -pthread -o out
$ ./out <dest_ip> <dest_port_num> <num_sockets> <num_threads>
```
