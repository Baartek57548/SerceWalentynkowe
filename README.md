# SerceWalentynkowe

Finalna wersja pliku
Z okazji walentynek zbudowałem układ opierający się na płytce Digisparc attiny85, a mający za zadanie sterować 18 diodami ws2812b.
- w petli setup() znalazły się "szalone" efekty świetlne
- w pętli loop() spokojniejsze
Dużym ograniczeniem jest ilość pamięci mikroprocesora - 6012 bajtów. Pierwsza wersja przebiła tę wartość o 150%, dlatego została taka wersja z taką ilością kodu.

Użyte podzespoły: attiny85, pasek diod ws2812b, ładowarka tp4056, akumulator 3,7V LiPo 1000mAh, włącznik.
