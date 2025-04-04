#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;

//FILE NAME THAT WILL BE USED IN PROGRAM CAN BE CHANGED ANY TIME JUST CHANGE THE NAME BETWEEN BRACKETS.
#define DATA_FILE "virtual.csv"

//A STRUCT TO HANDLE THE NAME AND THE NUMBER. CAN BE UPGRADED EASILY TO CONTAIN MORE FIELDS.
typedef struct 
{
    string name;
    string number;
}cntct;

//ARRAY CONTAINS THE SERVICES NAME WHICH THE PROGRAM PROVIDES.
const string MENU_ITEMS[] = 
{   "WELCOME TO YOUR PHONE BOOK :\n", 
    "(1). View All Contacts.",
    "(2). Add New Contact.",
    "(3). Search Your Phone Book.",
    "(4). Edit Existing Contact.",
    "(5). Exit Program."
};

const string line = "-----------------------------------------------";

fstream FS;

vector <cntct> CONATCTS;

void MAIN_MENU(void);//FUNCTION TO PRINT THE MAIN MENU ITEMS.
void VIEW_ALL_CONTACTS(void);//FUNCTION TO VIEW ALL SAVED CONTACTS.
void ADD_NEW_CONTACT(void);
void SEARCH_CONTACTS(void);//NEW SEARCH FUNCTION

string GET_STRING (size_t max_length);
void CLEAR_SCREEN(void);//FUNCTION TO CLEAN THE SCREEN.
void ADD_CONTACTS_TO_VECTOR (void);//FUNCTION TO ADD .CSV DATA TO VECTOR.
void SORT_VECTOR_AND_FILE (void);//FUNCTION TO SORT VECTOR ELEMENTS AND RE-WRITE IT AGAIN TO FILE SORTED.
void FILE_CONTROL_OPEN_AND_CLOSE(char Control);

int main()
{
    FILE_CONTROL_OPEN_AND_CLOSE('o');
    ADD_CONTACTS_TO_VECTOR();
    SORT_VECTOR_AND_FILE();
    while(true)
    {
        MAIN_MENU();
        int choice;
        cin>>choice;

        //INPUT ERROR HANDLING.
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout<<"RE-CHOOSE THE PREFERRED SERVICE NUMBER";
        }

        switch(choice)
        {
            //(1.) VIEW ALL CONTACTS.
            case 1:
            {
                CLEAR_SCREEN();
                cout<<MENU_ITEMS[1]<<endl;
                cout<<line<<endl;
                VIEW_ALL_CONTACTS();
                cout << "\nPress ENTER to return to the main menu...";
                cin.ignore();  // REMOVE ANY REMAINING DATA IN THE BUFFER (IMPORTANT BEFORE cin.get())
                cin.get();     // WAIT FOR THE USER TO PRESS ENTER
                CLEAR_SCREEN();
            }
            break;

            //(2.)ADD NEW CONTACT.
            case 2:
            {
                CLEAR_SCREEN();
                cout<<MENU_ITEMS[2]<<endl;
                ADD_NEW_CONTACT();
            }
            break;
            
            case 3://(3.)SEARCH CONTACTS.
            {
                CLEAR_SCREEN();
                cout<<MENU_ITEMS[3]<<line;
                SEARCH_CONTACTS();
            }
            break;
            
            case 4://(4.)EDIT EXISTING CONTACT.
            {
                CLEAR_SCREEN();
                cout<<MENU_ITEMS[4]<<line;
            }
            break;

            case 5:
            {
                CLEAR_SCREEN();
                cout<<"See You Soon"<<endl<<line;
                FILE_CONTROL_OPEN_AND_CLOSE('c');
                return 0;
            }
            break;

            default:
            {
                CLEAR_SCREEN();
                cout<<"RE-CHOOSE THE PREFERRED SERVICE NUMBER";
                MAIN_MENU();
                break;
            }
        }
    }
    return 0;
}

