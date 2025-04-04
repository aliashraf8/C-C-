
#include <QApplication>
#include <QWidget>
#include <QPushButton>
using namespace std;
int main(int argc, char *argv[])
 {
    QApplication app(argc, argv);
    
    QWidget window;
    window.setWindowTitle("ATM Machine");
    window.setFixedSize(300, 200);
    
    QPushButton *checkBalanceBtn = new QPushButton("Check Balance", &window);
    checkBalanceBtn->setGeometry(50, 50, 200, 40);

    window.show();
    return app.exec();
}