**# دليل شامل لاستخدام stringstream في C++**

## **مقدمة**

`stringstream` هي أداة قوية في C++ تُستخدم لمعالجة النصوص وتجزئتها بسهولة. يتم تضمينها في المكتبة `<sstream>` وتساعد في تحويل النصوص إلى بيانات مهيكلة.

---

## **1. ما هو stringstream؟**

`stringstream` هو نوع من **streams** يُستخدم لمعالجة النصوص كما لو كانت تدفقات بيانات. يسمح بتحليل النصوص وفصلها بسهولة.

### **🔹 تعريف stringstream**

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    stringstream ss("123 456 789"); // تحويل النص إلى stream
    int num;
    while (ss >> num) {
        cout << num << endl;
    }
    return 0;
}


**📌 الإخراج:**

```
123
456
789


✅ يتم تقسيم النص تلقائيًا بناءً على المسافات.

---

## **2. الفرق بين stringstream و iostream**

| **المكتبة**  | **الاستخدام**                                   |
| ------------ | ----------------------------------------------- |
| `<iostream>` | الإدخال والإخراج من الـ console (`cin`, `cout`) |
| `<sstream>`  | معالجة النصوص داخل الذاكرة وتحليلها             |

---

## **3. استخدام stringstream لتقسيم النصوص**

يمكن استخدام `stringstream` لفصل النصوص سواء بناءً على المسافات أو باستخدام فاصل معين مثل `,` أو `:`.

### **🔹 التقسيم باستخدام المسافات (افتراضيًا)**

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string text = "hello world c++";
    stringstream ss(text);
    string word;
    
    while (ss >> word) {
        cout << word << endl;
    }
    return 0;
}
```

**📌 الإخراج:**

```
hello
world
c++
```

✅ يتم تقسيم النص بناءً على المسافات تلقائيًا.

### **🔹 التقسيم باستخدام فاصلة **``** كما في CSV**

```cpp
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string text = "apple,banana,grape,orange";
    stringstream ss(text);
    string word;
    
    while (getline(ss, word, ',')) { // استخدام فاصلة كفاصل
        cout << word << endl;
    }
    return 0;
}
```

**📌 الإخراج:**

```
apple
banana
grape
orange
```

✅ `getline(ss, word, ',')` تستخدم الفاصلة كفاصل بين الكلمات.

---

## **4. قراءة بيانات من ملف CSV باستخدام stringstream**

بما أن ملفات CSV تحتوي على بيانات مفصولة بفاصلة، فإن `stringstream` يكون مفيدًا جدًا لاستخراج القيم منها.

### **🔹 مثال: قراءة ملف CSV وحفظ البيانات في vector**

```cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct Contact {
    string name;
    string number;
};

int main() {
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
```

### **📌 الإخراج عند تشغيل البرنامج**

```
Name: ali | Number: 01000407217
Name: randa | Number: 01003965177
Name: ganna | Number: 01090915527
```

✅ `getline(ss, c.name, ',')` يأخذ الاسم قبل الفاصلة `,`. ✅ `getline(ss, c.number)` يأخذ الرقم بعد الفاصلة.

---

## **5. إعادة تعيين stringstream لاستخدامه من جديد**

```cpp
ss.str("");   // تعيين قيمة جديدة فارغة
ss.clear();    // مسح أي أخطاء داخل stream
```

✅ مفيد عندما تحتاج إلى إعادة استخدام نفس `stringstream` لمعالجة بيانات جديدة.

---

## **🎯 الخلاصة**

✅ `stringstream` يُستخدم لتقسيم النصوص وتحليلها بسهولة. ✅ يمكن فصل النصوص باستخدام `getline(ss, var, ',')` لتحديد فاصل مخصص. ✅ `stringstream` مفيد جدًا عند التعامل مع ملفات CSV. ✅ يمكن إعادة تعيين `stringstream` باستخدام `ss.str("")` و `ss.clear()`. 🚀

