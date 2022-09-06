#include "lexer.h"
#include "generator.h"
#include <stdio.h>

int main(int argc, char** argv) {
 
    ...
 
    FILE *output_file = fopen("program.bin", "wb");
    init_generator(output_file);
 
    program();
 
    generate_output();
    fclose(output_file);
    printf("Program vygenerovany v program.bin\n");
 
    getchar();
    return 0;
}