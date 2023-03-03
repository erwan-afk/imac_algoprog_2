#include <QApplication>
#include <time.h>

#include "tp2.h"

MainWindow* w=nullptr;


void bubbleSort(Array& toSort){

    for (uint i=toSort.size(); i>0; i--){
        for (uint j = 1; j<i; j++){

                if(toSort[j-1]>toSort[j]){
                    toSort.swap(j-1,j);
                }


        }

    }

}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 100;
	w = new TestMainWindow(bubbleSort);
	w->show();

	return a.exec();
}
