//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AList.h"
#include "Node.h"
#include "FileList.h"

// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

FileList::FileList()
: pHead(nullptr),
NumNodes(0)
{
	// Hint you might need to rework this...
	// if you add data to FileList class
}

FileList::~FileList()
{
	// Hint you might need to rework this...
	Node* curr = pHead;
	while (curr != nullptr)
	{
		Node* next = curr->pNext;
		delete curr;
		curr = next;
	}
}


void FileList::WriteToFile(const char * const pFileName, AList *pAList)
{
	// Do your magic

	// Make sure you close the file after you fill it
	// Use fopen,fwrite,ftell,...,fclose

	// Hint: Open the file, write the nodes into the file 

	// Ungrads - You need to store the data and reconstruct the linked list
	//           You can use as many new/deletes as needed

	// Everyone - Fill in your destructor.

	// Quick sample code... remove this code and replace with your own

	FILE* pFileHandle = nullptr;
	errno_t status;
	status = fopen_s(&pFileHandle, pFileName, "wb");

	fwrite(&NumNodes, sizeof(int), 1, pFileHandle);
	Node* curr = pAList->GetHead();
	while (curr != nullptr)
	{
		fwrite(&(curr->x), sizeof(unsigned int), 1, pFileHandle);
		fwrite(&(curr->y), sizeof(unsigned int), 1, pFileHandle);
		fwrite(&(curr->z), sizeof(unsigned int), 1, pFileHandle);
		fwrite(&(curr->key), sizeof(unsigned int), 1, pFileHandle);
		curr = curr->pNext;
	}
	fclose(pFileHandle);

}

FileList::FileList(const char * const pFileName, int numNodes)
{
	// Do your magic here:

	// Create the Linked List... You cannot use the original code
	// The input file, and numNodes is all you need to recreate the FileList
	
	// Hint: Open the file, read and create new nodes, 
	//       fill them with the data from the file

	// Ungrads - You need to store the data and reconstruct the linked list
	//           You can use as many new/deletes as needed

	// Everyone - Fill in your destructor.

	// Quick sample code... remove this code and replace with your own

	this->pHead = nullptr;
	this->NumNodes = numNodes;

	FILE* pFileHandle;

	errno_t status;
	assert(pFileName);
	status = fopen_s(&pFileHandle, pFileName, "rb");
	assert(pFileHandle);
	assert(status == 0);

	int fileNumNodes;
	fread(&fileNumNodes, sizeof(int), 1, pFileHandle);
	assert(fileNumNodes == NumNodes);

	for (int i = 0; i < NumNodes; ++i)
	{
		Node* newNode = new Node();
		fread(&newNode->x, sizeof(unsigned int), 1, pFileHandle);
		fread(&newNode->y, sizeof(unsigned int), 1, pFileHandle);
		fread(&newNode->z, sizeof(unsigned int), 1, pFileHandle);
		fread(&newNode->key, sizeof(unsigned int), 1, pFileHandle);

		if (pHead == nullptr)
		{
			pHead = newNode;
		}
		else
		{
			Node* curr = pHead;
			while (curr->pNext != nullptr)
			{
				curr = curr->pNext;
			}
			curr->pNext = newNode;
			newNode->pPrev = curr;
		}
	}

	fclose(pFileHandle);
}

// ---  End of File ---
