#include "flashcardsmainwindow.h"
#include "DBManager.h"
#include <QApplication>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const char* host = "localhost";
    const char* user = "root";
    const char* password = "2512";
    const char* DB = "testdb";

    DBManager db (host,user,password,DB);

    db.SetTable("words");

    std::vector<Line> l;

    l = db.BulkRead();

    FlashCardsMainWindow w(nullptr,&db);

    if(l.size() != 0){
        w.setLines(l);
        w.displayLines();
    }


    w.show();
    return a.exec();
}