void MAIN_MENU (void)
{
    CLEAR_SCREEN();
    //SIZE OF THE GLOBAL ARRAY ABOVE^^^.
unsigned int MENU_ITEMS_NUMBER = sizeof(MENU_ITEMS)/sizeof(MENU_ITEMS[0]);
    //A LOOP TO PRINT ALL THE MENU ITEMS VERTICALLY.
    for(unsigned int i = 0; i < MENU_ITEMS_NUMBER; i++)
    {
        cout<<MENU_ITEMS[i]<<endl;
    }
    cout<< "\n"<<"FORM 1"<< " to "<< MENU_ITEMS_NUMBER -1 <<endl;
    cout<<"ENTER PREFERRED CHOICE NUMBER THEN PRESS ""ENTER""  >>  ";
}

void CLEAR_SCREEN(void)
{
#ifdef _WIN32
    system("cls");  //COMPATIBLE WITH WINDOWS.
#else
    system("clear");  //COMPATIBLE WITH Linux & macOS.
#endif
}

void VIEW_ALL_CONTACTS(void)
{
    for (const auto& c : CONATCTS)
    {
        cout << left << setw(25) << c.name <<  setw(15) << c.number << endl;
    }
}

void ADD_CONTACTS_TO_VECTOR (void)
{
    
    //READING LINE BY LINE VERTICALLY.
    string READING_LINE;
    while(getline(FS,READING_LINE))
    {
        //AVOIDING THE HEADER LINE IN THE .CSV FILE
        if(READING_LINE.empty() || READING_LINE.rfind("name",0) == 0)
        {
            continue;
        }
        //INITIALIZE NAME AND NUMBER FOR TWO STRINGS TO STORE IT SEPARATELY IN VECTOR OF CNTCT.
        string NAME,NUMBER;
        //STRING STREAM TO SEPARATE THE TEXT BEFORE AND AFTER THE ','.
        stringstream STRNG_LN (READING_LINE);
        getline(STRNG_LN , NAME , ',');
        getline(STRNG_LN , NUMBER);
        //ADD EACH CONTACT NAME AND NUMBER TO VECTOR.
        CONATCTS.push_back({NAME,NUMBER});
    }
}

void SORT_VECTOR_AND_FILE (void)
{
     // CLOSE THE FILE FIRST BEFORE OPENING IT WITH `TRUNC` MODE.
    if (FS.is_open()) 
    {
        FS.close();
    }

    FS.open(DATA_FILE, ios::out | ios::trunc);

    if (!FS) {
        cout << "Error opening file for sorting!\n";
        return;
    }
    sort(CONATCTS.begin(),CONATCTS.end(),[](const cntct& a,cntct& b)
    {
        return a.name < b.name;
    });
    for ( auto c : CONATCTS)
    {
        FS<<c.name<<','<<c.number<<endl;
    }
}

void FILE_CONTROL_OPEN_AND_CLOSE(char Control)
{
    if(Control == 'o' ||Control == 'O')
    {
        FS.open(DATA_FILE, std::ios::in | std::ios::out | std::ios::app);
        if (!FS)
        {
            cout<<"ERROR OPENING FILE IN OPEN FILE FUNCTION";
            return;
        }
    }
    else if(Control == 'c' ||Control == 'C')
    {
        {
            if (FS.is_open()) 
            {
                FS.close();
            }
            else
            {
                cout<<"FILE IS NOT OPENED";
            }
        }

    }
    else
    {
        cout<<"ERROR USING ""FILE_CONTROL_OPEN_AND_CLOSE"" FUNCTION ";
    }
}

