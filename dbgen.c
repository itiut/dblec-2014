#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dbgen.h"

int main(int argc, char *argv[]) {
    srand(time(NULL));
    generate_branches(stdout, 10);
    generate_customers(stdout, 10);
    generate_parts(stdout, 10);
    generate_orders(stdout, 10);
    return 0;
}

/* TODO: use random in C++11 */
int random_int(int min, int max) {
    return min + (int)((max - min + 1.0) * rand() / (1.0 + RAND_MAX));
}

void generate_zipcode(char *s) {
    int zipcode = random_int(0, ZIPCODE_UPPER_BOUND);
    snprintf(s, ZIPCODE_LENGTH + 1, ZIPCODE_FORMAT, zipcode / ZIPCODE_HALF_MOD, zipcode % ZIPCODE_HALF_MOD);
}

void generate_branches(FILE *fp, int size) {
    for (int i = 0; i < size; i++) {
        branch_t branch;
        memset(&branch, 0, sizeof(branch));
        branch.id = i + 1;
        snprintf(branch.name, sizeof(branch.name), NAME_FORMAT, "Branch", branch.id);
        snprintf(branch.email, sizeof(branch.email), EMAIL_FORMAT, "Branch", branch.id);
        generate_zipcode(branch.zipcode);
        fprintf(fp, BRANCH_OUTPUT_FORMAT, branch.id, branch.name, branch.email, branch.zipcode);
    }
}

void generate_customers(FILE *fp, int size) {
    for (int i = 0; i < size; i++) {
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

void generate_parts(FILE *fp, int size) {
    for (int i = 0; i < size; i++) {
        part_t part;
        memset(&part, 0, sizeof(part));
        part.id = i + 1;
        snprintf(part.name, sizeof(part.name), NAME_FORMAT, "Part", part.id);
        part.price = random_int(100, 4000);
        part.stock = random_int(100, 1000);
        part.production_per_week = random_int(100, 1000);
        fprintf(fp, PART_OUTPUT_FORMAT, part.id, part.name, part.price, part.stock, part.production_per_week);
    }
}

void generate_orders(FILE *fp, int size) {
    for (int i = 0; i < size; i++) {
        order_t order;
        memset(&order, 0, sizeof(order));
        order.id = i + 1;
        /* TODO: generate random int */
        order.bid = 0;
        order.cid = 0;
        order.pid = 0;
        order.quantity = random_int(1, 50);
        /* TODO: change random int to date(time) */
        order.order_datetime = 0;
        order.due_date = 0;
        order.delivery_date = 0;
        fprintf(fp, ORDER_OUTPUT_FORMAT, order.id, order.bid, order.cid, order.pid, order.quantity, order.order_datetime, order.due_date, order.delivery_date);
    }
}
