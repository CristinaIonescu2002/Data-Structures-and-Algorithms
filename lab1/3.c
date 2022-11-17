#include <stdio.h>
#include <string.h>
int palind(int st, int dr, char *v)
{
    if(st>=dr)
        return 1;
    else if(v[dr]!=v[st])
        return 0;
    return palind(st+1,dr-1,v);
}
int main()
{
    char v[100];
    scanf("%s", v);
    if(palind(0,strlen(v)-1,v)==1)
        printf("E palindrom!");
    else
        printf("Nu e palindrom!");
}