# sJVM
MI-RUN 2014/2015 (zimní semestr)

- Autori -

David Kotalík (kotaldav), Jakub Veverka (veverja2)

- Zvolené zadání -

Naimplementovat VM pro Javovský bytecode.

- Implementační jazyk -

Naimplementováno v jazyce C++ verze 11 s využitím některých STL prvků (stack, vector)

- Struktura archivu -

root
| Makefile
| README.txt
|
├─── bin - přeložený spustitelný soubor virtualního stroje
|
├─── build - pomocná složka pro překladové soubory *.o
|
├─── include - složka s hlavičkovými soubory
|
├─── src - zdrojové soubory VM
|
└─── test - testovací Javovské soubory a jejich .class soubory

- Kompilace semestrální práce -

Překládá se pomocí GNU Makefile
V root složce příkazem: make

- Spuštění Virtuálního stroje -

Program bere jako argument jméno třídy, ve které se nachází metoda main (bez přípony .class)

./bin/jvm test/*

Příklad: ./bin/jvm test/AddNumbers

Další třídy a jejich soubory, které program potřebuje, si nahrává automaticky.
Testovací třídy kvůli správnému přístupu k souborům a jejich nahrání musí obsahovat na začátku: package test;
V programu jsou zapnuty podpůrné debug výstupy prováděných instrukcí. Pro nezobrazování těchto výstupu je prozatím nutné zakomentovat v souboru: include/debugMsg.hpp  následující definici: #define DEBUG

- Popis výsledné práce -

Vytvořili jsme omezenou verzi Java Virtual Machine. Jsou podporovány objekty, které jsou organizovány pomocí Object Table na haldě. Omezili jsme práci s operandy pouze na Integer, stringové řetězce a vstup a výstup do souboru. O uvolňování objektů z haldy se stará naimplementovaný garbage collector.

- Řešený problém v Javě -

SAT solver.

Spuštění SATu - ./bin/jvm test/SAT/SatDoubleIntInput

Příklad vstupu pro SAT je v souboru test/SAT/input.txt (programu zadáte jako input.txt, output soubor bude ve stejné složce). První řádek je počet proměnných ve formuli. Druhý řádek je již samotná formule.
Proměnné musí jít abecedně po sobě a operand s proměnnou by měla oddělovat mezera (kromě negace). Po a před případnými závorkami mezera nenásleduje, případně nepředchází.
Závorky jsou se mohou vnořovat jen do jedné úrovně.
