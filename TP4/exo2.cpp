#include <time.h>
#include <stdio.h>

#include <QApplication>
#include <QDebug>

#include "tp3.h"
#include "tp4.h"
#include "tp4_exo2.h"
#include "HuffmanNode.h"

_TestMainWindow* w1 = nullptr;
using std::size_t;
using std::string;

void processCharFrequences(string data, Array& frequences);
void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize);
HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode);
HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize);

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree);
string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot);


void main_function(HuffmanNode*& huffmanTree)
{
    string data = "Ouesh, bien ou bien ? Ceci est une chaine de caracteres sans grand interet";

    // this array store each caracter frequences indexed by their ascii code
    Array characterFrequences(256);
    characterFrequences.fill(0);
    // this array store each caracter code indexed by their ascii code
    string characterCodes[256];
    HuffmanHeap priorityMinHeap;
    int heapSize = 0;

    processCharFrequences(data, characterFrequences);
    displayCharacterFrequences(characterFrequences);
    buildHuffmanHeap(characterFrequences, priorityMinHeap, heapSize);
    qDebug() << priorityMinHeap.toString().toStdString().c_str();

    huffmanTree = buildHuffmanTree(priorityMinHeap, heapSize);
    huffmanTree->processCodes("");
    string encoded = huffmanEncode(data, huffmanTree);
    string decoded = huffmanDecode(encoded, *huffmanTree);

    qDebug("Encoded: %s\n", encoded.c_str());
    qDebug("Decoded: %s\n", decoded.c_str());
}


void processCharFrequences(string data, Array& frequences)
{
    /**
      * Fill `frequences` array with each caracter frequence.
      * frequences is an array of 256 int. frequences[i]
      * is the frequence of the caracter with ASCII code i
     **/

    int dataSize = data.size();
        for(int i = 0; i < dataSize; i++){
            int asciiCode = (int)data[i];
            frequences[asciiCode] += 1;
        }
}

void HuffmanHeap::insertHeapNode(int heapSize, HuffmanNode* newNode)
{
    /**
      * Insert a HuffmanNode into the lower heap. A min-heap put the lowest value
      * as the first cell, so check the parent should be lower than children.
      * Instead of storing int, the cells of HuffmanHeap store HuffmanNode*.
      * To compare these nodes use their frequences.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/

    // Your code
    int i = heapSize;
    this->set(i, newNode);

        while (i > 0 && this->get(i)->frequences < this->get((i-1)/2)->frequences) {
            this->swap(i, (i-1)/2);
            i = (i-1)/2;
        }

}


void buildHuffmanHeap(const Array& frequences, HuffmanHeap& priorityMinHeap, int& heapSize)
{
    /**
      * Do like Heap::buildHeap. Use only non-null frequences
      * Define heapSize as numbers of inserted nodes
      * allocate a HuffmanNode with `new`
     **/

    // Your code
    heapSize = 0;

        for (int i = 0; i < frequences.size(); i++) {
            if (frequences[i] > 0) {
                HuffmanNode* node = new HuffmanNode(i, frequences[i]);
                priorityMinHeap.insertHeapNode(heapSize, node);
                heapSize++;
            }
        }

}

void HuffmanHeap::heapify(int heapSize, int nodeIndex)
{
    /**
      * Repair the heap starting from nodeIndex. this is a min-heap,
      * so check the parent should be lower than children.
      * this->get(i): HuffmanNode*  <-> this->get(i)->frequences
      * you can use `this->swap(firstIndex, secondIndex)`
     **/
    int smallest = nodeIndex;
    int leftChild = 2 * nodeIndex + 1;
    int rightChild = 2 * nodeIndex + 2;

    if (leftChild < heapSize && this->get(leftChild)->frequences < this->get(smallest)->frequences) {
        smallest = leftChild;
    }

    if (rightChild < heapSize && this->get(rightChild)->frequences < this->get(smallest)->frequences) {
        smallest = rightChild;
    }

    if (smallest != nodeIndex) {
        this->swap(nodeIndex, smallest);
        heapify(heapSize, smallest);
    }

}


HuffmanNode* HuffmanHeap::extractMinNode(int heapSize)
{
    /**
      * Extract the first cell, replace the first cell with the last one and
      * heapify the heap to get a new well-formed heap without the returned cell
      * you can use `this->swap`
     **/

    // Si le tas est vide, renvoyer un pointeur nul
        if (heapSize == 0) {
            return nullptr;
        }

        // Stocker la valeur minimale (la tête)
        HuffmanNode* minNode = get(0);

        // Remplacer la tête par le dernier nœud
        swap(0, heapSize - 1);

        // Décrémenter la taille du tas
        heapSize--;

        // Réparer le tas depuis la racine (index 0)
        heapify(heapSize, 0);

        // Retourner la valeur minimale extraite
        return minNode;
}

