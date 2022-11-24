#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int timestamp;
    double value;
    struct node *next;
    struct node *prev;
}node_t;

typedef struct list{
    node_t *head;
    node_t *tail;
    int len;
}list_t;

list_t *initList(){                                 //functie de initializare lista
    list_t *list=malloc(sizeof(list_t));
    list->head=NULL;
    list->tail=NULL;
    list->len=0;
}
node_t *initnode(int timestamp, double value){      //functie de initializare nod
    node_t *node=malloc(sizeof(node_t));    
    node->timestamp=timestamp;
    node->value=value;
    node->next=NULL;
    node->prev=NULL;
}
void destroyList(list_t *list){                     //functie de distrugere lista
    node_t *aux;
    while(list->len > 0){
        aux=list->head;
        list->head=aux->next;
        free(aux);
        list->len--;
    }
    free(list);
}   
void print_list(list_t *list){                      //functie de printare lista
    node_t *nod=list->head;
    printf("%d\n", list->len);
    while(nod !=NULL){
        printf("%d %.2lf\n", nod->timestamp, nod->value);
        nod=nod->next;
    }
}
node_t *add_node(list_t *list, int a_timestamp, double b_value){       //functie de adaugare nod la finalul listei
    if(list->len==0){
        node_t *node=initnode(a_timestamp,b_value);
        list->head=node;
        list->tail=node;
        list->len++;
    }else{
        node_t *node=initnode(a_timestamp,b_value);
        node->prev=list->tail;
        list->tail->next=node;
        list->tail=node;
        list->len++;
    }
}
list_t* eliminare_exceptii(list_t *list)
{
    node_t *nod_vechi=list->head->next->next;                          //se incepe cu nodul de pe pozitia 2
    list_t *new_list=initList();                                      //se creeaza noua lista
    add_node(new_list,list->head->timestamp,list->head->value);                 //primele 2 noduri din lista convin doarece ele 
    add_node(new_list,list->head->next->timestamp,list->head->next->value);     //nu pot fi verificate prin metoda data
    int nr_elemente=list->len;
    double medie=0;
    double deviatie=0; 
    for(int i=2; i<nr_elemente-2; i++){                 //   |                           //asa sunt alese valorile
        double a=nod_vechi->prev->prev->value;          //  nod   |
        double b=nod_vechi->prev->value;                //       nod       |
        double c=nod_vechi->value;                      //            nod(curent)  |
        double d=nod_vechi->next->value;                //                        nod    |
        double e=nod_vechi->next->next->value;          //                              nod
                                    //se calculeaza media si deviatia
        medie=(a+b+c+d+e)/5;
        deviatie=(a-medie)*(a-medie)+(b-medie)*(b-medie)+(c-medie)*(c-medie)+(d-medie)*(d-medie)+(e-medie)*(e-medie);
        deviatie/=5;
        deviatie=sqrt(deviatie);
                                    //nodul va fi adaugat in lista doar daca apartine intervalului cerut
        if(c>=medie-deviatie && c<=medie+deviatie){
            add_node(new_list,nod_vechi->timestamp,nod_vechi->value);
        }
        nod_vechi=nod_vechi->next;
    }
    add_node(new_list,list->tail->prev->timestamp,list->tail->prev->value);
    add_node(new_list,list->tail->timestamp,list->tail->value);
    destroyList(list);                               //distrugere lista folosita
    return new_list;                                //returnare lista creata
}
list_t* sort_list(list_t *mediana){                                      //functie de sortare a valorilor din lista
    for(node_t *aux=mediana->head; aux->next != NULL; aux=aux->next){
        for(node_t *aux2=aux->next; aux2 != NULL; aux2=aux2->next){
            if(aux->value > aux2->value){
                double auxiliar=aux->value;
                aux->value=aux2->value;
                aux2->value=auxiliar;
            }
        }
    }
    return mediana;
}
list_t* filtru_median(list_t *list){
    list_t *new_list=initList();                               //se initializeaza noua lista
    node_t *node=list->head;                                   //se incepe cu primul nod
    for(int i=0;i<list->len-5+1; i++){                      //forul se opreste cu 4 elemente inainte de final, deoarece
                                                              //ele vor mai putea intra in alte liste mediane 
        list_t *mediana=initList();                         //se initializeaza o lista intermediara
        node_t *aux=node;
        int timestamp_element=node->next->next->timestamp;  //se retine timestampul elementului din mijlocul listei
                                                              //inainte de sortare
        for(int k=0; k<5; k++){                             //adauga intr-o lista intermediara nodul curent si
            add_node(mediana,aux->timestamp,aux->value);     //urmatoarele 4
            aux=aux->next;
        }
        mediana=sort_list(mediana);                         //sortam lista mediana
        add_node(new_list,timestamp_element,mediana->head->next->next->value);     //adaugam nodul cerut in noua lista
        node=node->next;                                                            //cu timestampul retinut initial
        destroyList(mediana);                               //distrugem lista mediana
    }
    destroyList(list);                                      //distrugem lista cu care s-a lucrat
    return new_list;                                        //afisam lista creeata
}
list_t* filtru_medie_aritmetica(list_t* list){              //aceasta functie merge cu aceasi gandire ca la filtrul median
    node_t *nod_vechi=list->head->next->next;                 //doar ca se vor adauga in lista noua noduri cu timestempul 
    list_t *new_list=initList();                              //nodului curent si valuarea mediei dintre cele 5 noduri alese
    int nr_elemente=list->len;                                //dupa schema de mai jos
    double medie=0;
    for(int i=2; i<nr_elemente-2; i++){              //  |
        double a=nod_vechi->prev->prev->value;       // nod  |
        double b=nod_vechi->prev->value;             //     nod      |
        double c=nod_vechi->value;                   //         not(curent)  |
        double d=nod_vechi->next->value;             //                     nod  |
        double e=nod_vechi->next->next->value;       //                         nod
        medie=(a+b+c+d+e)/5;
        add_node(new_list,nod_vechi->timestamp,medie);
        nod_vechi=nod_vechi->next;
    }
    destroyList(list);
    return new_list;
}
list_t* uniformizare_frecventa(list_t *list){
    node_t *nod_vechi=list->head->next;                     //se incepe cu nodul de pe pozitia 1, deoarece la primul nu 
                                                              //se poate face verificare
    while(nod_vechi != NULL){
        int difference=nod_vechi->timestamp - nod_vechi->prev->timestamp;       //se afla diferenta de milisecunde
        if(difference>=100 && difference<=1000){                                //daca apartine intervalului dat, se schimba
            nod_vechi->timestamp=(nod_vechi->timestamp + nod_vechi->prev->timestamp)/2;     //timestampul si valoare cu cele
            nod_vechi->value=(nod_vechi->value + nod_vechi->prev->value)/2;                 //calculate prin formula
        }
        nod_vechi=nod_vechi->next;
    }
    return list;                                            //se returneaza lista modificata
}
double w(double i, double k){                               //functie pentru w-uri (respecta formula din cerinta)
    double rezultat=0;
    double sum0 = 0;
    double sum1 = 1/(k-1);
    sum1 = sum1*sum1*0.9;
    double sum2 = 2/(k-1);
    sum2=sum2*sum2*0.9;
    double numitor = 0.3 + sum0 + sum1 + sum2;
    if(i==0){
        double numarator = sum0 + 0.1;
        rezultat = numarator/numitor;
    }
    if(i==1){
        double numarator = sum1 + 0.1;
        rezultat = numarator/numitor;
    }
    if(i==2){
        double numarator = sum2 + 0.1;
        rezultat = numarator/numitor;
    }
    return rezultat;
}

