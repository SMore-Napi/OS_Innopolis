#include <stdio.h>
#include <stdlib.h>

/**
 * Roman Soldatov BS19-02
 *
 * Exercise 5
 */

/**
 * Element of doubly linked list
 */
struct node {
    // The pointer to the next node
    struct node *next;

    // The pointer to the previous node
    struct node *previous;

    // The value of it's node
    int data;
};

/**
 * The Doubly Linked List data structure
 */
struct doubly_linked_list {
    // The head of the list. head->next refers to the first list's element
    struct node *head;

    // The tail of the list. tail->previous refers to the last list's element
    struct node *tail;
};

/**
 * Function declarations
 */

/**
 * Nullify the data and allocate a memory for the doubly linked list
 */
void initialize_doubly_linked_list(struct doubly_linked_list *list);

/**
 * Print doubly linked list's elements
 */
void print_list(struct doubly_linked_list *list);

/**
 * Insert a new element to the doubly linked list by a value
 */
void insert_node(struct doubly_linked_list *list, int value);

/**
 * Delete an element from the doubly linked list by value.
 * It deletes the first encountered element from a list which data is equal to value
 * It does nothing if a list doesn't contain any node with data = value.
 */
void delete_node(struct doubly_linked_list *list, int value);

int main() {

    struct doubly_linked_list list;
    initialize_doubly_linked_list(&list);

    printf("Initial list:\n");
    print_list(&list);
    printf("\n");

    printf("Insert 1, 2, 3, 4, 5:\n");
    insert_node(&list, 1);
    insert_node(&list, 2);
    insert_node(&list, 3);
    insert_node(&list, 4);
    insert_node(&list, 5);
    print_list(&list);
    printf("\n");

    printf("Delete 3, 5, 1:\n");
    delete_node(&list, 3);
    delete_node(&list, 5);
    delete_node(&list, 1);
    print_list(&list);

    return 0;
}

/**
 * Function implementations
 */

void initialize_doubly_linked_list(struct doubly_linked_list *list) {
    list->head = malloc(sizeof(struct node));
    list->tail = malloc(sizeof(struct node));

    list->head->next = list->tail;
    list->tail->previous = list->head;
}

void print_list(struct doubly_linked_list *list) {
    printf("[");
    struct node *current_node = list->head->next;
    if (current_node != list->tail) {
        // Iterate by each list's node
        while (current_node->next != list->tail) {
            printf("%d, ", current_node->data);
            current_node = current_node->next;
        }
        printf("%d", current_node->data);
    }
    printf("]\n");
}

void insert_node(struct doubly_linked_list *list, int value) {

    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;

    new_node->previous = list->tail->previous;
    new_node->next = list->tail;

    new_node->previous->next = new_node;
    list->tail->previous = new_node;
}

void delete_node(struct doubly_linked_list *list, int value) {
    struct node *current_node = list->head;

    // Iterate by the list until we find the node which data is equal to value
    while (current_node->next != list->tail) {
        if (current_node->next->data == value) {
            // Remember the address of a node to delete
            struct node *node_to_delete = current_node->next;

            // Reassign the address to the next node after the 'node_to_delete'
            // and previous node before the 'node_to_delete'
            current_node->next = node_to_delete->next;
            node_to_delete->next->previous = current_node;

            // Free memory of a deleted node
            free(node_to_delete);

            break;
        } else {
            current_node = current_node->next;
        }
    }
}