#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

///二叉树前序遍历
void PreOrder(BTNode *root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

///二叉树中序遍历
void InOrder(BTNode *root) {
    if (root == NULL)
        return;

    InOrder(root->left);
    printf("%d ", root->data);
    InOrder(root->right);
}

///二叉树后序遍历
void PostOrder(BTNode *root) {
    if (root == 0)
        return;

    PostOrder(root->left);
    PostOrder(root->right);
    printf("%d ", root->data);
}

///二叉树层序遍历
void TreeLevelOrder(BTNode* root)
{
    Queue q;
    QueueInit(&q);
    if (root)
        QueuePush(&q, root);

    while (!QueueEmpty(&q))
    {
        BTNode* front = QueueFront(&q);
        QueuePop(&q);
        printf("%d ", front->data);

        /// 下一层，入队列
        if (front->left)
            QueuePush(&q, front->left);

        if (front->right)
            QueuePush(&q, front->right);
    }
    printf("\n");

    QueueDestroy(&q);
}

///判断一棵树是否是完全二叉树
int BinaryTreeComplete(BTNode* root)
{
    Queue q;
    QueueInit(&q);
    if (root)
        QueuePush(&q, root);

    while (!QueueEmpty(&q))
    {
        BTNode* front = QueueFront(&q);
        QueuePop(&q);

        if (front == NULL)
        {
            break;
        }

        QueuePush(&q, front->left);
        QueuePush(&q, front->right);
    }

    // 遇到空以后，后面全是空，则是完全二叉树
    // 遇到空以后，后面存在非空，则不是完全二叉树
    while (!QueueEmpty(&q))
    {
        BTNode* front = QueueFront(&q);
        QueuePop(&q);
        if (front != NULL)
        {
            QueueDestroy(&q);
            return false;
        }
    }

    QueueDestroy(&q);
    return true;
}

//遍历计数的方式
//int count = 0;
//void TreeSize(BTNode *root) {
//    if (root == NULL)
//        return;
//
//    ++count;
//    TreeSize(root->left);
//    TreeSize(root->right);
//}

int TreeSize(BTNode *root) {
    return root == NULL ? 0 : TreeSize(root->left) + TreeSize(root->right) + 1;
}

int TreeLeaSize(BTNode *root) {
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    return TreeLeaSize(root->left) + TreeLeaSize(root->right);
}

int TreeHeight(BTNode *root) {
    if (root == NULL)
        return 0;

    int lh = TreeHeight(root->left);
    int rh = TreeHeight(root->right);
    return lh > rh ? lh + 1 : rh + 1;
}

///求第k层的节点个数
int TreeKLevel(BTNode *root, int k) {
    assert(k > 0);

    if (root == NULL)
        return 0;
    if (k == 1)
        return 1;
    return TreeKLevel(root->left, k - 1) + TreeKLevel(root->right, k - 1);
}

///返回x所在的节点
BTNode *TreeFind(BTNode *root, BTDataType x) {
    if (root == NULL)
        return NULL;
    if (root->data == x)
        return root;
    ///先去左树找
    BTNode *lret = TreeFind(root->left, x);
    if (lret)
        return lret;
    ///左树没有找到再去右树找
    BTNode *rret = TreeFind(root->right, x);
    if (rret)
        return rret;

    return NULL;
}

void BinaryTreeDestroy(BTNode *root) {
    if(root == NULL)
        return;
    BinaryTreeDestroy(root->left);
    BinaryTreeDestroy(root->right);
    free(root);
}

BTNode *CreatTree() {
    BTNode *n1 = (BTNode *) malloc(sizeof(BTNode));
    assert(n1);
    BTNode *n2 = (BTNode *) malloc(sizeof(BTNode));
    assert(n2);
    BTNode *n3 = (BTNode *) malloc(sizeof(BTNode));
    assert(n3);
    BTNode *n4 = (BTNode *) malloc(sizeof(BTNode));
    assert(n4);
    BTNode *n5 = (BTNode *) malloc(sizeof(BTNode));
    assert(n5);
    BTNode *n6 = (BTNode *) malloc(sizeof(BTNode));
    assert(n6);
    BTNode *n7 = (BTNode *) malloc(sizeof(BTNode));
    assert(n7);

    n1->data = 1;
    n2->data = 2;
    n3->data = 3;
    n4->data = 4;
    n5->data = 5;
    n6->data = 6;
    n7->data = 7;

    n1->left = n2;
    n1->right = n4;

    n2->left = n3;
    n2->right = NULL;

    n3->left = NULL;
    n3->right = n7;

    n4->left = n5;
    n4->right = n6;

    n5->left = n5->right = NULL;

    n6->left = n6->right = NULL;

    n7->left = n7->right = NULL;


    return n1;
}

int main() {
    BTNode *root = CreatTree();
    PreOrder(root);
    printf("\n");

    InOrder(root);
    printf("\n");

    PostOrder(root);
    printf("\n");

    TreeLevelOrder(root);

    printf("Tree Size:%d\n", TreeSize(root));

    printf("Leaf Size:%d\n", TreeLeaSize(root));

    printf("Tree Height:%d\n", TreeHeight(root));

    printf("Tree K Level:%d\n", TreeKLevel(root, 4));

    printf("Tree Find:%p\n", TreeFind(root, 3));

    BinaryTreeDestroy(root);
    root = NULL;

    return 0;
}
