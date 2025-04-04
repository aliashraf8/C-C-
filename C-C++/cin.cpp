#include<iostream>

using namespace std;

int main()
{
    int i;
    do
    {
        cout<<"enter number ";
        cin>>i;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout<<"error\n"; 
        }
        else
        {
            cout<<"done\n";
            break;
        }
    }while(!cin.fail());

    cout<<i;

    int a;
    while(true)
    {
        cout<<"enter number  ";
        cin>>a;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000000,'\n');
            cout<<"error\n";
        }
        else
        {
            cout<<"done";
            break;
        }
    }

}