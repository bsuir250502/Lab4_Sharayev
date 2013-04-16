#include "mylib.h"

int confirm_choice(void)
{
    char arg[3];
    printf("Set (Y/N)\n");
    while (1) {
        myfgets(arg, 3);
        if (arg[0] == 'Y' || arg[0] == 'y') {
            return 1;
        }
        if (arg[0] == 'N' || arg[0] == 'n') {
            return 0;
        } else {
            printf("Wrong key");
        }
    }

    return 0;
}

char *myfgets(char *str, int num)
{
    if (!(fgets(str, num, stdin))) {
        return 0;
    } else {
        str[strlen(str) - 1] = '\0';
    }

    return str;
}

int print_manual(void)
{
    char input_buffer[128];
    FILE *fp = fopen("Manual.txt", "r");
    while (fgets(input_buffer, SIZE(input_buffer), fp)) {
        printf("%s", input_buffer);
    }
    printf("\n");
    fclose(fp);

    return 0;
}

int input_number_in_range(int from, int to)
{
    int n;
    char *endptr;
    char input_buffer[128];
    int first = 1;
    do {
        if (!first) {
            printf("Please enter number between %d and %d\n", from, to);
        }
        myfgets(input_buffer, 128);
        n = strtol(input_buffer, &endptr, 10);
        first = 0;
    } while (*endptr || n < from || n > to);

    return n;
}
