#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUCK CAPITAL! GO OPEN SOURCE!

const char* help = "Are you kidding me, private!? You just called me up with ZERO INSTRUCTIONS!? You expect me to tolerate this nonsense!? FINE. LET ME SPELL OUT THE DAMN TUTORIAL FOR YOU, SOLDIER:\n'bvmc -i [file path]' - sets the input. Compiles your garbage code and leaves it... NOWHERE, YOU MORON, SPECIFY THE DAMN OUTPUT, SOLDIER!\n'bvmc -o [file path]' - sets the output. Saves the compiled binary... WAIT, DID YOU EVEN SET THE INPUT, SOLDIER!?\n'bvmc --no-temporary' - disables saving the intermediate representation in the 'build' folder. Makes things cleaner for people who know what the hell they're doing.\n'bvmc --help' - if you will send me this innstruction, I WILL TELL YOU DAMN TUTORIAL AGAIN, SOLDIER!";
const char* pussyTutorial = "Listen me, pussy private:\n'bvmc -i [file path]' - sets the input. Compiles your garbage code and leaves it... NOWHERE, YOU MORON, SPECIFY THE DAMN OUTPUT, SOLDIER!\n'bvmc -o [file path]' - sets the output. Saves the compiled binary... WAIT, DID YOU EVEN SET THE INPUT, SOLDIER!?\n'bvmc --no-temporary' - disables saving the intermediate representation in the 'build' folder. Makes things cleaner for people who know what the hell they're doing.\n'bvmc --help' - if you will send me this innstruction, I WILL TELL YOU DAMN TUTORIAL AGAIN, SOLDIER!";

const char debugMode = 1;

char* inputFile = "";
char* outputFile = "";

char* inputFileBuffer;
char* outputFileBuffer;

int* skip;
int skipSize = 0;

int input(int argc, char* argv[], int num) {
    if (num + 2 > argc)
        return 2;
    else {
        inputFile = argv[num + 1];
        skipSize++;
        skip = realloc(skip, skipSize);
        skip[skipSize - 1] = num + 1;
        if (debugMode == 1)
            printf("Debug: input file set: '%s'\n", inputFile);
    }
    return 0;
}
int output(int argc, char* argv[], int num) {
    if (num + 2 > argc)
        return 2;
    else {
        outputFile = argv[num + 1];
        skipSize++;
        skip = realloc(skip, skipSize);
        skip[skipSize - 1] = num + 1;
        if (debugMode == 1)
            printf("Debug: output file set: '%s'\n", outputFile);
    }
    return 0;
}
int helpNahui(int argc, char* argv[], int num) {
    printf("%s\n", pussyTutorial);
    return 0;
}

typedef struct {
    const char* command_name;
    int (*handler)(int argc, char* argv[], int num);
} Command;

typedef struct {
    const char* mode_name;
    const char mode;
}

Command commands[] = {
    {"--help", helpNahui},
    {"-i", input},
    {"-o", output},
    {NULL, NULL}
};

