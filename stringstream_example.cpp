
// برنامج لشرح stringstream في C++

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

// تعريف هيكل لتخزين جهات الاتصال
struct Contact {
    string name;
    string number;
};

int main() {
    cout << "مثال 1: تقسيم النص باستخدام المسافات\n";
    stringstream ss("123 456 789");
    int num;
    while (ss >> num) {
        cout << num << endl;
    }

    cout << "\nمثال 2: تقسيم النص باستخدام فاصلة كما في CSV\n";
    string text = "apple,banana,grape,orange";
    stringstream ss2(text);
    string word;
    while (getline(ss2, word, ',')) {
        cout << word << endl;
    }

    cout << "\nمثال 3: قراءة بيانات من ملف CSV وحفظها في vector\n";
    ifstream file("contacts.csv");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<Contact> contacts;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;
        getline(ss, c.name, ',');
        getline(ss, c.number);
        contacts.push_back(c);
    }
    file.close();

    for (const auto &c : contacts) {
        cout << "Name: " << c.name << " | Number: " << c.number << endl;
    }

    return 0;
}
