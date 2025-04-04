#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<algorithm>

using namespace std;

#define DATA_BASE "virtual.csv"

typedef struct
{
    string name;
    string number;
}cntct;

vector<cntct>V;

string Mn_tms[] = {"", 
"(1). View All Contacts.",
"(2). Add New Contact.",
"(3). Search Your Phone Book.",
"(4). Edit Existing Contact."};

void INTRO              (void);//HEAD LINE IN INTRODUCTION.
void MIAN_MENU          (void);//PRINTS MAIN MENUE ITEMS.
void VIEW_ALL_CONTACTS  (void);//VIEW ALL IN .CSV FILE.
void ADD_NEW_CONTACT    (cntct& a);//ADD NEW CONTACT.
void DIVIDER            (void);//PRINTS AN UNDERLINE DIVIDER.
void SORT               (void);//SORTING FUNCTION FOR SORTING AFTER ADDING NEW CONTACT.
void print              (void);
void EXIT_CASE          (void);//THE EXIT MENU AND OPTIONS.
void ADD_DATA_TO_VECTOR (void);//ADD DATA IN .CSV FILE TO A VECTOR INSIDE THE PROGRAM.

int main()
{

    INTRO();
    while(true)
    {
        int choice;
        cin>>choice;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "Invalid input, please enter.\n";
        }

        switch(choice)
        {
            case 1: //(1). View All Contacts.
            {
                system("cls");
                cout<<Mn_tms[choice]<<"\n";
                VIEW_ALL_CONTACTS();
                EXIT_CASE();
            }break;

            case 2: //(2). Add New Contact.
            {
                system("cls");
                cout<<Mn_tms[choice]<<endl;
                cntct NEW;
                ADD_NEW_CONTACT(NEW);
                EXIT_CASE();
            }break;

            case 3: //(3). Search Your Phone Book.
            {
                system("cls");
                cout<<Mn_tms[choice];
                ADD_DATA_TO_VECTOR();
                print();
                EXIT_CASE();
            }break;

            case 4: //(4). Edit Existing Contact.
            {
                system("cls");
                cout<<Mn_tms[choice];
                EXIT_CASE();
            }break;

            default:
            system("cls");
            cout<<"INVALID INPUT .... TRY AGAIN\n";
            DIVIDER();
            MIAN_MENU();
        }
    }         
} 

