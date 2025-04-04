#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    string filename = "data.csv";

    // 1️⃣ فتح الملف للقراءة
    ifstream file_in(filename);
    if (!file_in) {
        cout << "Error opening file for reading!" << endl;
        return 1;
    }

    cout << "📂 Current File Content:\n";
    string line;
    while (getline(file_in, line)) {
        cout << line << endl;  // طباعة محتوى الملف
    }
    file_in.close();  // إغلاق الملف بعد القراءة

    // 2️⃣ فتح الملف للكتابة (إضافة بيانات جديدة دون حذف القديم)
    ofstream file_out(filename, ios::app);  // ios::app للإضافة فقط
    if (!file_out) {
        cout << "Error opening file for writing!" << endl;
        return 1;
    }

    // إدخال بيانات جديدة
    string name, country;
    int age;

    cout << "\nEnter new contact details:\n";
    cout << "Name: ";
    cin >> name;
    cout << "Age: ";
    cin >> age;
    cout << "Country: ";
    cin >> country;

    // كتابة البيانات الجديدة إلى الملف
    file_out << name << "," << age << "," << country << "\n";
    file_out.close();

    cout << "✅ New data added successfully!" << endl;
    return 0;
}
r