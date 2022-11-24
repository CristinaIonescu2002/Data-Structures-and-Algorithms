#include <stdio.h>
#include <stdlib.h>


typedef struct graphMat{
    int nr_nodes;
    int **mat_adj;
}graph_mat;

typedef struct graphNode{
    struct graphNode *next;
    int ID_node;
}graph_node;

typedef struct graphList{
    graph_node **adj_list;
    int nr_nodes;
}graph_list;


void inserareMuchieMat(int **mat,int nod1, int nod2)
{
    if(mat[nod1][nod2]!=1){
        mat[nod1][nod2]=1;
        mat[nod2][nod1]=1;
    }  
}
void stergereMuchieMat(int **mat, int nod1, int nod2)
{
    if(mat[nod1][nod2]==1){
        mat[nod1][nod2]=0;
        mat[nod1][nod2]=0;
    }
}
int gradNodMat(int **mat, int nod, int nr_noduri)
{
    int ct=0;
    for (int i=0; i<nr_noduri; i++)
        if(mat[nod][i]==1)
            ct++;
    return ct;
}
void afisareMat(int **mat, int nr_noduri){
    for(int i=0; i<nr_noduri; i++){
        for(int j=0; j<nr_noduri; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}
void destroyMat(int **mat, int nr_noduri){
    for(int i=0; i<nr_noduri; i++){
        free(mat[i]);
    }
    free(mat);
}


graph_mat init_graph_mat(int nr_nodes){
    graph_mat G;
    G.nr_nodes = nr_nodes;
    G.mat_adj = calloc(nr_nodes, sizeof(int*));
    for(int i = 0; i < nr_nodes; i++)
        G.mat_adj[i] = calloc(nr_nodes, sizeof(int));
    return G;
}
graph_node* init_node(int j){
    graph_node *node;
    node = calloc(1, sizeof(graph_node));
    node->ID_node = j;
    node->next = NULL;
    return node;
}
graph_list init_graph_list(int nr_nodes){
    graph_list G;
    G.nr_nodes = nr_nodes;
    G.adj_list = calloc(nr_nodes, sizeof(graph_node*));
    return G;
}
void add_edge_list(graph_list *G, int i, int j){
    graph_node *aux;
    if(G->adj_list[i] == NULL){
        G->adj_list[i] = init_node(j);
    }
    else{
        for(aux = G->adj_list[i]; aux->next != NULL; aux = aux->next);
        aux->next = init_node(j); 
    }
    
    if(G->adj_list[j] == NULL){
        G->adj_list[j] = init_node(i);
    }
    else{
        for(aux = G->adj_list[j]; aux->next != NULL; aux = aux->next);
        aux->next = init_node(i); 
    }
}

void delete_edge_list(graph_list *G, int i, int j){
    if(G->adj_list[i] == NULL)
        return;
    graph_node *aux;
    if(G->adj_list[i]->next == NULL && G->adj_list[i]->ID_node == j)
        G->adj_list[i] = NULL;
    else{
        aux = G->adj_list[i];
        if(aux->ID_node != j){
            while(aux->next != NULL){
                if(aux->next->ID_node == j)
                    break;
                aux = aux->next;
            }
            if(aux != NULL){
                graph_node *this = aux->next;
                aux->next = this->next;
                this->next = NULL;
                free(this);
            }
        }
        else{
            graph_node *this = G->adj_list[j];
            G->adj_list[j] = G->adj_list[j]->next;
            free(this);
        }
    }
    

    if(G->adj_list[j]->next == NULL && G->adj_list[j]->ID_node == i)
        G->adj_list[j] = NULL;
    else{
        aux = G->adj_list[j];
        if(aux->ID_node != i){
                while(aux->next != NULL){
                    if(aux->next->ID_node == i)
                        break;
                    aux = aux->next;
            }
            if(aux != NULL){
                graph_node *this = aux->next;
                aux->next = this->next;
                this->next = NULL;
                free(this);
            }
        
        }
        else{
            graph_node *this = G->adj_list[j];
            G->adj_list[j] = G->adj_list[j]->next;
            free(this);
        }
    }
}
void print_list(graph_list G){
    for(int i = 0; i < G.nr_nodes; i++){
        printf("%d: ", i);
        graph_node *aux;
        for(aux = G.adj_list[i]; aux != NULL; aux = aux->next)
            printf("%d ", aux->ID_node);
        printf("\n");
    }
}
void free_graph_list(graph_list *G){
    for(int i = 0; i < G->nr_nodes; i++){
        graph_node *aux = G->adj_list[i];
        while(aux != NULL){
            graph_node *this = aux;
            aux = aux->next;
            this->next = NULL;
            free(this);
        }
    }
}
int get_grad_list(graph_list G, int i){
    int ans = 0;
    graph_node *this = G.adj_list[i];
    while(this != NULL){
        ++ans;
        this = this->next;
    }
    return ans;
}
void set_zeros(int **v, int n){
    for(int i = 0; i < n; i++)
        (*v)[i] = 0;
}
void dfs(graph_mat G, int i, int **vis){
    (*vis)[i] = 1;
    printf("%d ", i);
    for(int j = 0; j < G.nr_nodes; j++)
        if(G.mat_adj[i][j] && !(*vis)[j])
            dfs(G, j, vis);
}
void bfs(graph_mat G, int i, int **vis){
    int *queue;
    queue = calloc(10*G.nr_nodes, sizeof(int));
    set_zeros(&queue, G.nr_nodes);
    int p = 0, u = 0;
    queue[p] = i;
    u++;
    (*vis)[i] = 1;
    while(p < u){
        printf("%d ", queue[p]);
        for(int j = 0; j < G.nr_nodes; j++)
            if(G.mat_adj[queue[p]][j] && (*vis)[j] == 0){
                queue[u++] = j;
                (*vis)[j] = 1;
            }
        p++;
    }
}
int dfs_cycle(graph_mat G, int i, int **vis, int parent){
    (*vis)[i] = 1;
    for(int j = 0; j < G.nr_nodes; j++)
        if(G.mat_adj[i][j]){
        if((*vis)[j] == 0){
            if(dfs_cycle(G, j, vis, i))
                return 1;
            }
        else if(j != parent)
            return 1;
        }
    return 0;
}
int has_cycle(graph_mat G, int **vis){
    for(int i = 0; i < G.nr_nodes; i++)
        if(!(*vis)[i])
            if(dfs_cycle(G, i, vis, -1)){
                return 1;
            }
    return 0;
}
int main()
{



    int nr_noduri, nr_linii;
    int nod1, nod2;
    fscanf(stdin, "%d%d", &nr_noduri, &nr_linii);
    int **mat=malloc(nr_noduri*sizeof(int *));
    for(int i=0; i<nr_noduri; i++)
        mat[i]=calloc(nr_noduri,sizeof(int));
    for (int i=0; i<nr_linii; i++){
        scanf("%d %d", &nod1, &nod2);
        mat[nod1][nod2]=1;
        mat[nod2][nod1]=1;
    }
    afisareMat(&(*mat), nr_noduri);
    nod1=0;
    nod2=3;
    afisareMat(&(*mat), nr_noduri);
    afisareMat(&(*mat), nr_noduri);
    nod1=4;
    int grad;
    grad=gradNodMat(&(*mat), nod1, nr_noduri);
    printf("grad: %d\n", grad);
    destroyMat(mat, nr_noduri);

    printf("\n");

    graph_mat GMat = init_graph_mat(nr_noduri);
    graph_list GList = init_graph_list(nr_noduri);
    for(int i = 0; i < nr_linii; i++){
        int u, v;
        fscanf(stdin, "%d%d", &u, &v);
        // add_edge_mat(&GMat, u, v);
        add_edge_list(&GList, u, v);
    }



    // printf("Implementarea cu liste:\n");
    print_list(GList);
    printf("\n");
    // printf("Gradul lui 2: %d\nSterg legatura (2,4)...\n", get_grad_list(GList, 2));
    delete_edge_list(&GList, 2, 4);
    // printf("Gradul lui 2 dupa delete: %d\n", get_grad_list(GList, 2));
    printf("\n");
    print_list(GList);
    add_edge_mat(&GMat, 2, 4);

    // Parcurgerile
    int *visited;
    visited = calloc(nr_noduri, sizeof(int));
    set_zeros(&visited, nr_noduri);
    // printf("Parcurgerea in adancime pornind din nodul 3: ");
    dfs(GMat, 3, &visited);
    printf("\n");
    set_zeros(&visited, nr_noduri);
    // printf("Parcurgerea in latime pornind din nodul 3: ");
    bfs(GMat, 3, &visited);
    printf("\n");
    set_zeros(&visited, nr_noduri);
    
    // Verificarea existentei ciclurilor

    printf("%s", has_cycle(GMat, &visited) ? "Exista ciclu\n" : "Nu exista ciclu\n");

    
    return 0;
}