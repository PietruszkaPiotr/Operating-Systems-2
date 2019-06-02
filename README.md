Systemy Operacyjne 2 - projekt 3
Data zakończenia: 21.05.2019

Projetk polegał na stworzeniu programu wielowątkoewgo, który symuluje działanie firmy dostawczej typu "InPost".
Pięć samochodów jeździ od firmy do pięciu paczkomatów. 
Samochody jak i paczkomaty mają ograniczone miejsce.
Z paczkomatów zabierane są co jakiś czas przesyłki przez klientów.
Klienci zabierają losową liczbę paczek. Jeżeli w danym paczkomacie nie ma wystarczającej liczby paczek, będą czekać, aż zostaną dowiezione. 
Do firmy jak i paczkomatów została zastosowana kolejka typu FIFO. 
Jak samochód zostanie załadowany to jedzie do paczkomatu 1. Jeżeli paczkomat jest zajęty to samochód będzie czekać. Jeżeli paczkomat jest pełny to jedzie do następnego punktu, itd.
Jak samochód nie będzie miał już paczek na pace to wróci do firmy, aby uzupełnić. Jeżeli dojedzie do ostatniego paczkomatu to będzie czekał, aż zostanie rozładowany, dopiero potem pojedzie do firmy.

Problemy napotkane podczas tworzenia:
- Samochody potrafiły dodać się kilkakrotnie do kolejki przez co była blokowana. Rozwiązane zostało to po dodaniu zmiennej zawierającą informajcę czy znajduje sie już w kolejce czy nie.
- Po dodaniu funkcji, by samochody ustawiały się w kolejce nie dodawały się one do kolejki przez co już więcej się nie poruszały. Musiałem dodać zmienne w klasie Car: destX i destY, i odpowiednio je zmieniać. 
- Większość probelmów zapomniałem, przez co nie jestem w stanie je opisać.

Biblioteki, z których korzystałem najwięcej:
thread, mutex, queue, condition_variable, ncurses.h

--English description

Operating Systems - project 3
Create date: 21.05.2019

Project consisted creating multithread's program, which simulates how delivery company works e.g "InPost".
Five cars drives between company and five pack machines.
Cars and pack machines have limited space.
Clients are taking random number of packs from pack machines. If there are not enough packs, clients will wait, till packs are delivered.
Queue to firm and pack machines are FIFO type.
If car is loaded, it will drive to pack machine 1. If pack machine is occupied, car will wait. If pack machine is full, car will drive to next pack machine, etc.
If car is empty, it will drive back to company to load new packs. If car is at last pack machine, it will wait, till is empty and it will drive back to company.

Encountered problems:
- Cars could add themselves few times to queue and because of that queue was blocked. It was solved after added variable, which contained information if car is already in queue.
- After creating a function, that make cars set in a queue, they didn't added themselves to queue and didn't move anymore. I needed to add variables ni Car class: destX and destY, abd had to change them properly.
- I forgot most of problems, that I faced and I can't describe more.

Libraries, that i used most:
thread, mutex, queue, condition_variable, ncurses.h
