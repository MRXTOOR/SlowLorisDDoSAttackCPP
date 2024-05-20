# SlowLorisDDoSAttackCPP
Реализация атаки Slow Loris DDoS на языке C++. - Vighnesh Souda


1. Откройте терминал в расположении файла программы slowlorisattackmultithread.cpp.

2. Скомпилируйте файл с установленными флагами -std=c++0x и -pthread; убедитесь, что создаете выходной файл:
Пример: g++ slowlorisattackmultithread.cpp -std=c++0x -pthread -o out

3. Запустите выходной файл.
Пример: ./out
-> Терминал автоматически покажет правильный способ выполнения при ошибке.

## Ubuntu (у меня был arch но далекого изменения это не несет)
Terminal Preview:
```
$ git clone https://github.com/vsouda/SlowLorisDDoSAttackCPP.git
$ cd SlowLorisDDoSAttackCPP
$ g++ slowlorisattackmultithread.cpp -std=c++0x -pthread -o out
$ ./out <dest_ip> <dest_port_num> <num_sockets> <num_threads>
```


