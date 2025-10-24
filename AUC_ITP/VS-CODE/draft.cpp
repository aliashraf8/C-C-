#include<iostream>

using namespace std;

int a, b, c , sum ;
float av;

int main()
{
    cout<<"enter first number ";
    cin>> a;

    cout<<"enter second number ";
    cin>> b;

    cout<<"enter third number ";
    cin>> c;

    sum = a + b + c;
    av = sum / 3.0;

    cout<< sum << endl << av;
}