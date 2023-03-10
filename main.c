#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

#define TABLE_SIZE 30

int two_to_n(int n) {
    if (n == 0)
        return 1;

    return 2 * two_to_n(n - 1);
}

uint64_t factorial_iter(uint64_t n) {
    uint64_t res = 1;

    for (uint64_t i = 1; i <= n; i++)
        res *= i;
    
    return res;
}

uint64_t factorial_rec(uint64_t n) {
    if (n == 0)
        return 1;

    return n * factorial_rec(n - 1);
}

uint64_t factorial_dyn(uint64_t n) {
    static uint64_t result_table[TABLE_SIZE] = {0};

    uint64_t lookup = result_table[n];
    if (lookup != 0)
        return lookup;

    if (n == 0) {
        result_table[0] = 1;
        return 1;
    }

    uint64_t result = n * factorial_dyn(n - 1);
    result_table[n] = result;

    return result;
}

typedef uint64_t (*fact_fn)(uint64_t);

void benchmark_fn(fact_fn fn, char *name) {
    uint64_t n = 65;
    clock_t acc = 0;

    int iterations = 10000000;
    for (uint64_t i = 0; i < iterations; i++) {
        clock_t start = clock();
        fn(n);
        clock_t end = clock();

        acc += end - start;
    }

    float avg = (float) (acc / iterations) / CLOCKS_PER_SEC;
    printf("A funcao fatorial %s levou em media %f segundos para calcular o fatorial de %llu\n", name, avg, n);
}

int main() {
    printf("2^8 = %d\n", two_to_n(8));

    uint64_t n = 65;
    printf("factorial iter of %llu: %llu\n", n, factorial_iter(n));
    printf("factorial rec of %llu: %llu\n", n, factorial_rec(n));
    printf("factorial_dyn of %llu: %llu\n", n, factorial_dyn(n));

    benchmark_fn(factorial_iter, "iterative");
    benchmark_fn(factorial_rec, "recursive");
    benchmark_fn(factorial_dyn, "dynamic");

    return 0;
}
