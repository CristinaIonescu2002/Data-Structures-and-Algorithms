#include <stdio.h>
void afisare(int *v, int k)
{
    for(int i=0; i<k; i++)
        printf("%d ", v[i]);
    printf("\n");
}
void bkt(int k, int *v, int sum, int n)
{
    if(sum==n){
        afisare(v,k);
        return;
    }
    else if(sum>n)
        return;
    for(int i=n; i>=1; i--){
        int ok=1;
        v[k]=i;
        if(k==0)
            ok=0;
        if(k>0 && v[k-1]>=v[k])
            ok=0;
        if(ok==0)
            bkt(k+1,v,sum+v[k],n);
    }
}
int main()
{
    int n,v[100];
    scanf("%d", &n);
    bkt(0,v,0,n);

    return 0;
}