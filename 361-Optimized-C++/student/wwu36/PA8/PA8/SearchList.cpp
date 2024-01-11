//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "SearchList.h"
#include "Node.h"
#include "AList.h"

// --------------------------------
// -->    MODIFY This FILE    <----
// --------------------------------

Node* split(Node* head)
{
    Node* fast = head, * slow = head;
    while (fast->pNext && fast->pNext->pNext)
    {
        fast = fast->pNext->pNext;
        slow = slow->pNext;
    }
    Node* temp = slow->pNext;
    slow->pNext = NULL;
    return temp;
}

// Function to merge two linked lists
Node* merge(Node* first, Node* second)
{
    // If first linked list is empty
    if (!first)
        return second;

    // If second linked list is empty
    if (!second)
        return first;

    // Pick the smaller value
    if (first->key < second->key)
    {
        first->pNext = merge(first->pNext, second);
        first->pNext->pPrev = first;
        first->pPrev = NULL;
        return first;
    }
    else
    {
        second->pNext = merge(first, second->pNext);
        second->pNext->pPrev = second;
        second->pPrev = NULL;
        return second;
    }
}

Node* mergeSort(Node* head)
{
    if (!head || !head->pNext)
        return head;
    Node* second = split(head);

    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the two sorted halves
    return merge(head, second);
}

void SearchList::MergeSort()
{
    this->pHead = mergeSort(this->pHead);
}

void sortedInsert(Node*& head_ref, Node* newNode)
{
    Node* current;

    // if list is empty
    if (head_ref == NULL)
        head_ref = newNode;

    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if ((head_ref)->key >= newNode->key) {
        newNode->pNext = head_ref;
        newNode->pNext->pPrev = newNode;
        head_ref = newNode;
    }

    else {
        current = head_ref;

        // locate the node after which the new node
        // is to be inserted
        while (current->pNext != NULL &&
            current->pNext->key < newNode->key)
            current = current->pNext;

        /*Make the appropriate links */

        newNode->pNext = current->pNext;

        // if the new node is not inserted
        // at the end of the list
        if (current->pNext != NULL)
            newNode->pNext->pPrev = newNode;

        current->pNext = newNode;
        newNode->pPrev = current;
    }
}

void SearchList::InsertionSort()
{
    // Initialize 'sorted' - a sorted doubly linked list
    Node* sorted = nullptr;

    // Traverse the given doubly linked list and
    // insert every node to 'sorted'
    Node* curr = pHead;
    while (curr != NULL) {

        // Store ppNext for ppNext iteration
        Node* ppNext = curr->pNext;

        // removing all the links so as to create 'curr'
        // as a new node for insertion
        curr->pPrev = curr->pNext = NULL;

        // insert curr in 'sorted' doubly linked list
        sortedInsert(sorted, curr);

        // Update curr
        curr = ppNext;
    }

    // Update head_ref to point to sorted doubly linked list
    this->pHead = sorted;
}

void SearchList::MergeComboSort(int CutoffLength)
{
    this->pHead = _MergeComboSort(pHead, CutoffLength);
}

Node* SearchList::_MergeComboSort(Node* head, int cutoffLength)
{
    if (!head || !head->pNext)
        return head;
    if (this->NumNodes <= cutoffLength)
    {
        InsertionSort();
        return pHead;
    }

    Node* secondHalf = split(head);
    head = _MergeComboSort(head, cutoffLength);
    secondHalf = _MergeComboSort(secondHalf, cutoffLength);
    return merge(head, secondHalf);
}


// ---  End of File ---
