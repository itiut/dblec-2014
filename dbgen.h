#ifndef DBGEN_H
#define DBGEN_H

#include <stdio.h>
#include <time.h>

static const int BASE_BRANCH_ROWS   =   100; /*   10000 */
static const int BASE_CUSTOMER_ROWS =  1500; /*  150000 */
static const int BASE_PART_ROWS     =  2000; /*  200000 */
static const int BASE_ORDER_ROWS    = 30000; /* 6000000 */

#define NAME_LENGTH 30
#define HALF_NAME_LENGTH 15
#define EMAIL_LENGTH 45
#define ZIPCODE_LENGTH 8
#define DATETIME_LENGTH 19
#define DATE_LENGTH 10

static const int PART_PRICE_MIN = 100;
static const int PART_PRICE_MAX = 4000; /* TODO: change value for Q1 */
static const int PART_STOCK_MIN = 100;
static const int PART_STOCK_MAX = 1000;
static const int PART_PRODUCTION_MIN = 100;
static const int PART_PRODUCTION_MAX = 1000;

static const int ORDER_QUANTITY_MIN = 1;
static const int ORDER_QUANTITY_MAX = 50;
static const int ORDER_DATE_YEAR = 2013;
static const double ORDER_IN_SAME_PREFECTURE_RATE = 0.9;
static const int MAX_DUE_DATE_LENGTH = 10;
static const int MAX_DELIVERY_DATE_LENGTH = 15;

static const int ZIPCODE_UPPER_BOUND = 10000000;
static const int ZIPCODE_HALF_MOD = 10000;

static const char *NAME_FORMAT = "%s#%09d";
static const char *LAST_NAME_FORMAT = "%s";
static const char *FIRST_NAME_FORMAT = "#%09d";
static const char *EMAIL_FORMAT = "%s#%09d@example.com";
static const char *ZIPCODE_FORMAT = "%03d-%04d";
static const char *DATETIME_FORMAT = "%F %T";
static const char *DATE_FORMAT = "%F";

static const char *BRANCH_OUTPUT_FORMAT   = "%d\t%s\t%s\t%s\n";
static const char *CUSTOMER_OUTPUT_FORMAT = "%d\t%s\t%s\t%s\t%s\n";
static const char *PART_OUTPUT_FORMAT     = "%d\t%s\t%d\t%d\t%d\n";
static const char *ORDER_OUTPUT_FORMAT    = "%d\t%d\t%d\t%d\t%d\t%s\t%s\t%s\n";

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
    char order_datetime[DATETIME_LENGTH + 1];
    char due_date[DATE_LENGTH + 1];
    char delivery_date[DATE_LENGTH + 1];
} order_t;

int random_int(int min, int max);
double random_double(double min, double max);
time_t xmktime(int year, int month, int day);

void generate_zipcode(const int id, char *s);
void generate_dates(order_t *order);

/* NOTICE: the number of rows is limitted to INT_MAX */
/*         sf * BASE_ORDER_ROWS must be smaller than or equal to INT_MAX */
void generate_branches(FILE *fp, int sf);
void generate_customers(FILE *fp, int sf);
void generate_parts(FILE *fp, int sf);
void generate_orders(FILE *fp, int sf);

#endif /* DBGEN_H */
