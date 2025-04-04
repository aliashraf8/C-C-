#include<iostream>
#include<algorithm>

using namespace std;

string GET_STRING (size_t max_length);

int main()
{
    cout<<"enter name  :";
    string name = GET_STRING(20);
    cout<<"enter number  :";
    string number = GET_STRING(10);
    cout<<name<<','<<number<<endl;
}

string GET_STRING (size_t max_length)
{
    string String;

      // 🔍 التحقق إذا كان هناك بيانات متبقية في الـ buffer قبل `getline()`
      if (cin.peek() != '\n')  
      {
          cin.ignore();  // 🛑 مسح الـ buffer إذا كان فيه حاجة
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