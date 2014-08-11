#ifndef DBGEN_H
#define DBGEN_H

#include <stdio.h>

#define NAME_LENGTH 30
#define HALF_NAME_LENGTH 15
#define EMAIL_LENGTH 45
#define ZIPCODE_LENGTH 8

static const char *NAME_FORMAT = "%s#%09d";
static const char *LAST_NAME_FORMAT = "%s";
static const char *FIRST_NAME_FORMAT = "#%09d";
static const char *EMAIL_FORMAT = "%s#%09d@example.com";
static const char *ZIPCODE_FORMAT = "%03d-%04d";

static const int ZIPCODE_UPPER_BOUND = 10000000;
static const int ZIPCODE_HALF_MOD = 10000;

static const char *BRANCH_OUTPUT_FORMAT   = "%d\t%s\t%s\t%s\n";
static const char *CUSTOMER_OUTPUT_FORMAT = "%d\t%s\t%s\t%s\t%s\n";
static const char *PART_OUTPUT_FORMAT     = "%d\t%s\t%d\t%d\t%d\n";
static const char *ORDER_OUTPUT_FORMAT    = "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n";

typedef struct {
    int id;
    char name[NAME_LENGTH + 1];
    char email[EMAIL_LENGTH + 1];
    char zipcode[ZIPCODE_LENGTH + 1];
} branch_t;

typedef struct {
    int id;
    char last_name[HALF_NAME_LENGTH + 1];
    char first_name[HALF_NAME_LENGTH + 1];
    char email[EMAIL_LENGTH + 1];
    char zipcode[ZIPCODE_LENGTH + 1];
} customer_t;

typedef struct {
    int id;
    char name[NAME_LENGTH + 1];
    int price;
    int stock;
    int production_per_week;
} part_t;

typedef struct {
    int id;
    int bid;
    int cid;
    int pid;
    int quantity;
    int order_datetime;
    int due_date;
    int delivery_date;
} order_t;

int random_int(int min, int max);
void generate_zipcode(char *s);

/* NOTICE: the number of rows is limitted to INT_MAX */
void generate_branches(FILE *fp, int size);
void generate_customers(FILE *fp, int size);
void generate_parts(FILE *fp, int size);
void generate_orders(FILE *fp, int size);

#endif /* DBGEN_H */
