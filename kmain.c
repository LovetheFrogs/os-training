struct example {
        unsigned char config;           /* bit 0-7 */
        unsigned short address;         /* bit 8-23 */
        unsigned char index;            /* bit 24-31 */
    } __attribute__((packed));

/* Function sum of three sums three numbers together */
int sum_of_three(int arg1, int arg2, int arg3) {
    return arg1 + arg2 + arg3;
}

/* Function exponent raises a number base to exp */
int exponent(int base, int exp) {
    int result = 1;
    for (int i = 1; i <= exp; i++) {
    	result = result * base;
    }
    return result;
}

int kmain() {
    return 0;    
}
