#include "ui/qapp.h"
#include <QApplication>
#include <iostream>
#include <stdlib.h>
#include "src/ia/connection.h"
using namespace std;

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    QApp w;
//    w.show();

//    return a.exec();
    char btaddress[18] = "00:16:53:16:13:88";
        cout << "Hello world!" << endl;
            // initiate bluetooth connection
        if (init_bluetooth(btaddress,1) < 0)      {
             cout << "marche pas " << endl;
        }
}
