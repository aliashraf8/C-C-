#include<cs50.h>
#include<stdio.h>

//finding number with linear search

int T = 13;

float find (float A[]);
int F_TARGET ( float A[] , float c );

int main(void)
{
    float a[] = {15,18,2,8,98,30,50,40,45,8,99,66,87};
    float target = find(a);

    printf("%.1f , at index[%i]\n" ,target , F_TARGET(a , target));
}
float find (float A[])
{
    float lngst_sd = 0;
    for(int i = 0 ; i < T ; i++)
    {
        if(lngst_sd < A[i])
        { lngst_sd = A[i]; }
    }
    return lngst_sd;
}
int F_TARGET ( float A[] , float c )
{
    for (int i = 0;  i < T ; i++)
    {
        if(c == A[i])
        {
            return i;
        }
    }
    return 0;
}