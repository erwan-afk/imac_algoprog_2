#include "tp6.h"
#include <QApplication>
#include <time.h>

MainWindow* w = nullptr;

void Graph::buildFromAdjenciesMatrix(int **adjacencies, int nodeCount)
{
    for (int nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++) {
        GraphNode* node = new GraphNode(nodeIndex);
        this->appendNewNode(node);
    }

    for (int sourceIndex = 0; sourceIndex < nodeCount; sourceIndex++) {
        for (int destinationIndex = 0; destinationIndex < nodeCount; destinationIndex++) {
            if (adjacencies[sourceIndex][destinationIndex] != 0) {
                GraphNode* sourceNode = nodes[sourceIndex];
                GraphNode* destinationNode = nodes[destinationIndex];
                sourceNode->appendNewEdge(destinationNode);
            }
        }
    }
}

void Graph::deepTravel(GraphNode *first, GraphNode *nodes[], int &nodesSize, bool visited[])
{
     // Marquer le nœud actuel comme visité
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

        // Créer une file d'attente (queue) pour stocker les nœuds à visiter
    std::queue<GraphNode*> nodeQueue;

    // Marquer le nœud initial comme visité et l'ajouter à la liste des nœuds
    visited[first->value] = true;
    nodes[nodesSize++] = first;

    // Enfiler le nœud initial dans la file d'attente
    nodeQueue.push(first);

    // Parcourir la file d'attente jusqu'à ce qu'elle soit vide
    while (!nodeQueue.empty()) {
        // Récupérer le premier nœud de la file d'attente
        GraphNode* current = nodeQueue.front();
        nodeQueue.pop();

        // Parcourir les arêtes du nœud actuel
        Edge* edge = current->edges;
        while (edge != nullptr) {
            GraphNode* destination = edge->destination;
            if (!visited[destination->value]) {
                // Marquer le nœud de destination comme visité
                visited[destination->value] = true;

                // Ajouter le nœud de destination à la liste des nœuds
                nodes[nodesSize++] = destination;

                // Enfiler le nœud de destination dans la file d'attente
                nodeQueue.push(destination);
            }
            edge = edge->next;
        }
    }

}

bool Graph::detectCycle(GraphNode *first, bool visited[])
{
    visited[first->value] = true;

    Edge* edge = first->edges;
    while (edge != nullptr) {
        GraphNode* destination = edge->destination;
        if (visited[destination->value]) {
            // Le nœud de destination a déjà été visité, donc il y a un cycle
            return true;
        } else {
            if (detectCycle(destination, visited)) {
                // Un cycle a été détecté dans le sous-graphe à partir de la destination
                return true;
            }
        }
        edge = edge->next;
    }

    // Aucun cycle détecté à partir de ce nœud
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
