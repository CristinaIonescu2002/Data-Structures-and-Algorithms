#include <stdio.h>

int cate(int c, int nr)
{
    if(nr==0)
        return 0;
    else if(nr%10<c)
        return 1+cate(c,nr/10);
    else
        return cate(c,nr/10);
}

int main()
{
    int c, nr;
    scanf("%d%d", &nr, &c);
    printf("%d", cate(nr, c));
}