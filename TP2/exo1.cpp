#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w = nullptr;

void selectionSort(Array& toSort){

    int min_val = toSort[0];
    int min_index = 0;

    for (uint j=0; j<toSort.size(); j++)
    {
        for (uint i=1; i<toSort.size(); i++)
        {
            if(toSort[i] < min_val){
                min_index = i;
            }

        }

        toSort.swap(min_index, j);


    }





}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(selectionSort); // window which display the behavior of the sort algorithm
    w->show();

	return a.exec();
}
