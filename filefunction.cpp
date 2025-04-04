#include<iostream>
#include<fstream>
using namespace std;

void file_function (string f_name, char MODE_i_o);

string file_name = "contaghcts.csv";

int main()
{

}

 file_function (string f_name, char MODE_i_o)
{
    if(MODE_i_o == 'R')
    {
        ifstream IF (f_name);
        if(!IF)
        {
            cout<<"error opening file in file function";
            exit(1);
        }
        return IF;
    }
    else if(MODE_i_o == 'W')
    {
        ofstream OF (f_name,ios::in);
        if(!OF)
        {
            cout<<"error opening file in file function";
            exit(1);
        }
        return OF;
    }
    else
    {
        cout<<"ERROR CHOOSING MODE IN FUNCTION ARGUMENTS\n";
        cout<<" 'i' for ifstream , 'o' for ofstream";
        exit(1);
    }
}