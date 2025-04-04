#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<algorithm>

using namespace std;

typedef struct
{
    string name;
    string number;
}cntct;

int main()
{
    ifstream file("contacts.csv");
    if(!file)
    {
        cout<<"File not found"<<endl;
        return 1;
    }

    vector<cntct>contacts;
    string line,nm,num;
    while(getline(file,line))
    {
        stringstream ss (line);
        getline(ss,nm,',');
        getline(ss,num);

        contacts.push_back({nm,num});
    }
    file.close();
    for(auto a : contacts)
    {
        cout<<a.name<<","<<a.number<<endl;      
    }
    string search_phrase;
    cout<<"enter text to search";
    getline(cin,search_phrase);
    if(search_phrase.empty())
    {
        cout<<"error";
    }
    else
    {
        for(auto a : contacts)
        {
            if(a.name == search_phrase)
            {
                cout<<"found"<<a.name<<","<<a.number<<endl;
            }
        }
    }
}