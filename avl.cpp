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

void updateBF(Node *node);
Node *rotateLL(Node **tree, Node **x);
Node *rotateRR(Node **tree, Node **x);
Node *rotateLR(Node **tree, Node **x);
Node *rotateRL(Node **tree, Node **x);
Node *search(Node *current, int key);
void rotate(Node **tree);

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

    // 새로운 노드 할당, 설정.

    if (newKey < parent->key)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    updateBF(*tree);
    rotate(tree);
    updateBF(*tree);

    //Node *searchNode = searchParent(*tree, parent->key);

    //if (searchNode != NULL)
    //{
    //    //조상 노드들 중 bf가 1 이상인 것을 찾아내도록 하자.
    //    bool isRoot = false;
    //    while (abs(searchNode->bf) <= 1)
    //    {
    //        if (*tree == searchNode)
    //        {
    //            isRoot = true;
    //            break;
    //        }
    //        //parent 노드의 parent를 구하고
    //        parent = searchNode;
    //        searchNode = searchParent(*tree, parent->key);
    //    }
    //    if (!isRoot)
    //    {
    //        Node *lSubNode = searchNode->left;
    //        Node *rSubNode = searchNode->right;

    //        //L
    //        if (searchNode->bf >= 0)
    //        {
    //            //LL
    //            if (newKey < lSubNode->key)
    //            {
    //                cout << "LL ";
    //                rotateLL(tree, &searchNode);
    //                updateBF(*tree);
    //            }
    //            //LR
    //            if (newKey > lSubNode->key)
    //            {
    //                cout << "LR ";
    //                rotateLR(tree, &searchNode);
    //                updateBF(*tree);
    //            }
    //        }
    //        //R
    //        else
    //        {
    //            //RR
    //            if (newKey > rSubNode->key)
    //            {
    //                cout << "RR ";
    //                rotateRR(tree, &searchNode);
    //                updateBF(*tree);
    //            }
    //            //RL
    //            else if (newKey < rSubNode->key)
    //            {
    //                //inorderAVL(*tree);
    //                cout << "RL ";
    //                rotateRL(tree, &searchNode);
    //                updateBF(*tree);
    //            }
    //        }
    //    }
    //    else
    //    {
    //        cout << "NO ";
    //    }
    //}
    //else
    //{
    //    cout << "NO ";
    //}
}

Node *searchNearestParentNotBalanced(Node **tree, Node *node)
{
    bool isRoot = false;
    Node *parent = node;
    Node *searchNode = searchParent(*tree, parent->key);
    if (searchNode == nullptr)
    {
        return nullptr;
    }
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
    return isRoot ? nullptr : searchNode;
}

void rotate(Node **tree)
{

    Node *assumeNode;

    //current를 찾았으면 그것의 부모를 찾는데 부모가 !=nullptr 이어야함
    Node *current = *tree;
    while (abs(current->bf) != 0)
    {
        current = current->bf > 0 ? current->left : current->right;
    }

    Node *parent = searchNearestParentNotBalanced(tree, current);
    //parent가 nullptr 일 때는 current가 *tree
    if (parent == nullptr)
    {
        cout << "NO ";
    }
    else
    {
        //current는 최근 추가된 노드
        cout << "/// present : " << current->key << ", near : " << parent->key << " /// ";
        Node *lSubNode = parent->left;
        Node *rSubNode = parent->right;

        //L
        if (parent->bf >= 0)
        {
            //LL
            if (current->key <= lSubNode->key)
            {
                cout << "LL ";
                rotateLL(tree, &parent);
                updateBF(*tree);
            }
            //LR
            if (current->key > lSubNode->key)
            {
                cout << "LR ";
                rotateLR(tree, &parent);
                updateBF(*tree);
            }
        }
        //R
        else
        {
            //RR
            if (current->key > rSubNode->key)
            {
                cout << "RR ";
                rotateRR(tree, &parent);
                updateBF(*tree);
            }
            //RL
            else if (current->key <= rSubNode->key)
            {
                //inorderAVL(*tree);
                cout << "RL ";
                rotateRL(tree, &parent);
                updateBF(*tree);
            }
        }
    }
}

