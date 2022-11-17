#include<stdio.h>       // Prim's Algorithm in C
#include<stdbool.h> 
#define INF 9999999
#define V 5             // number of vertices in graph
int G[V][V] = {         //matrice de costuri
  {0, 9, 75, 0, 0},
  {9, 0, 95, 19, 42},
  {75, 95, 0, 51, 66},
  {0, 19, 51, 0, 31},
  {0, 42, 66, 31, 0}};

int main() {
  int no_edge;              // number of edge
  int selected[V];          //vector de vizitati
  memset(selected, false, sizeof(selected));
  no_edge = 0;              //incepem cu nodul 0
  selected[0] = true;       //il marcam ca vizitat
  int x;                    //  row number
  int y;                    //  col number
  printf("Edge : Weight\n");// print for edge and weight
  while (no_edge < V - 1) {     //For every vertex in the set S, find the all adjacent vertices      
    int min = INF;              // , calculate the distance from the vertex selected at step 1.
    x = 0;                      // if the vertex is already in the set S, discard it otherwise
    y = 0;                      //choose another vertex nearest to selected vertex  at step 1
    for (int i = 0; i < V; i++)
      if (selected[i]) 
        for (int j = 0; j < V; j++) 
          if (!selected[j] && G[i][j])   // not in selected and there is an edge
            if (min > G[i][j]) {
              min = G[i][j];
              x = i;
              y = j;
            }
    printf("%d - %d : %d\n", x, y, G[x][y]);
    selected[y] = true;
    no_edge++;
  }
  return 0;
}


int min(int,int);
void floyds(int p[10][10],int n) {
	int i,j,k;
	for (k=1;k<=n;k++)
	  for (i=1;i<=n;i++)
	   for (j=1;j<=n;j++)
	    if(i==j)
	     p[i][j]=0; else
	     p[i][j]=min(p[i][j],p[i][k]+p[k][j]);
}
int min(int a,int b) {
	if(a<b)
	  return(a); else
	  return(b);
}