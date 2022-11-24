#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define INFINITY 9999
int ct,contor_coloana;

void initMat(float **Mat, int n)            //functie de initializare a unei matrice de float cu "0"
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            Mat[i][j]=0;
}
void freeMatfloat(float **Mat, int n)       //functie de eliberare a memorie pentru o matrice de float
{
    for(int i=0; i<n; i++)
        free(Mat[i]);
    free(Mat);
}
void freeMatint(int **Mat, int n)           //functie de eliberare a memorie pentru o matrice de int
{
    for(int i=0; i<n; i++)
        free(Mat[i]);
    free(Mat);
}
void completareMat(float **Mat, int m)      //functie de completare a matricei grafului cu datele date in fisier
{
    int u,v;                                //nodul1, nodul2, costul parcurgerii dintre ele
    float w;
    for(int j=0; j<m; j++){                 //punem in matrice graficului costul dintre ficare nod
        scanf("%d%d%f", &u, &v, &w);
        Mat[u][v]=w;
    }
}
void initVectDep(int *vect_dep, int d)      //functie de completare a vectorului de depozite, cu depozitele date in fisier
{
    int indice;
    for(int i=0; i<d; i++){
        scanf("%d", &indice);
        vect_dep[i]=indice;
    }
}
void makeSolutii(int **solutii, int n)      //functie care imi umple matrice de solutii cu "-1"
{
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            solutii[i][j]=-1;
}
void Dijkstra(float **Mat,int n,int start, int end, float *total)       //algoritmul Dijkstra
{
    int ct1=0;                                        //contor care retine cate elemente are primul drum
    int ct2=0;                                        //contor care retine cate elemente are al doilea drum
    printf("%d\n", end);                              //afisez nodul la care trebuie sa ajung
    int *path=malloc(2*n*sizeof(int));                //aloc memorie pentru vectorul care va retine ambele drumuri
    int pas=0;                                        // avem 2 pasi, se fac 2 drumuri, dus si intors
    while(pas<2){
        float cost[n][n],distance[n],mindistance;     //pentru fiecare drum se va folosi algoritmul Dijkstra (luat pe pe sitteul din README)
        int pred[n];
        int visited[n],count,nextnode,i,j;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(Mat[i][j]==0)
                    cost[i][j]=INFINITY;
                else cost[i][j]=Mat[i][j];
        for(i=0;i<n;i++){
            distance[i]=cost[start][i];
            pred[i]=start;
            visited[i]=0;
        }
        distance[start]=0;
        visited[start]=1;
        count=1;
        while(count<n-1){
            mindistance=INFINITY;
            for(i=0;i<n;i++)
                if(distance[i]<mindistance&&!visited[i]){
                    mindistance=distance[i];
                    nextnode=i;
                }
            visited[nextnode]=1;
            for(i=0;i<n;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i]){
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
            count++;
        }
        if(pas==0){                             //daca este primul drum
            i=end;
            path[0]=i;                          //retin in path nodul la care trebuie sa ajung
            ct1++;
            printf("%.1f ", distance[i]);       //se afiseaza costul lui
            (*total)+=distance[i];
            j=i;
            while(j!=start){                    //retin restul nodurilor prin care am trecut de la start pana la end
                j=pred[j];
                path[ct1]=j;
                ct1++;
            }
            int copie=start;                    //se schimba startul cu endul pentru a face si drumul de intoarcere
            start=end;
            end=copie;
        }
        else if(pas==1){                        //daca este al doilea drum se va face acelasi lucru ca la pasul 1
            i=end;                              //dar nu mai e nevoie de inteschimbarea valorilor start si end 
            path[ct1]=i;
            ct2++;
            printf("%.1f\n", distance[i]);
            (*total)+=distance[i];
            j=i;
            while(j!=start){
                j=pred[j];
                path[ct2+ct1]=j;
                ct2++;
            } 
        }
        pas++;
    }
    for(int i=ct1-1; i>=0; i--)             //afisam elementele din ambele drumuri stiind ca am fost retinute in ordine inversa
        printf("%d ", path[i]);             //sarim peste ultimul element al drumului de intoarcere deoarece contine inca o data
    for(int i=ct1+ct2-2; i>=ct1; i--)       //valoare magazinului la care s-au facut drumurile
        if(i==ct1)
            printf("%d", path[i]);
        else
            printf("%d ", path[i]);
    printf("\n");
    free(path);                             //eliberez memoria alocata pentru "path"
}
void reverseMat(float **Mat, float **RevMat, int n)                 //functie care retine intr-o matrice transpusa unei alte matrice
{
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            RevMat[j][i]=Mat[i][j];
        }
    }
}
void DFS(float **Mat, int *visited,int i, int n,int *stack)         //functie care imi face DFS pe o matricea grafului
{
    int j;
    visited[i]=1;
    stack[ct]=i;
    ct++;                                                           //contorul a fost facut global pentru a putea retine indicele la care am  din stack
                                                                    //la care am ajuns (functia e recursiva si era mai usor de folosit o variabila globala)
    for(j=0;j<n;j++){
        if(Mat[i][j]!=0 && visited[j]==0)
            DFS(Mat,visited,j,n,stack);
    }
}
void DFS2(float **RevMat, int *visited, int n,int i,int **solutii)  //functie care imi face DFS pe matricea transpusa 
{                                                                   //in viseted, toate depozitele sunt vizitate (nu avem nevoie de ele)
    int j;
    visited[i]=1;
    solutii[ct][contor_coloana]=i;                                  //ct=nr sirului, contor_coloana=nr nodului din sir
    contor_coloana++;                                               //retinem in matricea re solutii toate sirurile
    for(j=0;j<n;j++){
        if(RevMat[i][j]!=0 && visited[j]==0)
            DFS2(RevMat,visited,n,j,solutii);
    }
}
void ordonareLinii(int **solutii, int n, int ct)                    //functie de ordonare a elementelor de pe fiecare linie
{
    int max;                                                        //in max vom retine numarul maxim de elemente importante de pe linie
    for(int i=0; i<ct; i++){
        max=0;
        for(int j=0; j<n-1; j++){
            if(solutii[i][j]!=-1){                                  //ordonam doar elementele importante, care nu sunt "-1"
                for(int h=j+1; h<n; h++){
                    if(solutii[i][j] < solutii[i][h]){              //ordonarea este descrescatoare pentru a ajuta afisarea
                        int aux=solutii[i][j];
                        solutii[i][j]=solutii[i][h];
                        solutii[i][h]=aux;
                    }
                }
                max++;
            }
        }
        if(max>contor_coloana)
            contor_coloana=max;
    }
}
void swapline(int **solutii, int i, int j, int contor_coloana)      //functie care schimba 2 linii intre ele
{
    for(int k=0; k<contor_coloana; k++){
        int aux=solutii[i][k];
        solutii[i][k]=solutii[j][k];
        solutii[j][k]=aux;
    }
}
void ordonareColoane(int **solutii, int ct, int contor_coloana)     //functie care imi ordoneaza crescator liniile intre ele 
{
    if(ct==1)
        return;
    for(int i=0; i<ct; i++){
        for(int j=i+1; j<ct; j++){
            if(solutii[i][0]>solutii[j][0]){                        //daca linia trebuie schimbata cu alta se va folosi functia de swapLine
                swapline(solutii,i,j,contor_coloana);
            }
        }
    }
}
void afisareSolutii(int **solutii, int ct, int contor_coloane)      //functie care imi afiseaza nodurile cerute
{                                                                   //umbla doar pe partea importanta din matrice si stim ca valorile sunt ordonate descrescator pe 
    for(int i=0; i<ct; i++){                                        //fiecare linie => citim liniile de la sfarsit la inceput si sarim peste elemntele "-1"
        for(int j=contor_coloana-1; j>=0; j--){
            if(solutii[i][j]!=-1){                                  
                if(j!=0){                                           // " " este pus doar daca urmeaza inca un element
                    printf("%d ", solutii[i][j]);
                }else printf("%d", solutii[i][j]);
            }
        }
        if(i!=ct-1)                                                 // "\n" este pus doar daca urmeaza inca un sir
            printf("\n");
    }
}

