#include<stdio.h>

void swap(int* a , int* b);

int main()
{
    int a []= {34,47,4,3,2,5,8,0,7,4,3,2,4};
    int x = sizeof(a)/sizeof(a[0]);
    int z;
    for(z = 0; z < x ; z++)
    {
        printf("%i ,", a[z]);
    }
    printf("\n");

    for(int i = 0; i < x-1; i ++)
    {
        for(int j = 0; j < x-1; j++)
        {
            if(a[j]> a[j+1])
            {
                swap(&a[j], &a[j+1]);
            }
        }
    }
    for(z = 0; z < x ; z++)
    {
        printf("%i ,", a[z]);
    }
    printf("\n");

}
void swap(int* a , int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}