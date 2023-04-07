#include "tp3.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;
using std::size_t;

/**
 * @brief define indexMin and indexMax as the first and the last index of toSearch
 * @param array array of int to process
 * @param toSearch value to find
 * @param indexMin first index of the value to find
 * @param indexMax last index of the value to find
 */
void binarySearchAll(Array array, int toSearch, int& indexMin, int& indexMax)
{
    indexMin = -1;
    indexMax = -1;

    int start = 0;
    int end = array.size() - 1;

    // Recherche de l'index minimum
    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (array[mid] < toSearch)
        {
            start = mid + 1;
        }
        else if (array[mid] >= toSearch)
        {
            indexMin = mid;
            end = mid - 1;
        }
    }

    // Réinitialisation des variables
    start = 0;
    end = array.size() - 1;

    // Recherche de l'index maximum
    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (array[mid] <= toSearch)
        {
            indexMax = mid;
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    // Si l'élément n'est pas dans le tableau, on réinitialise les index
    if (indexMin == -1 || indexMax == -1)
    {
        indexMin = -1;
        indexMax = -1;
    }
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 500;
	w = new BinarySearchAllWindow(binarySearchAll);
	w->show();

	return a.exec();
}
