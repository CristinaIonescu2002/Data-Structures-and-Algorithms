#include <stdio.h>
int DeI(int *v, int left, int right)
{
    int mid=(left+right)/2;
    if(left>=right){
        if(mid%2==0)
            return v[mid];
        else 
            return 0;
    }
    else 
        return DeI(v,left, mid-1)+DeI(v,mid+1,right);
}
int main()
{
    int v[5] = {1, 2, 3, 4, 5};
    printf("%d\n", DeI(v,0,4));
    return 0;
}