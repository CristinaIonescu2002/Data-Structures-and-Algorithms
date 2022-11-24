#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int indexare=0;
int nr_frunze=0;

typedef struct QuadtreeNode {                                               //structura de QuadtreeNode
    unsigned char blue, green, red;
    uint32_t area;
    int32_t top_left, top_right;
    int32_t bottom_left, bottom_right;
} __attribute__((packed)) QuadtreeNode;

typedef struct Pixel{                                                       //structura Pixel care contine culorile in ordinea RGB cu ajutorul careia vom retine in matricea de pixeli culorile
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} __attribute__((packed)) Pixel_p;

typedef struct Arbore{                                                      //arbore care contine nodul, copii si indexul
    QuadtreeNode *node;
    struct Arbore *copil1;
    struct Arbore *copil2;
    struct Arbore *copil3;
    struct Arbore *copil4;
    int index;
}Arbore;

Arbore *InitArbore()                                                        //initializare arbore
{
    Arbore *arbore=malloc(sizeof(Arbore));
    QuadtreeNode *node=malloc(sizeof(QuadtreeNode));
    arbore->node = node;
    arbore->copil1=NULL;
    arbore->copil2=NULL;
    arbore->copil3=NULL;
    arbore->copil4=NULL;
}
Arbore *creareArbore(Pixel_p **matrice, int lungime, int colt_st_h, int colt_st_w, int colt_dr_h, int colt_dr_w, int factor)
{
    Arbore *arbore=InitArbore();                                            //initializam nodul din arbore
    arbore->index=indexare;                                                 //retinem in el indexarea corespunzatoare si aria
    arbore->node->area=lungime*lungime;

    unsigned long long sum_r, sum_g, sum_b;                                 //calculez mediile pentru red, green si blue
    sum_r=0;
    sum_g=0;
    sum_b=0;
    for(int i=colt_st_h; i<colt_dr_h; i++){
        for(int j=colt_st_w; j<colt_dr_w; j++){
            sum_r+=matrice[i][j].red;
            sum_g+=matrice[i][j].green;
            sum_b+=matrice[i][j].blue;
        }
    }
    sum_r=sum_r/arbore->node->area;
    sum_g=sum_g/arbore->node->area;
    sum_b=sum_b/arbore->node->area;
    arbore->node->red=sum_r;                                                //apoi retinem in nod acele medii
    arbore->node->green=sum_g;
    arbore->node->blue=sum_b;
    unsigned long long mean=0;
    for(int i=colt_st_h; i<colt_dr_h; i++){                                                                         //calculez meean-ul cerut in cerinta, dupa foemula
        for(int j=colt_st_w; j<colt_dr_w; j++){
            mean=mean+(arbore->node->red-matrice[i][j].red)*(arbore->node->red-matrice[i][j].red);
            mean=mean+(arbore->node->green-matrice[i][j].green)*(arbore->node->green-matrice[i][j].green);
            mean=mean+(arbore->node->blue-matrice[i][j].blue)*(arbore->node->blue-matrice[i][j].blue);
        }
    }
    mean/=3;
    mean/=arbore->node->area;
    if(mean>factor){                                                                                                //daca nu s-a ajuns la factorul cerut se va impartii imaginea in 4 copii
        indexare++;                                                                                                                               //se va creste mereu indicele pentru a pune 
        arbore->copil1=creareArbore(matrice,lungime/2,colt_st_h,colt_st_w,colt_st_h+lungime/2,colt_st_w+lungime/2, factor);                         //la fiecare indicele bun
        indexare++;
        arbore->copil2=creareArbore(matrice,lungime/2,colt_st_h,colt_st_w+lungime/2,colt_st_h+lungime/2,colt_st_w+lungime, factor);
        indexare++;
        arbore->copil3=creareArbore(matrice,lungime/2,colt_st_h+lungime/2,colt_st_w+lungime/2,colt_st_h+lungime,colt_st_w+lungime, factor);
        indexare++;
        arbore->copil4=creareArbore(matrice,lungime/2,colt_st_h+lungime/2,colt_st_w,colt_st_h+lungime,colt_st_w+lungime/2, factor);
    }
    return arbore;
}
void parcurgere(Arbore **root){                                                //parcurgem arborele si retinem pentru fiecare nod indicii copiilor, daca are
    if((*root)->copil1!=NULL){                                                 //daca nu are retinem -1
        (*root)->node->top_left=(*root)->copil1->index;
        (*root)->node->top_right=(*root)->copil2->index;
        (*root)->node->bottom_right=(*root)->copil3->index;
        (*root)->node->bottom_left=(*root)->copil4->index;
        parcurgere(&(*root)->copil1);
        parcurgere(&(*root)->copil2);
        parcurgere(&(*root)->copil3);
        parcurgere(&(*root)->copil4);
    }else{
        nr_frunze++;
        (*root)->node->top_left=-1;
        (*root)->node->top_right=-1;
        (*root)->node->bottom_right=-1;
        (*root)->node->bottom_left=-1;
    }
}
void creare(Arbore *root, QuadtreeNode **v){                                    //adaugam in v fiecare nod din arbore, cu tot ce contine el                
                                                                                //la pozitia din vector a indicelui pe care il are
    (*v)[root->index]=*root->node;
    if(root->copil1!=NULL){
        creare(root->copil1,v);
        creare(root->copil2,v);
        creare(root->copil3,v);
        creare(root->copil4,v);
    }

}
void destroyTree(Arbore **root)                                                 //eliberare memorie din Arbore
{
    if((*root)->copil1!=NULL){
        destroyTree(&(*root)->copil1);
        destroyTree(&(*root)->copil2);
        destroyTree(&(*root)->copil3);
        destroyTree(&(*root)->copil4);
    }
    free((*root)->node);
    free((*root));
}

