/*
 C语言 二维数组输入输出框架
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

// 二叉树节点
typedef struct __treeNode {
    char val;
    struct __treeNode *left;
    struct __treeNode *right;
} BiNode;

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


int main(int argc, const char *argv[])
{
    printf("\n>> -------- %s -------\n", __TIME__);

    printf("使用先序创建二叉树， #表示空节点，请输入二叉树的数据：\n");
    // 示例：-+a##*b##-c##d##/e##f##
    // 前序：-+a*b-cd/ef
    // 中序: a+b*c-d-e/f
    // 后序: abcd-*+ef/-
    // 层序:
    //      -
    //      +/
    //      a*ef
    //      b-
    //      cd
    BiNode *root = CreatBiTreePreOrder();

    PrintResult("前序遍历", PreOrderBiTree, root);
    PrintResult("中序遍历", InOrderBiTree, root);
    PrintResult("后序遍历", PostOrderBiTree, root);

    return 0;
}
