#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;

// FILE NAME THAT WILL BE USED IN THE PROGRAM. CAN BE CHANGED ANYTIME BY MODIFYING THE NAME BETWEEN BRACKETS.
#define DATA_FILE "virtual.csv"

// A STRUCT TO HANDLE THE NAME AND THE NUMBER. CAN BE UPGRADED EASILY TO CONTAIN MORE FIELDS.
typedef struct 
{
    string name;   // CONTACT NAME.
    string number; // CONTACT NUMBER.
}cntct;

// ARRAY CONTAINING THE SERVICES NAMES THAT THE PROGRAM PROVIDES.
const string MENU_ITEMS[] = 
{   
    "WELCOME TO YOUR PHONE BOOK :\n",  // WELCOME MESSAGE.
    "(1). VIEW ALL CONTACTS.",         // OPTION TO VIEW ALL CONTACTS.
    "(2). ADD NEW CONTACT.",           // OPTION TO ADD A NEW CONTACT.
    "(3). SEARCH YOUR PHONE BOOK.",    // OPTION TO SEARCH CONTACTS.
    "(4). EXIT PROGRAM."               // OPTION TO EXIT THE PROGRAM.
};

// SEPARATOR LINE USED FOR FORMATTING OUTPUT.
const string line = "----------------------------\n";

// FILE STREAM FOR THE USED .CSV FILE.
fstream FS;

// VECTOR THAT WILL CONTAIN CONTACTS SAVED IN THE .CSV FILE.
vector <cntct> CONATCTS;

// FUNCTION DECLARATIONS.
void MAIN_MENU(void);                 // FUNCTION TO PRINT THE MAIN MENU ITEMS.
void VIEW_ALL_CONTACTS(void);         // FUNCTION TO VIEW ALL SAVED CONTACTS.
void ADD_NEW_CONTACT(void);           // FUNCTION TO ADD A NEW CONTACT.
void SEARCH_CONTACTS(void);           // FUNCTION TO SEARCH THE PHONEBOOK.
string GET_STRING (size_t max_length);// FUNCTION TO GET A STRING FROM THE USER. 
void CLEAR_SCREEN(void);              // FUNCTION TO CLEAR THE SCREEN.
void ADD_CONTACTS_TO_VECTOR (void);   // FUNCTION TO ADD .CSV DATA TO THE VECTOR.
void SORT_VECTOR_AND_FILE (void);     // FUNCTION TO SORT VECTOR ELEMENTS AND REWRITE THEM TO THE FILE SORTED.
void FILE_CONTROL_OPEN_AND_CLOSE(char Control); // FUNCTION TO OPEN OR CLOSE THE FILE.
void PRINT_OUT_INPUT(cntct C);        // FUNCTION TO PRINT CONTACT DETAILS BEFORE SAVING.

