#include<iostream>

using namespace std;

int main()
{
    string name = "hello";
    int x  = name.size();
    cout<<x<<endl;

    for(int i = 4; i <= x; i--)
    {
        cout<<name[i];
        if(i == 0)
        {
            break;
        }
    }
}