#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbgen.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <scale_factor>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sf = atoi(argv[1]);
    if (sf <= 0) {
        printf("scale factor must be greater then zero\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    char *tsvs[] = {
        "branches.tsv", "customers.tsv", "parts.tsv", "orders.tsv"
    };
    void (*gfs[])(FILE *, int) = {
        generate_branches, generate_customers, generate_parts, generate_orders
    };
    for (int i = 0; i < sizeof(tsvs) / sizeof(tsvs[0]); i++) {
        FILE *fp = fopen(tsvs[i], "w");
        gfs[i](fp, sf);
        fclose(fp);
    }
    return 0;
}

/* TODO: use Mersenne Twister */
int random_int(int min, int max) {
    return min + (int)((max - min + 1.0) * (double) rand() / (1.0 + RAND_MAX));
}

double random_double(double min, double max) {
    return min + ((double) rand() / RAND_MAX) * (max - min);
}

time_t xmktime(int year, int month, int day) {
    struct tm timeinfo = {
        .tm_year = year - 1900,
        .tm_mon = month - 1,
        .tm_mday = day
    };
    time_t t = mktime(&timeinfo);
    if (t == -1) {
        perror("mktime(3)");
        exit(EXIT_FAILURE);
    }
    return t;
}

/**
 * Generate zipcode and set it to char *s
 * For selectivity of query 2, set first two digits of zipcode to last two digits of id.
 */
void generate_zipcode(const int id, char *s) {
    int zipcode =
        (id % 100) * ZIPCODE_UPPER_BOUND / 100
        + random_int(0, ZIPCODE_UPPER_BOUND / 100);
    snprintf(s, ZIPCODE_LENGTH + 1, ZIPCODE_FORMAT, zipcode / ZIPCODE_HALF_MOD, zipcode % ZIPCODE_HALF_MOD);
}

void generate_dates(order_t *order) {
    time_t begin_time= xmktime(ORDER_DATE_YEAR, 1, 1);
    time_t end_time = xmktime(ORDER_DATE_YEAR + 1, 1, 1);

    time_t order_time = random_int(begin_time, end_time - 1 - MAX_DELIVERY_DATE_LENGTH * 86400);
    int due_date_length = random_int(1, MAX_DUE_DATE_LENGTH);
    time_t due_time = order_time + due_date_length * 86400;
    time_t delivery_time = order_time + due_date_length * random_double(0.5, 1.5) * 86400;

    strftime(order->order_datetime, sizeof(order->order_datetime), DATETIME_FORMAT, localtime(&order_time));
    strftime(order->due_date, sizeof(order->due_date), DATE_FORMAT, localtime(&due_time));
    strftime(order->delivery_date, sizeof(order->delivery_date), DATE_FORMAT, localtime(&delivery_time));
}

void generate_branches(FILE *fp, int sf) {
    for (int i = 0; i < sf * BASE_BRANCH_ROWS; i++) {
        branch_t branch;
        memset(&branch, 0, sizeof(branch));
        branch.id = i + 1;
        snprintf(branch.name, sizeof(branch.name), NAME_FORMAT, "Branch", branch.id);
        snprintf(branch.email, sizeof(branch.email), EMAIL_FORMAT, "Branch", branch.id);
        generate_zipcode(branch.id, branch.zipcode);
        fprintf(fp, BRANCH_OUTPUT_FORMAT, branch.id, branch.name, branch.email, branch.zipcode);
    }
}

void generate_customers(FILE *fp, int sf) {
    for (int i = 0; i < sf * BASE_CUSTOMER_ROWS; i++) {
        customer_t customer;
        memset(&customer, 0, sizeof(customer));
        customer.id = i + 1;
        snprintf(customer.last_name, sizeof(customer.last_name), LAST_NAME_FORMAT, "Customer");
        snprintf(customer.first_name, sizeof(customer.first_name), FIRST_NAME_FORMAT, customer.id);
        snprintf(customer.email, sizeof(customer.email), EMAIL_FORMAT, "Customer", customer.id);
        generate_zipcode(customer.id, customer.zipcode);
        fprintf(fp, CUSTOMER_OUTPUT_FORMAT, customer.id, customer.last_name, customer.first_name, customer.email, customer.zipcode);
    }
}

void generate_parts(FILE *fp, int sf) {
    for (int i = 0; i < sf * BASE_PART_ROWS; i++) {
        part_t part;
        memset(&part, 0, sizeof(part));
        part.id = i + 1;
        snprintf(part.name, sizeof(part.name), NAME_FORMAT, "Part", part.id);
        part.price = random_int(PART_PRICE_MIN, PART_PRICE_MAX);
        part.stock = random_int(PART_STOCK_MIN, PART_STOCK_MAX);
        part.production_per_week = random_int(PART_PRODUCTION_MIN, PART_PRODUCTION_MAX);
        fprintf(fp, PART_OUTPUT_FORMAT, part.id, part.name, part.price, part.stock, part.production_per_week);
    }
}

/**
 * Generate data of orders table and write them into FILE *fp
 * For selectivity of query 2, set last two digits of bid and cid to the same value with a probability of ORDER_IN_SAME_PREFECTURE_RATE.
 */
void generate_orders(FILE *fp, int sf) {
    for (int i = 0; i < sf * BASE_ORDER_ROWS; i++) {
        order_t order;
        memset(&order, 0, sizeof(order));
        order.id = i + 1;
        order.bid = random_int(1, sf * BASE_BRANCH_ROWS);
        order.cid = random_int(1, sf * BASE_CUSTOMER_ROWS);
        if (ORDER_IN_SAME_PREFECTURE_RATE > random_double(0, 1)) {
            /* same prefecture */
            int pref = random_int(0, 99);
            order.bid--;
            order.bid += -(order.bid % 100) + pref;
            order.bid++;
            order.cid--;
            order.cid += -(order.cid % 100) + pref;
            order.cid++;
        }
        order.pid = random_int(1, sf * BASE_PART_ROWS);
        order.quantity = random_int(ORDER_QUANTITY_MIN, ORDER_QUANTITY_MAX);
        generate_dates(&order);
        fprintf(fp, ORDER_OUTPUT_FORMAT, order.id, order.bid, order.cid, order.pid, order.quantity, order.order_datetime, order.due_date, order.delivery_date);
    }
}