void ADD_NEW_CONTACT (cntct& a)
{
    DIVIDER();

    cout<<"\nENTER CONTACT NAME :  ";
    cin.ignore();
    getline(cin,a.name);
    size_t name_max_length = 20;

    if((a.name).length() > name_max_length && (a.name).length()!= 0)
    {
        a.name = (a.name).substr(0,name_max_length);
    }
    transform(a.name.begin() , a.name.end() , a.name.begin() , ::tolower);
    bool capitalizenext = true;
    for(size_t i = 0; i < name_max_length; i++)
    {
        if(capitalizenext && isalpha(a.name[i]))
        {
            a.name[i] = toupper(a.name[i]);
            capitalizenext = false;
        }
        else if(a.name[i] == ' ')
        {
            capitalizenext = true;
        }
    }
    //---------------------------------------------------------
    cout<<"ENTER CONTACT NUMBER :  ";
    getline(cin,a.number);
    size_t number_length = (a.number).length();
    size_t number_max_length = 12;
    if(number_length > number_max_length && !a.number.empty())
    {
        a.number = (a.number).substr(0,number_max_length);
    }
    //----------------------------------------------------------
    DIVIDER();
    cout<<endl<<"NAME : "<<a.name<<endl; 
    cout<<"NUMBER : "<<a.number<<endl; 
    //----------------------------------------------------------
    DIVIDER();
    string msg ="\n1 - CONFIRM SAVING\n2 - RE-ENTER DETAILS\n3 - EXIT TO MAIN MENU  >>> "; 
    cout<<msg;
    int Confirm;
    do
    {    
        cin>>Confirm;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000,'\n');
        }
        switch(Confirm)
        {
            case 1://CONFIRM SAVING.
            {
                ofstream file(DATA_BASE, ios::app);
                if(!file)
                {
                    cout<<"CANNOT OPEN .csv FILE FOR WRITING IN"<<
                     "SWITCH CASE IN ADD_NEW_CONATCTS FUNCTION";
                    break;
                }
                file<<endl<<a.name<<","<<a.number;
               
                file.close();
                
                SORT();
                system("cls");
                cout<<"CONTACT SAVED SUCCESSFULLY";
                EXIT_CASE();
            }break;

            case 2://RE-ENTER DETAILS.
            {
                cout<<Mn_tms[2];
                system("cls");
                ADD_NEW_CONTACT(a);
            }break;

            case 3://BACK TO MAIN MENU.
            {
                system("cls");
                return;
            }break;

            default:
            {
                cout<<"INVALID CHOICE "<<endl;
                cout<<msg;
            }
        }
    }while(Confirm !=3);
}       
void MIAN_MENU (void)
{
    size_t mn_size = sizeof(Mn_tms)/sizeof(Mn_tms[0]);
    for(int i = 0; i < mn_size ; i++)
    {
        cout<<Mn_tms[i]<<"\n";
    }
    cout<< "\n"<<1<< " to "<< mn_size-1<<endl;
    cout<<"ENTER PREFERED CHOICE NUMBER THEN PRESS ""ENTER""  >>  ";
}
void VIEW_ALL_CONTACTS(void)
{
    ifstream csvfile(DATA_BASE);
    if(!csvfile)
    {
        cout<<"CANNOT OPEN .csv FILE";
        return ;
    }
    string view;
    while(getline(csvfile,view))
    {
        cout<<view<<endl;
    }
    csvfile.close();
}
void DIVIDER (void)
{
    cout<<"-----------------------------------------------";
}
void EXIT_CASE (void)
{
    int e;
    cout<<"\n(1). Main Menue\n(2). Exit The Programe.\n";
    do{
        DIVIDER();
        cin>> e;
         if (cin.fail())
          {
            cin.clear();               
            cin.ignore(10000, '\n');   
            cout << "Invalid input, please enter 1 or 2.\n";
            continue;
          }

        switch(e)
        {
            case 1:
            main();
            break;
        
            case 2:
            system("cls");
            cout<<"SEE YOU SOON";
            exit(0);
            break;
        
            default:
            cout<<"TRY AGAIN\n";
        }
    }while(e != 1 && e != 2);
}
void INTRO(void)
{
    system("cls");
    ifstream intro("contacts_intro.txt");
    if(!intro)
    {
        cout<<"error opening intro file";
        return;
    }
    string intro_line;
    while(getline(intro,intro_line))
    {
        cout<<intro_line<<endl;
    }
    intro.close();
    MIAN_MENU();
}
void SORT (void)    
{
    V = {};
    ifstream infile (DATA_BASE);
    if(!infile)
    {
        cout<<"ERROR OPENING FILE FOR READING IN SORTING FUNCTION";
        exit(1);
    }
    string sorting_line;
    while(getline(infile,sorting_line))
    {
        if(sorting_line.rfind("name",0) == 0 || sorting_line.empty())
        {
            continue;
        }
        string nm,num;
        stringstream ss (sorting_line);
        getline(ss,nm,',');
        getline(ss,num);
        V.push_back({nm,num});
    }
//-----------------------------------------------------------------------------------------
    infile.close();
    sort(V.begin(),V.end(),[](const cntct& a,cntct& b)
    {
        return a.name < b.name;
    });
//-----------------------------------------------------------------------------------------
    
    ofstream outfile(DATA_BASE);
    if(!outfile)
    {
        cout<<"ERROR OPENING FILE FOR WRITING SORTED CONTACTS IN SORTING FUNCTION";
        exit(1);
    }
//-----------------------------------------------------------------------------------------
    outfile<<"name"<<","<<"number"<<endl;
    for(auto a : V)
    {
        outfile<<a.name<<","<<a.number<<endl;
    }
    vector<cntct>().swap(V);

    outfile.close();
}
void ADD_DATA_TO_VECTOR (void)
{
    V = {};
    vector<cntct>().swap(V);
    ifstream VF (DATA_BASE);
    if(!VF)
    {
        cout<<"ERROR OPEING FILE FOR WRITING IN ""VECTOR"" IN ADD_DATA_TO_VECTOR FUNCTION";
        exit(1);
    }

    string line;
    while(getline(VF,line))
    {
        if(line.empty()||line.rfind("name", 0) == 0)
        {
            continue;
        }
        string nm,num;
        stringstream ss (line);
        getline(ss,nm,',');
        getline(ss,num);
        V.push_back({nm,num});
    }
    VF.close();
}
void print (void)
{
    for(auto k : V)
    {
        cout<<k.name<<","<<k.number<<endl;
    }
}