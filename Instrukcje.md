# Wstęp 



 
Mikrokontroler jest urządzeniem programowalnym pod postacią układu scalonego. Układem scalonym nazywamy komponent elektroniczny scalający wiele elementów  w jednej obudowie. Mikrokontroler zawiera w sobie: 

- mikroprocesor 

- RAM 

- ROM (Flash lub EEPROM) 

- Peryferia 

Mikrokontrolery różnią się od typowego komputera PC: 

- ilością zasobów (RAM I ROM) 

- Architekturą procesora - PC uniwersalnie używają architektur x86 i x86-64, natomiast mikrokontrolery mogą mieć różne architektury procesorów. Często używane są procesory o architekturze ARM. 

- Mikrokontrolery wykorzystywane są do niskopoziomowych  (blisko sprzętu i elektroniki) zadań, w porównaniu z PC gdzie operujemy daleko od sprzętu, na wysokim poziomie abstrakcji. 

Mikrokontrolery są przystosowane do “bycia mózgiem” i sterowania urządzeń nie wymagających dużych mocy obliczeniowych (np. pralek). Urządzenia wykorzystujące mikrokontrolery są nazywane systemami wbudowanymi. 


 
Podczas laboratorium nauczymy się programowania mikrokontrolera firmy Nordic Smiconductor, a mianowicie NRF52840. Cechą szczególną tego mikrokontrolera jest dodatkowy rdzeń będący sterownikiem BLE (Bluetooth Low Energy) 
 
Mikrokontrolery są sprzedawane razem z devkitem, czyli pomocniczą płytką elektroniczną stanowiącą interfejs do programowania. 

 
Używany przez nas devkit to płytka PCA10059, która jest w formie Dongle USB, jak widać na rys. 1.  Mikrokontroler nrf52 to ten czarny kwadratowy układ scalony pośrodku płytki. Płytka zawiera też kilka peryferów takich jak przycisk reset, diody LED, czy antenę BLE, które będą naszym interfejsem z mikrokontrolerem. 
 
By zaprogramować płytkę będzie nam potrzebny również interfejs z naszym PC. W wypadku PCA10059 mamy do dyspozycji złącze USB. Oprócz programowania posłuży ono nam do komunikacji poprzez porty szeregowe, dzięki czemu będizemy mogli widzieć komunikaty w naszej konsoli na PC. 
Kod kompilować będziemy również na PC. Zabieg programowania z jednej architektury na drugą nazywamy kompilacją na krzyż (cross-compilation). Pomimo niskopoziomowej natury, mikrokontrolery będziemy programować używając wysokopoziomowego języka C. 

<p align="center">
  <img   src="./instrukcje_img/nRF52840_Dongle.png" "Title" >
</p>
<p align="center">
  Rys. 1: nrf52 PCA10059 USB Dongle
</p>


Żródła:
img https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-Dongle


# LAB1  

 

## GPIO 

Każdy element elektroniczny posiada określoną ilość wyprowadzeń (pinów), czyli miejsc do których możemy się podłączyć przewodami lub ścieżkami nadrukowanymi na płytce. Rys 3 przedstawia notę katalogową naszego mikrokontrolera, na której widać wszystkie jego piny. 

 <p align="center">
  <img   src="./instrukcje_img/leds.png" "Title"  >
</p>
<p align="center">
 *Rys. 2: Połączenie diod na płytce*
</p>
 

W układach cyfrowych przyjmujemy zazwyczaj dwa poziomy sygnałów które będą płynąć w naszym ukłądzie - 0 oraz 1; Tym wartościom przypisujemy określone poziomy napięć. Tu jedynka będzie miała wartość 3.3V, a zero będzie małym napięciem bliskim 0V. Te same jedynki i zera są zapisywane w rejestrach jako znane nam liczby w systemie binarnym. 

Najprostszym peryferium mikrokontrolera są piny GPIO (General Purpose Input Output). GPIO może być w jednym z dwóch trybów: trybie wejścia (input)), trybie wyjścia(output). 

