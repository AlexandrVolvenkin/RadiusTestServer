# RadiusTestServer

RadiusTestServer - программа для замера времени ответа сервера
на канальном уровне.

параметры командной строки:
-m - режим работы: сервер - server или клиент - client
-e - имя интерфейса ethernet
-a - mac адрес сервера
-c - имя интерфейса comm
-p - время периода в мкс (Задача РЗА-алгоритм) если режим сервера или
     время периода в мкс (посылка запросов) если режим клиента
-l - процент загрузки от времени периода (Задача РЗА-алгоритм)
-h - справка
-v - версия программы

вариант запуска сервера на BeagleBone:
sudo ./RadiusTestServer -m server -e eth0 -c ttyO1 -p 5000 -l 50

вариант запуска клиента на BeagleBone:
sudo ./RadiusTestServer -m client -e eth0 -a "64:cf:d9:55:ca:1e" -c ttyO1 -p 5000

вариант запуска клиента на lenovo:
sudo ./RadiusTestServer -m server -e wlo1 -c ttyO1 -p 5000 -l 50
sudo ./RadiusTestServer -m client -e wlo1 -a "64:cf:d9:55:ca:1e" -c ttyO1 -p 1000

вариант запуска клиента на msi
sudo ./RadiusTestServer -m client -e wlo1 -a "20:1a:06:9f:a5:48" -c ttyO1 -p 1000

статистика выводится раз в секунду
вариант окна вывода статистики:

//----------------------------------------
Client statistics session: 5

Transmited: 13176
Received: 13176
Lost: 3
Min: 420
Max: 1076
Average: 447

//----------------------------------------


 
