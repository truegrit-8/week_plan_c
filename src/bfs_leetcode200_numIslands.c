#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "leetcode200_numIslands.h"
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
int **que;
int rows;
int cols;
static int dir[4][2] = {{0, 1},    // 右
                        {1, 0},    // 下
                        {-1, 0},   // 上
                        {0, -1}};  // 左

// BFS模版
#if 0
bool visited[rows][cols];
void bfs(int sx, int sy)
{
    queue<pair<int, int>> que;
    // step1. 源点入队
    que.push({sx, sy});
    visited[sx][sy] = true;

    int dx[] = {0, 0, 1, -1};  // 下，上
    int dy[] = {1, -1, 0, 0,}; // 右，左

    // step2. 当队列不为空时，取出队首元素
    while (!que.empty()) {
        pair<int, int> cur = que.front();
        que.pop();

        // step3. 对队首元素进行扩展（遍历孩子）
        int curx = cur.first;
        int cury = cur.second;
        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];
            if (nx > 0 && nx < rows && ny > 0 && ny < cols && !visited[nx][ny]) ) {
                que.push({nx, ny});
                visited[nx][ny] = true;
            }
        }
    }
}
#endif

static void bfs(char** grid, int x, int y)
{
    int left = 0;
    int right = 0;
    // push
    que[right][0] = x;
    que[right++][1] = y;
    visited[x][y] = 1;

    while (left < right) {
        // pop
        int curx = que[left][0];
        int cury = que[left][1];
        left++;

        for (int i = 0; i < 4; i++) {
            int nx = curx + dir[i][0];
            int ny = cury + dir[i][1];
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) {
                continue;
            }
            if (visited[nx][ny] == 0 && grid[nx][ny] == '1') {
                visited[nx][ny] = 1;
                // push
                que[right][0] = nx;
                que[right++][1] = ny;
            }
        }
    }
}

static int numIslands(char** grid, int gridSize, int* gridColSize)
{
    int ans = 0;
    rows = gridSize;
    cols = gridColSize[0];
    int nums = rows * cols;
    que = (int **)malloc(sizeof(int *) * rows * cols);
    for (int i = 0; i < nums; i++) {
        que[i] = (int *)malloc(sizeof(int) * 2);
    }

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
                bfs(grid, i, j); // 将与其链接的陆地都标记上 true
            }
        }
    }
    return ans;
}

void test_bfs_leetcode200_numIslands_case1(void)
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

void test_bfs_leetcode200_numIslands_case2(void)
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

