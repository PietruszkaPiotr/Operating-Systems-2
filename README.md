Systemy Operacyjne 2 - projekt 3
Data stworzenia: 21.05.2019

Projetk polegał na stworzeniu programu wielowątkoewgo, który symuluje działanie firmy dostawczej typu "InPost".
Pięć samochodów jeździ od firmy do pięciu paczkomatów. 
Samochody jak i paczkomaty mają ograniczone miejsce.
Z paczkomatów zabierane są co jakiś czas przesyłki przez klientów.
Klienci zabierają losową liczbę paczek. Jeżeli w danym paczkomacie nie ma wystarczającej liczby paczek, będą czekać, aż zostaną dowiezione. 
Do firmy jak i paczkomatów została zastosowana kolejka typu fifo. 
Jak samochód zostanie załadowany to jedzie do paczkomatu nr 1. Jeżeli jest zajęty to czeka. Jeżeli jest pełny to jedzie do następnego punktu, itd.
Jak samochód nie będzie miał już paczek na pace to wróci do firmy, aby uzupełnić. Jeżeli dojedzie do ostatniego paczkomatu to będzie czekał, aż zostanie rozładowany, dopiero potem pojedzie do firmy.

Problemy napotkane podczas tworzenia:
- Samochody potrafiły dodać się kilkakrotnie do kolejki przez co była blokowana. Rozwiązane zostało to po dodaniu zmiennej zawierającą informajcę czy znajduje sie już w kolejce czy nie.
- Podczas dodawania funkcji, by samochody ustawiały się w kolejce nie dodawały się one do kolejki przez co już więcej się nie poruszały. Musiałem dodać zmienne w klasie Car: destX i destY i odpowiednio je zmieniać. 
- Większość probelmów zapomniałem, przez co nie jestem w stanie je opisać.

Biblioteki, z których korzystałem najwięcej:
thread, mutex, queue, condition_variable, ncurses.h
