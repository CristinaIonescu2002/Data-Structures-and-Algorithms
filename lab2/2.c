#include <stdio.h>
#include <math.h>
double loog(double st, double dr, double x,double marj)
{
    if(x==0)
        return NAN;
    else if (x==1)
        return 0;
    else{
        int mid=(st+dr)/2;
        if (pow(2,mid)<x)
            return loog(mid,dr,x,marj);
        else if(pow(2,mid)>x)
            return loog(st,mid,x,marj);
        else if(abs(pow(2,mid)-x)<=marj)
            return mid;
    }
}
int main()
{
    double x,marj;
    scanf("%lf", &x);
    scanf("%lf", &marj);
    if(x>=1)
        printf("%.3lf\n", loog(0,x,x,marj));
    else{
        double y=pow(x,-1);
        printf("%.3lf\n", loog(0,y,y,marj)*(-1));
    }
        
    return 0;
}