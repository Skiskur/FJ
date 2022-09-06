#include <stdio.h>

/* Codes of Computron instructions */
enum OP_Code {
    NOP, BZE, JMP, JSR, RTS, EXIT,
    INPC, INP, INPR, OUTC, OUT, OUTR,
    POP, POPR, PUSH, PUSHR,
    LDA, LDAM, LDAI, LDAX,
    LDR, LDRI, STA,
    STAI, STRI,
    LDX, STX, LDS, STS,
    OR, AND, NOT,
    EQ, NE, LT, LE, GT, GE,
    EQR, NER, LTR, LER, GTR, GER,
    ADD, ADDM, SUB, SUBM,
    MUL, DIV, NEG,
    ADDR, SUBR, MULR, DIVR, NEGR
};

/* Representation of real numbers in Computron */
typedef union {
    float R;

    struct {
        unsigned short RL;
        unsigned short RH;
    } Dword;
} RealRegister;

/* File for writing Computron code */
FILE *output_stream;

/* Write instruction or data word */
void put_word(unsigned short arg)
{
    fwrite(&arg, sizeof (short), 1, output_stream);
}

/* Write real number */
void put_real(float arg)
{
    RealRegister rvalue;
    rvalue.R = arg;
    put_word(rvalue.Dword.RL);
    put_word(rvalue.Dword.RH);
}


int main()
{
    /* Open file for writing (in binary mode) */
    output_stream = fopen("program.bin", "wb");
    put_word(INP);
    put_word(OUT);
    put_word(EXIT);
    fclose(output_stream);
    return 0;
}