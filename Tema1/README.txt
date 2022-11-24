    In primul rand am facut cate o functie pentru:
-initializare lista (initList)
-initializare nod (initNode)
-distrugere lista (destroyList)
-afisare lista (print_list)
-adaugare nod (add_node) unde adaug nodurile de fiecare data la sfarsitul listei pentru a tine o ordine
-sortare in ordine crescatoare a listei dupa value (sort_list)
-convertirea unui numar din char in int (covert)

    Explicare main:
*Citesc:
        -numarul de noduri
        -apoi timestampul si valoarea fiecarui nod
*Argumentele:
    -Verific fiecare argument primit pentru a vedea carui task ii apartine. Pentru taskul cu delta se va lua
partea din argument care contine valoarea si apoi se converteste in int prin functia covert.
    -Voi lua si un contor ok, deoarece atunci cand se fac statisticile se schimba modul de afisare a rezultatelor.
    -Se va distruge lista folosita

    Explicare eliminare exceptii:
-creez o lista noua (new_list) pentru a pune valorile bune in ea 
-primele 2 valori se vor adauga automat in lista pentru ca ele nu pot fi verificate, la fel si uiltimele 2
-media se calculeaza medie=(a+b+c+d+e)/5
-deviatia=(a-medie)*(a-medie)+(b-medie)*(b-medie)+(c-medie)*(c-medie)+(d-medie)*(d-medie)+(e-medie)*(e-medie)
    deviatie=deviatie/5
    deviatie=sqrt(deviatie)

         a   b       c       d   e 
         |   |       |       |   |
        nod  |       |       |   |
            nod      |       |   |
                nod(curent)  |   |
                            nod  |
                                nod
-nodul se adauga doar daca nodul apartie [medie-deviatie ; medie+deviatie]
-se distruge lista vechi
-se returneaza lista noua

    Filtru median:
-initializez o lista noua
-voi citi noduri din 5 in 5, pentru a forma cate o lista mediana pentru fiecare
-se retine timestampul din mijlocul, se ordoneaza lista noua, apoi se ia valoare nodului din mijloc
-se adauga in lista nodul cu timestampul retinut si valoarea aflata
-se distruge lista veche
-se returneaza lista noua

    Filtru medie aritmetica:
-initializez o lista noua (new_list)
-vom trece prin fiecare nod, dar vom incepe cu al 3-lea nod din lista si ne vom opri la antepenultimul,
pentru a putea lua cate 5 valori: a,b,c,d,e cu care se va calcula de fiecare data media=(a+b+c+d+e)/5

         a   b       c       d   e 
         |   |       |       |   |
        nod  |       |       |   |
            nod      |       |   |
                nod(curent)  |   |
                            nod  |
                                nod

-se adauga in lista noua un nod cu timestampul lui c si valoarea mediei
-se distruge lista veche 
-se returneaza cea noua

    Uniformizare frecventa:
-se trece prin fiecare nod
-primul nu se poate verificat
-daca diferenta dintre timestampul nodului curent si nodul precedent este intre [100,1000], 
timestampul nodului curent se va transforma in media aritmetica dintre timestampul curent si cel precedent,
iar valoarea se va face tot prin media aritmetica a valorii curente si a valorii precedente
-se returneaza lista schimbata

    Completare date:
-initializez o lista noua
-primul element se adauga in lista deoarece nu poate fi verificat, la fel si ultimului
    (primele 2 si ultimele 2 elemente nu pot avea gap-uri deoarece calculul noilor valori necesita cel putin 3 elemente inainte 
        si dupa gap)
-daca diferenata dintre timestampul elementului curent si precedent este <= 1000, elementul convine, deci va fi adaugat
-pentru orice diferenta > 1000 se voi adauga noduri din 200 in 200 pana se completeaza lista
-voi initializa doua liste left si right:

   a           b           c    gap     e           f           g
   |           |           |            |           |           |
left[0]     left[1]     left[2]     right[2]    right[1]    right[0]
                           ^        nod_curent 
                ^       new[len-1]
    ^       new[len-2]
new[len-3]

                !!pentru lista left se vor lua valori din lista nou creata pentru a exclude posibilitatea ca inainte sa se 
            fi mai umplut un gap

-voi calcula w0, w1 si w2 cu o functie w (se vor calcula prin formula data in cerinta)
-se calculeaza cele doua sume din formula finala a valorilor nodurilor (dupa formula)
-se vor calcula timestampuri si valori pentru noduri pana cand golul se umple, la fiecare nod se fa calcula c-ul si valoarea
dupa formula din cerinta, se adauga toate nodurile bune si apoi, la final, nodul curent
-se distrug listele left si right dupa fiecare folosire
-se distruge lista veche 
-se returneaza lista noua


    Statistici:
-initializez o lista noua 
-se vor cauta intervale de forma [a,b], unde b=a+delta, si in care exista cel putin unul din nodurile listei
-se sorteaza lista, pentru a verifica ce intervale trebuie afisate
-a-ul de la primul interval se va lua primul numar intreg mai mic decat valoarea primului nod
-se cauta elemente in fiecare interval posibil, daca se gasesc elemente, se va afisa intervalul si numarul de
noduri din ele 
-se vor verifica intervale pana cand b va fi mai mare ca valoarea ultimului nod