HuffmanNode* makeHuffmanSubTree(HuffmanNode* rightNode, HuffmanNode* leftNode)
{
    /**
     * Make a subtree (parent + 2 children) with the given 2 nodes.
     * These 2 characters will be the children of a new parent node which character is '\0'
     * and frequence is the sum of the 2 children frequences
     * Return the new HuffmanNode* parent
     **/
    // Create a new parent node with '\0' as character and sum of the children frequencies as frequency
        int parentFreq = rightNode->frequences + leftNode->frequences;
        HuffmanNode* parentNode = new HuffmanNode('\0', parentFreq);

        // Set the children of the parent node
        parentNode->left = leftNode;
        parentNode->right = rightNode;

        return parentNode;
}

HuffmanNode* buildHuffmanTree(HuffmanHeap& priorityMinHeap, int heapSize)
{
    /**
      * Build Huffman Tree from the priorityMinHeap, pick nodes from the heap until having
      * one node in the heap. For every 2 min nodes, create a subtree and put the new parent
      * into the heap. The last node of the heap is the HuffmanTree;
      * use extractMinNode()
     **/

    // build Huffman tree by taking nodes from the priority min-heap
    while (heapSize > 1) {
        // extract two minimum nodes from the heap
        HuffmanNode* leftNode = priorityMinHeap.extractMinNode(heapSize--);
        HuffmanNode* rightNode = priorityMinHeap.extractMinNode(heapSize--);

        // make a subtree with the two nodes and add it to the heap
        HuffmanNode* parent = makeHuffmanSubTree(rightNode, leftNode);
        parent->frequences = leftNode->frequences + rightNode->frequences;
        priorityMinHeap.insertHeapNode(heapSize++, parent);
    }

    // the last node of the heap is the Huffman tree
    return priorityMinHeap.extractMinNode(heapSize);
}

void HuffmanNode::processCodes(const std::string& baseCode)
{
    /**
      * Travel whole tree of HuffmanNode to determine the code of each
      * leaf/character.
      * Each time you call the left child, add '0' to the baseCode
      * and each time call the right child, add '1'.
      * If the node is a leaf, it takes the baseCode.
     **/

    // If the current node is a leaf, set its code to the baseCode
        if (isLeaf()) {
            code = baseCode;
            return;
        }

        // Traverse the left child and append '0' to the baseCode
        if (left) {
            std::string newBaseCode = baseCode + '0';
            left->processCodes(newBaseCode);
        }

        // Traverse the right child and append '1' to the baseCode
        if (right) {
            std::string newBaseCode = baseCode + '1';
            right->processCodes(newBaseCode);
        }
}

void HuffmanNode::fillCharactersArray(std::string charactersCodes[])
{
    /**
      * Fill the string array with all nodes codes of the tree
      * It store a node into the cell corresponding to its ascii code
      * For example: the node describing 'O' should be at index 79
     **/
    if (!this->left && !this->right)
        charactersCodes[this->character] = this->code;
    else {
        if (this->left)
            this->left->fillCharactersArray(charactersCodes);
        if (this->right)
            this->right->fillCharactersArray(charactersCodes);
    }
}

string huffmanEncode(const string& toEncode, HuffmanNode* huffmanTree)
{
    /**
      * Encode a string by using the huffman compression.
      * With the huffmanTree, determine the code for each character
     **/

    // Your code
    std::string charactersCodes[256]; // array of 256 huffman codes for each character
    huffmanTree->fillCharactersArray(charactersCodes);
    string encoded = "";

    for (char c : toEncode) {
           encoded += charactersCodes[(unsigned char) c];
    }

    return encoded;
}


string huffmanDecode(const string& toDecode, const HuffmanNode& huffmanTreeRoot)
{

    string decoded = "";
    HuffmanNode* currentNode = const_cast<HuffmanNode*>(&huffmanTreeRoot);

    for (char c : toDecode) {
        if (c == '0') {

            currentNode = static_cast<HuffmanNode*>(currentNode->get_left_child());
        }
        else if (c == '1') {

            currentNode = static_cast<HuffmanNode*>(currentNode->get_right_child());
        }

        if (currentNode->isLeaf()) {
            decoded += currentNode->character;
            currentNode = const_cast<HuffmanNode*>(&huffmanTreeRoot);
        }
    }
    return decoded;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Array::wait_for_operations = false;
    w1 = new HuffmanMainWindow(main_function);
    w1->show();
    return a.exec();
}
