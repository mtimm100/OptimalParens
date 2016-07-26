/***************************************************************
  Student Name: Mikayla Timm
  File Name: OptimalParensTest.c
  Assignment number 5

 * Compute the optimal parenthesization needed to use the smallest number of
 * scalar multiplications in calculating the result of multiplying matrices.
***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "FileIO.h"
#include "Matrix.h"

int main() {
    printf("1. Computing optimal parenthesization: ");
    MatrixChainP mcp = runPart1();
    printf("\n");
    printf("2. Infix to postfix: ");
    int charCounter = 0;
    inToPost(&charCounter, mcp, 1, mcp->numMatrices);
    printf("\n");
    printf("3. Loading Matrices from matrixData.txt\n");
    getMatrixData(mcp);
    printf("4. Final result:");
    evaluatePostfix(mcp);
    printf("\nDimensions of resulting matrix: %d x %d", mcp->matrices[maxNumMatrices]->rows, mcp->matrices[maxNumMatrices]->columns);
    printf("\nNumber of scalar multiplications: %d\n\n", mcp->numScalarMults);
    display(mcp->matrices[maxNumMatrices]);

    return 0;
}