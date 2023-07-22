# Semestrální práce ZOO 2021

## POPIS PRÁCE
S Markem Glasem a Ondřejem Škrobem vytváříme hru na styl SimCity.
Uživatel dostane mapu o velikosti 20x20 polí s počáteční
silnicí. Na silnici musí navazovat i jeho vytvořená cesta.
U této cesty může postavit různé druhy domů. <br>
Druhy staveb jsou:
- silnice - ID: 0, potřebná pro propojení domů, cena: 100 XP
- dům - ID: 1, pocetObyvatel +5, cena: 200 XP
- park - ID: 2, spokojenost +2 %, cena: 400 XP
- policie - ID: 3, cena: 450 XP
- - plus 5 pracovnich mist 
- - 1 stanice na 10 domů, jinak spokojenost -2 %
- ZZS, ID: 4, cena: 450 XP
- - plus 6 pracovnich mist
- kultura, ID: 5, cena: 300 XP
  - spokojenost +3 % za každou kulturní budovu
- hasiči, ID: 6, cena: 450 XP
  - plus 6 pracovnich mist 
  - 1 stanice na 20 budov, jinak spokojenost -1 %
- továrna, ID: 7, cena: 150 XP
- - plus 30 pracovních mist
- obchod, ID: 8, cena: 150 XP
  - plus 8 pracovnich mist
  - 1 obchod na 25 budov (jedná se o velký obchod), jinak -5 % spokojenost 
- elektrárna, ID: 9, cena: 150 XP
- vodárna, ID: 10, cena: 150 XP

Ve městě budeme hlídat počet obyvatel a spokojenost.
S postupem času budeme hlídat i nezaměstnanost, ale to
až ve vyšších levelech. Naše hra bude mít ~~20~~ 11 levelů.

Hráč bude mít ve městě pozici starosty. Bude sbírat XP,
které se bude počítat ze spokojenosti, počtu obyvatel a nezaměstnanosti.
Za toto XP bude moct stavět vše, co je možné.

Budovy bude možné i bourat za poloviční cenu jejich stavby.

## ÚKOLY PRO NÁS
Anička
- komunikaci s uzivatelem
- switch puvodni
- prevod z intu na druh
- aplikovat do vzpisu ve meste Zobrazmesto()

Marek
- ~~setspokojenost vymysli sam~~ dulezite spokojenosti zavedeny, podle me takhle staci
- pole v budovach

Ondra
- trida lvl
- napojeni do hry
- kontrola lvl
- setpocetObyvatel a setNezamestnanost