int main()
{
    // OPENING FILE FOR READING AND WRITING.
    FILE_CONTROL_OPEN_AND_CLOSE('o');
    // ADDING CONTACTS TO VECTOR FOR USE IN THE PROGRAM FLOW.
    ADD_CONTACTS_TO_VECTOR();
    // SORTING THE DATA FROM THE FILE IF NOT ALREADY SORTED.
    SORT_VECTOR_AND_FILE();
    while(true)
    {
        // PRINTING THE MAIN MENU OPTIONS.
        MAIN_MENU();
        int choice;
        cin>>choice;

        // INPUT ERROR HANDLING.
        if(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout<<"RE-CHOOSE THE PREFERRED SERVICE NUMBER";
        }

        switch(choice)
        {
            case 1:// (1.) VIEW ALL CONTACTS.
            {
                CLEAR_SCREEN(); // CLEAR TERMINAL.
                cout<<MENU_ITEMS[1]<<endl; // PRINTING THE CHOSEN OPTION HEADLINE.
                cout<<line<<endl;
                VIEW_ALL_CONTACTS();
                cout << "\nPRESS ENTER TO RETURN TO THE MAIN MENU...";
                cin.ignore();  // REMOVE ANY REMAINING DATA IN THE BUFFER (IMPORTANT BEFORE cin.get()).
                cin.get();     // WAIT FOR THE USER TO PRESS ENTER.
                CLEAR_SCREEN();
            }
            break;

            case 2:// (2.) ADD NEW CONTACT.
            {
                CLEAR_SCREEN(); // CLEAR TERMINAL.
                cout<<MENU_ITEMS[2]<<endl<<line; // PRINTING THE CHOSEN OPTION HEADLINE.
                ADD_NEW_CONTACT(); // ADDING A NEW CONTACT USING THE FUNCTION DEFINED BELOW.
            }
            break;
            
            case 3:// (3.) SEARCH CONTACTS.
            {
                CLEAR_SCREEN(); // CLEAR TERMINAL.
                cout<<MENU_ITEMS[3]<<endl<<line; // PRINTING THE CHOSEN OPTION HEADLINE.
                SEARCH_CONTACTS(); // SEARCHING USING THE FUNCTION DEFINED BELOW.
            }
            break;
            
            case 4:// (4.) EXIT PROGRAM.
            {
                CLEAR_SCREEN(); // CLEAR TERMINAL.
                cout<<"SEE YOU SOON"<<endl<<line; // PRINTING THE CHOSEN OPTION HEADLINE.
                FILE_CONTROL_OPEN_AND_CLOSE('c'); // CLOSING THE FILE SAFELY.
                return 0;
            }
            break;

            default:
            {
                CLEAR_SCREEN(); // CLEAR TERMINAL.
                cout<<"RE-CHOOSE THE PREFERRED SERVICE NUMBER"; // INPUT ERROR HANDLING.
                break;
            }
        }
    }
    return 0;
}

void MAIN_MENU (void)
{
    CLEAR_SCREEN(); // CLEAR TERMINAL.

    // SIZE OF THE GLOBAL ARRAY ABOVE^^^.
    unsigned int MENU_ITEMS_NUMBER = sizeof(MENU_ITEMS)/sizeof(MENU_ITEMS[0]);
    // A LOOP TO PRINT ALL THE MENU ITEMS VERTICALLY.
    for(unsigned int i = 0; i < MENU_ITEMS_NUMBER; i++)
    {
        cout<<MENU_ITEMS[i]<<endl;
    }
    // INSTRUCTION MESSAGE.
    cout<< "\n"<<"FORM 1"<< " TO "<< MENU_ITEMS_NUMBER -1 <<endl;
    cout<<"ENTER PREFERRED CHOICE NUMBER THEN PRESS ""ENTER""  >>  ";
}

void CLEAR_SCREEN(void)
{
#ifdef _WIN32
    system("cls");  // COMPATIBLE WITH WINDOWS.
#else
    system("clear");  // COMPATIBLE WITH LINUX & macOS.
#endif
}

void VIEW_ALL_CONTACTS(void)
{
    // SIMPLY PRINTING CONTACTS SAVED IN THE VECTOR.
    for (const auto& c : CONATCTS)
    {
        cout << left << setw(25) << c.name <<  setw(15) << c.number << endl;
    }
}

