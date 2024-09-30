#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint64_t key;
    uint64_t value;
} cache_entry_t;

int collatz(int num) {
    int count = 0;
    while (num != 1) {
        if (num % 2 == 1) {
            num = (3 * num) + 1;
        }
        else {
            num = num / 2;
        }
        count++;
    }
    return count;
}

cache_entry_t cache[1000];
int idx = 0;
int cache_hits = 0;

int collatz_wrapper(int num, int cache_size) {
    for (int i = 0; i < 1000; i++) {
        if (cache[i].key == num) {
            cache_hits++;
            return cache[i].value;
        }
    }
    cache_entry_t entry;
    entry.key = num;
    entry.value = collatz(num);
    cache[idx] = entry;
    if (idx != cache_size) {
        idx++;
    }
    else {
        idx = 0;
    }
    return collatz(num);
}

int main(int argc, char* argv[]) {
    int num_of_values = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    int cache_policy;
    if (strcmp(argv[4], "LRU") || strcmp(argv[4], "lru")) {
        cache_policy = 0;
    }
    else if (strcmp(argv[4], "LFU") || strcmp(argv[4], "lfu")) {
        cache_policy = 1;
    }
    else {
        cache_policy = 2;
    }

    int cache_size = atoi(argv[5]);

    if (num_of_values <= 0 || min <= 0 || max <= 0 || max <= min) {
        printf("Not a valid input.\n");
    }
    else {
        FILE* csv_to_import = fopen("collatz_output.txt", "w");

        if (csv_to_import == NULL) {
            printf("File failed to be created. Exiting program.");
            exit(0);
        }

        int total_requests = 0;
        fprintf(csv_to_import, "%s,%s,%s,%s,%s,%s\n", "Random Number", "Number of Steps", "Range Size",
                "Cache Policy", "Cache Size", "Cache Hit %%");
        for (int i = 0; i < num_of_values; i++) {
            total_requests++;
            int random = rand() % (max - min + 1) + min;
            fprintf(csv_to_import, "%d,%d,%d,%s,%d,%d\n", random, collatz_wrapper(random, cache_size), max - min,
                    argv[4], cache_size, cache_hits / total_requests);
        }

        fclose(csv_to_import);
    }

    return 0;
}