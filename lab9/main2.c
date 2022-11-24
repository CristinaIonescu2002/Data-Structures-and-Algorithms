#include <stdlib.h>
#include <stdio.h>

typedef struct graf{
    int nr_noduri;
    int **mat;
}MAT;
typedef struct NODE{
    struct NODE *next;
    int ID_node;
}node;
typedef struct LIST{
    node **adj_list;
    int nr_noduri;
}list;
MAT init_mat(int nr_noduri){
    MAT Str;
    Str.nr_noduri=nr_noduri;
    Str.mat=calloc(nr_noduri, sizeof(int*));
    for(int i=0; i<nr_noduri; i++)
        Str.mat[i]=calloc(nr_noduri, sizeof(int));
    return Str;
}
node* init_node(int j){
    node *node;
    node=calloc(1, sizeof(node));
    node->ID_node=j;
    node->next=NULL;
    return node;
}
list init_list(int nr_noduri){
    list Str;
    Str.nr_noduri=nr_noduri;
    Str.adj_list=calloc(nr_noduri, sizeof(node*));
    return Str;
}
void add_muchie_mat(MAT *Str, int i, int j){
    Str->mat[i][j]=1;
    Str->mat[j][i]=1;
}
void delete_muchie_mat(MAT *Str, int i, int j){
    Str->mat[i][j]=0;
    Str->mat[j][i]=0;
}
int get_grad(MAT Str, int i){
    int grad=0;
    for(int j=0; j<Str.nr_noduri; j++)
        grad=grad+Str.mat[i][j];
    return grad;
}
void free_mat(MAT *Str){
    for(int i=0; i<Str->nr_noduri; i++)
        free(Str->mat[i]);
    free(Str->mat);
}
void print_matr_adj(MAT Str){
    for(int i=0; i<Str.nr_noduri; i++){
        for(int j=0; j<Str.nr_noduri; j++)
            printf("%d ", Str.mat[i][j]);
        printf("\n");
    }
}
void add_muchie_list(list *Str, int i, int j){
    node *aux;
    if(Str->adj_list[i]==NULL){
        Str->adj_list[i]=init_node(j);
    }else{
        for(aux=Str->adj_list[i]; aux->next!=NULL; aux=aux->next);
        aux->next=init_node(j); 
    }
    if(Str->adj_list[j]==NULL){
        Str->adj_list[j]=init_node(i);
    }else{
        for(aux=Str->adj_list[j]; aux->next!=NULL; aux=aux->next);
        aux->next=init_node(i); 
    }
}
void delete_muchie_list(list *Str, int i, int j){
    if(Str->adj_list[i] == NULL)
        return;
    node *aux;
    if(Str->adj_list[i]->next==NULL && Str->adj_list[i]->ID_node==j)
        Str->adj_list[i] = NULL;
    else{
        aux=Str->adj_list[i];
        if(aux->ID_node!=j){
            while(aux->next!=NULL){
                if(aux->next->ID_node==j)
                    break;
                aux=aux->next;
            }
            if(aux!=NULL){
                node *this=aux->next;
                aux->next=this->next;
                this->next=NULL;
                free(this);
            }
        }else{
            node *this=Str->adj_list[j];
            Str->adj_list[j]=Str->adj_list[j]->next;
            free(this);
        }
    }
    if(Str->adj_list[j]->next==NULL && Str->adj_list[j]->ID_node==i)
        Str->adj_list[j]=NULL;
    else{
        aux=Str->adj_list[j];
        if(aux->ID_node!=i){
                while(aux->next!=NULL){
                    if(aux->next->ID_node==i)
                        break;
                    aux=aux->next;
            }
            if(aux!=NULL){
                node *this=aux->next;
                aux->next=this->next;
                this->next=NULL;
                free(this);
            }
        }else{
            node *this=Str->adj_list[j];
            Str->adj_list[j]=Str->adj_list[j]->next;
            free(this);
        }
    }
}
void print_list(list Str){
    for(int i=0; i<Str.nr_noduri; i++){
        printf("%d: ", i);
        node *aux;
        for(aux=Str.adj_list[i]; aux!=NULL; aux=aux->next)
            printf("%d ", aux->ID_node);
        printf("\n");
    }
}
void free_list(list *Str){
    for(int i=0; i<Str->nr_noduri; i++){
        node *aux=Str->adj_list[i];
        while(aux!=NULL){
            node *this=aux;
            aux=aux->next;
            this->next=NULL;
            free(this);
        }
    }
}
int grad_list(list Str, int i){
    int ans=0;
    node *this =Str.adj_list[i];
    while(this!=NULL){
        ans++;
        this=this->next;
    }
    return ans;
}
void set_zeros(int **v, int n){
    for(int i=0; i<n; i++)
        (*v)[i]=0;
}
void DFS(MAT Str, int i, int **vizitat){
    (*vizitat)[i] = 1;
    printf("%d ", i);
    for(int j=0; j<Str.nr_noduri; j++)
        if(Str.mat[i][j] && !(*vizitat)[j])
            DFS(Str, j, vizitat);
}
void BFS(MAT Str, int i, int **vizitat){
    int *queue;
    queue = calloc(10*Str.nr_noduri, sizeof(int));
    set_zeros(&queue, Str.nr_noduri);
    int p=0;
    int u=0;
    queue[p]=i;
    u++;
    (*vizitat)[i]=1;
    while(p<u){
        printf("%d ", queue[p]);
        for(int j=0; j<Str.nr_noduri; j++)
            if(Str.mat[queue[p]][j] && (*vizitat)[j]==0){
                queue[u++]=j;
                (*vizitat)[j]=1;
            }
        p++;
    }
}
int DFScycle(MAT Str, int i, int **vizitat, int parent){
    (*vizitat)[i] = 1;
    for(int j=0; j<Str.nr_noduri; j++)
        if(Str.mat[i][j]){
        if((*vizitat)[j]==0){
            if(DFScycle(Str, j, vizitat, i))
                return 1;
        }else if(j!=parent)
            return 1;
        }
    return 0;
}
int cycle(MAT Str, int **vizitat){
    for(int i=0; i<Str.nr_noduri; i++)
        if(!(*vizitat)[i])
            if(DFScycle(Str, i, vizitat, -1)){
                return 1;
            }
    return 0;
}

