#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int random_num(int min, int max) {
    return rand() % (max - min + 1) + min;
}

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

int main(int argc, char* argv[]) {

    int num_of_values = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    if (num_of_values <= 0 || min <= 0 || max <= 0 || max <= min) {
        printf("Not a valid input.\n");
    }
    else {
        FILE* csv_to_import = fopen("collatz_output.txt", "w");

        if (csv_to_import == NULL) {
            printf("File failed to be created. Exiting program.");
            exit(0);
        }

        fprintf(csv_to_import, "%s,%s,%s\n", "Random Number", "Number of Steps", "Range Size");
        for (int i = 0; i < num_of_values; i++) {
            int random = random_num(min, max);
            fprintf(csv_to_import, "%d,%d,%d\n", random, collatz(random), max - min);
        }

        fclose(csv_to_import);
    }


    return 0;
}