list_t* completare_date(list_t *list){
    node_t *node=list->head;
    list_t *new_list=initList();                                //initializez o lista noua
    add_node(new_list,node->timestamp,node->value);             //primul nod nu poate fi gresit, deci se adauga in noua lista
    node=node->next;
    while(node != NULL){
        if(node->timestamp - node->prev->timestamp <= 1000)     //daca deferenta de timestamp e <= 1000 este bun, deci se adauga in lista
            add_node(new_list,node->timestamp,node->value);
        else{
            list_t *left_list = initList();                     //initializare lista pentru left si right
            list_t *right_list = initList();

            add_node(left_list,new_list->tail->prev->prev->timestamp,new_list->tail->prev->prev->value);        //in left se vor adauga noduri din lista noua
            add_node(left_list,new_list->tail->prev->timestamp,new_list->tail->prev->value);
            add_node(left_list,new_list->tail->timestamp,new_list->tail->value);
            
            add_node(right_list,node->next->next->timestamp,node->next->next->value);                    //in right urm noduri din lista veche
            add_node(right_list,node->next->timestamp,node->next->value);
            add_node(right_list,node->timestamp,node->value);

            double w0=w(0,3);                                   //se calculeaza w-urile dupa formula
            double w1=w(1,3);
            double w2=w(2,3);

            double sum1 = left_list->head->value * w0 + left_list->head->next->value * w1 + left_list->tail->value * w2;        //se calculeaza sumele din formula finala
            double sum2 = right_list->head->value * w0 + right_list->head->next->value * w1 + right_list->tail->value * w2;       //de value
            
            int new_timestamp=node->prev->timestamp + 200;                                          //se ia urmatoarea valoare posibila de timestamp
            while(new_timestamp < node->timestamp){
                double numarator = new_timestamp - left_list->tail->timestamp;                      
                double numitor = right_list->tail->timestamp - left_list->tail->timestamp;
                double c = numarator/numitor;                                                       //se calculeaza c-ul pentru fiecare nod dupa formula
                double new_value = (1-c)*sum1 + c*sum2;                                             //se calculeaza noua valoare
                add_node(new_list,new_timestamp,new_value);                                         //se adauga nodul cu valorile aflate

                new_timestamp+=200;
            }
            add_node(new_list,node->timestamp,node->value);                                         //se adauga ultimul nod din lista veche in cea noua (el nu poate sa aiba gap
                                                                                                      //deoarece nu se vor putea calcula valorile)-este acelasi caz ca si la primul eleement
            destroyList(left_list);                                                                 //se distrug listele left si right la fiecare folosire
            destroyList(right_list);
        }
        node=node->next;
    }
    destroyList(list);                                          //se distruge lista veche
    return new_list;                                            //se returneaza lista noua
}

