//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Boustrophedonic.h"

void Boustropehedic::Remove(Node *&pHead, int row, int col)
{
    if (pHead == nullptr)
        return;

    Node* currNode = pHead;
    Node* north = nullptr;
    Node* east = nullptr;
    Node* south = nullptr;
    Node* west = nullptr;
    int currRow = 0;
    int currCol = 0;
    bool evenRow = row % 2 == 0;
    // traverse list
    if (evenRow == true) {
        while (currRow < row) {
            currNode = currNode->pEast;
            currNode = currNode->pSouth;
            currNode = currNode->pWest;
            currNode = currNode->pSouth;
            currRow += 2;
        }
        while (currCol < col) {
            currNode = currNode->pEast;
            currCol += 1;
        }
    }
    else {
        while (currCol < col) {
            currNode = currNode->pEast;
            currCol += 1;
        }
        while (currRow < row) {
            if (currNode->pSouth == nullptr) {
                currNode = currNode->pEast;
                currNode = currNode->pSouth;
                currNode = currNode->pWest;
            }
            else {
                currNode = currNode->pSouth;
            }
            currRow += 1;
        }
    }
    
    //find adjacent nodes
    Node* north, east, south, west;
    if (row == 0)
        north = nullptr;
    else if (currNode->pNorth != nullptr)
        north = currNode->pNorth;
    else
        north = currNode->pWest->pNorth->pEast;

    printf("%d, %d\n", currRow, currCol);
}

// ---  End of File ---

