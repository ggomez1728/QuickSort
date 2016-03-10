//
//  main.cpp
//  Tarea_QuickSort
//
//  Created by Pollinion User on 01/03/16.
//  Copyright © 2016 Pollinion INC. All rights reserved.
//

// A C++ program to sort a linked list using Quicksort
#include <iostream>
#include <stdio.h>
using namespace std;

/* Nodo de la lista con enlace doble */
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};



// funcion utilizada para encontrar el ultimo nodo de la lista
struct node *lastNode(node *root)
{
    while (root && root->next)
        root = root->next;
    return root;
}

struct node *returnNode(node *root, int steps)
{
    while (root && root->next)
        root = root->next;
    return root;
}
//counter steps
int counter(node * first, node * last)
{
    int elements = 1;
    while (first != last)
    {
        first = first->next;
        elements++;
    }
    return elements;
}

/* funcion utilizada para el intercabio (swap) de dos elementos */
void swap ( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* Considers last element as pivot, places the pivot element at its
 correct position in sorted array, and places all smaller (smaller than
 pivot) to left of pivot and all greater elements to right of pivot */

/*
 Consideramos el ultimo elemento como elemento pivot
*/
node* partition(node *l, node *h)
{
    // set pivot as h element
    int x  = h->data;
    
    // similar to i = l-1 for array implementation
    node *i = l->prev;
    
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (node *j = l; j != h; j = j->next)
    {
        if (j->data <= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
            
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->data), &(h->data));
    return i;
}

/* A recursive implementation of quicksort for linked list */
void _quickSort(struct node* l, struct node *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        struct node *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}

int busquedaSimple(struct node* vector, int dato) {
    struct node* element = vector;
    while (element != NULL) {
        if (element->data == dato) {
            return element->data;
        }
        element = element->next;
    }
    return -1;
}


bool busquedaBinaria(struct node* first, struct node * last, int data) {
    // struct node* first = vector;
    // struct node * last = lastNode(vector);
    bool searchBool=false;
    struct node* middle = first;
    int steps = 0;
    if (first == last) {
        if (first->data == data) {
            searchBool = true;
        }
        else{
            searchBool = false;
        }
       
        return searchBool;
    }
    steps = (int)counter(first, last) / 2;
    while (steps>1) {
        middle = middle->next;
        steps--;
    }
    if (middle->data < data) {
        // busca la otra mitad sumada
        searchBool = busquedaBinaria(middle->next, last, data);
    }
    else if(middle->data > data){
        //busca la otra mitad restada
        searchBool = busquedaBinaria(first, middle->prev, data);
    }
    else{
        //el elemento es encontrado
        searchBool = true;
    }
    return searchBool;
}


// The main function to sort a linked list. It mainly calls _quickSort()
void quickSort(struct node *head)
{
    // Find last node
    struct node * h = lastNode(head);
    // Call the recursive QuickSort
    _quickSort(head, h);
}

// A utility function to print contents of arr
void printList(struct node *head)
{
    while (head)
    {
        cout << head->data << "  ";
        head = head->next;
    }
    cout << endl;
}

/* Function to insert a node at the beginging of the Doubly Linked List */
void push(struct node** head_ref, int new_data)
{
    struct node* new_node = new node;     /* allocate node */
    new_node->data  = new_data;
    
    /* since we are adding at the begining, prev is always NULL */
    new_node->prev = NULL;
    
    /* link the old list off the new node */
    new_node->next = (*head_ref);
    
    /* change prev of head node to new node */
    if ((*head_ref) !=  NULL)  (*head_ref)->prev = new_node ;
    
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}


/* Driver program to test above function */
int main()
{
    int size_elements;
    bool search = true;
    int searchElement = 0;

    srand (time(NULL));

    std::cout << "cantidad de datos generados aleatoriamente: ";
    std::cin >> size_elements;
    
    // set some initial values:
    struct node *a = NULL;

    for (int i=0; i<size_elements; ++i){
        push(&a, (rand() % size_elements + 1));
    }

    cout << "\n Lista para ser ordenada \n";
    printList(a);
    
    quickSort(a);
    struct node * first = a;
    struct node * last = lastNode(a);
    cout << "\n Lista ordenada \n";
    printList(a);
    
    while (search == true) {
        int optionSearch = 0;
        std::cout << "\n 1 - Busqueda simple o Lineal \n";
        std::cout << "2 - Busqueda simple o Lineal \n";
        std::cout << "3 - terminar programa \n";
        std::cout << "Seleccion(1-3):";

        std::cin >> optionSearch;
        

        if (optionSearch ==1) {
            search = true;
            std::cout << "Elemento de busqueda:";
            std::cin >> optionSearch;
            if (busquedaSimple(a, optionSearch)!=-1)
            {
                std::cout << "<<ELEMENTO ENCONTRADO>> \n";
            }
            else
            {
                std::cout << "<<ELEMENTO NO ENCONTRADO>> \n";
            }
        }
        else if (optionSearch ==2) {
            std::cout << "\n Elemento de busqueda:";
            std::cin >> optionSearch;
            bool search_value = busquedaBinaria(first, last, optionSearch);
            if (search_value==true)
            {
                std::cout << "<<ELEMENTO ENCONTRADO>> \n";
            }
            else
            {
                std::cout << "<<ELEMENTO NO ENCONTRADO>> \n";
            }

        }
        else if (optionSearch ==3) {
            search = false;
        }
        
        
    }
    //busquedaSimple(a, 4);
    
    return 0;
}

