#include <stdio.h>

float sum(int lenght, int array[]);

int main(void)
{
    int n; 
    printf("how many ? ");
    scanf("%i" , &n);
    int scores[n];
    for (int i = 0; i < n; i++)
    {
        scores[i];
        printf("score:  ");
        scanf("%i", &scores[i]);
    }
    printf("average = %.2f", sum(n, scores));
}

float sum(int lenght, int array[])
{
    int sum = 0;
    for (int j = 0; j < lenght; j++)
    {
        sum += array[j];
    }
    return sum / lenght;
}
