#include <stdio.h>

// Uruchomic powyzszy program poprzez funkcje execlp w procesie potomnym innego
// procesu (z uzyciem funkcji fork) i wysylac do niego sygnaly poprzez funkcje syste-
// mowa kill z procesu macierzystego. ! Uwaga: Przed wyslaniem sygnalu sprawdzic,
// na zakonczenie swojego potomka przy pomocy funkcji wait, a nastepnie wypisac
// czy proces istnieje (patrz podrozdzial 3.2). Proces macierzysty powinien zaczekac
// jego PID i status zakonczenia zwracane przez te funkcje. W przypadku zakonczenia
// procesu potomnego przez sygnal, powinien dodatkowo wypisac numer tego sygnalu
// zawarty w statusie zakonczenia, a takze jego nazwe (uzyc funkcji strsignal). Do
// wyluskania numeru sygnalu ze statusu zakonczenia uzyc makr opisanych w podroz-
// dziale 2.4.
int main() {
	printf("asd");

	return 0;
}
