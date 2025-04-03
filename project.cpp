#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#define SIZE 1000000000
#define INT_OPERATION_TIME 100
#define FLOAT_OPERATION_TIME 100
#define MEMORY_OPERATION_TIME 100
#define HARD_DRIVE_OPERATION_1_TIME 250
#define HARD_DRIVE_OPERATION_2_TIME 10
#define N 1000000000
#define B 100
#define B2 10000

int main() {
    // Integer operation benchmark
    auto start = std::chrono::high_resolution_clock::now();
    int result = 1;
    for (int i = 1; i <= SIZE; i++) result += i;
    for (int i = 1; i <= SIZE / 2; i++) result *= i;
    for (int i = 1; i <= SIZE / 4; i++) if (i != 0) result /= i;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Integer operation benchmark took: "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";

    // Floating point operation benchmark
    start = std::chrono::high_resolution_clock::now();
    double result_f = 1.0;
    for (int i = 1; i <= SIZE; i++) result_f += i;
    for (int i = 1; i <= SIZE / 2; i++) result_f *= i;
    for (int i = 1; i <= SIZE / 4; i++) if (i != 0) result_f /= i;
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Floating point operation benchmark took: "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";

    // Memory operation benchmark
    start = std::chrono::high_resolution_clock::now();
    int *array = new int[SIZE];
    for (int i = 0; i < SIZE; i++) array[i] = i;
    for (int i = 0; i < SIZE; i++) result += array[i];
    for (int i = 0; i < SIZE; i++) array[i] = result;
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Memory operation benchmark took: "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";
    delete[] array;

    // Hard drive benchmark 1
    start = std::chrono::high_resolution_clock::now();
    FILE *fp = fopen("file1.txt", "w");
    char buf[B] = {0};
    for (int i = 0; i < N / B; i++) fwrite(buf, sizeof(char), B, fp);
    fclose(fp);
    
    fp = fopen("file1.txt", "r");
    for (int i = 0; i < N / B; i++) fread(buf, sizeof(char), B, fp);
    fclose(fp);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Hard drive benchmark 1 took: "
              << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";
    
    // Hard drive benchmark 2
    start = std::chrono::high_resolution_clock::now();
    fp = fopen("file2.txt", "w");
    char buf2[B2] = {0};
    for (int i = 0; i < N / B2; i++) fwrite(buf2, sizeof(char), B2, fp);
    fclose(fp);

    fp = fopen("file2.txt", "r");
    for (int i = 0; i < N / B2; i++) fread(buf2, sizeof(char), B2, fp);
    fclose(fp);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Hard drive benchmark 2 took: "
                << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " seconds\n";
    
    return 0;
}                