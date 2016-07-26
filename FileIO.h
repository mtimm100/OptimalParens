/***************************************************************
  Student Name: Mikayla Timm
  File Name: FileIO.h
  Assignment number 5

 * This file outlines the file IO functions for reading from
 * MatrixDimensions.txt and matrixData.txt
***************************************************************/
#ifndef FILEIO_H
#define	FILEIO_H

#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

/*
 * Opens MatrixDimensions.txt for reading. Gets the number of dimensions
 * and the actual dimensions
 */
void getMatrixDim(MatrixChainP mcp);
/*
 * Read in all of the matrix data from matrixData.txt.
 */
void getMatrixData(MatrixChainP mcp);
#endif