#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 3 // Number of frames in memory

// Function to print the contents of the frames
void print_frames(int frames[], int size) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == -1) {
            printf("_ ");
        } else {
            printf("%d ", frames[i]);
        }
    }
    printf("\n");
}

// Function to simulate FIFO page replacement
void fifo_page_replacement(int pages[], int num_pages, int frame_size) {
    int frames[frame_size];
    int page_faults = 0;
    int pointer = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < frame_size; i++) {
        frames[i] = -1;
    }

    printf("Page Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    printf("Frames:\n");

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int page_fault = 1;

        // Check if the page is already in one of the frames
        for (int j = 0; j < frame_size; j++) {
            if (frames[j] == page) {
                page_fault = 0;
                break;
            }
        }

        // If page fault, replace the oldest page
        if (page_fault) {
            frames[pointer] = page;
            pointer = (pointer + 1) % frame_size;
            page_faults++;
        }

        // Print the frames
        print_frames(frames, frame_size);
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0};
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    printf("FIFO Page Replacement Simulation\n");
    fifo_page_replacement(pages, num_pages, FRAME_SIZE);

    return 0;
}