void ADD_CONTACTS_TO_VECTOR (void)
{
    // READING LINE BY LINE VERTICALLY.
    string READING_LINE;
    while(getline(FS,READING_LINE))
    {
        // AVOIDING THE HEADER LINE IN THE .CSV FILE.
        if(READING_LINE.empty() || READING_LINE.rfind("name",0) == 0)
        {
            continue;
        }
        // INITIALIZE NAME AND NUMBER FOR TWO STRINGS TO STORE THEM SEPARATELY IN THE VECTOR OF CNTCT.
        string NAME,NUMBER;
        // STRING STREAM TO SEPARATE THE TEXT BEFORE AND AFTER THE ','.
        stringstream STRNG_LN (READING_LINE);
        // STORING DATA BEFORE ',' IN THE NAME FIELD.
        getline(STRNG_LN , NAME , ',');
        // STORING DATA AFTER ',' IN THE NUMBER FIELD.
        getline(STRNG_LN , NUMBER);
        // ADD EACH CONTACT NAME AND NUMBER TO THE VECTOR.
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
    // RE-OPENING THE FILE TO REWRITE SORTED DATA.
    FS.open(DATA_FILE, ios::out | ios::trunc);
    // FILE OPENING ERROR HANDLING.
    if (!FS) 
    {
        cout << "ERROR OPENING FILE IN SORT_VECTOR_AND_FILE\n";
        return;
    }
    // SORTING CONTACTS.
    sort(CONATCTS.begin(),CONATCTS.end(),[](const cntct& a,cntct& b)
    {
        return a.name < b.name;
    });
    // REWRITE THE DATA AFTER SORTING IN THE FILE.
    for ( auto c : CONATCTS)
    {
        FS<<c.name<<','<<c.number<<endl;
    }
}

void FILE_CONTROL_OPEN_AND_CLOSE(char Control)
{
    // CHECKING FUNCTION ARGUMENTS.
    if(Control == 'o' ||Control == 'O')
    {
        FS.open(DATA_FILE, std::ios::in | std::ios::out | std::ios::app);
        if (!FS)
        {
            cout<<"ERROR OPENING FILE IN FILE_CONTROL_OPEN_AND_CLOSE FUNCTION";
            return;
        }
    }
    // CHECKING FUNCTION ARGUMENTS.
    else if(Control == 'c' ||Control == 'C')
    {
        {
            if (FS.is_open()) // CHECKING IF FILE IS STILL OPEN.
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
        // ERROR MESSAGE IF SOMETHING IS WRONG.
        cout<<"ERROR USING ""FILE_CONTROL_OPEN_AND_CLOSE"" FUNCTION ";
    }
}

void ADD_NEW_CONTACT (void)
{
    // DECLARING A CONTAINER TO CONTAIN THE NAME AND NUMBER.
    cntct NEW;

    // PROMPT USER FOR NAME INPUT.
    cout<<"ENTER CONTACT NAME : ";
    NEW.name = GET_STRING(20); // GETTING INPUT USING THE GET_STRING FUNCTION.

    // PROMPT USER FOR NUMBER INPUT.
    cout<<"ENTER CONTACT NUMBER : ";
    NEW.number = GET_STRING(12); // GETTING INPUT USING THE GET_STRING FUNCTION.

    CLEAR_SCREEN(); // CLEAR TERMINAL.
    // PRINTING OUT THE INPUT TO LET THE USER CHECK IT BEFORE SAVING.
    PRINT_OUT_INPUT(NEW); 
    cout<<line<<endl;

    // PRINTING OUT OPTIONS FOR THE INPUT.
    string msg ="1 - CONFIRM SAVING\n2 - RE-ENTER DETAILS\n3 - EXIT TO MAIN MENU WITHOUT SAVING  >>> "; 
    cout<<msg;
    
    int Confirm;
    do
    {   
        cin >> Confirm;
        // INPUT ERROR HANDLING.
        if(cin.fail())
        {
            // CLEAR THE ERROR FLAG.
            cin.clear();
            // IGNORE INVALID INPUT UNTIL THE END OF THE LINE.
            cin.ignore(10000, '\n');
            // PRINT ERROR MESSAGE.
            CLEAR_SCREEN();
            cout << "INVALID CHOICE TRY AGAIN" << endl;
            // PRINT OUT THE INPUT AGAIN.
            PRINT_OUT_INPUT(NEW);
            cout<<line;
            cout << msg << endl;
        }
        else
        {
            // CHOOSING THE PREFERRED CHOICE.
            switch(Confirm)
            {
                case 1:// CONFIRM SAVING.
                {
                    // ADD THE NEW CONTACT TO THE VECTOR.
                    CONATCTS.push_back({NEW.name,NEW.number});
                    // REWRITE THE VECTOR TO THE FILE AFTER SAVING AND SORTING.
                    SORT_VECTOR_AND_FILE();
                    CLEAR_SCREEN(); // CLEAR TERMINAL.
                    cout<<"CONTACT SAVED SUCCESSFULLY PRESS ENTER TO CONTINUE...";
                    // REMOVE ANY REMAINING DATA IN THE BUFFER (IMPORTANT BEFORE cin.get()).
                    cin.ignore();
                    // WAIT FOR THE USER TO PRESS ENTER.
                    cin.get();
                    CLEAR_SCREEN(); // CLEAR TERMINAL.
                    return;
                }
                break;

                case 2:// RE-ENTER DETAILS.
                {
                    // PRINT OUT THE HEADLINE.
                    cout<<MENU_ITEMS[2];
                    CLEAR_SCREEN(); // CLEAR TERMINAL.
                    ADD_NEW_CONTACT(); // RECURSION OF THE FUNCTION UNTIL SAVING OR REFUSING.
                }break;

                case 3:// BACK TO MAIN MENU.
                {
                    CLEAR_SCREEN();
                    return;
                }
                break;

                default:
                {
                    // INPUT ERROR HANDLING.
                    CLEAR_SCREEN();
                    cout<<"INVALID CHOICE TRY AGAIN"<<endl;
                    PRINT_OUT_INPUT(NEW);
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

     // IF THE NEXT CHARACTER IS A NEWLINE, THEN IGNORE IT.
     if(cin.peek() == '\n')
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // PROMPT USER FOR INPUT.
    getline(cin,String);
    // TRUNCATING THE STRING TO GET THE PREFERRED LENGTH.
    if((String).length() > max_length && (String).length()!= 0)
    {
        String = (String).substr(0,max_length);
    }
    // CONVERT ALL CHARACTERS TO LOWERCASE.
    transform(String.begin() , String.end() , String.begin() , ::tolower);
    // IF THE STRING IS NOT EMPTY AND THE FIRST CHARACTER IS ALPHABETIC, CAPITALIZE IT.
    if (!String.empty() && isalpha(String[0]))
    {
        String[0] = toupper(String[0]);
    }

    // FOR EACH CHARACTER STARTING FROM THE SECOND,
    // IF THE PREVIOUS CHARACTER IS A SPACE AND THE CURRENT CHARACTER IS ALPHABETIC, CAPITALIZE IT.
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
    // PROMPT USER TO CHOOSE SEARCH CRITERIA (BY NAME OR NUMBER).
    int searchChoice;
    do
    {
        CLEAR_SCREEN();
        cout << "SEARCH BY:\n"<<line<<"1. NAME\n2. NUMBER\n\n";
        cout << "ENTER YOUR CHOICE (1 OR 2): ";
        cin >> searchChoice;
        
        // HANDLE INVALID INPUT.
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000,'\n');
            cout << "INVALID INPUT!\n";
        }
    }while(searchChoice !=1 && searchChoice != 2);

    // PROMPT USER FOR SEARCH TERM.
    string searchTerm;
    cout << "ENTER SEARCH TERM: ";
    cin.ignore();
    getline(cin, searchTerm);
    
    // CONVERT SEARCH TERM TO LOWERCASE FOR CASE-INSENSITIVE SEARCH.
    transform(searchTerm.begin(), searchTerm.end(), searchTerm.begin(), ::tolower);
    
    // SEARCH FOR MATCHING CONTACTS.
    bool found = false;
    CLEAR_SCREEN();
    cout << "\nSEARCH RESULTS FOR :"<<searchTerm<<endl;
    cout << line << endl;
    
    for(const auto& contact : CONATCTS)
    {
        string compareName = contact.name;
        transform(compareName.begin(), compareName.end(), compareName.begin(), ::tolower);
        
        // CHECK IF SEARCH TERM MATCHES NAME OR NUMBER BASED ON USER CHOICE.
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
    
    // PRINT MESSAGE IF NO MATCHES FOUND.
    if(!found)
    {
        cout << "NO CONTACTS FOUND MATCHING YOUR SEARCH.\n";
    }
    
    cout << line << endl;
    cout << "\nPRESS ENTER TO RETURN TO THE MAIN MENU...";
    cin.get();
    CLEAR_SCREEN();
}

void PRINT_OUT_INPUT(cntct C)
{
    // PRINT THE CONTACT DETAILS BEFORE SAVING.
    cout<<"YOU ARE ABOUT TO SAVE TO YOUR CONTACTS :\n"<<line;
    cout<<"NAME : "<<C.name<<endl; 
    cout<<"NUMBER : "<<C.number<<endl; 
}