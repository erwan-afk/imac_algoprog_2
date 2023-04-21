#include <tp5.h>
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;


std::vector<string> TP5::names(
{
    "Yolo", "Anastasiya", "Clement", "Sirine", "Julien", "Sacha", "Leo", "Margot",
    "JoLeClodo", "Anais", "Jolan", "Marie", "Cindy", "Flavien", "Tanguy", "Audrey",
    "Mr.PeanutButter", "Bojack", "Mugiwara", "Sully", "Solem",
    "Leo", "Nils", "Vincent", "Paul", "Zoe", "Julien", "Matteo",
    "Fanny", "Jeanne", "Elo"
});


int HashTable::hash(std::string element)
{
    int hashValue = 0;

    // Calculate the sum of the ASCII values of all characters in the string
    for (char c : element) {
        hashValue += c;
    }

    // Take the modulo of the sum with the size of the hash table to get the hash value
    return hashValue % this->size();
}

void HashTable::insert(std::string element)
{
    int index = hash(element) % this->size(); // get index based on hash value
    (*this)[index] = element; // insert element at index
}

/**
 * @brief buildHashTable: fill the HashTable with given names
 * @param table table to fiil
 * @param names array of names to insert
 * @param namesCount size of names array
 */
void buildHashTable(HashTable& table, std::string* names, int namesCount)
{
    for (int i = 0; i < namesCount; i++)
    {
        table.insert(names[i]); // insert each name into the table
    }
}

bool HashTable::contains(std::string element)
{
    int index = hash(element) % this->size(); // get index based on hash value
    return (*this)[index] == element; // check if element is at index
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 10;
	w = new HashWindow();
	w->show();

	return a.exec();
}
