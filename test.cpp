#include <iostream>
using namespace std;

class Node
{
public:
    Node *left, *right;
    int key, bf;

    Node(int key, int bf = 0, Node *left = NULL, Node *right = NULL)
    {
        this->key = key;
        this->left = left;
        this->right = right;
    }
};

void insertAVL(Node ** tree, int newKey)
{
    //cout<<(*tree)->key<<endl;
    //Node * root = (*tree);
    //cout<<"1"<<endl;

    Node *newNode = new Node(newKey);

    if (tree==NULL)
    {
        cout<<"ddd"<<endl;
        tree = &newNode;
        return;
    }
    Node *current = *tree;
    Node *parent;

    while (current != NULL)
    {
        parent = current;
        if (newKey < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    // 새로운 노드 할당, 설정.

    if (newKey < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
}

void inorderAVL(Node * node)
{
    if (node == NULL)
        return;

    inorderAVL(node->left);

    cout << node->key << " ";

    inorderAVL(node->right);
}


int main()
{
    int testcase[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80,
                      66, 10, 22, 30, 44, 55, 50, 60, 25, 49};
    Node * tree = nullptr;

    Node * node = new Node(3);

    tree = &node;

    cout<<(*tree)->key<<endl;

    if(tree==nullptr){
        cout<<"dd"<<endl;
    }

    int ** temp;
    int * temp1=*temp;
    cout<<temp1<<endl;

}
