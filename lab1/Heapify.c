#include <stdio.h>
typedef struct{
    int v[10];
    int n;
}heap;
void swap(heap h, int i, int j)
{
    int t;
    t=h.v[i];
    h.v[i]=h.v[j];
    h.v[j]=t;
}
void heapify(heap h, int i)
{
    int st,dr,m,aux;
    st=2*i;
    dr=st+1;
    if(st<=h.n && h.v[st]>h.v[i])
        m=st;
    else m=i;
    if(dr<=h.n && h.v[dr]>h.v[m])
        m=dr;
    if(m!=i){
        swap(h,i,m);
        heapify(h,m);
    }
}
// int main()
// {
//     heap h;
//     int i;
//     heapify(h, i);
//     return 0;
// }