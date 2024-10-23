#include <stdio.h>

#define r_brainfuck_size 1001
#define r_loop_stack_size 124

static int r_brainfuck_interpreter_function(char* r_program_pointer, char* arguments_pointer) {
    char brainfuck[r_brainfuck_size] = { 0 };
    char* brainfuck_pointer = &brainfuck[r_brainfuck_size / 2];

    int loop_stack[r_loop_stack_size];
    int loop_index = 0;

    for (unsigned int iterator = 0; r_program_pointer[iterator] != '\0'; ++iterator) {
        if (r_program_pointer[iterator] == '>' || r_program_pointer[iterator] == '<') {
            if (r_program_pointer[iterator] == '>') brainfuck_pointer++;
            else brainfuck_pointer--;
            continue;
        }

        if (r_program_pointer[iterator] == '+' || r_program_pointer[iterator] == '-') {
            if (r_program_pointer[iterator] == '+') (*brainfuck_pointer)++;
            else (*brainfuck_pointer)--; 
            continue;
        }

        if (r_program_pointer[iterator] == '.') { putchar(*brainfuck_pointer); continue; }
        else if (r_program_pointer[iterator] == ',') { *brainfuck_pointer = *arguments_pointer++; continue; }

        if (r_program_pointer[iterator] == '[' || r_program_pointer[iterator] == ']') {
            if (r_program_pointer[iterator] == '[') {
                if (*brainfuck_pointer == 0) {
                    unsigned int r_loop_count = 1u;
                    while (r_loop_count > 0) {
                        iterator++;
                        if (r_program_pointer[iterator] == '[') r_loop_count++;
                        if (r_program_pointer[iterator] == ']') r_loop_count--;
                        continue;
                    }
                } else loop_stack[loop_index++] = iterator;
            } else {
                if (*brainfuck_pointer != 0) iterator = loop_stack[loop_index - 1];
                else loop_index--;
            }
            continue;
        }
        continue;
    } return 0;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Usage Error: BRAINFUCK_INTERPRETER <brainfuck_code> [<args>...](optional)\n");
        return 1;
    }

    char* program_pointer = argv[1];
    char* arguments_pointer = { 0 };

    if (argc >= 3) arguments_pointer = argv[2];
    return r_brainfuck_interpreter_function(program_pointer, arguments_pointer);
}
