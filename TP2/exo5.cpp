#include <QApplication>
#include <time.h>
#include "tp2.h"

MainWindow* w=nullptr;

void merge(Array& first, Array& second, Array& result);

void splitAndMerge(Array& origin)
{
    // stop statement = condition + return (return stop the function even if it does not return anything)
    if (origin.size() < 2) {
           return;
       }
    // initialisation
    Array& first = w->newArray(origin.size()/2);
    Array& second = w->newArray(origin.size()-first.size());

    // split


    for (uint i = 0; i < first.size(); i++) {
            first[i] = origin[i];
        }

        for (uint i = 0; i < second.size(); i++) {
            second[i] = origin[first.size() + i];
        }

    // recursiv splitAndMerge of lowerArray and greaterArray
    splitAndMerge(first);
    splitAndMerge(second);

    // merge
    merge(first,second,origin);


}

void merge(Array& first, Array& second, Array& result)
{
       int indexFirst = 0;
       int indexSecond = 0;
       int index = 0;

       for (uint i = 0; i < result.size(); i++) {
           if (indexFirst >= first.size() || indexSecond >= second.size()) {
               break;
           }

           if (first[indexFirst] < second[indexSecond]) {
               result[i] = first[indexFirst];
               indexFirst++;
           } else {
               result[i] = second[indexSecond];
               indexSecond++;
           }

           index++;
       }

       for (uint i = indexFirst; i < first.size(); i++) {
           result[index++] = first[i];
       }
       for (uint i = indexSecond; i < second.size(); i++) {
           result[index++] = second[i];
       }
}

void mergeSort(Array& toSort)
{
    splitAndMerge(toSort);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 50;
    w = new TestMainWindow(mergeSort);
	w->show();

	return a.exec();
}
