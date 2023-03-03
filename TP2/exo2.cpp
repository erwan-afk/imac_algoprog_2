#include <QApplication>
#include <time.h>
#include <QDebug>

#include "tp2.h"

using namespace std;

MainWindow* w=nullptr;

void insertionSort(Array& toSort){
	Array& sorted=w->newArray(toSort.size());

    sorted[0] = toSort[0];
    int taille_trie = sorted.size();

    // insertion sort from toSort to sorted
    for (uint n=1; n<toSort.size(); n++) {

        for (uint m=0; m<sorted.size(); m++) {

            if ( toSort[n] < sorted[m] ){
                                sorted.insert(m,toSort[n]);
                                break;
                            }

            if(toSort[n]>sorted[m]){
                if(sorted[m+1] == -1){
                    sorted.insert(m+1,toSort[n]);
                    break;
                }

            }


        }


    }
	
	toSort=sorted; // update the original array
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    uint elementCount=15; // number of elements to sort
    MainWindow::instruction_duration = 100; // delay between each array access (set, get, insert, ...)
    w = new TestMainWindow(insertionSort); // window which display the behavior of the sort algorithm
	w->show();

	return a.exec();
}