void ADD_NEW_CONTACT (void)
{
    cntct NEW;
    cout<<line<<endl;

    cout<<"ENTER CONTACT NAME : ";
    NEW.name = GET_STRING(20);

    cout<<"ENTER CONTACT NUMBER : ";
    NEW.number = GET_STRING(12);

    CLEAR_SCREEN();
    cout<<"NAME : "<<NEW.name<<endl; 
    cout<<"NUMBER : "<<NEW.number<<endl; 
    cout<<line<<endl;
    string msg ="1 - CONFIRM SAVING\n2 - RE-ENTER DETAILS\n3 - EXIT TO MAIN MENU WITHOUT SAVING  >>> "; 
    cout<<msg;
    
    int Confirm;
    do
    {   
        cin >> Confirm;
        // CHECK IF INPUT IS INVALID
        if(cin.fail())
        {
            // CLEAR THE ERROR FLAG
            cin.clear();
            // IGNORE INVALID INPUT UNTIL THE END OF THE LINE
            cin.ignore(10000, '\n');
            // PRINT ERROR MESSAGE
            CLEAR_SCREEN();
            cout << "INVALID CHOICE TRY AGAIN" << endl;
            cout<<"NAME : "<<NEW.name<<endl; 
            cout<<"NUMBER : "<<NEW.number<<endl;
            cout<<line;
            cout << msg << endl;
        }
        else
        {
            switch(Confirm)
            {
                case 1://CONFIRM SAVING.
                {
                    CONATCTS.push_back({NEW.name,NEW.number});
                    SORT_VECTOR_AND_FILE();
                    CLEAR_SCREEN();
                    cout<<"CONTACT SAVED SUCCESSFULLY PRESS ENTER TO CONTINUE...";
                    cin.ignore();  // REMOVE ANY REMAINING DATA IN THE BUFFER (IMPORTANT BEFORE cin.get())
                    cin.get();     // WAIT FOR THE USER TO PRESS ENTER
                    CLEAR_SCREEN();

                    return;
                }break;

                case 2://RE-ENTER DETAILS.
                {
                    cout<<MENU_ITEMS[2];
                    CLEAR_SCREEN();
                    ADD_NEW_CONTACT();
                }break;

                case 3://BACK TO MAIN MENU.
                {
                    CLEAR_SCREEN();
                    return;
                }break;

                default:
                {
                    CLEAR_SCREEN();
                    cout<<"INVALID CHOICE TRY AGAIN"<<endl;
                    cout<<"NAME : "<<NEW.name<<endl; 
                    cout<<"NUMBER : "<<NEW.number<<endl;
                    cout<<line;
                    cout<<msg;
                }
            }
        }
    }while(Confirm !=3);
}

string GET_STRING (size_t max_length)
{
    string String;

     // IF THE NEXT CHARACTER IS A NEWLINE, THEN IGNORE IT
     if(cin.peek() == '\n')
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    getline(cin,String);

    if((String).length() > max_length && (String).length()!= 0)
    {
        String = (String).substr(0,max_length);
    }
    transform(String.begin() , String.end() , String.begin() , ::tolower);
    // IF THE STRING IS NOT EMPTY AND THE FIRST CHARACTER IS ALPHABETIC, CAPITALIZE IT
    if (!String.empty() && isalpha(String[0]))
    {
        String[0] = toupper(String[0]);
    }

    // FOR EACH CHARACTER STARTING FROM THE SECOND,
    // IF THE PREVIOUS CHARACTER IS A SPACE AND THE CURRENT CHARACTER IS ALPHABETIC, CAPITALIZE IT
    for (size_t i = 1; i < String.size(); i++)
    {
        if (String[i - 1] == ' ' && isalpha(String[i]))
        {
            String[i] = toupper(String[i]);
        }
    }
    return String;
}

void SEARCH_CONTACTS(void)
{
    cout << "\nSearch by:\n";
    cout << "1. Name\n";
    cout << "2. Number\n";
    cout << "Enter your choice (1 or 2): ";
    
    int searchChoice;
    cin >> searchChoice;
    
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(10000,'\n');
        cout << "Invalid input!\n";
        return;
    }

    string searchTerm;
    cout << "Enter search term: ";
    cin.ignore();
    getline(cin, searchTerm);
    
    // Convert search term to lowercase for case-insensitive search
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
    
    bool found = false;
    cout << "\nSearch Results:\n";
    cout << line << endl;
    
    for(const auto& contact : CONATCTS)
    {
        string compareName = contact.name;
        transform(compareName.begin(), compareName.end(), compareName.begin(), ::tolower);
        
        if(searchChoice == 1 && compareName.find(searchTerm) != string::npos)
        {
            cout << left << setw(25) << contact.name << setw(15) << contact.number << endl;
            found = true;
        }
        else if(searchChoice == 2 && contact.number.find(searchTerm) != string::npos)
        {
            cout << left << setw(25) << contact.name << setw(15) << contact.number << endl;
            found = true;
        }
    }
    
    if(!found)
    {
        cout << "No contacts found matching your search.\n";
    }
    
    cout << line << endl;
    cout << "\nPress ENTER to return to the main menu...";
    cin.get();
    CLEAR_SCREEN();
}