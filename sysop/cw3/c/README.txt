========================================================================
Autor: Mateusz Wojtyna                                        xx.03.2025
========================================================================

* Uruchamianie:
===============
Aby uruchomić poszczególne programy:
$ make
$ ./3c.x

Usuwanie plików *.o, *.x:
$ make clean

Pakowanie do archiwum:
$ make tar

* Treść zadania:
================
3c. W procesie macierzystym utworzyc proces potomny (funkcja fork) i sprawic, aby stal
sie liderem nowej grupy procesow (funkcja setpgid), a nastepnie poprzez funkcje
execlp uruchomic w nim program tworzacy kilka procesow potomnych (funkcja fork
w petli), ktore poprzez funkcje execlp wykonuja program do obslugi sygnalow z
punktu (a). Z pierwszego procesu macierzystego wysylac sygnaly do calej grupy
procesow potomnych po uprzednim sprawdzeniu jej istnienia. Identyfikator tej
grupy procesow uzyskac przy pomocy funkcji getpgid. Proces bedacy liderem grupy
procesow niech ignoruje sygnaly, a na koncu czeka na zakonczenie wszystkich swo-
ich procesow potomnych i wypisuje ich identyfikatory PID oraz status zakonczenia
(zwracane przez funkcje wait), a w przypadku zakonczenia tych procesow przez
sygnal, takze numer i nazwe odpowiedniego sygnalu. Pierwszy proces macierzy-
sty rowniez powinien zaczekac na zakonczenie swojego bezposredniego potomka i
wypisac jego PID oraz status zakonczenia zwracane przez funkcje wait.

Numer sygnalu oraz opcje jego obslugi we wszystkich powyzszych programach przeka-
zywac za pomoca argumentow wywolania programu – sprawdzac ich liczbe i wypisywac
odpowiedni komunikat w przypadku blednego uruchomienia (ze wskazowka jak poprawnie
uruchomic program).

