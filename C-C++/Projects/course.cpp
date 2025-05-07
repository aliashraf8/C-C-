#include <iostream>

using namespace std;

int day, month, year, d_in_m;
int num_of_days_to_add;

int main()
{
    system("cls");
    cout << "Enter today's date (day month year): ";
    cin >> day >> month >> year;
    cout<<"HOW MANY DAYS WOULD YOU LIKE TO COUNT ?";
    cin>> num_of_days_to_add;
    switch(month) 
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            d_in_m = 31;
            break;
        case 4: case 6: case 9: case 11:
            d_in_m = 30;
            break;
        case 2:
            if ((year % 4 == 0))
                d_in_m = 29;
            else
                d_in_m = 28;
            break;
        default:
            cout << "try again";
    }
    
    for(int i = 0; i < num_of_days_to_add; i++)
    {   
        day++;
        if (day > d_in_m)
        {
            day = 1;
            month++;
            if (month > 12) 
            {
                month = 1;
                year++;
            }
        }
    }
    cout << "date is: " << day << "/" << month << "/" << year ;
    return 0;
}
