#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbgen.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    generate_branches(stdout, 10);
    printf("\n");
    return 0;
}

void generate_zipcode(char *s) {
    int zipcode = rand() %  ZIPCODE_UPPER_BOUND;
    snprintf(s, ZIPCODE_LENGTH + 1, ZIPCODE_FORMAT, zipcode / ZIPCODE_HALF_MOD, zipcode % ZIPCODE_HALF_MOD);
}


void generate_branches(FILE *fp, int size) {
    for (int i = 0; i < size; i++) {
        branch_t branch;
        memset(&branch, 0, sizeof(branch));
        branch.id = i + 1;
        snprintf(branch.name, sizeof(branch.name), NAME_FORMAT, "Branch", branch.id);
        snprintf(branch.email, sizeof(branch.email), BRANCH_EMAIL_FORMAT, "Branch", branch.id);
        generate_zipcode(branch.zipcode);
        fprintf(fp, BRANCH_OUTPUT_FORMAT, branch.id, branch.name, branch.email, branch.zipcode);
    }
}

void generate_customers(FILE *fp, int size);
void generate_parts(FILE *fp, int size);
void generate_orders(FILE *fp, int size);
