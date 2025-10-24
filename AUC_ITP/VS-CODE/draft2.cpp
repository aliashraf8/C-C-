#include <iostream>

using namespace std;

int main() 
{
    float f_wid, f_len;
    float yieldPerFeddan;
    float siloRadius, siloHeight;

    cout << "Enter field width (fieldWidth): ";
    cin >> f_wid;
    cout << "Enter field length (fieldLength): ";
    cin >> f_len;
uu
    float fieldArea = f_wid * f_len;
    float fieldAreaInFeddans = fieldArea / 4200;

    cout << "Enter yield per feddan (yieldPerFeddan): ";
    cin >> yieldPerFeddan;
    float totalYield = fieldAreaInFeddans * yieldPerFeddan;

    cout << "Enter silo radius (siloRadius): ";
    cin >> siloRadius;

    cout << "Enter silo height (siloHeight): ";
    cin >> siloHeight;

    float siloCapacity = 3.14f * siloRadius * siloRadius * siloHeight;
    int requiredSilos = totalYield / siloCapacity;

    if (totalYield > requiredSilos * siloCapacity) {
        requiredSilos += 1;
    }

    cout << "Number of silos needed: " << requiredSilos << endl;

    return 0;
}
