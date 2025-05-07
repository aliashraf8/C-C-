#include<iostream>
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
        int X = d_in_m - num_of_days_to_add;
        if(day < X)
        {
            day 
        }
        break;
    }
}