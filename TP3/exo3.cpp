#include "mainwindow.h"
#include "tp3.h"
#include <QApplication>
#include <time.h>
#include <stack>
#include <queue>

MainWindow* w = nullptr;
using std::size_t;

struct SearchTreeNode : public Node
{    
    SearchTreeNode* left;
    SearchTreeNode* right;
    int value;

    void initNode(int value)
    {
        this->value = value;
        this->left = NULL;
        this->right = NULL;
    }

	void insertNumber(int value) {
        // create a new node and insert it in right or left child

        if (value < this->value) {
                if (left == NULL) {
                    left = new SearchTreeNode(value);
                    left->initNode(value);
                } else {
                    left->insertNumber(value);
                }
            } else if (value > this->value) {
                if (right == NULL) {
                    right = new SearchTreeNode(value);
                    right->initNode(value);
                } else {
                    right->insertNumber(value);
                }
            }
    }

	uint height() const	{
        uint leftHeight = 0, rightHeight = 0;
            if (left != NULL) {
                leftHeight = left->height();
            }
            if (right != NULL) {
                rightHeight = right->height();
            }
            return std::max(leftHeight, rightHeight) + 1;
    }

	uint nodesCount() const {
        uint leftCount = 0, rightCount = 0;
                if (left != NULL) {
                    leftCount = left->nodesCount();
                }
                if (right != NULL) {
                    rightCount = right->nodesCount();
                }
                return leftCount + rightCount + 1;
	}

	bool isLeaf() const {
        // return True if the node is a leaf (it has no children)
        return (left == NULL) && (right == NULL);

	}

	void allLeaves(Node* leaves[], uint& leavesCount) {
        // fill leaves array with all leaves of this tree
        if (isLeaf()) {
                    leaves[leavesCount++] = this;
                } else {
                    if (left != NULL) {
                        left->allLeaves(leaves, leavesCount);
                    }
                    if (right != NULL) {
                        right->allLeaves(leaves, leavesCount);
                    }
                }
	}

	void inorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with inorder travel
        if (left != NULL) {
                    left->inorderTravel(nodes, nodesCount);
                }
                nodes[nodesCount++] = this;
                if (right != NULL) {
                    right->inorderTravel(nodes, nodesCount);
                }
	}

	void preorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with preorder travel
        nodes[nodesCount++] = this;
                if (left != NULL) {
                    left->preorderTravel(nodes, nodesCount);
                }
                if (right != NULL) {
                    right->preorderTravel(nodes, nodesCount);
                }
	}

	void postorderTravel(Node* nodes[], uint& nodesCount) {
        // fill nodes array with all nodes with postorder travel
        if (left != NULL) {
                    left->postorderTravel(nodes, nodesCount);
                }
                if (right != NULL) {
                    right->postorderTravel(nodes, nodesCount);
                }
                nodes[nodesCount++] = this;
	}

	Node* find(int value) {
        // find the node containing value
        if (this->value == value) {
                    return this;
                } else if (value < this->value && left != NULL) {
                    return left->find(value);
                } else if (right != NULL) {
                    return right->find(value);
                }
                return NULL;
	}

    void reset()
    {
        if (left != NULL)
            delete left;
        if (right != NULL)
            delete right;
        left = right = NULL;
    }

    SearchTreeNode(int value) : Node(value) {initNode(value);}
    ~SearchTreeNode() {}
    int get_value() const {return value;}
    Node* get_left_child() const {return left;}
    Node* get_right_child() const {return right;}
};

Node* createNode(int value) {
    return new SearchTreeNode(value);
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow::instruction_duration = 200;
    w = new BinarySearchTreeWindow<SearchTreeNode>();
	w->show();

	return a.exec();
}
