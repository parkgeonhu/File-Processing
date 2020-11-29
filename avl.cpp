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
        this->bf = bf;
        this->left = left;
        this->right = right;
    }
};

void updateBF(Node *node, Node *y);
Node *rotateLL(Node **tree, Node **x);
Node *rotateRR(Node **tree, Node **x);
Node *rotateLR(Node **tree, Node **x);
Node *rotateRL(Node **tree, Node **x);

void inorderAVL(Node *node);

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

Node *searchInsertion(Node *node, int key)
{
    Node *parent;
    Node *current = node;
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

Node *searchParent(Node *tree, int key)
{
    Node *parent = NULL;
    Node *current = tree;
    if (tree->key == key)
    {
        return NULL;
    }
    parent = current;
    while (current != NULL)
    {
        Node *left = current->left;
        Node *right = current->right;
        if (current->key == key)
        {
            break;
        }
        parent = current;

        if (key < current->key)
        {
            current = left;
        }
        else
        {
            current = right;
        }
    }
    return parent;
}

int getRotationType() {}

void insertAVL(Node **tree, int newKey)
{
    Node *newNode = new Node(newKey);

    if (*tree == nullptr)
    {
        *tree = newNode;
        return;
    }
    Node *parent = searchInsertion(*tree, newKey);
    //if(parent == NULL){
    //    parent = *tree;
    //}

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

    Node *searchNode = searchParent(*tree, parent->key);
    //inorderAVL(*tree);

    //Node *current = parent;

    if (searchNode != NULL)
    {
        //cout << searchNode->key << " " << searchNode->bf << endl;
        //조상 노드들 중 bf가 1 이상인 것을 찾아내도록 하자.
        bool isRoot = false;
        while (abs(searchNode->bf) <= 1)
        {
            if (*tree == searchNode)
            {
                isRoot = true;
                break;
            }
            //parent 노드의 parent를 구하고
            parent = searchNode;
            searchNode = searchParent(*tree, parent->key);
        }
        if (!isRoot)
        {
            Node *lSubNode = searchNode->left;
            Node *rSubNode = searchNode->right;

            //L
            if (searchNode->bf >= 0)
            {
                //LL
                if (newKey < lSubNode->key)
                {
                    cout << "LL ";
                    rotateLL(tree, &searchNode);
                    updateBF(*tree, newNode);
                }
                //LR
                if (newKey > lSubNode->key)
                {
                    cout << "LR ";
                    rotateLR(tree, &searchNode);
                    updateBF(*tree, newNode);
                }

            }
            //R
            else
            {
                //RR
                if (newKey > rSubNode->key)
                {
                    cout << "RR ";
                    rotateRR(tree, &searchNode);
                    updateBF(*tree, newNode);
                }
                //RL
                else if (newKey < rSubNode->key)
                {
                    //inorderAVL(*tree);
                    cout << "RL ";
                    rotateRL(tree, &searchNode);
                    updateBF(*tree, newNode);
                }
            }
        }
        else
        {
            cout << "NO ";
        }
    }
    else
    {
        cout << "NO ";
    }
}

void updateBF(Node *node, Node *y)
{
    if (node == NULL || y->key == node->key)
    {
        return;
    }
    Node *left = node->left;
    Node *right = node->right;

    int lDepth = getHeight(left);
    int rDepth = getHeight(right);

    int bf = lDepth - rDepth;
    node->bf = bf;

    //cout << node->key << " " << node->bf << endl;

    //if (abs(bf) <= 1)
    //{
    //    return;
    //}

    updateBF(left, y);
    updateBF(right, y);
    //if (y->key < left->key)
    //{
    //    updateBF(left, y);
    //}
    //else if (y->key == node->key)
    //{
    //    return;
    //}
    //else
    //{
    //    updateBF(right, y);
    //}
}

void inorderAVL(Node *node)
{
    if (node == NULL)
        return;

    inorderAVL(node->left);

    cout << node->key << " ";
    cout << "BF : " << node->bf << ", ";

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

// y 삭제, 삽입된 노드
// x : y랑 가장 가까우면서 unbalance
// p : x의 부모노드
Node *rotateLL(Node **tree, Node **near)
{
    Node *parent = searchParent(*tree, (*near)->key);

    Node *sub = (*near)->left;
    (*near)->left = sub->right;
    sub->right = *near;
    //(*near)->bf = 0;

    if (parent == NULL)
    {
        *tree = sub;
    }
    else
    {
        if(sub->key < parent->key){
            parent->left = sub;
        }
        else{
            parent->right = sub;
        }

    }

    return sub;
}

Node *rotateLR(Node **tree, Node **near)
{
    Node *sub = (*near)->left;
    (*near)->left = rotateRR(tree, &sub);
    return rotateLL(tree, near);
}

Node *rotateRL(Node **tree, Node **near)
{
    Node *sub = (*near)->right;
    (*near)->right = rotateLL(tree, &sub);
    return rotateRR(tree, near);
}

Node *rotateRR(Node **tree, Node **near)
{
    Node *parent = searchParent(*tree, (*near)->key);

    Node *sub = (*near)->right;
    (*near)->right = sub->left;
    sub->left = *near;

    if (parent == NULL)
    {
        *tree = sub;
    }
    else
    {
        if(sub->key < parent->key){
            parent->left = sub;
        }
        else{
            parent->right = sub;
        }
    }
    return sub;
}

void testLL()
{
    int testcase[] = {15, 14, 13, 12, 11, 10, 9};
    Node *tree = nullptr;

    for (int i = 0; i < 7; i++)
    {
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        printf("\n");
    }
    cout << endl;
}

void testRR()
{
    int testcase[] = {9, 10, 11, 12, 13, 14, 15};
    Node *tree = nullptr;

    for (int i = 0; i < 7; i++)
    {
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        printf("\n");
    }
    cout << endl;
}

void testEntire()
{
    int testcase[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80,
                      66, 10, 22, 30, 44, 55, 50, 60, 25, 49};
    Node *tree = nullptr;

    for (int i = 0; i < 20; i++)
    {
        insertAVL(&tree, testcase[i]);
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

int main()
{
    testEntire();
}
