#include<iostream>

using namespace std; 

int main()
{
    int years = 0;
    float A = 24000;
    float B = 30000;
    do
    {
        A = A*0.12;
        B = B*0.1;
        years++;

    } while (A == B);

    cout<<years;
}
/*
a 24000
b 30000

A 12%
B 10%
*/ 