int main()
{
    int n,m,d;
    scanf("%d%d%d", &n, &m, &d);                //citim nr de noduri, nr de arce si de depozite
    float **Mat=malloc(n*sizeof(*Mat));         //aloc dinamic matricea grafului
    for(int i=0; i<n; i++)
        Mat[i]=malloc(n*sizeof(**Mat));
    int *vect_dep=malloc(d*sizeof(int));        //aloc un vector in care sa retin depozitele
    initMat(Mat, n);                            //umplu matrigea grafului cu 0
    completareMat(Mat, m);                      //pun in matrice consturile dintre noduri
    initVectDep(vect_dep,d);                    //pun depozitele in vectorul de depozite
    int nr_cerinte;
    scanf("%d", &nr_cerinte);                   //retin numarul cerintei ca sa stiu ce task fac
    char cerinta[3];                            //stiu ca numele taskului e "e1", "e2" sau "e3", stiu ce lungime are stringul
    for(int i=0; i<nr_cerinte; i++){            //for-ul este pentru a face cerinta de cate ori este ceruta
        scanf("%s", cerinta);                   //retin numele cerintei si vad ce cerinta se cere
        if(strcmp(cerinta,"e1")==0){                                        //daca este cerinta 1
            int depozit_marfa, k;                                           //retin depozitul si numarul de magazine care vor fi aprovizionate
            scanf("%d%d", &depozit_marfa, &k);
            int *n_deVizitat=malloc(k*sizeof(int));                         //aloc un vector pentru magazinele care vor fi vizitate
            for(int j=0; j<k; j++)                                          //pun in el indicii magazinelor
                scanf("%d", &n_deVizitat[j]);
            float total=0;                                                  //in total voi retine costul traseului
            for(int j=0; j<k; j++)                                          //pentru fiecare magazin folosesc "Dijkstra" pentru a afla drumul si costul
                Dijkstra(Mat,n,depozit_marfa,n_deVizitat[j], &total);
            printf("%.1f", total);                                          //afisez costul cu o zecimala
            if(i!=nr_cerinte-1)                                             //daca am facut numarul cerintei am grija sa nu pun "\n"
                printf("\n");
            free(n_deVizitat);                                              //eliberez memoria vectorului cu magasine de vizitat
        }else if(strcmp(cerinta,"e2")==0){
            float **RevMat=malloc(n*sizeof(*RevMat));               //aloca dinamic o matrice in care voi retine transpusa matricei grafului
            for(int i=0; i<n; i++)
                RevMat[i]=calloc(n,sizeof(**RevMat));
            int *visited=calloc(n,sizeof(int));                     //aloc dinamic un vector in vare voi contoriza daca am vizitat sau nu nod (il umplu cu 0)
            int *stack=malloc(n*sizeof(int));                       //si un vector in care voi retine nodurile dupa trecerea prin ele cu DFS
            reverseMat(Mat,RevMat,n);                               //retin in RevMat transpusa lui Mat
            DFS(Mat,visited,0,n,stack);                             //aplic DFS pe matricea grafului se retin ordinea nodurilor in "stack"
            for(int i=0; i<n; i++)                                  //umplu iar vectorul de vizitati cu 0
                visited[i]=0;
            for(int w=0; w<d; w++)                                  //spun ca am vizitat toate depozitele deoarece nu dorim sa fie afisate
                visited[vect_dep[w]]=1;
            int **solutii=malloc(n*sizeof(*solutii));               //aloc dinamic o matrice in care vom retine siruri de componente tari conexe
            for(int i=0; i<n; i++)
                solutii[i]=malloc(n*sizeof(**solutii));
            makeSolutii(solutii,n);                                 //o fac pe toata "-1", pentru a delimita nodurile de restul matricei
            ct=0;                                                   //"ct" imi va spune cate siruri de felul asta avem (ne ajuta sa umblam doar la liniile matricei
                                                                    //care contin componente tari conexe)
            for(int w=n-1; w>=0; w--){
                if(visited[stack[w]]==0){                           //pentru fiecare nod din stack care nu a fost vizitat, aplic iar DFS pe matrice transpusa, pt a
                    contor_coloana=0;                               //gasi sirurile de componente tari conexe
                    DFS2(RevMat,visited,n,stack[w],solutii);
                    ct++;
                }
            }
            printf("%d\n", ct);                                     //afisam cate siruri am gasit
            ordonareLinii(solutii,n,ct);                            //ordonam pe rand sirurile cu componente tari conexe din matricea de solutii
            ordonareColoane(solutii,ct,contor_coloana);             //apoi punem in ordine descrescatoare coloanele
            afisareSolutii(solutii,ct,contor_coloana);              //afisam componentele tari conexe in oridinea ceruta

            freeMatfloat(RevMat,n);                                 //eliberam memoria la tot ce am alocat      
            freeMatint(solutii,n);
            free(visited);
            free(stack);
        }else if(strcmp(cerinta,"e3")==0){
            printf("am ajuns 3\n");
            scanf("%s", cerinta);
        }
    }    
    freeMatfloat(Mat, n);                       //eliberez memoria folosita
    free(vect_dep);
    return 0;
}