#include <stdio.h>
int binarySearch(int *v, int x, int left, int right)
{
    int mij=(left+right)/2;
    if(v[mij]==x)
        return 1;
    else if(left>right)
        return 0;
    else if(x<v[mij])
        return binarySearch(v,x,left,mij-1);
    else 
        return binarySearch(v,x,mij+1,right);
    
}
int main()
{
    int v[100],n,cf,i;
    scanf("%d", &n);
    for(i=0; i<n; i++)
        scanf("%d", &v[i]);
    scanf("%d", &cf);
    printf("%d\n", binarySearch(v,cf,0,n-1));
}