int main( int argc, char *argv[])
{
    int ct_pozitie_arg=1;                                                       //argumentele propriu zise incep de la indicele 1;
    char *inputfile, *outputfile;
    if(strcmp(argv[ct_pozitie_arg]+1,"c")==0 || strcmp(argv[ct_pozitie_arg]+1,"d")==0){
        inputfile=argv[ct_pozitie_arg+2];                                                  //vad care sunt numele fisierelor de input si output
        outputfile=argv[ct_pozitie_arg+3];
    }else{
        inputfile=argv[ct_pozitie_arg+1];
        outputfile=argv[ct_pozitie_arg+2];
    }
    FILE *in=fopen(inputfile,"rb");                                             //deschid inputfile-ul cu drepturi de citire (pt fisier binar)
    FILE *out=fopen(outputfile, "w");                                           //deschid outputfile-ul cu drepturi de scriere
    char tip[3];
    int width, height, max_value;
    fread(tip, sizeof(char), 3, in);                                            //imi iau numarul de elemente pe lungime si latime si valoarea maxima pe care o poate avea culoarea
    fscanf(in, "%d %d %d", &width, &height, &max_value);
    Pixel_p **matrice=malloc(height*sizeof(*matrice));
    for(int i=0; i<height; i++){
        matrice[i]=malloc(width*sizeof(**matrice));
    }
    char ct;
    fread(&ct, sizeof(char), 1, in);                                            //sar peste /n de dinaintea pixelilor
    for(int i=0; i<width; i++){                                                 //apoi citesc cate un pixel pe rand, retinand fiecare culoare in matricea de pixeli
        for(int j=0; j<height; j++){
            fread(&matrice[i][j], sizeof(**matrice), 1, in);
        }
    }
    int factor=0;
    if(strcmp(argv[ct_pozitie_arg]+1,"c")==0){                                  // fac rost de factorul de comprimare, daca se vrea comprimare
        ct_pozitie_arg++;
        factor=atoi(argv[ct_pozitie_arg]);
        ct_pozitie_arg++;

        Arbore *root=creareArbore(matrice,width,0,0,width,width, factor);       //creez arborele folosind CreareArbore
        parcurgere(&root);                                                      //parcurgem arborele pentru a pune indicii copiilor fiecarui nod
        QuadtreeNode *v=malloc((indexare+1)*sizeof(QuadtreeNode));              //alocam memorie pentru vectorul v
        creare(root,&v);                                                        //punem nodurile in v
        indexare++;
        fwrite(&nr_frunze,sizeof(int),1,out);                                   //afisam in output file numarul de frunze, numarul de noduri, si v
        fwrite(&indexare,sizeof(int),1,out);
        fwrite(v,sizeof(QuadtreeNode),indexare,out);

        free(v);                                                                //eliberam memoria lui v
        destroyTree(&root);                                                     //reliberam memoria arborelui
    }
    if(strcmp(argv[ct_pozitie_arg]+1,"d")==0){
        ct_pozitie_arg++;
    }   
    if(strcmp(argv[ct_pozitie_arg]+1,"m")==0){                                  //vad daca se doreste oglindire pe verticala sau pe verticala
        int verticala=0, orizontala=0;
        ct_pozitie_arg++;
        if(strcmp(argv[ct_pozitie_arg],"h"))
            orizontala=1;
        else
            verticala=1;
    }
    for(int i=0; i<height; i++){                                                //eliberez memoria elementelor matricei de pixeli
        free(matrice[i]);
    }
    free(matrice);                                                              //eliberez matricea
    fclose(in);                                                                 //inchid fisierele in si out
    fclose(out);
    return 0;
}