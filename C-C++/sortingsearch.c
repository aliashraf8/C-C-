#include<stdio.h>

void swap (int *a , int *b);
void print(int a[] , int b);
void sort (int a[] , int b);
void find (int t, int a[], int b);

int main()
{
    int array [] = {1321,45,6,1,2,8,3,46,4,849,321,2}; 
    int length = sizeof(array)/sizeof array[0];
    print(array ,length);
    sort(array, length);
    print(array, length);
    int target;
    printf("enter target : ");
    scanf("%i" , &target);
    find(target , array , length);


}
void swap (int *a , int *b)
{
    int temp = 0;
    temp = *a; 
    *a = *b;
    *b = temp;
}
void sort (int a[] , int b)
{
    for (int s = 0 ; s < b -1 ;s++)
    {
        for(int r = 0 ; r < b -1 ; r++)
        {
            if(a[r] > a[r+1])
            {
                swap(&a[r] , &a[r+1]);
            }
        }
    }
}
void print(int a[] , int b)
{
    for(int p = 0 ; p < b ; p++)
    {
        printf("%i ," , a[p]);
    }
    printf("\n");
}
void find (int t, int a[], int b)
{
    for ( int i = 0 ; i < b ; i++)
    {
        if(t == a[i])
        {
            printf("%i found in element %i" ,t , i);
        }
    }
    printf("not found");
}