W trybie wyjścia GPIO może podać na swój pin wartość 1 lub 0. W trybie wejścia moze odczytać te wartości i podać je nam na poziomie aplikacji. GPIO jest więc naszym elektronicznym interfejsem. 

W mikrokontrolerze nrf52 mamy do dyspozycji dwa sterowniki GPIO po ok. 32 piny każdy.  

 <p align="center">
  <img   src="./instrukcje_img/mc.png" "Title" >
</p>
<p align="center">
  *Rys. 3: Mikrokontroler i opisanymi pinami*
</p>
 

Na rys 3 są one opisane jako Px.yy , gdzie x to numer sterownika, a yy to numer pinu. 
 

## LED  

Podstawowym interfejsem w przypadku mikrokontrolerów są zazwyczaj LEDy. Więc nasze “Hello World” będzie polegać na zapaleniu diody.  
 
Dioda to element elektroniczny który cechuje sie tym, że przewodzi prąd tylko w jedną stronę. Rys. 2 i 3 zostąły wzięte z dokumentacji naszego devkitu (dostępne [tutaj](https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-Dongle/Download#infotabs) ). Na Rys 2. Zaznaczone są połączenia diod LED na płytce. Symbol VDD lub czasem VCC oznacza zasilanie, natomiast symbol GND lub symbol masy (rys.4), oznacza masę. Zasilanie to w naszym przypadku węzeł mający potencjał 3.3V, a masą węzeł o potencjale 0V. 

 <p align="center">
  <img   src="./instrukcje_img/masa.png" "Title" width=200  >
</p>
<p align="center">
  *Rys. 4: Symbol masy*
</p>


Gdybyśmy mieli baterię, potencjał 3.3V byłby “plusem” baterii a potencjał 0V, “minusem”. By mógł popłynąć prąd, musi istnieć różnica potencjałów. Tak więc, przez element znajdujący się między plusem i minusem baterii popłynie prąd, gdyż różnica potencjałów na obu końcach tego elementu wynosi 3.3V-0V=3.3V. 

Diody w naszym układzie są jednak podpięte do GPIO mikrokontrolera. Dioda LD1 jest podpięta do węzła LED1 (Rys. 2) który jest podpięty do GPIO P0.06. Tak więc ten pin GPIO steruje diodą LD1. Ustawiając stan GPIO na 1, dioda (z rezystorem do zmniejszenia prądu) jest między potencjałami 3.3V i 3.3V, więc prąd nie popłynie. Ustawiając GPIO na 0, dioda będzie między potencjałami 3.3V i 0V, więc prąd popłynie a dioda się zaświeci. 

 

 
 

 

 
 
 
 

Biblioteki dla naszego mikrokontrolera tworzą dla nas wysokopoziomowe API, dzięki czemu nie musimy mieć wiedzy o elektronice by zapalić diodę. Funkcje którymi możemy zmieniać stan diody  to np: bsp_board_led_on oraz bsp_board_led_off czy nawet bsp_board_led_invert. Funkjce te ustawią odpowiednie piny mikrokontrolera na odpowiedni stan. 

Przykładowo, funkcja włączająca LED,  bsp_board_led_on, ma następującą implementację. Funkcja nrf_gpio_pin_write ustawia dany pin na wartość drugiego argumentu. Zgodnie z naszą wcześniejszą dedukcją, LEDS_ACTIVE_STATE jest zdefiniowane na 0, bo pin GPIO musi mieć wartość zero by dioda sie zaświeciła. 

 

 

 

## Timer 

 
Timer jest podukładem odpowiedzialnym za mierzenie czasu.  

W najprostszej postaci składa się z licznika, czyli rejestru inkrementującego swoją wartość z każdym impulsem zegara układu.  
 
Setup timera zazwyczaj polega na ustawianiu alarmów. Gdy licznik dojdzie do odpowiedniej liczby ustawionej przez alarm, zostaje wywołane przerwanie. 
 
Nasz mikrokontroler działa jednowątkowo. Tymczasową “równoległość” możemy osiągnąć porpzez przerywania wykonywania kodu przerwaniami. Synchronizację niektórych poleceń możemy np zaimplementować używając przerwań timera. 
 

Źródła:
img: https://www.vhv.rs/download/bwTwho_ground-electrical-hd-png-download/ 

## Zadania 

​	W mikrokontrolerach timery służą do cyklicznego wykonywania różnych operacji, np. pobrania danych z czujników czy przesłania jakiejś informacji. W tym ćwiczeniu zadaniem będzie wykorzystanie timera, aby zmieniać stan na diodzie. 

​	W projekcie `lab1` dioda została już skonfigurowana i powinna zapalić się po wgraniu programu na moduł. Korzystając z dokumentacji (https://infocenter.nordicsemi.com/topic/sdk_nrf5_v16.0.0/lib_timer.html oraz https://infocenter.nordicsemi.com/topic/sdk_nrf5_v16.0.0/group__app__timer.html) zmodyfikuj oprogramowanie w taki sposób, aby stan na diodzie zmieniał się cyklicznie (np. co 100 ms, podpowiedź: należy zdefiniować timer, stworzyć go, uruchomić i w odpowiedni sposób obsłużyć).



# Lab2  

## Interfejs USB  

 
Programy konsolowe na PC są zazwyczaj uruchamiane w konsoli, gdzie widzimy tekstowe komunikaty pisane przez program Podobny interfejs możemy stworzyć z mikrokontrolerem używając portu szeregowego takiego jak USB czy UART. 

 

## Czujniki 

Czujniki lub sensory to elektroniczne przyrządy pomiarowe. Za pomocą różnych zjawisk fizycznych jesteśmy w stanie przetworzyć parametry środowiskowe na sygnały elektryczne, np określoną wartość temperatury na określoną wartość napięcia czy prądu. Wartość taka w formie napięcia może być już odczytana za pomocą mikrokontrolera.  
 
Nrf52 zawiera wewnętrzny czujnik temperatury. Wartość jego odczytywana jest z API dzięki czemu dostajemy bezpośrednio liczbę oznaczajacą temperaturę w stopniach C. 
 
## Zadania 

​	W module nRF52840 Dongle można przesyłać dane do komputera poprzez interfejs USB. Wykrywany jest on w systemie jako wirtualny port szeregowy. Otwórz projekt `lab2`, skompiluj go, a następnie zaprogramuj moduł. Następnie otwórz monitor portu szeregowego taskiem readUSB. Twoim oczom powinien ukazać się komunikat "Systemy wbudowane i mikrokontrolery!".

​	Moduł nRF5840 Dongle posiada również wbudowany czujnik temperatury. W pliku `temperature.c` znajduje się funkcja `get_temperature()`, która służy do odczytu wartości temperatury. Korzystając z wiedzy zdobytej w poprzednim ćwiczeniu zmodyfikuj oprogramowanie w taki sposób, aby odczytująć regularnie wartość temperatury, zapalić diodę, jeśli wartość ta przekroczy wartość np. 25 °C. Wyślij również odpowiedni komunikat (np. "LED ON") poprzez USB.


# Lab 3 

 

## Fototranzystor 

Tranzystory są elementami elektronicznymi które przewodzą prąd warunkowo. Warunkiem otwarcia kanału i przepływu prądu między głównymi pinami tranzystora jest zazwyczaj wartość napięcia lub prądu na dodatkowym pinie zwanym bramką lub bazą (zależnie od rodzaju tranzystora). W przypadku fototranzystora zamiast dodatkowego pinu mamy czujnik światła. Im większe natężenie światła padające na czujnik, tym większą przewodność ma fototranzystor. Podłączając fototranzystor do mikrokontrolera możemy stworzyć prosty detektor światła. 

 <p align="center">
  <img   src="./instrukcje_img/fototrans.png" "Title"  width=200 >
</p>
<p align="center">
  *Rys. 5: Symbol fototranzystora*
</p>
 
Źródła:
img: https://www.vhv.rs/viewpic/iJxRhbb_free-vector-electronic-phototransistor-pnp-circuit-phototransistor-symbol/ 
 
 

 
 

## Zaawansowana obsługa GPIO 

 
W przypadku diody w lab1 API nrf52 zajęło się wszystkimi niskopoziomowymi problemami za nas, by zapalić diodę. Jeśli chcemy wysterować lub odczytać inny element musimy napisać sterownik samemu. Do tego możemy użyć znanego już GPIO lub ADC  (Analog-Digital Converter), korzystając z niskopoziomowego API tych modułów. 

Podłączmy nasz fototranzystor podobnie jak diodę z lab1, lecz ustawmy GPIO w tryb wejścia. Wtedy zmiana stanu fototranzystora pod wpływem światła wznowi lub zatrzyma przepływ prądu. Jest do jednoznaczne z podłączeniem naszego pinu GPIO z napięciem 3.3V (gdy tranzystor przewodzi - tworzy połączenie między swoimi pinami), lub odłączeniem go od tego zasilania (gdy tranzystor nie przewodzi). Innymi słowy fototranzystor staje się swego rodzaju przełącznikiem. Za pomocą API GPIO jesteśmy w stanie odczytać wartość na pinie GPIO w naszej aplikacji jako jedynkę lub zero. 
 
Problem jaki się tu pojawia to jednowątkowość naszego mikrokontrolera. Odczyt wartości GPIO jest instrukcją, linią w kodzie, więc jeśli chcielibyśmy  wykonać jakąś operację gdy zmieni się wartość natężenia światła musielibyśmy czytać tą wartość w pętli i czekać aż się zmieni (polling). Pilnowanie tej wartości i robienie innych operacji nie wchodzi wtedy w grę. Na pomoc przychodzą nam przerwania - możemy ustawić je tak by zmiana wartości na pinie GPIO generowała przerwanie. Dzięki temu nasz program będzie mógł się zająć innymi operacjami podczas tego oczekiwania. 
 
## Zadania 
 
 ​	GPIO (General Purpose Input/Output) czyli wejścia/wyjścia ogólnego przeznaczenia, są to piny służace do komunikacji pomiędzy elementami systemu (np. między mikrokontrolerem a urządzeniami peryferyjnymi). Takie wyprowadzenia mogą pełnić rolę zarówno wejść jak i wyjść, i jest to zazwyczaj właściwość konfigurowalna. Ważną własnością urządzeń korzystających z interfejsu GPIO jest możliwość zgłaszania przerwań.

​	Do naszego modułu nRF52840, a dokładniej do pinu P0.20 podłączony został fototranzystor. Fototranzystor to element optoelektroniczny, który pod wpływem światła zmienia napięcie na swoim wyjściu. Można zastosować go jako prosty detektor światła. 

​	Korzystając z wiedzy zdobytej w poprzednich ćwiczeniach oraz dokumentacji https://infocenter.nordicsemi.com/topic/sdk_nrf5_v16.0.0/hardware_driver_gpiote.html stwórz prosty czujnik oświetlenia. Program powinien działać w taki sposób, aby po jego uruchomieniu zapaliła się dioda, natomiast po zapaleniu światła (korzystając z interfejsu webowego) dioda zgasła. Zainicjalizuj pin, do którego podłączony jest fototranzystor jako wejście, skonfiguruj w odpowiedni sposób przerwanie oraz napisz funkcję obsługującą to przerwanie. Dla parametru konfiguracyjnego `pull` ustaw wartość `NRF_GPIO_PIN_PULLUP` (tak jak w sekcji *Initialization* dokumentacji).

# Lab 4   

 

## BLE  

BLE (Bluetooth Low Energy) jest standardem komunikacji bezprzewodowej opracowanej przez Bluetooth SIG(Special Interest Group). Standard ten jest używany w systemach wbudowanych ze względu na niewielkie potrzeby obliczeniowe i zapotrzebowanie na energię, w stosunku do innych rozwiązań takich jak Wi-Fi.  
Warto pamiętać, że wszystkie popularne standardy komunikacji bezprzewodowej (Wi-Fi, BLE, Thread), korzystają z tego samego pasma częstotliwości (2.400-2.480GHz) . Trzeba więc uważać by wiele takich urządzeń nie działało w swoim otoczeniu, gdyż to łącze może się zapełnić. 


 <p align="center">
  <img   src="./instrukcje_img/blestack.png" "Title" >
</p>
<p align="center">
  *Rys. 6: Stos BLE. Zejdziemy najniżej do obsługi warstw GATT i GAP*
</p>

Podobnie jak protokół TCP/IP, BLE ma swój własny stos (rys.). Pisząc aplikacje oparte na BLE będziemy operować na dwóch warstwach stosu BLE: GAP i GATT.  

Nrf52 implementuje stos BLE jako osobny program zwany softdevice, który działa na osobnym dedykowanym rdzeniu. Aplikacja która korzysta z protokołu BLE, będzie komunikować się z softdevice za pomocą funkcji z przedrostkiem “sd_” np. sd_ble_gap_adv_start. 

 
 

 


 

 

## GAP (Generic Access Profile) 

 
Warstwa GAP definiuje jak urządzenia BLE mogą wchodzić w interakcje ze sobą. Odpowiada za zestawianie połączeń i Advertising. 

 GAP definiuje dwa rodzaje interakcji: 

1. połączeniowe, które definiuje role: 

- peripheral - rozgłasza się (advertising) i czeka na połączenia 

- central - skanuje w poszukiwaniu urządzeń peryferyjnych, i inicjuje połączenia z nimi 

2. bezpołączeniowe, które definiuje role: 

- broadcaster - tylko się rozgłasza (advertising) 

- observer - tylko skanuje 

W pierwszym zadaniu zajmiemy się interakcjami bezpołączeniowymi, a w drugim połączeniowymi. 

## Advertising 

Advertising jest sposobem przesyłania danych rozgłoszeniowo (broadcast) i “zareklamowania” urządzenia BLE  w sieci. Sam proces polega na synchronicznym wysyłaniu pakietu rozgłoszeniowego w eter, by pokazać się urządzeniom skanującym.  
Pakiet ten jest dość elastyczny jeśli chodzi o przesyłane w nim dane. Łącznie pakiet może mieć wielkość 31 oktetów (bajtów). Pakiet składa się z dowolnej ilości struktur o dowolnych rozmiarach. Przykładową daną może być nazwa urządzenia - im dłuższa tym więcej bajtów z 31 dostępnych zużyjemy. Podczas inicjalizacji advertisingu API częściowo wypełni te struktury za nas. Będziemy jednak mogli zdecydować które z możliwych rodzajów informacj itam zamieścimy. 

Urządzenia o roli broadcaster lub peripheral są zazwyczaj niewielkie i pracują na zasilaniu bateryjnym. Tego typu moduły nazywamy beaconami. 

 


 
 

Żródła: 

https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/bluetooth-smart-and-the-nordics-softdevices-part-1 
https://devzone.nordicsemi.com/nordic/short-range-guides/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial 
https://learn.adafruit.com/introduction-to-bluetooth-low-energy/gap 
https://punchthrough.com/how-gap-and-gatt-work/ 
img: https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsds_s140%2FSDS%2Fs1xx%2Fble_protocol_stack%2Fble_protocol_stack.html 

## Zadania 

BLE jest popularnym standardem komunikacji bezprzewodowej. Najprostszym urządzeniem BLE jest Beacon wykonujący Advertising. Advertising jest sposobem urządzeń BLE na "przedstawienie" się nasłuchującym klientom. Projekt lab4 posiada już zaimplementowany advertising. Przetestuj go za pomocą aplikacji test.py którą znajdziesz bezpośrednio na urządzeniu zdalnym. Najłatwiej ją włączyć za pomocą  tasku BLEtest w VSCode.

Advertising może być użyty również do przekazywania informacji. Ramka advertisingu posiada pole "manufacturer data", w którym można zawrzeć kilka bajtów informacji. Zawrzyj w tym polu wartość stanu czujnika oświetlenia (0 lub 1). Wartość ta ma się aktualizować za każdym razem gdy się zmieni się stan czujnika. W polu company_identifier wpisz 0x0059.



Dokumentacja:
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsdk_nrf5_v16.0.0%2Fstructble__advdata__t.html 

**UWAGA: Dla tego zadania użyj taska flashNordicSD**
 

 
 
 
 
 
 
 
 
 
 
 