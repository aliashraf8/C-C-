#include<iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;

typedef struct
{
    string name;
    string number;
}cntct;

vector<cntct> v;
int main()
{
    fstream csvfile ("text.csv");
    if(!csvfile)
    {
        cout<<"error opening csv file in fstreram";
        return 1;
    }
    string line;
    while(getline(csvfile,line))
    {
        string nm,num;
        stringstream ss (line);
        getline(ss,nm,',');
        getline(ss,num);
        v.push_back({nm,num});
    }
    for(auto& h:v)
    {
        cout<<h.name<<"...."<<h.number<<endl;
    }
    
}