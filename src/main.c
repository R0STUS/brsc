#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <argp.h>

const char *argp_program_version = "alpha 1.0.0";
const char *argp_program_bug_address = "<alexeevha@gmail.com>";

static char doc[] = "THIS IS B.R.A.S.S. COMPILER, SOLDIER!";
static struct argp_option options[] = {
    {"input", 'i', "FILE", 0, "Input filename.", 0},
    {"output", 'o', "FILE", 0, "Output filename.", 0},
    {0}
};

typedef struct {
    char name;
    char* arg;
} Arg;

Arg* args;
int argsSize = 1;

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    int i;
    (void) state;
    for (i = 0; options[i].name != 0; i++) {
        if (options[i].key == key) {
            args[argsSize - 1].name = key;
            args[argsSize - 1].arg = arg;
            argsSize++;
            args = realloc(args, argsSize);
            args[argsSize - 1].name = 0;
            return 0;
        }
    }
    return ARGP_ERR_UNKNOWN;
}

static struct argp argp = { options, parse_opt, 0, doc, 0, 0, 0 };

char* getArg(char wh) {
    int i;
    for (i = 0; args[i].name != 0; i++) {
        if (args[i].name == wh)
            return args[i].arg;
    }
    return NULL;
}

int parseFile(char** code, char* filename, int* codeSize) {
    FILE* infile = fopen(filename, "r");
    char line[256];
    char* buf = malloc(1);
    int bufsize = 0;
    int prevpos = 0;
    int i;
    if (infile == NULL) {
        fprintf(stderr, "Cannot open input file '%s': %s\n", filename, strerror(errno));
        return -1;
    }
    while(fgets(line, sizeof(line), infile)) {
        for (i = 0; line[i] != 0; i++) {
            if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') {
                if (bufsize == 0)
                    continue;
                bufsize++;
                bufsize -= prevpos;
                buf = malloc(bufsize);
                if (buf == NULL) {
                    fprintf(stderr, "Cannot allocate memory!\n");
                    return -1;
                }
                snprintf(buf, bufsize, "%s", line + prevpos);
                getMeaning(buf, bufsize);
                bufsize = 0;
            }
            bufsize++;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    char* code;
    int codeSize;
    char* inp;
    args = malloc(sizeof(Arg));
    args[0].name = 0;
    argp_parse(&argp, argc, argv, 0, 0, 0);
    inp = getArg('i');
    if (inp == NULL) {
        fprintf(stderr, "No input file specified!\n");
        return 1;
    }
    if (parseFile(&code, inp, &codeSize) != 0) {
        fprintf(stderr, "An error occured while parsing!\n");
        return -1;
    }
    return 0;
}
