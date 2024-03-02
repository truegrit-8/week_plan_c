/*
 C语言 二维数组输入输出框架
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"

#define MAP_ROW 3 // 三行

// ------------------------ 二维数组作为入参 ------------------------
// 假设需要输入如下数据
// [[10, 20], [11, 21, 31], [41]]
void Array2DFrameInput(int **input, int inputSize, int *inputColSize)
{
    printf(">> ------------- input case -------------\n");
    for (int i = 0; i < inputSize; i++) {
        for (int j = 0; j < inputColSize[i]; j++) {
            printf("%2d ", input[i][j]);
        }
        printf("\n");
    }
}

// ------------------------ 二维数组作为返回 ------------------------
// 假设需要输出如下数据
// [[11, 21], [12, 22, 32], [42]]
int **Array2DFrameOutput(int *returnSize, int **returnColSize)
{
    // step1. 第1个malloc. 申请二维指针, 行数尽可能大，行数最后以*returnSize返回
    *returnSize = MAP_ROW;
    int **ret = (int **)malloc(sizeof(int *) * MAP_ROW);

    // step2. 第2个mallco. 为每行申请指针，指定每行有多少个元素
    ret[0] = (int *)malloc(sizeof(int) * 2); // 第一行有2个元素
    ret[1] = (int *)malloc(sizeof(int) * 3); // 第二行有3个元素
    ret[2] = (int *)malloc(sizeof(int) * 1); // 第三行有1个元素

    // step3. 第3个malloc. 对返回的数组申请空间，指定每行有多少个元素
    (*returnColSize) = (int *)malloc(sizeof(int) * MAP_ROW); // 一共有3行
    (*returnColSize)[0] = 2; // 返回的数组中，第一行有2个元素
    (*returnColSize)[1] = 3; // 返回的数组中，第二行有3个元素
    (*returnColSize)[2] = 1; // 返回的数组中，第三行有1个元素

    // step4. 给每一个元素赋值
    ret[0][0] = 11;
    ret[0][1] = 21;
    ret[1][0] = 12;
    ret[1][1] = 22;
    ret[1][2] = 32;
    ret[2][0] = 42;

    return ret; // 别忘记返回二维指针
}


// ------------------------ 输入示例 main 函数------------------------
int main(int argc, const char *argv[])
{
#if 1 // 方式一：动态分配
    // step1. 确定行数，动态申请二维指针
    int inputSize = MAP_ROW;
    int **input = (int **)malloc(inputSize * sizeof(int *));

    // step2. 为每一行，动态申请一维指针
    input[0] = (int *)malloc(2 * sizeof(int));
    input[1] = (int *)malloc(3 * sizeof(int));
    input[2] = (int *)malloc(1 * sizeof(int));

    // step3. 每行有多少个元素，需要一个数组来存储记录
    int *inputColSize = (int *)malloc(inputSize * sizeof(int));
    inputColSize[0] = 2;
    inputColSize[1] = 3;
    inputColSize[2] = 1;

    // step4. 赋值
    input[0][0] = 10;
    input[0][1] = 20;
    input[1][0] = 11;
    input[1][1] = 21;
    input[1][2] = 31;
    input[2][0] = 41;

    Array2DFrameInput(input, inputSize, inputColSize);

    // 动态申请的内存记得释放
    for (int i = 0; i < inputSize; i++) {
        for (int j = 0; j < inputColSize[i]; j++) {
        }
        free(input[i]);
    }
    free(input);
    free(inputColSize);

#else // 方式二：二维数组定义初始化，无需释放内存
    int inputSize = MAP_ROW;
    int input[MAP_ROW][3] = {{10, 20},
                             {11, 21, 31},
                             {41}};
    // 将类型int(*)[3]转换为int**
    int *inputPtr[MAP_ROW] = {input[0], input[1], input[2]};
    int inputColSize[MAP_ROW] = {2, 3, 1};

    // 注意第1个入参的类型为int**，而二维数组名input的类型为int(*)[3]
    Array2DFrameInput(inputPtr, inputSize, inputColSize);

#endif

    int returnSize;
    int *returnColSize;

    int **ret = Array2DFrameOutput(&returnSize, &returnColSize);

    printf(">> ------------- output case -------------\n");
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColSize[i]; j++) {
            printf("%2d ", ret[i][j]);
        }
        printf("\n");
        free(ret[i]);
    }
    free(ret);
    free(returnColSize);

    return 0;
}
