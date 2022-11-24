        ----- Variabile Globale -----
- am 2 variabile globale care ajuta la rezolvarea taskurilor

        ----- Main -----
- aloc dinamic "matricea grafului" si "un vector ce contine depozitele"
- "matricea grafului" va fi umpluta cu 0 apoi veor fi puse costurile dintre noduri
- in "vectorul cu depozite" se vor retine depozitele
- retin nr de noduri, nr de arce, nr de depozite si numarul de cerinte
- aloc static un string pentru nemele taskului, deoarece stiu ca e de forma "e1", "e2 sau "e3", ii stiu lungime
- apoi fac o bucla pentru a face cerintele de cate ori se cere
    * In for:
- citesc numele cerintei si vad care cerinta este

- la final o sa eliberez memoria folosita (Matricea grafului si vectorul de depozite)

    * Pentru taskul 1:
- retin depozitul dat si numarul de magazine care trebuie vizitate
- aloc dinamic un vector in care retin magazinele care vor trebui vizitate si pun indicele lor in el
- in variabila "total" retin costul total al fiecarui drum (drumul fiind dus-intors)
- pentru fiecare magazin voi folosi algoritmul "Dijkstra" pentru a afla drumul si costul lui (drumul este de forma: depozit->magazin->depozit)
- apoi afizez costul total si am grija sa pun "\n" doar daca urmeaza sa fie afisata rezolvarea unei alte cerinte
- apoi eliberez memoria alocata vectorului de magazine de vizitat

    * Pentru taskul 2:
- voi aloca dinamic:
    - "RevMat" in care retin transpusa metricei grafului
    - "visited" un vector care imi contorizeaza ce noduri am vizitat care va fi umpluta inainte de fiecare folosire cu "0"
    - "stack" in care voi retine nodurile dupa parcurgerea DFS-ului
    - "solutii" o matrice de marimea matricei grafului, care va fi umpluta initial cu "-1" si in care se vor pune sirurile de componente tari conexe gasite, pe fiecare linie, in ordinea gasirii (practic va contine componentele tari conexe si in rest va fi "-1", pentru a stii ca restul elementelor sunt neimportante)
- aplic DFS pe matricea grafului si retin nodurile in ordinea trecerii prin ele in "stack"
- dupa, deoarece o sa folosesc inca o data vectorul de vizitari, il umplu iar cu "0" si am grija sa retin ca vizitate toate depozitele (deoatrece nu vreau sa apara in sirul de componente tari conexe)
- variabila "ct" ma va ajuta sa retin cate siruri de componente avem (ca sa folosesc doar partea importanta din matricea de solutii)
- aplic inca o data DFS, pentru fiecare nod in stack care nu este vizitat, pentru a afla sirurile de care avem nevoie si le punem in matricea solutii
- variabila "contor_coloana", care e folosita prin functiile folosite, va retine numarul maxim de elemente din sir (motivul este acelasi ca si la "ct", de a folosi doar parte importanta din matricea de solutii, nu pe toata)
----------- ex:
            _____________
            | 8 -1 -1 -1 |-1 -1 -1 -1 
            | 5  2  1 -1 |-1 -1 -1 -1           ->voi folosi doar parte incadrata din toata
            | 7  4  3  6 |-1 -1 -1 -1             matricea de solutii
            ______________
             -1 -1 -1 -1  -1 -1 -1 -1
             -1 -1 -1 -1  -1 -1 -1 -1
             -1 -1 -1 -1  -1 -1 -1 -1
             -1 -1 -1 -1  -1 -1 -1 -1
             -1 -1 -1 -1  -1 -1 -1 -1

- afisez numarul de siruri (randuri folosite din matrice)
- ordonez elementele de pe fiecare linie in ordine descrescatoare (ca sa sar mai usor peste "-1", la aceste ordonari "contor_coloana" retine numarul maxim de noduri, deci dupa terminarea nodurilor, pe unele randuri vor fi "-1")
- dupa ordonez liniile
- afisez doar ce ma intereseaza din "solutii"
- eliberez memoria folosita

        ----- initMat -----
