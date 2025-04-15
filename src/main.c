#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWAG_MEMORY_SIZE 30000

typedef struct swag {
    unsigned char *swagmemory;
    size_t pointerggggg;
} swag;

void executeStuff(swag *interpreter, const char *code) {
    size_t code_length = strlen(code);
    size_t *gregloop = malloc(code_length * sizeof(size_t));
    size_t gregloop_top = 0;

    for (size_t i = 0; i < code_length; ++i) {
        char instruction = code[i];

        switch (instruction) {
            case '>': 
                ++(interpreter->pointerggggg);
                if (interpreter->pointerggggg >= SWAG_MEMORY_SIZE) {
                    interpreter->swagmemory = realloc(interpreter->swagmemory, SWAG_MEMORY_SIZE * 2);
                }
                break;

            case '<': 
                if (interpreter->pointerggggg > 0) {
                    --(interpreter->pointerggggg);
                } else {
                    fprintf(stderr, "error: pointer out of bounds\n");
                    free(gregloop);
                    return;
                }
                break;

            case '+': 
                ++(interpreter->swagmemory[interpreter->pointerggggg]);
                break;

            case '-': 
                --(interpreter->swagmemory[interpreter->pointerggggg]);
                break;

            case '.': 
                putchar(interpreter->swagmemory[interpreter->pointerggggg]);
                break;

            case ',': 
                {
                    char input;
                    input = getchar();
                    interpreter->swagmemory[interpreter->pointerggggg] = input;
                }
                break;

            case '[': 
                if (interpreter->swagmemory[interpreter->pointerggggg] == 0) {
                    int nestL = 1;
                    while (nestL > 0 && ++i < code_length) {
                        if (code[i] == '[') {
                            ++nestL;
                        } else if (code[i] == ']') {
                            --nestL;
                        }
                    }

                    if (nestL > 0) {
                        fprintf(stderr, "error: unmatched '['\n");
                        free(gregloop);
                        return;
                    }
                } else {
                    gregloop[gregloop_top++] = i;
                }
                break;

            case ']': 
                if (gregloop_top == 0) {
                    fprintf(stderr, "error: unmatched ']'\n");
                    free(gregloop);
                    return;
                }

                if (interpreter->swagmemory[interpreter->pointerggggg] != 0) {
                    i = gregloop[gregloop_top - 1]; 
                } else {
                    --gregloop_top;
                }
                break;
        }
    }

    if (gregloop_top > 0) {
        fprintf(stderr, "error: unmatched '['\n");
    }

    free(gregloop);
}

int bracketgreg(const char *code) {
    size_t code_length = strlen(code);
    size_t *bracketthing = malloc(code_length * sizeof(size_t));
    size_t bracketthing_top = 0;

    for (size_t i = 0; i < code_length; ++i) {
        if (code[i] == '[') {
            bracketthing[bracketthing_top++] = i;
        } else if (code[i] == ']') {
            if (bracketthing_top == 0) {
                fprintf(stderr, "error: unmatched ']' at position %zu\n", i);
                free(bracketthing);
                return 0;
            }
            --bracketthing_top;
        }
    }

    if (bracketthing_top > 0) {
        fprintf(stderr, "error: unmatched '[' at position %zu\n", bracketthing[bracketthing_top - 1]);
        free(bracketthing);
        return 0;
    }

    free(bracketthing);
    return 1;
}

void fileexxxxxxxxx(swag *interpreter, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "error: could not open file %s\n", filename);
        return;
    }

    char *code = malloc(SWAG_MEMORY_SIZE * sizeof(char));
    size_t code_len = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (strchr("><+-.,[]", c)) {
            code[code_len++] = c;
        }
    }
    fclose(file);

    if (bracketgreg(code)) {
        executeStuff(interpreter, code);
    }

    free(code);
}

int main(int argc, char *argv[]) {
    swag interpreter;
    interpreter.swagmemory = malloc(SWAG_MEMORY_SIZE * sizeof(unsigned char));
    interpreter.pointerggggg = 0;

    if (argc > 1) {
        fileexxxxxxxxx(&interpreter, argv[1]);
    } else {
        char *code = malloc(SWAG_MEMORY_SIZE * sizeof(char));
        size_t code_len = 0;
        char line[256];

        printf("enter brainfucm code (type 'end' to stop):\n");

        while (fgets(line, sizeof(line), stdin)) {
            if (strcmp(line, "end\n") == 0) {
                break;
            }

            for (size_t i = 0; i < strlen(line); ++i) {
                if (strchr("><+-.,[]", line[i])) {
                    code[code_len++] = line[i];
                }
            }
        }

        printf("\nrunning\n");
        if (bracketgreg(code)) {
            for (size_t i = 0; i < 60; ++i) {
                putchar('=');
            }
            putchar('\n');
            executeStuff(&interpreter, code);
        }

        free(code);
    }

    printf("\npress enter to exit...\n");
    getchar();

    free(interpreter.swagmemory);
    return 0;
}