void statistici(list_t *list, int delta){
    list=sort_list(list);                    //incep prin a sorta lista
    int a=floor(list->head->value);          //setez margine inferioara pentru interval luand intregul mai muc decat
                                                //primul nr din lista
    node_t *nod=list->head;
    int ct=0;                                //imi iau un contor care sa retina cate elemente apartin unui interval
    int b=a+delta;                           //setez marginea superioara a intervalului
    while(nod != NULL){                      //parcurg fiecare nod
        if(nod->value <=b){
            ct++;                            //cand un not apartine intervalului ct creste
        }else{
            if(ct>0)
                printf("[%d, %d] %d\n", a, b, ct);       //daca exista nr in interval, il afisam
            ct=0;                                        //ct revine 0
            while(nod->value > b){                       //cautam urmatorul interval in care exista nod
                a=b;
                b=a+delta;
            }
            ct++;                            //adaugam nodul curent (care stim ca apartine intervalului)
        }
        nod=nod->next;
    }
    if(ct>0)                                             //verificam daca a ramas vreun nod necontorizat la
        printf("[%d, %d] %d\n", a, b, ct);                  //iesire din while
}
int convert(char *arg){                             //functie de convertire a unui nr in char 
    int n=strlen(arg);                                //intr-un nr int
    int numar=0;
    for(int i=0; i<n; i++)
        numar=numar*10+(arg[i]-'0');
    return numar;
}
int main( int argc, char *argv[]){
    int n,a_timestamp;
    scanf("%d", &n);                                //citim numarul de noduri care va fi dat
    double b_value;
    list_t *list=initList();
    for(int i=0; i<n; i++){                         //adaugam nodurile in lista
        scanf("%d %lf", &a_timestamp, &b_value);
        add_node(list,a_timestamp,b_value);
    }
    int ok=0;
    for(int i=1; i<argc; i++){                      //cautam si apelam functia corespunzatoare argumentului dat
        if(strcmp(argv[i]+2,"e1")==0)
            list=eliminare_exceptii(list);
        else if(strcmp(argv[i]+2,"e2")==0)
            list=filtru_median(list);
        else if(strcmp(argv[i]+2,"e3")==0)
            list=filtru_medie_aritmetica(list);
        else if(strcmp(argv[i]+2,"u")==0)
            list=uniformizare_frecventa(list);
        else if(strcmp(argv[i]+2,"c")==0)
            list=completare_date(list);
        else if(strstr(argv[i]+2,"st") != NULL){
            ok=1;
            int delta=convert(argv[i]+4);           //convertim nr dat in argument, din char in int;
            statistici(list,delta);
        }
    }
    if(ok==0)                           //daca nu s-a facut task-ul "statistici", care afiseaza doar intervale
        print_list(list);                 //se va afisa lista finala
    destroyList(list);
    return 0;
}