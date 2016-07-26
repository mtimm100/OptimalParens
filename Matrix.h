/***************************************************************
  Student Name: Mikayla Timm
  File Name: Matrix.h
  Assignment number 5

 * This file outlines all of the functions as well as data structures
 * for the matrix operations, including multiplication and postfix/infix.
***************************************************************/

#ifndef MATRIX_H
#define	MATRIX_H

#include <stdlib.h>
#define maxMS 200
#define maxMatrixDim 20
#define maxNumMatrices 20
typedef struct Matrix *MatrixP;
typedef struct MatrixChain *MatrixChainP;
typedef struct Stack *StackP;

struct Matrix{
    int rows;
    int columns;
    long int values[maxMatrixDim][maxMatrixDim];
};

struct MatrixChain{
    int m[maxMS][maxMS]; //array where we compute optimal number of scalar multiplications
    int s[maxMS][maxMS]; //values of k that enable recreation of the optimal parenthesization
    int *p; //array of dimensions for the parens
    char optimalExpression[maxMS];
    char postfixExpression[maxMS];
    MatrixP intermediateMatrices[maxNumMatrices]; //for storing intermediate results in the postfix calculation
    MatrixP matrices[maxNumMatrices+1]; //matrix array: 1 additional matrix for final result matrix
    int numMatrices; //number of matrices
    int lengthP;
    int numScalarMults;
};

struct Stack{
    int stack[maxMS];
    int top;
};
/*
 * Runs part 1 of the project: finding optimal paren
 */
MatrixChainP runPart1();
/*
 * Dynamic programming solution to finding the optimal parenthesization
 */
void MatrixChainOrder(MatrixChainP mcp);
/*
 * prints and saves the optimal parenthesization
 */
void PrintOptimalParens(int *charCounter, MatrixChainP mcp, int i, int j);
/*
 * Converts the infix expression into postfix
 */
void inToPost(int *charCounter, MatrixChainP mcp, int i, int j);
/*
 * Multiplies two matrices together and saves the result, keeping track of number of scalar multiplications
 */
void matrixMultiplication(MatrixChainP mcp, MatrixP matrix1, MatrixP matrix2, MatrixP result);
/*
 * displays the values in the matrix
 */
void display(MatrixP matrixToShow);
/*
 * Evaluates the multiplication indicated by the postfix expression and saves the result into the last matrix in the
 * matrix array.
 */
void evaluatePostfix(MatrixChainP mcp);
/*
 * Push an index off the stack we're using for evaluating the expression
 */
void pushStack(StackP stack, int value);
/*
 * Pop an index off the stack we're using for evaluating the expression
 */
int popStack(StackP stack);
#endif	/* MATRIX_H */

