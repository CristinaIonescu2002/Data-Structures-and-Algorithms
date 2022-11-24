#include <stdio.h>
#include <stdlib.h>
#include "graph_adj_matrix.h"
#include "priority_queue.h"

#define INF 999999

typedef struct components{
    int group;
    int nr_e;
    graphEdge_t * edges;
}components_t;

void Kruskal(graphAdjMat_t *g, graphEdge_t *vert, int m)
{
    for (int i=0;i<m-1;i++)
        for (int j=i+1;j<m;j++){
            if (vert[i].cost > vert[j].cost){
                int aux = vert[i].u;
                vert[i].u = vert[j].u;
                vert[j].u = aux;
                aux = vert[i].v;
                vert[i].v = vert[j].v;
                vert[j].v = aux;
                aux = vert[i].cost;
                vert[i].cost = vert[j].cost;
                vert[j].cost = aux;
            }
        }
    components_t * comps = malloc (g->numNodes * sizeof(components_t));
    for (int i=0;i<g->numNodes;i++){
        comps[i].group = i;
        comps[i].nr_e = 0;
        comps[i].edges = calloc (m , sizeof(int));
    }
    int last_group_id;
    for (int i=0;i<m;i++){
        if (comps[vert[i].u].group != comps[vert[i].v].group){
            int id = comps[vert[i].u].group;
            int o_id = comps[vert[i].v].group;
            comps[id].edges[comps[id].nr_e] = vert[i];
            comps[id].nr_e++;
            for (int j=comps[id].nr_e; j < comps[id].nr_e + comps[id].nr_e; j++)
                comps[id].edges[j] = comps[o_id].edges[j-comps[id].nr_e];
            comps[vert[i].v].group = id;
            for (int j=0;j<g->numNodes;j++)
                if (comps[j].group == o_id)
                    comps[j].group = id;
            last_group_id = id;
            comps[id].nr_e += comps[o_id].nr_e;
        }
    }
    for (int i=0;i<comps[last_group_id].nr_e;i++)
        printf("%d %d %d\n",comps[last_group_id].edges[i].u,comps[last_group_id].edges[i].v,comps[last_group_id].edges[i].cost);
    for (int i=0;i<g->numNodes;i++)
    free(comps[i].edges);
    free(comps);
}
void Prim(graphAdjMat_t *g, graphEdge_t *vert, int m)
{
    int nodes_covered = 0;
    int *viz = calloc (g->numNodes , sizeof(int));
    graphEdge_t* tree = malloc (g->numNodes * sizeof(graphEdge_t));
    int k=0;
    heapArray_t * q = initHeap(sizeof(graphEdge_t));
    for (int i=0;i<m;i++)
        if (vert[i].u == 0)
            priorityEnqueue(&q,&vert[i],sizeof(graphEdge_t),vert[i].cost);
    while (!isHeapEmpty(q) && nodes_covered < g->numNodes){
        pQueueItem_t *item;
        priorityDequeue(&q,(void *) item);
        int u =((graphEdge_t*)item->data)->u;
        int v =((graphEdge_t*)item->data)->v;
        int cost = ((graphEdge_t*)item->data)->cost;
        tree[k].u = u;
        tree[k].v = v;
        tree[k].cost = cost;
        k++;
        viz[u] = 1;
        nodes_covered++; 
        for(int i=0;i<m;i++){
            if (vert[i].u == v && viz[vert[i].v] == 0){
                priorityEnqueue(&q,&vert[i],sizeof(graphEdge_t),vert[i].cost);
            }else if (vert[i].v == v && viz[vert[i].u] == 0){
                graphEdge_t new_vert;
                new_vert.u = vert[i].v;
                new_vert.v = vert[i].u;
                new_vert.cost = vert[i].cost;
                priorityEnqueue(&q,&new_vert,sizeof(graphEdge_t),new_vert.cost);
            }
        }
        if (nodes_covered < g->numNodes)
            printf("Graful nu este conex\n");
        else{
            for (int i=0;i<k;i++)
                printf("%d %d %d\n",tree[i].u,tree[i].v,tree[i].cost);
        }
    }
    free(viz);
    free(tree);
    freeHeap(&q);
}
int main()
{
    int n,m,u,v,w;
    scanf("%d%d",&n,&m);
    graphAdjMat_t * g = initGraph(n);
    graphEdge_t * vert = malloc (m * sizeof(graphEdge_t));
    for (int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w);
        insertEdge(g,u,v,w);
        vert[i].u = u;
        vert[i].v = v;
        vert[i].cost = w;
    }
        Kruskal(g,vert,m);
        Prim(g,vert,m);
        return 0;
}