#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "AAAAA_array2DFrame.h"
#include "AAAAA_binaryTree_order.h"
#include "dfs_leetcode797.h"
#include "leetcode200_numIslands.h"

int main(int argc, char *argv[])
{
    printf(">> ------------%s------------\n", __TIME__);

    // test_array2DFrame();
    // test_binaryTree_order();
    test_dfs_leetcode797_case1();
    test_dfs_leetcode200_numIslands_case1();
    test_dfs_leetcode200_numIslands_case2();
    test_bfs_leetcode200_numIslands_case1();
    test_bfs_leetcode200_numIslands_case2();
    // getchar();
    return 0;
}
