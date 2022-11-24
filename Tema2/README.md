-voi folosi o variabila locala "indexare" in care voi retine numarul nodurilor din arbore 

        Main:
-pentru inceput verific de ce forma este primul argument pentru a sti peste cate sar pentru a putea lua numele fisierelor de input si output
-deschid fisierul de input cu drepturi de citire, stiind ca e fisier binar
-deschid fisierul de output cu drepturi de scriere
-se citeste mai intai tipul, stim ca este mereu P6
-citesc height si width care imi spun cate elemente de forma (R G B) sunt pe latime si pe lungime
-citesc valoare maxima pe care o poate lua culoarea
-ciesc fiecare pixel pe rand retinand in matricea de pixeli culorile
-convertesc din char in int factorul daca se doreste comprimare
    --Comprimare--
-creez arborele folosind CreareArbore
-pun indicii copiilor fiecarui nod folosind parcurgere
-alocam memorie pentru v
-punem elementele in v
-afisam numarul de frunze, numarul de noduri si toate elementele din v
-eliberam memoria luiv
-eliberam memoria din arbore folosind destroyTree

            QuadtreeNode
-structura Quadtree din cerinta
-contine si indicii fiecarui copil

            Pixel
-structura care retine culorile fiecarui pixel dat in input file

            Arbore
-arbore care contine nodul, cei 4 copii pe care ii are sau nu si indexxul foiecarui nod

            InitArbore
-alocam memorie pentru arbore si pentru fiecare node de forma QuadtreeNode
-punem ca default copiii NULL

            CreareArbore
-se initializeaza nodul din arbore
-se pune indexul si aria lui
-calculam media pentru fiecare culoare din acea arie, apoi punem valorile corespunzatoare in nod
-calculam meanul din arie dupa formula data
-verificam daca meanul convine factorului dat
-daca nu convine, imaginea va fi impartina in 4 parti, in functie de locatia fiecaruia

-am folosit "indexare" ca vector global pentru a retine corect si in ordine indii nodurilor, cu toate ca "creareArbore" este o functie recursiva

            Parcurgere
-parcurgem arborele si punem pentru fiecare nod indicii copiilor lui daca are si -1 daca nu are copii;

            Creare
-adaugam in v fiecare nod din arbore, cu tot ce contine el, la pozitia indicelui pe care in are

