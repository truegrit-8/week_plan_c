/*
 C语言 二维数组输入输出框架
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

// 二叉树节点
typedef struct __node {
    char val;
    struct __node *left;
    struct __node *right;
} BiNode;

BiNode *CreatBiTreePreOrder(void); // 先序法创建二叉树（递归）
void PreOrderBiTree(BiNode *root);
void InOrderBiTree(BiNode *root);
void PostOrderBiTree(BiNode *root);
void PrintResult(char *msg, void (*p)(BiNode *), BiNode *root);

// 循环队列
#define QUEUE_MAX 32
typedef struct {
    int front;
    int rear;
    int size;
    // BiNode *data; // 数组存放的是节点
    BiNode *data[QUEUE_MAX]; // 数组存放的是节点
} CircleQueue;

// 循环队列初始化和push pop
CircleQueue *InitQueue(void);
bool PushQue(CircleQueue *que, BiNode *pNode);
BiNode *PopQue(CircleQueue *que);

// 输出层序遍历结果：1直接打印, 2一维数组, 3二维数组
void LayerOrderBiTree1(BiNode *root);
char *LayerOrderBiTree2(BiNode *root, int *returnSize);
char **LayerOrderBiTree3(BiNode *root, int *returnSize, int **returnColSize);

// 层序法创建二叉树
BiNode *CreatBiTreeByLayerIt(char *str, int i); // 递归法创建，输入str必须是满二叉树
BiNode *CreatBiTreeByLayer(char *str);

/**
 main函数
 */
int main(int argc, const char *argv[])
{
    printf("\n>> -------- %s -------\n", __TIME__);

    // 答案如下
    // 前序：-+a*b-cd/ef
    // 中序: a+b*c-d-e/f
    // 后序: abcd-*+ef/-
    // 层序:
    //      -
    //      +/
    //      a*ef
    //      b-
    //      cd

#if 0
    printf("使用先序创建二叉树， #表示空节点，请输入二叉树的数据：\n");
    // 示例：-+a##*b##-c##d##/e##f##
    BiNode *root = CreatBiTreePreOrder();
#else
    // 示例：-+/a*ef##b-##########cd########
    // printf("层序创建二叉树， #表示空节点，必须为满二叉树：\n");
    // char str[100] = "-+/a*ef##b-##########cd########";
    // BiNode *root = CreatBiTreeByLayerIt(str, 0);

    // 示例：-+/a*ef##b-######cd####
    printf("层序创建二叉树， #表示空节点：\n");
    char str[100] = "-+/a*ef##b-######cd####"; // 层序创建二叉树， #表示空节点
    BiNode *root = CreatBiTreeByLayer(str);
#endif

    PrintResult("前序遍历", PreOrderBiTree, root);
    PrintResult("中序遍历", InOrderBiTree, root);
    PrintResult("后序遍历", PostOrderBiTree, root);

    /* 方式1：直接打印 */
    PrintResult("层序遍历1", LayerOrderBiTree1, root);

    /* 方式2：一维数组承接 */
    printf("\n>> -------- %s -------\n", "层序遍历2");
    int returnSize;
    char *ret = LayerOrderBiTree2(root, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%c", ret[i]);
    }

    /* 方式3：二维数组承接 */
    printf("\n>> -------- %s -------\n", "层序遍历3");
    int *returnColSize;
    char **ans = LayerOrderBiTree3(root, &returnSize, &returnColSize);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColSize[i]; j++) {
            printf("%c", ans[i][j]);
        }
        printf("\n");
    }

    return 0;
}

/**
 先序创建二叉树，递归方式创建，使用 # 符号进行分隔
 */
BiNode *CreatBiTreePreOrder(void)
{
    BiNode *root;
    char ch;
    scanf("%c", &ch); // 输入节点数据scanf以space、enter、tab结束一次输入
    if (ch == '#') {
        root = NULL;
    } else {
        root = (BiNode *)malloc(sizeof(BiNode));
        root->val = ch;
        root->left = CreatBiTreePreOrder();  // 先序建立左孩子
        root->right = CreatBiTreePreOrder(); // 先序建立右孩子
    }
    return root; // 返回根节点
}

/**
 先序遍历，递归法
 */
void PreOrderBiTree(BiNode *root)
{
    if (root == NULL) {
        return;
    }
    printf("%c", root->val);
    PreOrderBiTree(root->left);
    PreOrderBiTree(root->right);
}

/**
 中序遍历，递归法
 */
void InOrderBiTree(BiNode *root)
{
    if (root == NULL) {
        return;
    }
    InOrderBiTree(root->left);
    printf("%c", root->val);
    InOrderBiTree(root->right);
}

/**
 后序遍历，递归法
 */
void PostOrderBiTree(BiNode *root)
{
    if (root == NULL) {
        return;
    }
    PostOrderBiTree(root->left);
    PostOrderBiTree(root->right);
    printf("%c", root->val);
}

/**
 打印遍历结果
 */
void PrintResult(char *msg, void (*p)(BiNode *), BiNode *root)
{
    printf("\n>> -------- %s -------\n", msg);
    p(root);
    printf("\n");
}

