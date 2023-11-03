#include <iostream>
#include <cassert>
#include <string>
using namespace std;
class QSTException : public exception {
    string message;

public:
    explicit QSTException(const string &msg) : message(msg) {}

    const char *what() const noexcept override {
        return message.c_str();
    }
};
template<typename T>
class QuartenarySearchTree {
private:
    struct Node {
        T data;
        Node *children[4];

        explicit Node(T value) : data(value) {
            for (auto &child : children) {
                child = nullptr;
            }
        }

        ~Node() {
            for (auto &child : children) {
                delete child;
            }
        }
    };

    Node *root;
  
   void deleteNode(Node* parent, Node* node, int childIndex) {
        if (!node) return;

        if (node->children[childIndex]) {
            deleteNode(node, node->children[childIndex], childIndex);
        } else {
            delete node;
            parent->children[childIndex] = nullptr;
        }
    }

public:
    QuartenarySearchTree() : root(nullptr) {}

    void insert(const T &value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }

        Node *current = root;
        while (true) {
            if (value < current->data) {
                if (current->children[0] == nullptr) {
                    current->children[0] = new Node(value);
                    break;
                }
                current = current->children[0];
            } else if (value >= current->data && value < 2 * current->data) {
                if (current->children[1] == nullptr) {
                    current->children[1] = new Node(value);
                    break;
                }
                current = current->children[1];
            } else if (value >= 2 * current->data && value < 3 * current->data) {
                if (current->children[2] == nullptr) {
                    current->children[2] = new Node(value);
                    break;
                }
                current = current->children[2];
            } else {
                if (current->children[3] == nullptr) {
                    current->children[3] = new Node(value);
                    break;
                }
                current = current->children[3];
            }
        }
    }
void remove(const T &val) {
    Node* parent = nullptr;
    Node* current = root;
    int childIndex = 0;

    while (current) {
        if (current->data == val) {
            if (!current->children[0] && !current->children[1] && !current->children[2] && !current->children[3]) {
                // If the node is a leaf node
                if (parent) {
                    parent->children[childIndex] = nullptr;
                } else {
                    root = nullptr;
                }
                delete current;
            } else if ((!current->children[0] || !current->children[1] || !current->children[2] || !current->children[3])) {
                // If the node has one child
                Node* child = nullptr;
                for (int i = 0; i < 4; ++i) {
                    if (current->children[i]) {
                        child = current->children[i];
                        break;
                    }
                }
                if (parent) {
                    parent->children[childIndex] = child;
                } else {
                    root = child;
                }
                current->children[0] = current->children[1] = current->children[2] = current->children[3] = nullptr;
                delete current;
            } else {
                // If the node has two or more children
                Node* successorParent = current;
                Node* successor = current->children[1];
                while (successor->children[0]) {
                    successorParent = successor;
                    successor = successor->children[0];
                }
                current->data = successor->data;
                if (successorParent == current) {
                    current->children[1] = successor->children[1];
                } else {
                    successorParent->children[0] = successor->children[1];
                }
                delete successor;
            }
            break;
        }

        if (val < current->data) {
            parent = current;
            current = current->children[0];
            childIndex = 0;
        } else if (val < current->data * 2) {
            parent = current;
            current = current->children[1];
            childIndex = 1;
        } else if (val < current->data * 3) {
            parent = current;
            current = current->children[2];
            childIndex = 2;
        } else {
            parent = current;
            current = current->children[3];
            childIndex = 3;
        }
    }
}

    void preorderTraversal(Node *node) const {
        if (node) {
            cout << node->data << " ";
            for (auto &child : node->children) {
                preorderTraversal(child);
            }
        }
    }

    void postorderTraversal(Node *node) const {
        if (node) {
            for (auto &child : node->children) {
                postorderTraversal(child);
            }
            cout << node->data << " ";
        }
    }

    void printPreorder() const {
        cout << "preorder traversal is: ";
        preorderTraversal(root);
        cout << endl;
    }

    void printPostorder() const {
        cout << "postorder traversal is: ";
        postorderTraversal(root);
        cout <<endl;
    }
    ~QuartenarySearchTree() {
        delete root;
    }
};

void printMenu() {
    cout << "1. insert element" << endl;
    cout << "2. delete element" << endl;
    cout << "3. pprint preorder traversal" << endl;
    cout << "4. print postorder traversal" << endl;
    cout << "5. exit" << endl;
    
}

int main() {
    try {
        QuartenarySearchTree<int> qst;
       

        while (true) {
            printMenu();
            int choice;
            cout << "enter your choice: ";
            cin >> choice;
             assert(choice >= 1 && choice <= 5 && "invalid choice");
          if (choice == 1) {
                int value;
                cout << "enter element to insert: ";
                cin >> value;
                qst.insert(value);
            } else if (choice == 2) {
                int value;
                cout << "enter element to delete: ";
                cin >> value;
                 qst.remove(value);
            } else if (choice == 3) {
                qst.printPreorder();
            } else if (choice == 4) {
                qst.printPostorder();
            } else if (choice == 5) {
                cout<<"exit";
            } else {
                cout << "invalid choice. please try again." << endl;
            }
        }
    } catch (const QSTException &e) {
        cout << "exception occured: " << e.what() << endl;
    }

    return 0;
}