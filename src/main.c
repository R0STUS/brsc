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
    fclose(inputSource);
    return 0;
}

int execute(char* arg, int argc, char* argv[], int num) {
    for (int i = 0; commands[i].command_name != NULL; i++) {
        if (strcmp(commands[i].command_name, arg) == 0) {
            return commands[i].handler(argc, argv, num);
        }
        else {
            char* tmp = commands[i].command_name;
            char* tmp2 = arg;
            if (debugMode == 1) {
                printf("Debug: '%s' = '", tmp2);
                while (*tmp2) {
                    printf("%02X ", (unsigned char)*tmp2);
                    tmp2++;
                }
                printf("\b' != '%s' = '", tmp);
                while (*tmp) {
                    printf("%02X ", (unsigned char)*tmp);
                    tmp++;
                }
                printf("\b'\n");
            }
        }
    }
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 2)
        printf("%s\n", help);
    else {
        for (int i = 1; i < argc; i++) {
            char cont = 0;
            for (int k = 0; k < skipSize; k++) {
                if (skip[k] == i)
                    cont = 1;
            }
            if (cont == 1)
                continue;
            char *tmp = NULL;
            int size = 0;
            int result;
            for (int j = 0; argv[i][j] != '\0'; j++) {
                size++;
                tmp = realloc(tmp, size);
                tmp[j] = argv[i][j];
            }
            result = execute(tmp, argc, argv, i);
            if (result == 0) {
            }
            else {
                printf("Error: ");
                if (result == 1) {
                    printf("Unknown instruction '%s'. SOLDIER, WHAT THE HELL ARE YOU TRYING!?\n", tmp);
                }
                else if (result == 2) {
                    printf("Missing input/output file: '%s'. SOLDIER, MIRACLES DON'T HAPPEN — MOVE!\n", tmp);
                }
                else
                    printf("Unknown error, while executing '%s'. WATCH YOURSELF, SOLDIER!\n", tmp);
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
        char trnsltd = translateToASM();
        if (trnsltd == 0) {
            trnsltd = compileASM();
            if (trnsltd == 0)
                printf("Done compiling.\n");
            else
                printf("CANNOT COMPILE, SOLDIER!\n");
        }
        else
            printf("CANNOT TRANSLATE YOUR CODE, SOLDIER! ARE YOU IDIOT!?\n");
    }
    return 0;
}