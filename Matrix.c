/***************************************************************
  Student Name: Mikayla Timm
  File Name: Matrix.c
  Assignment number 5

 * This file implements all of the functions 
 * for the matrix operations, including multiplication and postfix/infix.
***************************************************************/
#include "Matrix.h"
#include "FileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

//p = dimension struct the dimensions array and the number of dimensions
//s = k values array
//m = struct with array holding number of multiplications for each matrix pair

/*
 * Runs part 1 of the project: finding optimal paren
 */
MatrixChainP runPart1(){
    MatrixChainP mcp = (MatrixChainP)malloc(sizeof(struct MatrixChain));
    mcp->numMatrices = 0;
    getMatrixDim(mcp);
    MatrixChainOrder(mcp);
    int charCounter = 0;
    PrintOptimalParens(&charCounter, mcp, 1, mcp->numMatrices);
    mcp->optimalExpression[charCounter] = '\0'; //add null char to end of expression
    return mcp;
}
/*
 * Dynamic programming solution to finding the optimal parenthesization
 */
void MatrixChainOrder(MatrixChainP mcp){
    int n = mcp->lengthP - 1;
    int k;
    int L, i, j;
    
    for(i = 1; i <= n; i++){
       mcp->m[i][i] = 0;
    }
    for(L = 2; L <= n; L++){
       for(i = 1; i <= n - L + 1; i++){
            j = i + L - 1;
            mcp->m[i][j] = INT_MAX;
            for (k = i; k <= j-1; k++){
             int q = mcp->m[i][k] + mcp->m[k+1][j] + mcp->p[i-1] * mcp->p[k] * mcp->p[j];
             if(q < mcp->m[i][j]){
                mcp->m[i][j] = q;
                mcp->s[i][j] = k;
             }
          }   
       } 
    }    
}
/*
 * prints and saves the optimal parenthesization
 */
void PrintOptimalParens(int *charCounter, MatrixChainP mcp, int i, int j){
    if(i == j){
        printf("A%d", i);
        mcp->optimalExpression[(*charCounter)++] = 'A';
    }
    else{
        mcp->optimalExpression[(*charCounter)++] = '(';
        printf("(");
        PrintOptimalParens(charCounter, mcp,i,mcp->s[i][j]);
        mcp->optimalExpression[(*charCounter)++] = '*';
        printf("*");
        PrintOptimalParens(charCounter, mcp,mcp->s[i][j] + 1, j);
        mcp->optimalExpression[(*charCounter)++] = ')';
        printf(")");
    }
}
/*
 * Converts the infix expression into postfix
 */
void inToPost(int *charCounter, MatrixChainP mcp, int i, int j){
    if(i == j){
        printf("A%d ", i);
        mcp->postfixExpression[(*charCounter)++] = (i-1) + '0';
    }
    else{
        inToPost(charCounter, mcp,i,mcp->s[i][j]);
        inToPost(charCounter, mcp,mcp->s[i][j] + 1, j);
        mcp->postfixExpression[(*charCounter)++] = '*';
        printf("* ");
    }
}
/*
 * Multiplies two matrices together and saves the result, keeping track of number of scalar multiplications
 */
void matrixMultiplication(MatrixChainP mcp, MatrixP matrix1, MatrixP matrix2, MatrixP result){
    int i, j, k;
    for(i = 0; i < matrix1->rows; i++){
        for(j = 0; j < matrix2->columns; j++){
            result->values[i][j] = 0;
            for(k = 0; k < matrix1->columns; k++){
                result->values[i][j] += (matrix1->values[i][k] * matrix2->values[k][j]);
                mcp->numScalarMults++;
            }
        }
    }
    result->rows = matrix1->rows;
    result->columns = matrix2->columns;
}
/*
 * displays the values in the matrix
 */
void display(MatrixP matrixToShow) {
    int i, j;
    for (i = 0; i < matrixToShow->rows; ++i) {
        for (j = 0; j < matrixToShow->columns; ++j) {
            printf("%ld  ", matrixToShow->values[i][j]);
        }
        printf("\n\n");
    }
}
/*
 * Evaluates the multiplication indicated by the postfix expression and saves the result into the last matrix in the
 * matrix array.
 */
void evaluatePostfix(MatrixChainP mcp){
    StackP stack = (StackP)malloc(sizeof(struct Stack));
    stack->top = -1;
    mcp->numScalarMults = 0;
    int index = 0, intermediateCount = 0, offset = 2*maxNumMatrices, i, j;
    while(mcp->postfixExpression[index] != '\0'){
        if(isdigit(mcp->postfixExpression[index])){
            pushStack(stack, mcp->postfixExpression[index] - '0');
        }
        else{
            int index2 = popStack(stack), index1 = popStack(stack);
            MatrixP matrix1, matrix2;
            if(index1 >= offset)
                matrix1 = mcp->intermediateMatrices[index1-offset];
            else
                matrix1 = mcp->matrices[index1];
            if(index2 >= offset)
                matrix2 = mcp->intermediateMatrices[index2-offset];
            else
                matrix2 = mcp->matrices[index2];
            matrixMultiplication(mcp, matrix1, matrix2, mcp->intermediateMatrices[intermediateCount]);
            pushStack(stack, intermediateCount + offset);
            intermediateCount++;
        }
        index++;
    }
    MatrixP result =  mcp->intermediateMatrices[popStack(stack)-offset];
    for(i=0; i < result->rows; i++){
        for(j=0; j < result->columns; j++){
            mcp->matrices[maxNumMatrices]->values[i][j] = result->values[i][j];
        }
    }
    mcp->matrices[maxNumMatrices]->rows = result->rows;
    mcp->matrices[maxNumMatrices]->columns = result->columns;
}
/*
 * Pop an index off the stack we're using for evaluating the expression
 */
int popStack(StackP stack){
    (stack->top)--;
    return stack->stack[stack->top+1];
}
/*
 * Push an index off the stack we're using for evaluating the expression
 */
void pushStack(StackP stack, int value){
    (stack->top)++;
    stack->stack[stack->top] = value;
}