/**
 初始化队列
 */
CircleQueue *InitQueue(void)
{
    CircleQueue *que = (CircleQueue *)malloc(sizeof(CircleQueue));
    // que->data = (BiNode *)malloc(QUEUE_MAX * sizeof(BiNode));
    que->front = 0;
    que->rear = 0;
    que->size = 0;
    return que;
}

/**
 入队
 */
bool PushQue(CircleQueue *que, BiNode *pNode)
{
    if (que->size == QUEUE_MAX) {
        return false; // que is full
    }
    que->rear = (que->rear + 1) % QUEUE_MAX;
    que->data[que->rear] = pNode; // 将节点的地址存入队列中
    que->size++;
    return true;
}

/**
 出队
 */
BiNode *PopQue(CircleQueue *que)
{
    if (que->size == 0) {
        return NULL; // que is empty
    }
    que->front = (que->front + 1) % QUEUE_MAX;
    // pNode = que->data[que->front];
    BiNode *pNode = (BiNode *)malloc(sizeof(BiNode));
    pNode = que->data[que->front];
    que->size--;
    return pNode;
}


/**
 层序遍历：直接打印
 */
void LayerOrderBiTree1(BiNode *root)
{
    BiNode *pNode;
    CircleQueue *que = InitQueue();

    if (root != NULL) {
        PushQue(que, root);
    }

    while (que->size) {
        pNode = PopQue(que);

        printf("%c", pNode->val);

        if (pNode->left) {
            PushQue(que, pNode->left);
        }
        if (pNode->right) {
            PushQue(que, pNode->right);
        }
    }
}

/**
 层序遍历：一维数组承接结果
 */
char *LayerOrderBiTree2(BiNode *root, int *returnSize)
{
    BiNode *pNode;
    CircleQueue *que = InitQueue();

    char *ret = (char *)malloc(sizeof(char) * 20); // 数组大小取20

    if (root != NULL) {
        PushQue(que, root);
    }

    int idx = 0;
    while (que->size) {
        pNode = PopQue(que);

        ret[idx++] = pNode->val;

        if (pNode->left) {
            PushQue(que, pNode->left);
        }
        if (pNode->right) {
            PushQue(que, pNode->right);
        }
    }
    *returnSize = idx;
    return ret;
}

/**
 层序遍历：二维数组承接结果
 */
char **LayerOrderBiTree3(BiNode *root, int *returnSize, int **returnColSize)
{
    BiNode *pNode;
    CircleQueue *que = InitQueue();

    char **ret = (char **)malloc(sizeof(char *) * 10); // 先分配10行
    (*returnColSize) = (int *)malloc(sizeof(int) * 10); // 先分配10行, 后面会修改

    if (root != NULL) {
        PushQue(que, root);
    }

    int row = 0;
    while (que->size) {
        int size = que->size;
        ret[row] = (char *)malloc(sizeof(char) * size); // 每行有size个元素
        (*returnColSize)[row] = size; // 每行有size个元素

        for (int j = 0; j < size; j++) {
            pNode = PopQue(que);
            ret[row][j] = pNode->val;

            if (pNode->left) {
                PushQue(que, pNode->left);
            }
            if (pNode->right) {
                PushQue(que, pNode->right);
            }
        }
        row++; // 遍历每行元素，行数加1
    }
    *returnSize = row;
    return ret;
}

/** 
 层序法创建二叉树，递归法，必须为满二叉树，#表示空节点
*/
BiNode *CreatBiTreeByLayerIt(char *str, int i)
{
    if (i >= strlen(str) || str[i] == '#') {
        return NULL;
    }
    BiNode *root = (BiNode *)malloc(sizeof(BiNode));
    root->val = str[i];
    root->left = CreatBiTreeByLayerIt(str, 2 * i + 1);
    root->right = CreatBiTreeByLayerIt(str, 2 * i + 2);
    return root;
}

/** 
 层序法创建二叉树，字符串输入，#表示空节点
*/
BiNode *CreatBiTreeByLayer(char *str)
{
    CircleQueue *que = InitQueue();
    BiNode *root;
    BiNode *pNode;

    // 对根节点判断是否为空
    int idx = 0;
    char ch = str[idx++];
    // char ch;
    // scanf("%c", &ch);
    if (ch == '#') {
        return NULL;
    }
    root = (BiNode *)malloc(sizeof(BiNode));
    root->val = ch;
    root->left = NULL;
    root->right = NULL;
    PushQue(que, root);

    while(que->size) {
        pNode = PopQue(que);

        // 压入左节点
        // scanf("%c", &ch);
        ch = str[idx++];
        if (ch == '#') {
            pNode->left = NULL;
        } else {
            pNode->left = (BiNode *)malloc(sizeof(BiNode));
            pNode->left->val = ch;
            PushQue(que, pNode->left);
        }

        // 压入右节点
        // scanf("%c", &ch);
        ch = str[idx++];
        if (ch == '#') {
            pNode->right = NULL;
        } else {
            pNode->right = (BiNode *)malloc(sizeof(BiNode));
            pNode->right->val = ch;
            PushQue(que, pNode->right);
        }
    }
    return root;
}
