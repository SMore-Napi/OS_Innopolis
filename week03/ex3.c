#include <stdio.h>
#include <stdlib.h>

/**
 * Roman Soldatov BS19-02
 *
 * Exercise 3
 */

/**
 * Element of linked list
 */
struct node {
    // The pointer to the next node
    struct node *next;

    // The value of it's node
    int data;
};

/**
 * The Linked List data structure
 */
struct linked_list {
    // The head of the list. head->next refers to the first list's element
    struct node *head;
    // The count of elements inserted in the linked list
    int size;
};

/**
 * Function declarations
 */

/**
 * Nullify the data and allocate a memory for the linked list
 */
void initialize_linked_list(struct linked_list *list);

/**
 * Print linked list's elements
 */
void print_list(struct linked_list *list);

/**
 * Insert a new element to the linked list by a value
 */
void insert_node(struct linked_list *list, int value);

/**
 * Delete an element from the linked list by value.
 * It deletes the first element from a list which data is equal to value
 * It does nothing if a list doesn't contain any node with data = value.
 */
void delete_node(struct linked_list *list, int value);

int main() {

    struct linked_list list;
    initialize_linked_list(&list);

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

void initialize_linked_list(struct linked_list *list) {
    list->size = 0;
    list->head = malloc(sizeof(struct node));
}

void print_list(struct linked_list *list) {
    int size = list->size;
    printf("[");
    if (size > 0) {
        struct node *current_node = list->head->next;
        // Iterate by each list's node
        for (int i = 0; i < size - 1; i++) {
            printf("%d, ", current_node->data);
            current_node = current_node->next;
        }
        printf("%d", current_node->data);
    }
    printf("]\n");
}

void insert_node(struct linked_list *list, int value) {
    struct node *current_node = list->head;

    // Go to the list's tail
    for (int i = 0; i < list->size; i++) {
        current_node = current_node->next;
    }

    // Create a new node and assign it to the tail->next
    current_node->next = malloc(sizeof(struct node));
    current_node->next->data = value;

    list->size++;
}

void delete_node(struct linked_list *list, int value) {
    struct node *current_node = list->head;

    // Iterate by the list until we find the node which data is equal to value
    for (int i = 0; i < list->size; i++) {
        if (current_node->next->data == value) {
            // Remember the address of a node to delete
            struct node *node_to_delete = current_node->next;

            // Reassign the address to the next node after the 'node_to_delete'
            current_node->next = node_to_delete->next;

            // Free memory of a deleted node
            free(node_to_delete);

            list->size--;
            break;
        } else {
            current_node = current_node->next;
        }
    }
}

