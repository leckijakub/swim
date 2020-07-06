# Systemy wbudowane i mikrokontrolery

### 1. Dioda LED i sterowanie za pomocą timera

​	W mikrokontrolerach timery służą do cyklicznego wykonywania różnych operacji, np. pobrania danych z czujników czy przesłania jakiejś informacji. W tym ćwiczeniu zadaniem będzie wykorzystanie timera, aby zmieniać stan na diodzie. 

​	W projekcie `lab1` dioda została już skonfigurowana i powinna zapalić się po wgraniu programu na moduł. Korzystając z dokumentacji (https://infocenter.nordicsemi.com/topic/sdk_nrf5_v16.0.0/lib_timer.html oraz https://infocenter.nordicsemi.com/topic/sdk_nrf5_v16.0.0/group__app__timer.html) zmodyfikuj oprogramowanie w taki sposób, aby stan na diodzie zmieniał się cyklicznie (np. co 100 ms, podpowiedź: należy zdefiniować timer, stworzyć go, uruchomić i w odpowiedni sposób obsłużyć).



### 2. Interfejs USB i czujnik temperatury

​	W module nRF52840 Dongle można przesyłać dane do komputera poprzez interfejs USB. Wykrywany jest on w systemie jako wirtualny port szeregowy. Otwórz projekt `lab2`, skompiluj go, a następnie zaprogramuj moduł. Następnie otwórz monitor portu szeregowego (np. putty) z odpowiednimi ustawieniami: baudrate 115200, 8 bitów danych, 1 bit stopu, bez bitu parzystości. Twoim oczom powinien ukazać się komunikat "Systemy wbudowane i mikrokontrolery!". //Spróbuj zmienić ten komunikat i sprawdź czy zauważasz zmiany//

​	Moduł nRF5840 Dongle posiada również wbudowany czujnik temperatury. W pliku `temperature.c` znajduje się funkcja `get_temperature()`, która służy do odczytu wartości temperatury. Korzystając z wiedzy zdobytej w poprzednim ćwiczeniu zmodyfikuj oprogramowanie w taki sposób, aby odczytująć regularnie wartość temperatury, zapalić diodę, jeśli wartość ta przekroczy wartość np. 25 °C. Wyślij również odpowiedni komunikat (np. "LED ON") poprzez USB.



### 3. Fototranzystor - obsługa przerwania z GPIO

​	GPIO (General Purpose Input/Output) czyli wejścia/wyjścia ogólnego przeznaczenia, są to piny służace do komunikacji pomiędzy elementami systemu (np. między mikrokontrolerem a urządzeniami peryferyjnymi). Takie wyprowadzenia mogą pełnić rolę zarówno wejść jak i wyjść, i jest to zazwyczaj właściwość konfigurowalna. Ważną własnością urządzeń korzystających z interfejsu GPIO jest możliwość zgłaszania przerwań.

​	Do naszego modułu nRF52840, a dokładniej do pinu TODO x.yy podłączony został fototranzystor. Fototranzystor to element optoelektroniczny, który pod wpływem światła zmienia napięcie na swoim wyjściu. Można zastosować go jako prosty detektor światła. 

​	Korzystając z wiedzy zdobytej w poprzednich ćwiczeniach oraz dokumentacji https://infocenter.nordicsemi.com/topic/sdk_nrf5_v16.0.0/hardware_driver_gpiote.html stwórz prosty czujnik oświetlenia. Program powinien działać w taki sposób, aby po jego uruchomieniu zapaliła się dioda, natomiast po zapaleniu światła (korzystając z interfejsu webowego) dioda zgasła. Zainicjalizuj pin, do którego podłączony jest fototranzystor jako wejście, skonfiguruj w odpowiedni sposób przerwanie oraz napisz funkcję obsługującą to przerwanie. Dla parametru konfiguracyjnego `pull` ustaw wartość `NRF_GPIO_PIN_PULLUP` (tak jak w sekcji *Initialization* dokumentacji).



### 4. Bluetooth Low Energy - Advertising

​	BLE jest popularnym standardem komunikacji bezprzewodowej. Najprostszym urządzeniem BLE jest Beacon wykonujący Advertising. Advertising jest sposobem urządzeń BLE na "przedstawienie" się nasłuchującym klientom. Projekt 'lab4 posiada już zaimplementowany advertising. Przetestuj go za pomocą ...TODO.

Advertising może być użyty również do przekazywania informacji. Ramka advertisingu posiada pole "manufacturer data", w którym można zawrzeć kilka bajtów informacji. Zawrzyj w tym polu wartość stanu czujnika oświetlenia (0 lub 1). Wartość ta ma się aktualizować za każdym razem gdy się zmieni. W polu company_identifier wpisz 0x0059.

Dokumentacja:
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsdk_nrf5_v16.0.0%2Fstructble__advdata__t.html

