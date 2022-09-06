#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "lexer.h"
#include "generator.h"

#define MAX_INPUT_SIZE 160

/*** Syntakticky analyzator a interpretator ***/

/* Overenie symbolu na vstupe a precitanie dalsieho.
 * Vracia atribut overeneho symbolu. */
int match(const Symbol expected)
{
    if (lex_symbol == expected) {
        int attr = lex_attr;
        next_symbol();
        return attr;
    } else {
        fprintf(stderr,
                "CHYBA: Chyba symbol %s, namiesto toho sa vyskytol %s.\n",
                symbol_name(expected), symbol_name(lex_symbol));
        exit(1);
    }
}


/* Gramatika:
 *
 * Expr -> Term {("+"|"-") Term}
 * Term -> VALUE | "(" Expr ")"
 */

int expr(), term();

/* Term -> VALUE | "(" Expr ")" */
int term()
{
    int value; 
    switch (lex_symbol) {
    case VALUE:
        write_number(lex_attr);
        value = lex_attr;             
        next_symbol();
        break;
    case LPAR:    
        next_symbol();
        value = expr();
        match(RPAR);
        break;
    default:    
        fprintf(stderr, "CHYBA: Chyba operand, namiesto toho sa vyskytol %s\n.",
                symbol_name(lex_symbol));
        exit(1);
    }
    return value;
}

/* Expr -> Term {("+"|"-") Term} */
int expr()
{
    int leftOp, rightOp;
    Symbol operator;
    leftOp = term();
    while (lex_symbol == PLUS || lex_symbol == MINUS) {
        operator = lex_symbol;
        next_symbol();
        rightOp = term();
        switch (operator) {
        case PLUS:
            write_add();
            leftOp=leftOp+rightOp;
            break;
        case MINUS:
            write_sub();
            leftOp= leftOp - rightOp;
            break;
        default:
            assert("Neocakavany operator v expr()");
        }
    }
    
    return leftOp;
}

void print(){
    next_symbol();
    match(PRINT);
    int result = expr();
        printf("Vysledok je %d\n", result);
        write_result();
        //match(SEMICOL);
}


int main(int argc, char** argv)
{
    printf("Vstupny retazec: ");
    // Citanie vstupneho retazca
    char source[MAX_INPUT_SIZE];
    fgets(source, MAX_INPUT_SIZE, stdin);


    //write_begin(int num_vars);


    init_lexer(source);
    print_tokens();

    printf("\nZaciatok syntaxou riadenej interpretacie\n\n");    
    //next_symbol(); 
    init_lexer(source);
    FILE *output_file = fopen("program.bin", "wb");
    init_generator(output_file);

    print();

    //generate_output();

    fclose(output_file);
    getchar();
    return 0;
}