#include <stdio.h>
#include <stdlib.h>

/**
 * Roman Soldatov BS19-02
 * Exercise 1
 */

/**
 * The output of this program with 10, 50 and 100 page frames
 * using Lab 09 input.txt input file from Moodle (in this program it's name "input.txt")
 *
 * The number of page frames = 10
 * Hits = 10
 * Misses = 990
 * Hit/Miss = 0.010101
 *
 * The number of page frames = 50
 * Hits = 51
 * Misses = 949
 * Hit/Miss = 0.053741
 *
 * The number of page frames = 100
 * Hits = 93
 * Misses = 907
 * Hit/Miss = 0.102536
 */

struct page_frame {
    int page_number;
    int r; // reference bit
    uint8_t age; // 8 bits counter
};

/**
 * Function declarations
 */

// Initialize the page table
struct page_frame *create_page_table(int number_page_frames);

// Simulate the page system
void start_paging_system(struct page_frame *page_frames, int number_page_frames, int *hits, int *misses);

// Simulate the clock tick using the aging algorithm
void next_clock_tick(int next_page, struct page_frame *page_frames, int number_page_frames, int *hits, int *misses);

int get_index_page_to_replace(struct page_frame *page_frames, int number_page_frames);

void write_page_number_value(int next_page, int index_page_to_replace, struct page_frame *page_frames,
                             int number_page_frames, int *hits, int *misses);

void print_hit_miss_ratio(int number_page_frames, int hits, int misses);

int main(int argc, char *argv[]) {

    // Read the number of page page_frames as a parameter
    char *end;
    int number_page_frames = strtol(argv[1], &end, 10);

    int hits = 0;
    int misses = 0;

    // Create the page table
    struct page_frame *page_frames = create_page_table(number_page_frames);
    // Simulates a paging system
    start_paging_system(page_frames, number_page_frames, &hits, &misses);
    free(page_frames);

    // Print the result
    print_hit_miss_ratio(number_page_frames, hits, misses);

    return 0;
}

/**
 * Function implementations
 */

struct page_frame *create_page_table(int number_page_frames) {
    struct page_frame *page_frames = malloc(number_page_frames * sizeof(struct page_frame));

    for (int i = 0; i < number_page_frames; i++) {
        page_frames[i].age = 0;
        page_frames[i].page_number = -1;
        page_frames[i].r = 0;
    }

    return page_frames;
}

void start_paging_system(struct page_frame *page_frames, int number_page_frames, int *hits, int *misses) {
    FILE *file = fopen("input.txt", "r");

    // Read the sequence of page references from a file
    int next_page;
    while (fscanf(file, "%d", &next_page) != EOF) {
        next_clock_tick(next_page, page_frames, number_page_frames, hits, misses);
    }

    fclose(file);
}

void next_clock_tick(int next_page, struct page_frame *page_frames, int number_page_frames, int *hits, int *misses) {
    int index_page_to_replace = get_index_page_to_replace(page_frames, number_page_frames);

    // Update the reference bit
    for (int i = 0; i < number_page_frames; i++) {
        if (page_frames[i].page_number == next_page) {
            page_frames[i].r = 1;
        } else {
            page_frames[i].r = 0;
        }
    }

    // The aging algorithm
    for (int i = 0; i < number_page_frames; i++) {
        page_frames[i].age = (page_frames[i].age >> 1) | (page_frames[i].r << 7);
    }

    // Update the page table
    write_page_number_value(next_page, index_page_to_replace, page_frames, number_page_frames, hits, misses);
}

int get_index_page_to_replace(struct page_frame *page_frames, int number_page_frames) {
    // The index of the entry with minimal age
    int index_min_age = 0;

    for (int i = 0; i < number_page_frames; i++) {
        // In case the table has empty entries
        if (page_frames[i].page_number == -1) {
            return i;
        }
        // The entry with minimal age will be replaced
        if (page_frames[i].age < page_frames[index_min_age].age) {
            index_min_age = i;
        }
    }

    return index_min_age;
}

void write_page_number_value(int next_page, int index_page_to_replace, struct page_frame *page_frames,
                             int number_page_frames, int *hits, int *misses) {
    // Check if this page number is already in the table
    for (int i = 0; i < number_page_frames; i++) {
        if (page_frames[i].page_number == next_page) {
            // Update the hits statistics
            (*hits)++;
            return;
        }
    }

    // Write new page number in the table
    page_frames[index_page_to_replace].page_number = next_page;
    page_frames[index_page_to_replace].age = 1 << 7;
    page_frames[index_page_to_replace].r = 1;

    // Update the misses statistics
    (*misses)++;
}

void print_hit_miss_ratio(int number_page_frames, int hits, int misses) {
    printf("The number of page frames = %d\n", number_page_frames);
    printf("Hits = %d\n", hits);
    printf("Misses = %d\n", misses);
    printf("Hit/Miss = %f\n", (double) hits / misses);
}