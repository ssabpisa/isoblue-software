/*
    Library for Huffman Compression
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <compression.h>

#define len(x) ((int)log(x)+1)

/*Node of the huffman tree */
struct node
