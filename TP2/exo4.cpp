#include <QApplication>
#include <time.h>

#include "tp2.h"


MainWindow* w=nullptr;

void recursivQuickSort(Array& toSort, int size)
{
    if(size <= 1){
        return;
    }
	// stop statement = condition + return (return stop the function even if it does not return anything)
	
	Array& lowerArray = w->newArray(size);
	Array& greaterArray= w->newArray(size);
    int lowerSize = 0, greaterSize = 0; // effectives sizes


    int pivot = toSort[0];



    for(uint i = 1; i< size; i++){
        if(toSort[i]<pivot){
            lowerArray.insert(0,toSort[i]);
            lowerSize++;
        }if(toSort[i]>pivot) {
            greaterArray.insert(0,toSort[i]);
            greaterSize++;
        }

    }

    recursivQuickSort(lowerArray, lowerSize);
    recursivQuickSort(greaterArray, greaterSize);

    for(uint i = 0; i< lowerSize; i++){
        toSort[i] = lowerArray[i];

    }
    toSort[lowerSize] = pivot;

    for(uint i = lowerSize+1; i< lowerSize+1+greaterSize; i++){
        toSort[i] = greaterArray[i-lowerSize-1];
    }
}

void quickSort(Array& toSort){
	recursivQuickSort(toSort, toSort.size());
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	uint elementCount=20;
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(quickSort);
	w->show();

	return a.exec();
}