char translateToASM() {
    FILE *inputSource = fopen(inputFile, "r");
    if (inputSource == NULL) {
        printf("FILE NOT COMPATIBLE OR NOT EXISTS, SOLDIER!\n");
        return -1;
    }
    fseek(inputSource, 0, SEEK_END);
    long fileSize = ftell(inputSource);
    rewind(inputSource);
    inputFileBuffer = malloc(fileSize + 1);
    if (inputFileBuffer == NULL) {
        printf("FAILED TO ALLOCATE MEMORY, SOLDIER!\n");
        fclose(inputSource);
        return -1;
    }
    fread(inputFileBuffer, 1, fileSize, inputSource);
    inputFileBuffer[fileSize] = '\0';
    fclose(inputSource); // TODO: Optimize translator garbage code
    long i;
    char state = 0;
    unsigned char mode = 0;
    char** ddata_section = NULL;
    unsigned int ddata_section_sizeA = 0;
    unsigned int* ddata_section_sizeB = NULL;
    unsigned int ddata_section_operand_id = 0xDEADC0DE;
    /*char** dbss_section; // I don't know why I created this, so, mark as comment for while.
    unsigned int dbss_section_sizeA = 0;
    unsigned int dbss_section_sizeB = 0;*/
    char* operand = NULL;
    int operand_size = 0;
    for (i = 0; i < fileSize; i++) {
        if (inputFileBuffer == ';') {state = 0; mode = 0; operand_size = 0;}
        if (state == 0) {
            if (inputFileBuffer[i] == '+') {
                state = 1;
                mode = 1;
            }
        }
        else if (state == 1 && mode == 1) {
            if (inputFileBuffer[i] == ' ' && operand_size < 1) {
                printf("SOLDIER, WHAT DO YOU WANT TO DECLARE!? SPACE IS NOT A DECLARABLE SYMBOL!\n");
                return -1;
            }
            else if (inputFileBuffer[i] == ' ') {
                ddata_section_sizeA++;
                ddata_section = realloc(ddata_section, ddata_section_sizeA);
                ddata_section[ddata_section_sizeA - 1] = operand;
                ddata_section_sizeB[ddata_section_sizeA - 1] = operand_size + 5;
                ddata_section[ddata_section_sizeA - 1] = realloc(ddata_section[ddata_section_sizeA - 1], ddata_section_sizeB[ddata_section_sizeA - 1]);
                strcat(ddata_section[ddata_section_sizeA - 1], " res");
                operand_size = 0;
                operand = realloc(operand, operand_size);
                state = 2;
            }
            else {
                operand_size++;
                operand = realloc(operand, operand_size);
                operand[operand_size - 1] = inputFileBuffer[i];
            }
        }
        else if (state == 2 && mode == 1) {
            if (inputFileBuffer[i] == ' ' && operand_size > 0) {
                ddata_section[ddata_section_sizeA - 1] = declare(&ddata_section[ddata_section_sizeA - 1], &ddata_section_sizeB[ddata_section_sizeA - 1], operand, operand_size);
                operand_size = 0;
                operand = realloc(operand, operand_size);
                state = 2;
            }
        }
    }
    return 0;
}

int execute(char* arg, int argc, char* argv[], int num) {
    for (int i = 0; commands[i].command_name != NULL; i++) {
        if (strcmp(commands[i].command_name, arg) == 0) {
            return commands[i].handler(argc, argv, num);
        }
        else if (debugMode == 1) {
            char* tmp = arg;
            printf("Debug: '%s' = '", tmp);
            while (*tmp2) {
                printf("%02X ", (unsigned char)*tmp);
                tmp++;
            }
            tmp = commands[i].command_name;
            printf("\b' != '%s' = '", tmp);
            while (*tmp) {
                printf("%02X ", (unsigned char)*tmp);
                tmp++;
            }
            printf("\b'\n");
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        printf("%s\n", help);
    else {
        char cont;
        for (int i = 1; i < argc; i++) {
            cont = 0;
            for (int k = 0; k < skipSize; k++) {
                if (skip[k] == i)
                    cont = 1;
            }
            if (cont == 1)
                continue;
            int result;
            result = execute(argv[i], argc, argv, i);
            if (result == 0) {
            }
            else {
                printf("Error: ");
                if (result == 1) {
                    printf("Unknown instruction '%s'. SOLDIER, WHAT THE HELL ARE YOU TRYING!?\n", argv[i]);
                }
                else if (result == 2) {
                    printf("Missing input/output file: '%s'. SOLDIER, MIRACLES DON'T HAPPEN — MOVE!\n", argv[i]);
                }
                else
                    printf("Unknown error, while executing '%s'. WATCH YOURSELF, SOLDIER!\n", argv[i]);
                return -1;
            }
        }
        if (inputFile == "") {
            printf("WHAT I NEED TO COMPILE, SOLDIER!? YOU'RE NOT SET INPUT!\n");
            return -1;
        }
        if (outputFile == "") {
            printf("If I will compile it, WHERE I WILL SAVE IT, SODIER!? YOU'RE NOT SET OUTPUT!\n");
            return -1;
        }
        cont = translateToASM();
        if (cont == 0) {
            cont = compileASM();
            if (cont == 0)
                printf("Done compiling your garbage code, soldier.\n");
            else {
                printf("CANNOT COMPILE, SOLDIER!\n");
                return -1;
            }
        }
        else {
            printf("CANNOT TRANSLATE YOUR CODE, SOLDIER! ARE YOU IDIOT!?\n");
            return -1;
        }
    }
    return 0;
}