#include "mainwindow.h"
#include "custom_list.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    List<int> LinkedList = {1, 2, 3};
    print(LinkedList);

    LinkedList.push_back(4);
    print(LinkedList);

    LinkedList.push_front(0);
    print(LinkedList);

    LinkedList.pop_back();
    print(LinkedList);

    LinkedList.pop_front();
    print(LinkedList);

    std::cout << LinkedList.empty() << LinkedList.size();


    w.show();
    return a.exec();
}
