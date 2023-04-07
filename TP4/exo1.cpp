#include "tp4.h"
#include "mainwindow.h"

#include <QApplication>
#include <time.h>
#include <stdio.h>

MainWindow* w = nullptr;
using std::size_t;
using std::string;

int Heap::leftChildIndex(int nodeIndex)
{

    return nodeIndex * 2 +1;
}

int Heap::rightChildIndex(int nodeIndex)
{
    return nodeIndex * 2 +2;
}

void Heap::insertHeapNode(int heapSize, int value)
{
	// use (*this)[i] or this->get(i) to get a value at index i
	int i = heapSize;
    (*this)[i] = value;

    while (i>0 && (*this)[i]> (*this)[(i-1)/2]) {
        swap(i,(i-1)/2);
        i = ((i-1)/2);
    }
}

void Heap::heapify(int heapSize, int nodeIndex)
{
	// use (*this)[i] or this->get(i) to get a value at index i

    // Calculer l'indice des enfants gauche et droit
    int leftChildIndex = 2 * nodeIndex + 1;
    int rightChildIndex = 2 * nodeIndex + 2;

    // Trouver l'indice du noeud maximum entre le noeud courant et ses enfants
    int maxIndex = nodeIndex;
    if (leftChildIndex < heapSize && this->get(leftChildIndex) > this->get(maxIndex)) {
        maxIndex = leftChildIndex;
    }
    if (rightChildIndex < heapSize && this->get(rightChildIndex) > this->get(maxIndex)) {
        maxIndex = rightChildIndex;
    }

    // Si le noeud courant n'est pas le maximum, permuter avec le maximum et répéter
    if (maxIndex != nodeIndex) {
        this->swap(nodeIndex, maxIndex);
        heapify(heapSize, maxIndex);
    }
}

void Heap::buildHeap(Array& numbers)
{
    int heapSize = numbers.size();
    for (int i = 0; i < heapSize; i++) {
       insertHeapNode(i,numbers[i]);
    }

}

void Heap::heapSort()
{


    int heapSize = (*this).size();
    for (int i=heapSize-1 ; i>=0 ; i--) {
            swap(0,i);
            heapify(i,0);
        }
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    MainWindow::instruction_duration = 50;
    w = new HeapWindow();
	w->show();

	return a.exec();
}
