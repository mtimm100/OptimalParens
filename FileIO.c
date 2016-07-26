/***************************************************************
  Student Name: Mikayla Timm
  File Name: FileIO.c
  Assignment number 5

 * This file implements all of the necessary file input, reading 
 * from MatrixDimensions.txt and matrixData.txt
***************************************************************/
#include "FileIO.h"


/*
 * Opens MatrixDimensions.txt for reading. Gets the number of dimensions
 * and the actual dimensions
 */
void getMatrixDim(MatrixChainP mcp){
    int i = 0;
    FILE *matrixDim = fopen("MatrixDimensions.txt", "r");
    if(matrixDim == NULL){
        fprintf(stderr, "matrix dimensions null.\n");
    }
    fscanf(matrixDim, "%d", &mcp->numMatrices);
    mcp->p = (int*)malloc(sizeof(int) * mcp->numMatrices+1);
    mcp->lengthP = mcp->numMatrices+1;
    for(i=0; i < mcp->lengthP; i++){
        fscanf(matrixDim, "%d", &mcp->p[i]);
    }
    fclose(matrixDim);
}
/*
 * Read in all of the matrix data from matrixData.txt.
 */
void getMatrixData(MatrixChainP mcp){
    int row = 0;
    int column = 0;
    int matrixCounter = 0;
    FILE *matrixData = fopen("matrixData.txt", "r");
    for(matrixCounter = 0; matrixCounter < maxNumMatrices+1; matrixCounter++){
        mcp->matrices[matrixCounter] = (MatrixP)malloc(sizeof(struct Matrix));
        mcp->intermediateMatrices[matrixCounter] = (MatrixP)malloc(sizeof(struct Matrix));
    }

    for(matrixCounter = 0; matrixCounter < mcp->numMatrices; matrixCounter++){
        MatrixP currentMatrix = mcp->matrices[matrixCounter];
        //initialize rows and columns for matrix
        currentMatrix->rows = mcp->p[matrixCounter];
        currentMatrix->columns = mcp->p[matrixCounter+1];
        for(row = 0; row < mcp->p[matrixCounter]; row++){
            for(column = 0; column < mcp->p[matrixCounter+1]; column++){
                fscanf(matrixData, "%ld", &currentMatrix->values[row][column]);
            }
        }
    }
    fclose(matrixData);
}
