#include<iostream>

using namespace std;

int h;
int hours ,days;

int main()
{
    cout<<"enter hours :  ";
    cin>>h;

    days = h/24;
    hours = h % 24;
    cout<<"days : "<<days<<endl;
    cout<<"hours : "<<hours;
}