- fuctie care umple o matrice un elemente de tip float cu "0"

        ----- freeMatfloat -----
- functie care elibereaza memoria alocata a unei matrice cu elemente de tip float

        ----- freeMatint -----
- functie care elibereaza memoria alocata a unei matrice cu elemente de tip int

        ----- completareMat -----
- functie care imi completeaza matricea grafului cu costurile dintre noduri

        ----- initVectDep -----
- functie care imi pune in vectorul de depozite depozitele date in fisier

        ----- makeSolutii -----
- functie care imi umple matrice de solutii cu "-1"

        ----- Dijkstra -----
- De aici am luat algoritmul Dijkstra: https://www.thecrazyprogrammer.com/2014/03/dijkstra-algorithm-for-finding-shortest-path-of-a-graph.html
- am 2 contoare "ct1" care retine cate elemente are primul drum si "ct2" care retine cate elemente are al doilea drum, ele fiind depozit->nod respectiv nod->depozit
- aloc dinamic un vector "path" in care vom retine acste drumuri
- afisez nodul la care trebuie sa ajung
- avem doi pasi, practic 2 drumuri, dus si intors => voi face de 2 ori algoritmul de mai sus
- singura diferenta este ca la ambii pasi se va retine main intai nodul in care se ajunge si dupa nodurile prin care s-a trecut (practic se va retine drumul in ordine inversa, asa in face algoritmul)
- la fiecare pas se afiseaza si costul drumului facut
- la primul pas se vaor schimba si startul cu endul intre ele pentru a putea face si drumul de intoarcere

ex tast 0;
            3 0 0 3 -> va fi retinut in path
            3 0 -> drumul dus            | ambele vor fi retinute in ordine inversa
            0 3 -> drumul intors         |

- afisarea se va face pe rand, mai intai drumul dus, apoi intors, ambele in ordine inversa, am grija sa sar peste eltimul element al celui de-al doilea drum deoarece se va retin inca o data depozitul
            3 0 0 3
                  ^
                  |_ ex

- eliberez memoria folosita pentru path
        ----- reverseMat -----
- functie care imi face transpusa unui matrici
- face transpusa lui Mat si o retine in RevMat

        ----- DFS -----
- aplic algoritmul de DFS si retin in "stack" ordinea in care trec prin noduri
- "ct", aici, imi va retine indicele din stack la care am ajuns, pentru a pune bine nodurile prin care trec

        ----- DFS2 -----
- aplic iar algoritmul de DFS doar ca pe matricea transpusa 
- de data asta vectorul de vizitati care toate depozitele vizitate, deci se va sari peste el
- in i va fi nodul din care se incepe DFS-ul
- "ct" va retine al catelea element din sir este
- "contor_coloana" va retine al catelea sir este
- toate sirurile obtinute vor si retinute in matricea de solutii

        ----- ordonareLinii -----
- functie care ordoneaza elementele importante din matrice de solutii
- sortez descrescator elementele importante, deoarece (eu am luat matricea de n*n => e foarte mare => vor fi multe elemente neimportante, adica "-1" => va usura afisarea lor)
- voi ordona pana cand ajung la "-1"
- la final contor_coloana va retine valoarea lui max

        ----- ordonareColoana -----
- fuctie care imi ordoneaza crescator liniile importante din matrice 
- pentru schimbarea de linii se va folosi functia "swapLine"

        ----- swapline -----
- functie care da swap la 2 linii dintr-o matrice

        ----- afisareSolutii -----
- functiile care imi afiseaza nodurile cerute
- in primul rand in matricea de culutii lucram doar pe partea cu valori importante (cadranul de mai sus)
- in cadran avem ordonate descrescator nodurile pentru ca la inceput de linie sa fie valorile urmad dupa -1
- vom citi fiecare linie de la sfarsit la inceput si vom sari peste elementele "proaste"
- am grija sa pun " " doar daca mai urmeaza un element si "\n" daca mai urmeaza un sir
