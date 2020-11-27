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

int getHeight(Node *node)
{
    if (node == NULL)
        return 0;
    else
    {
        int lDepth = getHeight(node->left);
        int rDepth = getHeight(node->right);

        if (lDepth > rDepth)
            return (lDepth + 1);
        else
            return (rDepth + 1);
    }
}

Node *searchParent(Node *current, int key)
{
    Node *parent;
    while (current != NULL)
    {
        parent = current;
        if (key < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return parent;
}

void insertAVL(Node **tree, int newKey)
{
    //cout<<(*tree)->key<<endl;
    //Node * root = (*tree);
    //cout<<"1"<<endl;

    Node *newNode = new Node(newKey);

    if (*tree == nullptr)
    {
        *tree = newNode;
        return;
    }
    Node *current = *tree;
    Node *parent = searchParent(current, newKey);

    // 새로운 노드 할당, 설정.

    if (newKey < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    updateBF(*tree, newNode);

    Node *searchNode;
    Node *current = newNode;
    while (abs(current->bf) <= 1)
    {
        searchNode = current;
        Node *left = searchNode->left;
        Node *right = searchNode->right;

        if (searchNode->key < left->key)
        {
            current = left;
        }
        else
        {
            current = right;
        }
    }

    Node *lSubNode = searchNode->left;
    Node *rSubNode = searchNode->left;

    //LL
    if (newKey < lSubNode->key)
    {
    }
    //RR
    else if (newKey > rSubNode->key)
    {
    }
    
    //LR
    else if (newKey > lSubNode->key)
    {
    }

    //RL
    else if (newKey < rSubNode->key)
    {
    }
}

void updateBF(Node *node, Node *y)
{
    Node *left = node->left;
    Node *right = node->right;

    int lDepth = getHeight(left);
    int rDepth = getHeight(right);

    int bf = lDepth - rDepth;
    node->bf = bf;

    if (abs(bf) <= 1)
    {
        return;
    }

    if (y->key < left->key)
    {
        updateBF(left, y);
    }
    else
    {
        updateBF(right, y);
    }
}

// y 삭제, 삽입된 노드
// x : y랑 가장 가까우면서 unbalance
// p : x의 부모노드
//void updateBF(Node ** tree, Node * y, Node **x, Node **p){

//}

void inorderAVL(Node *node)
{
    if (node == NULL)
        return;

    inorderAVL(node->left);

    cout << node->key << " ";

    inorderAVL(node->right);
}

Node *search(Node *current, int key)
{
    if (current == NULL)
        return NULL;
    if (key == current->key)
    {
        return current;
    }
    else if (key < current->key)
    {
        search(current->left, key);
    }
    else
    {
        search(current->right, key);
    }
}

//Node *searchNearest(Node *current, int key)
//{
//    if (current == NULL)
//        return NULL;
//    if (key == current->key)
//    {
//        return current;
//    }
//    else if (key < current->key)
//    {
//        search(current->left, key);
//    }
//    else
//    {
//        search(current->right, key);
//    }
//}

void rotateLL(Node **tree, Node *x, Node *p)
{
}

void rotateLR(Node **tree, Node *x, Node *p)
{
}

void rotateRL(Node **tree, Node *x, Node *p)
{
}

void rotateRR(Node **tree, Node *x, Node *p)
{
}

int main()
{
    int testcase[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80,
                      66, 10, 22, 30, 44, 55, 50, 60, 25, 49};
    Node *tree = nullptr;

    //Node * node = new Node(3);

    //tree = &node;

    //cout<<(*tree)->key<<endl;

    //if(tree==nullptr){
    //    cout<<"dd"<<endl;
    //}

    for (int i = 0; i < 20; i++)
    {
        insertAVL(&tree, testcase[i]);
        printf(" : ");
        inorderAVL(tree);
        printf("\n");
    }
    //for (int i = 0; i < 20; i++)
    //{
    //    printf("%d ", testcase[i]);
    //    deleteAVL(&T, testcase[i]);
    //    printf(" : ");
    //    inorderAVL(T);
    //    printf("\n");
    //}
    //​ T = NULL;

    //for (int i = 0; i < 20; i++)
    //{
    //    printf("%d ", testcase[i]);
    //    insertAVL(&T, testcase[i]);
    //    printf(" : ");
    //    inorderAVL(T);
    //    printf("\n");
    //}
    //for (int i = 19; 0 <= i; i--)
    //{
    //    printf("%d ", testcase[i]);
    //    deleteAVL(&T, testcase[i]);
    //    printf(" : ");
    //    inorderAVL(T);
    //    printf("\n");
    //}
}
