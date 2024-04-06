#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
/*
200. 岛屿数量
中等
相关标签
相关企业
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

 

示例 1：

输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1
示例 2：

输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'
*/

// 优质题解：https://leetcode.cn/problems/number-of-islands/solutions/211211/dao-yu-lei-wen-ti-de-tong-yong-jie-fa-dfs2-bian-li-/

int **visited;
int rows;
int cols;
int dir[4][2] = {{0, 1},    // 右
                 {1, 0},    // 下
                 {-1, 0},   // 上
                 {0, -1}};  // 左

void dfs2(char** grid, int x, int y)
{
    for (int i = 0; i < 4; i++) {
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if (nextx < 0 || nextx >= rows || nexty < 0 || nexty >= cols) {
            continue;  // 越界了，直接跳过
        }
        if (visited[nextx][nexty] == 0 && grid[nextx][nexty] == '1') {  // 没有访问过的 同时 是陆地的
            visited[nextx][nexty] = 1;
            dfs2(grid, nextx, nexty);
        }
    }
}

int numIslands(char** grid, int gridSize, int* gridColSize)
{
    int ans = 0;
    rows = gridSize;
    cols = gridColSize[0];

    // 二维数组初始化为零
    visited = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        visited[i] = (int *)malloc(sizeof(int) * cols);
        memset(visited[i], 0, sizeof(int) * cols); // 对每一行memset为零，只能初始化为0或-1
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (visited[i][j] == 0 && grid[i][j] == '1') {
                ans++;  // 遇到没访问过的陆地，+1
                dfs2(grid, i, j); // 将与其链接的陆地都标记上 true
            }
        }
    }
    return ans;
}

void test_dfs_leetcode200_numIslands_case1(void)
{
    char grid[4][5] = {{'1', '1', '1', '1', '0'},
                       {'1', '1', '0', '1', '0'},
                       {'1', '1', '0', '0', '0'},
                       {'0', '0', '0', '0', '0'}};
    int gridSize = 4;
    char *gridPtr[4] = {grid[0], grid[1], grid[2], grid[3]};
    int gridColSize[4] = {5, 5, 5, 5};

    int ret = numIslands(gridPtr, gridSize, gridColSize);
    printf("case1: ans = %d\n", ret);
}

void test_dfs_leetcode200_numIslands_case2(void)
{
    char grid[4][5] = {{'1', '1', '0', '0', '0'},
                       {'1', '1', '0', '0', '0'},
                       {'0', '0', '1', '0', '0'},
                       {'0', '0', '0', '1', '1'}};
    int gridSize = 4;
    char *gridPtr[4] = {grid[0], grid[1], grid[2], grid[3]};
    int gridColSize[4] = {5, 5, 5, 5};

    int ret = numIslands(gridPtr, gridSize, gridColSize);
    printf("case2: ans = %d\n", ret);
}

// 版本一
#if 0
class Solution {
   private:
    int dir[4][2] = {0, 1, 1, 0, -1, 0, 0, -1};  // 四个方向
    void dfs2(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y) {
        for (int i = 0; i < 4; i++) {
            int nextx = x + dir[i][0];
            int nexty = y + dir[i][1];
            if (nextx < 0 || nextx >= grid.size() || nexty < 0 || nexty >= grid[0].size()) {
                continue;  // 越界了，直接跳过
            }
            if (!visited[nextx][nexty] && grid[nextx][nexty] == '1') {  // 没有访问过的 同时 是陆地的
                visited[nextx][nexty] = true;
                dfs2(grid, visited, nextx, nexty);
            }
        }
    }

   public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(m, false));

        int result = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!visited[i][j] && grid[i][j] == '1') {
                    result++;  // 遇到没访问过的陆地，+1
                    dfs2(grid, visited, i, j);  // 将与其链接的陆地都标记上 true
                }
            }
        }
        return result;
    }
};
#endif
