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
    generate_branches(stdout, sf);
    generate_customers(stdout, sf);
    generate_parts(stdout, sf);
    generate_orders(stdout, sf);
    return 0;
}

/* TODO: use Mersenne Twister */
int random_int(int min, int max) {
    return min + (int)((max - min + 1.0) * rand() / (1.0 + RAND_MAX));
}

void generate_zipcode(char *s) {
    int zipcode = random_int(0, ZIPCODE_UPPER_BOUND);
    snprintf(s, ZIPCODE_LENGTH + 1, ZIPCODE_FORMAT, zipcode / ZIPCODE_HALF_MOD, zipcode % ZIPCODE_HALF_MOD);
}

void generate_branches(FILE *fp, int sf) {
    for (int i = 0; i < sf * BASE_BRANCH_ROWS; i++) {
        branch_t branch;
        memset(&branch, 0, sizeof(branch));
        branch.id = i + 1;
        snprintf(branch.name, sizeof(branch.name), NAME_FORMAT, "Branch", branch.id);
        snprintf(branch.email, sizeof(branch.email), EMAIL_FORMAT, "Branch", branch.id);
        generate_zipcode(branch.zipcode);
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
        generate_zipcode(customer.zipcode);
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

void generate_orders(FILE *fp, int sf) {
    for (int i = 0; i < sf * BASE_ORDER_ROWS; i++) {
        order_t order;
        memset(&order, 0, sizeof(order));
        order.id = i + 1;
        order.bid = random_int(1, sf * BASE_BRANCH_ROWS);
        order.cid = random_int(1, sf * BASE_CUSTOMER_ROWS);
        order.pid = random_int(1, sf * BASE_PART_ROWS);
        order.quantity = random_int(ORDER_QUANTITY_MIN, ORDER_QUANTITY_MAX);
        /* TODO: change random int to date(time) */
        order.order_datetime = 0;
        order.due_date = 0;
        order.delivery_date = 0;
        fprintf(fp, ORDER_OUTPUT_FORMAT, order.id, order.bid, order.cid, order.pid, order.quantity, order.order_datetime, order.due_date, order.delivery_date);
    }
}
