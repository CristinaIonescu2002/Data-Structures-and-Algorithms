#include <stdio.h>
#include <stdlib.h>
#include "graph_adj_list.h"
#define BIG 100000

int getCost(graphAdjList_t *g, int u, int v){
    graphEdge_t **neighbours = getNeighbours(g, u);
    for(int idx = 0; neighbours[idx] != NULL; idx++)
        if(neighbours[idx]->v == v){
            int cost = neighbours[idx]->cost;
            freeNeighboursList(neighbours);
            return cost;
        }
    freeNeighboursList(neighbours);
    return 100000;
}

void dfs(graphAdjList_t *graf, int nod, int **visited, int **stack, int *head){
    (*visited)[nod] = 1;
    for(int i=0; i<graf->numNodes; i++){
        if(isNeighbour(graf, nod, i) && !(*visited)[i])
            dfs(graf, i, visited, stack, head);
    }
    (*stack)[*head] = nod;
    (*head)++;
}

void topological_sort_print(graphAdjList_t *graf){
    int *stack = malloc(graf->numNodes * sizeof(*stack));
    int *visited = malloc(graf->numNodes * sizeof(*stack));
    for(int i=0; i<graf->numNodes; i++)
        visited[i] = 0;
    int head = 0;
    for(int i=0; i<graf->numNodes; i++)
        if(getInDegree(graf, i) == 0){
            dfs(graf, i, &visited, &stack, &head);
        }
    printf("Sortare topologica: ");
    while(head>0)
        printf("%d ", stack[--head]);
    printf("\n");
    free(stack);
    free(visited);
}

void shortest_Floyd(graphAdjList_t *graf, int u, int v){
    if(u>=graf->numNodes || v>=graf->numNodes || u<0 || v<0){
        printf("Cel putin un nod nu exista\n");
        return;
    }
    int **dist;
    dist=malloc(sizeof(int*) * graf->numNodes);
    for(int i=0; i<graf->numNodes; i++)
        dist[i] = malloc(sizeof(int) * graf->numNodes);
    
    for(int i=0; i<graf->numNodes; i++)
        for(int j=0; j<graf->numNodes; j++)
            dist[i][j] = BIG;

    for(int i=0; i<graf->numNodes; i++){
        dist[i][i] = 0;
        graphEdge_t **neighbours = getNeighbours(graf, i);
        int idx = 0;
        while(neighbours[idx] != NULL){
            dist[i][neighbours[idx]->v] = neighbours[idx]->cost;
            idx ++;
        }
        freeNeighboursList(neighbours);
    }

    for(int k=0; k<graf->numNodes; k++)
        for(int i=0; i<graf->numNodes; i++)
            for(int j=0; j<graf->numNodes; j++)
                if(dist[i][j]>dist[i][k]+dist[k][j])
                    dist[i][j]=dist[i][k]+dist[k][j];
    
    if(dist[u][v] == BIG){
        printf("Nu exista drum de la %d la %d\n", u, v);
        for(int i=0; i<graf->numNodes; i++)
            free(dist[i]);
        free(dist);   
        return;
    }
    printf("Drumul de cost minim dintre nodurile %d si %d este: %d\n", u, v, dist[u][v]);
    for(int i=0; i<graf->numNodes; i++)
        free(dist[i]);
    free(dist);   
}

void shortest_Bellman(graphAdjList_t *graf, int src, int dest){
    int *dist;
    dist=calloc(graf->numNodes, sizeof(int));
    for(int i=0; i<graf->numNodes; i++)
        dist[i]=BIG;
    dist[src] = 0;
    
    for(int k=0; k<graf->numNodes-1; k++)
        for(int i=0; i<graf->numNodes; i++){
            graphEdge_t **neighbours=getNeighbours(graf, i);
            int idx=0;
            while(neighbours[idx]!=NULL){
                if(dist[i]!=BIG && dist[i]+neighbours[idx]->cost < dist[neighbours[idx]->v])
                    dist[neighbours[idx]->v]=dist[i]+neighbours[idx]->cost;
                idx++;
            }
            freeNeighboursList(neighbours);
        }

    for(int i=0; i<graf->numNodes; i++){
        graphEdge_t **neighbours=getNeighbours(graf, i);
            int idx=0;
            while(neighbours[idx]!=NULL){
                if(dist[i]!=BIG && dist[i]+neighbours[idx]->cost < dist[neighbours[idx]->v]){
                    printf("Exista ciclu negativ!\n");
                    freeNeighboursList(neighbours);
                    return;
                }
                idx++;
            }
            freeNeighboursList(neighbours);
    }
    if(dist[dest]==BIG){
        printf("Nu exista drum de la %d la %d\n", src, dest);
        free(dist);
        return;
    }
    printf("Drumul de cost minim dintre nodurile %d si %d este: %d\n", src, dest, dist[dest]);
    free(dist);

}

void shortest_Dijkstra(graphAdjList_t *graf, int src, int dest){
    int *found=calloc(graf->numNodes+1, sizeof(int));
    int *dist=calloc(graf->numNodes+1, sizeof(int));
    for(int i=0; i<graf->numNodes; i++){
        found[i+1]=0;
        dist[i+1]=getCost(graf, src, i);
    }
    found[src+1]=1;
    dist[src+1]=0;
    dist[0]=BIG;
    for(int k=0; k<graf->numNodes-1; k++){
        int pmax=0;
        for(int i=0; i<graf->numNodes; i++)
            if(found[i+1]==0 && dist[i+1]<dist[pmax])
                pmax=i+1;
        if(pmax>-1){
            found[pmax]=1;
            for(int i=0; i<graf->numNodes; i++)
                if(found[i+1]==0 && dist[i+1]>dist[pmax]+getCost(graf, pmax-1, i))
                    dist[i+1]=dist[pmax]+getCost(graf, pmax-1, i);
        }
    }
    if(dist[dest+1] == BIG){
        printf("Nu exista drum de la %d la %d\n", src, dest);
        free(dist);
        free(found);
        return;
    }
    printf("Drumul de cost minim dintre nodurile %d si %d este: %d\n", src, dest, dist[dest+1]);
    free(dist);
    free(found);
}


int main(void){
    int noduri,muchii;
    fscanf(stdin,"%d%d",&noduri,&muchii);
    graphAdjList_t *graf=initGraph(noduri);
    for(int i=0; i<muchii; i++){
        int u, v, w;
        fscanf(stdin,"%d%d%d", &u, &v, &w);
        insertEdge(graf, u, v, w);
    }
    topological_sort_print(graf);
    printf("\nFLOYD:\n");
    shortest_Floyd(graf, 0, 3);
    printf("\nBELLMAN:\n");
    shortest_Bellman(graf, 0, 3);
    printf("\nDIJKSTRA\n");
    shortest_Dijkstra(graf, 0, 3);
    freeGraph(&graf);
}