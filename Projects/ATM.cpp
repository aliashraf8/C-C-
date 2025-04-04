#include<iostream>

using namespace std;

const string MAIN_MENU_ITEMS[]=
{
    "WELCOME :\n----------- ",
    "[1].WITHDRAW",
    "[2].DEPOSIT",
    "[3].BALANCE AND TRANSACTIONS HISTORY",
};
const string LINE ="------------------------------------";

int REMAINING_BALANCE = 5000;

void MAIN_MENU(void);
void WITHDRAW (void);
void DEPOSIT (void);

void PIN_VERFICATION (void);
void CLEAR_SCREEN(void);
void PRINT_REMAINIG_BALANCE(void);
int main()
{
    CLEAR_SCREEN();
    // PIN_VERFICATION();
    
    int choice;
    while(true)
    {
        CLEAR_SCREEN();
        MAIN_MENU();
        PRINT_REMAINIG_BALANCE();
        cout<<"\nENTER NUMBER TO CHOOSE THE PREFERED SERVICE >> "; 
        cin>>choice;
        switch(choice)
        {
            case 1://WITHDRAW.
            {
                WITHDRAW();  
            }
            break;

            case 2:
            {
                DEPOSIT();
            }
            break;

            case 3:
            {

            }
            break;

            default:
            {
                exit(1);
            }
        }
    }
}

void PIN_VERFICATION()
{
    unsigned int pin;
    int COUNT = 3;
    
    while (COUNT > 0) 
    {
        CLEAR_SCREEN();
        cout << "WELCOME..." << endl;
        cout<<"Only "<<COUNT<<" attempts to enter the correct PIN\n";
        cout << "PLEASE ENTER YOUR FOUR DIGIT PIN >>> ";
        cin >> pin;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "INVALID INPUT, press Enter to try again ";
            cin.ignore(); 
            COUNT--;
            continue;
        }

        if (pin < 1000 || pin > 9999) 
        {
            cout << "WRONG PIN, press Enter to try again ";
            cin.ignore();
            cin.get();
            COUNT--;
        } 
        else 
        {
            CLEAR_SCREEN();
            cout << "PIN ACCEPTED. ACCESS GRANTED!\n";
            cout<<LINE<<endl;
            return; 
        }
    }
    cout << "TOO MANY ATTEMPTS. ACCESS DENIED.\n";
    exit (1);
}

void CLEAR_SCREEN(void)
{
#ifdef _WIN32
    system("cls");  // COMPATIBLE WITH WINDOWS.
#else
    system("clear");  // COMPATIBLE WITH LINUX & macOS.
#endif
}

void WITHDRAW (void)
{
    const string error_msg = "INVALID INPUT...PLEASE ENTER NUMERIC AMOUNT LESS THAN"; 
    unsigned int WITHDRAW_AMOUNT;
    
    CLEAR_SCREEN();
    cout<<MAIN_MENU_ITEMS[1]<<endl;
    do 
    {
        PRINT_REMAINIG_BALANCE();
        cout<<"MAXIMUM AMOUT TO WITHDRAW = "<<REMAINING_BALANCE-1<<endl;
        cout<<LINE<<endl;
        cout<<"ENTER AMOUNT YOU WANT TO WITHDRAW >>> ";
        cin>>WITHDRAW_AMOUNT;
        if(cin.fail())
        {
            CLEAR_SCREEN();
            cin.clear();
            cin.ignore(100000,'\n');
            cout<<error_msg<<REMAINING_BALANCE<<endl;
            continue;
        }
        if(WITHDRAW_AMOUNT > REMAINING_BALANCE -1)
        {
            CLEAR_SCREEN();
            cout<<error_msg<<endl;
        }
        else 
        {
            CLEAR_SCREEN();
            REMAINING_BALANCE -= WITHDRAW_AMOUNT;
            PRINT_REMAINIG_BALANCE();
            cout<<"PRESS ENTER TO GO BACK TO MAIN MENU\n";
            cin.ignore();
            cin.get();
            CLEAR_SCREEN();
            break;
        }
    }while(true);
}

void MAIN_MENU(void)
{
    for(string menu : MAIN_MENU_ITEMS )
    {
        cout<<menu<<endl;
    }
}

void PRINT_REMAINIG_BALANCE(void)
{
    cout<<LINE<<endl;
    cout<<"YOUR REMAINING BALANCE = "<<REMAINING_BALANCE<<endl;
    cout<<LINE<<endl;
}

void DEPOSIT (void)
{
    CLEAR_SCREEN();
    cout<<MAIN_MENU_ITEMS[2]<<endl;
    PRINT_REMAINIG_BALANCE();
    unsigned int DEPOSIT_AMOUNT;
    while(true)
    {
        cout<<"ENTER AMOUNT YOU WANT TO DEPOSIT >>> ";
        cin>>DEPOSIT_AMOUNT;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000,'\n');
            continue;
        }
        else
        {
            CLEAR_SCREEN();
            REMAINING_BALANCE += DEPOSIT_AMOUNT;
            PRINT_REMAINIG_BALANCE();
            cout<<"PRESS ENTER TO GO BACK TO MAIN MENU\n";
            cin.ignore();
            cin.get();
            CLEAR_SCREEN();
            break;
        }
    }
}