void deleteBST(Node **tree, int key)
{
    Node *node = search(*tree, key);
    Node *parent = searchParent(*tree, key);

    //node의 자식이 없을 때
    if (nullptr == node->left && nullptr == node->right)
    {
        if (parent == nullptr)
        {
            *tree = nullptr;
        }
        else
        {
            if (node == parent->left)
            {
                parent->left = nullptr;
            }
            else
            {
                parent->right = nullptr;
            }
        }
        delete node;
    }
    //node의 자식이 1개일 때
    else if (nullptr == node->left || nullptr == node->right)
    {
        Node *child = (nullptr != node->left) ? node->left : node->right;
        if (parent == nullptr)
        {
            *tree = child;
        }
        else
        {
            if (node == parent->left)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }
        delete node;
    }
    else
    {
        Node *childParent = node;
        Node *child = node->right;
        while (nullptr != child->left)
        {
            childParent = child;
            child = child->left;
        }
        if (child == childParent->left)
        {
            childParent->left = child->right;
        }
        else
        {
            childParent->right = child->right;
        }
        node->key = child->key;
        node = child;
        delete (node);
    }
}

void deleteAVL(Node **tree, int key)
{
    deleteBST(tree, key);
    updateBF(*tree);
    rotate(tree);
    updateBF(*tree);
}

void updateBF(Node *node)
{
    if (node == NULL)
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

    updateBF(left);
    updateBF(right);
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

Node *rotateLL(Node **tree, Node **near)
{
    Node *parent = searchParent(*tree, (*near)->key);

    Node *sub = (*near)->left;
    (*near)->left = sub->right;
    sub->right = *near;

    if (parent == NULL)
    {
        *tree = sub;
    }
    else
    {
        if (sub->key < parent->key)
        {
            parent->left = sub;
        }
        else
        {
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
        if (sub->key < parent->key)
        {
            parent->left = sub;
        }
        else
        {
            parent->right = sub;
        }
    }
    return sub;
}

void testDelete()
{
    int testcase[] = {15, 14, 13};
    int deleteOrder[] = {14, 13, 15};

    Node *tree = nullptr;

    for (int i = 0; i < 3; i++)
    {
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        printf("\n");
    }

    Node *temp = searchParent(tree, 14);
    //Node * temp1=searchParent(tree, temp->key);

    for (int i = 0; i < 3; i++)
    {
        printf("%d ", deleteOrder[i]);
        deleteAVL(&tree, deleteOrder[i]);
        printf(" : ");
        inorderAVL(tree);
        printf("\n");
    }

    bool result = tree == nullptr ? true : false;
    cout << result << endl;
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

    for (int i = 0; i < 7; i++)
    {
        printf("%d ", testcase[i]);
        deleteAVL(&tree, testcase[i]);
        printf(" : ");
        inorderAVL(tree);
        printf("\n");
    }
}

void testRR()
{
    int testcase[] = {9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
    Node *tree = nullptr;

    for (int i = 0; i < 7; i++)
    {
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        printf("\n");
    }

    for (int i = 6; i >= 0; i--)
    {
        printf("%d ", testcase[i]);
        deleteAVL(&tree, testcase[i]);
        printf(" : ");
        inorderAVL(tree);
        printf("\n");
    }

    cout << endl;
}

void testLR()
{
    int testcase[] = {13, 11, 12};
    Node *tree = nullptr;

    for (int i = 0; i < 3; i++)
    {
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        printf("\n");
    }

    Node *temp1 = search(tree, 12);

    for (int i = 2; i >= 0; i--)
    {
        printf("%d ", testcase[i]);
        deleteAVL(&tree, testcase[i]);
        printf(" : ");
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
        printf("%d ", testcase[i]);
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        printf("\n");
    }
    for (int i = 0; i < 20; i++)
    {
        printf("%d ", testcase[i]);
        deleteAVL(&tree, testcase[i]);
        printf(" : ");
        inorderAVL(tree);
        printf("\n");
    }
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

void testcase1()
{
    int testcase[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44};
    Node *tree = nullptr;

    for (int i = 0; i < 15; i++)
    {
        printf("%d ", testcase[i]);
        insertAVL(&tree, testcase[i]);
        inorderAVL(tree);
        cout << "//// tree :  " << tree->key << endl;
        printf("\n");
    }

    Node *temp = search(tree, 20);
    //Node * temp1=searchParent(tree, temp->key);

    cout << getHeight(temp->right) << endl;
    cout << temp->right->key << endl;
    //cout<<tree->right->key<<endl;

    //for (int i = 0; i < 20; i++)
    //{
    //    printf("%d ", testcase[i]);
    //    deleteAVL(&tree, testcase[i]);
    //    printf(" : ");
    //    inorderAVL(tree);
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
    testcase1();
}
