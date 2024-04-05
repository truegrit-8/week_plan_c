#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
/*
797. 所有可能的路径
中等
相关标签
相关企业
给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）

 graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。


输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径 0 -> 1 -> 3 和 0 -> 2 -> 3

*/

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

// 全局变量版本，dfs入参个数4
#if 1
int **ans = NULL;  // 返回结果：二维数组
int *stk = NULL;   // 单次路径：一维数组
int ansSize;   // 二维数组行数, 不要在这里初始化
int stkSize;   // path栈的大小, 不要在这里初始化
int *col = NULL;   // 可选：每一行的大小可能不一样

void dfs(int** graph, int graphSize, int* graphColSize, int idx)
{
    if (idx == (graphSize - 1)) {
        // 创建一个临时数组，把栈中的数值全部放入临时数组
        int *tmpPath = (int *)malloc(sizeof(int) * stkSize);
        memcpy(tmpPath, stk, sizeof(int) * stkSize);
        ans[ansSize] = tmpPath;

        // ans[ansSize] = stk;
        col[ansSize] = stkSize;
        ansSize++;
        return;
    }
    for (int i = 0; i < graphColSize[idx]; i++) {
        stk[stkSize++] = graph[idx][i];
        dfs(graph, graphSize, graphColSize, graph[idx][i]);
        stkSize--;
    }
}

int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes)
{
    // 初始化
    ans = (int **)malloc(sizeof(int *) * 16384); // 尽可能大, 否则heap-buffer-overflow
    stk = (int *)malloc(sizeof(int) * 16384); // 尽可能大, 否则heap-buffer-overflow
    col = (int *)malloc(sizeof(int) * 16384); // 尽可能大, 否则heap-buffer-overflow
    ansSize = 0;   // 二维数组行数，在主函数中初始化，而不要在全局变量定义处初始化
    stkSize = 0;   // path栈的大小

    // 将第一点压入栈中
    stk[stkSize++] = 0;
    // 深度搜索
    dfs(graph, graphSize, graphColSize, 0);

    // 二维数组后处理
    *returnSize = ansSize;
    (*returnColumnSizes) = (int *)malloc(sizeof(int) * ansSize);
    for (int i = 0; i < ansSize; i++) {
        (*returnColumnSizes)[i] = col[i];
    }
    return ans;
}

#else // 局部变量版本，dfs入参个数6
int **ans;  // 返回结果：二维数组
int *stk;   // 单次路径：一维数组
int stkSize; // path栈的大小, 不要在这里初始化

void dfs(int** graph, int graphSize, int* graphColSize, int idx, int *returnSize, int **returnColumnSizes)
{
    if (idx == (graphSize - 1)) {
        // 创建一个临时数组，把栈中的数值全部放入临时数组
        int *tmpPath = (int *)malloc(sizeof(int) * stkSize);
        memcpy(tmpPath, stk, sizeof(int) * stkSize);

        ans[*returnSize] = tmpPath;
        (*returnColumnSizes)[*returnSize] = stkSize;
        (*returnSize)++;
        return;
    }
    for (int i = 0; i < graphColSize[idx]; i++) {
        stk[stkSize++] = graph[idx][i];
        dfs(graph, graphSize, graphColSize, graph[idx][i], returnSize, returnColumnSizes);
        stkSize--;
    }
}

int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes)
{
    // 二维数组初始化
    ans = (int **)malloc(sizeof(int *) * 16384); // 尽可能大
    *returnColumnSizes = (int *)malloc(sizeof(int) * 16384); // 尽可能大
    *returnSize = 0;
    // 栈初始化
    stk = (int *)malloc(sizeof(int) * 16384); // 尽可能大
    stkSize = 0;   // path栈的大小

    // 将第一点压入栈中
    stk[stkSize++] = 0;
    // 深度搜索
    dfs(graph, graphSize, graphColSize, 0, returnSize, returnColumnSizes);
    return ans;
}

#endif


void test_dfs_leetcode797_case1(void)
{
    int graph[4][2] = {{1, 2},
                          {3},
                          {3}};
    int graphSize = 4;
    int *graphPtr[4] = {graph[0], graph[1], graph[2], graph[3]};
    int graphColSize[4] = {2, 1, 1, 0};

    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **ret = allPathsSourceTarget(graphPtr, graphSize, graphColSize, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }
}

void test_dfs_leetcode797_case2(void)
{
    int graph[5][3] = {{4, 3, 1},
                       {3, 2, 4},
                       {3},
                       {4}};
    int graphSize = 5;
    int *graphPtr[5] = {graph[0], graph[1], graph[2], graph[3], graph[4]};
    int graphColSize[5] = {3, 3, 1, 1, 0};

    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **ret = allPathsSourceTarget(graphPtr, graphSize, graphColSize, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }
}

void test_dfs_leetcode797_case3(void)
{
    int graph[12][10] = {{4, 3, 11, 5, 7, 8, 10, 2, 1, 6},
                        {2, 9, 3, 11, 10, 6, 7, 4, 5},
                        {10, 7, 9, 4, 3, 6, 11, 5},
                        {9, 4, 11, 6, 8, 10, 7, 5},
                        {5, 7, 6, 9, 8, 11, 10},
                        {8, 7, 11, 9, 10, 6},
                        {10, 7, 11, 9, 8},
                        {9, 10, 11, 8},
                        {10, 9},
                        {11, 10},
                        {11},
                        {}};
    int graphSize = 12;
    int *graphPtr[12] = {graph[0], graph[1], graph[2], graph[3], graph[4], graph[5],
                         graph[6], graph[7], graph[8], graph[9], graph[10], graph[11]};
    int graphColSize[12] = {10, 9, 8, 8, 7, 6, 5, 4, 2, 2, 1, 0};

    int returnSize = 0;
    int *returnColumnSizes = NULL;
    int **ret = allPathsSourceTarget(graphPtr, graphSize, graphColSize, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", ret[i][j]);
        }
        printf("\n");
    }
}


#if 0
class Solution {
private:
    vector<vector<int>> result; // 收集符合条件的路径
    vector<int> stk; // 0节点到终点的路径
    // x：目前遍历的节点
    // graph：存当前的图
    void dfs (vector<vector<int>>& graph, int x) {
        // 要求从节点 0 到节点 n-1 的路径并输出，所以是 graph.size() - 1
        if (x == graph.size() - 1) { // 找到符合条件的一条路径
            result.push_back(stk);
            return;
        }
        for (int i = 0; i < graph[x].size(); i++) { // 遍历节点n链接的所有节点
            stk.push_back(graph[x][i]); // 遍历到的节点加入到路径中来
            dfs(graph, graph[x][i]); // 进入下一层递归
            stk.pop_back(); // 回溯，撤销本节点
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        stk.push_back(0); // 无论什么路径已经是从0节点出发
        dfs(graph, 0); // 开始遍历
        return result;
    }
};
#endif