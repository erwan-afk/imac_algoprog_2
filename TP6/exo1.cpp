#include "tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{
	/**
	  * Make a graph from a matrix
	  * first create all nodes, add it to the graph then connect them
	  * this->appendNewNode
	  * this->nodes[i]->appendNewEdge
	  */

    for (int i = 0; i < nodeCount; i++) {
            // Create a new GraphNode with the value of i
            GraphNode* newNode = new GraphNode(i);
            // Add the new node to the graph
            this->appendNewNode(newNode);
            for (int j = 0; j < nodeCount; j++) {
                if (adjacencies[i][j] != 0) {
                    // Add a new edge to the node for each non-zero element in the row
                    this->nodes[i]->appendNewEdge(this->nodes[j], adjacencies[i][j]);
                }
            }
        }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	  * Fill nodes array by travelling graph starting from first and using recursivity
	  */
        visited[first->value] = true;
        nodes[nodesSize++] = first;

        Edge* edge = first->edges;
           while (edge != nullptr) {
               GraphNode* destination = edge->destination;
               if (!visited[destination->value]) {
                   deepTravel(destination, nodes, nodesSize, visited);
               }
               edge = edge->next;
           }


}

void Graph::wideTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
	/**
	 * Fill nodes array by travelling graph starting from first and using queue
	 * nodeQueue.push(a_node)
	 * nodeQueue.front() -> first node of the queue
	 * nodeQueue.pop() -> remove first node of the queue
	 * nodeQueue.size() -> size of the queue
	 */
        std::queue<GraphNode*> nodeQueue;
        nodeQueue.push(first);

        while (!nodeQueue.empty()) {
            GraphNode *current = nodeQueue.front();
            nodeQueue.pop();
            visited[current->value] = true;
            nodes[nodesSize++] = current;
            Edge* currentEdge = first->edges;

            while (currentEdge != nullptr)
                    {
                        GraphNode* adjacentNode = currentEdge->destination;
                        if (!visited[adjacentNode->value])
                        {
                            visited[adjacentNode->value] = true;
                            nodeQueue.push(adjacentNode);
                        }
                        currentEdge = currentEdge->next;
                    }

        }
}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
	/**
	  Detect if there is cycle when starting from first
	  (the first may not be in the cycle)
	  Think about what's happen when you get an already visited node
	**/
    visited[first->value] = true;
    Edge* currentEdge = first->edges;
    while (currentEdge != nullptr) {
        if (visited[currentEdge->destination->value]) {
            return true;
        }

        if (!visited[currentEdge->destination->value] && detectCycle(currentEdge->destination, visited)) {
            return true;
        }

        currentEdge = currentEdge->next;
    }

    visited[first->value] = false;
    return false;


}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 150;
	w = new GraphWindow();
	w->show();

	return a.exec();
}