int main(){
    int nr_noduri, nr_muchie;
    fscanf(stdin, "%d%d", &nr_noduri, &nr_muchie);
    MAT GMat = init_mat(nr_noduri);
    list GList = init_list(nr_noduri);
    for(int i = 0; i < nr_muchie; i++){
        int u, v;
        fscanf(stdin, "%d%d", &u, &v);
        add_muchie_mat(&GMat, u, v);
        add_muchie_list(&GList, u, v);
    }
    printf("Implementarea cu matrice:\n");
    print_matr_adj(GMat);
    printf("\n");
    printf("Gradul\n");
    printf("%d\n", get_grad(GMat, 2));
    delete_muchie_mat(&GMat, 2, 4);
    printf("Gradul\n");
    printf("%d\n", get_grad(GMat, 2));
    printf("\n");
    print_matr_adj(GMat);

    printf("\n");

    printf("Implementarea cu liste:\n");
    print_list(GList);
    printf("\n");
    printf("Gradul\n");
    printf("%d\n", grad_list(GList, 2));
    delete_muchie_list(&GList, 2, 4);
    printf("Gradul\n");
    printf("%d\n", grad_list(GList, 2));
    printf("\n");
    print_list(GList);
    add_muchie_mat(&GMat, 2, 4);

    int *vizitat;
    vizitat = calloc(nr_noduri, sizeof(int));
    set_zeros(&vizitat, nr_noduri);
    printf("Parcurgerea in adancime\n");
    DFS(GMat, 3, &vizitat);
    printf("\n");
    set_zeros(&vizitat, nr_noduri);
    printf("Parcurgerea in latime \n");
    BFS(GMat, 3, &vizitat);
    printf("\n");
    set_zeros(&vizitat, nr_noduri);
    if(cycle(GMat, &vizitat)==1)
        printf("Exista ciclu\n");
    else printf("Nu exista ciclu\n");
    return 0;
}