#include <stdio.h>
void swap(int *x, int *y)
{
    int t=*x;
    *x=*y;
    *y=t;
}
int partition(int *v, int st, int dr)
{
    int pivot=v[dr];
    int i=st-1;
    for (int j=st; j<dr; j++){
        if(v[j]<=pivot){
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i+1], &v[dr]);
    return i+1;
}
void quickSort(int *v, int st, int dr)
{
    if(st<dr){
        int mid=partition(v,st,dr);
        quickSort(v,st,mid-1);
        quickSort(v,mid+1,dr);
    }
}
int main()
{
    int n;
    int v[100];
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &v[i]);
    quickSort(v,0,n-1);
    for(int i=0; i<n; i++)
        printf("%d ", v[i]);
}