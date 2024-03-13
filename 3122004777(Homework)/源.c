#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define HASH_SIZE 64

typedef unsigned long long SimHash;

SimHash calculateSimHash(char* text);
int hammingDistance(SimHash hash1, SimHash hash2);
int bitCount(unsigned long long n);
SimHash hash(char* word);

SimHash calculateSimHash(char* text) {
    // 初始化SimHash为0
    SimHash simHash = 0;

    // 计算文本中每个单词的哈希值
    char* token = strtok(text, " ");
    while (token != NULL) {
        SimHash wordHash = hash(token);  // 计算单词的哈希值

        // 计算单词的权重
        int wordWeight = bitCount(wordHash);

        // 根据单词的权重更新SimHash
        if (wordWeight > 0) {
            simHash |= wordHash;
        }

        token = strtok(NULL, " ");
    }

    return simHash;
}

int hammingDistance(SimHash hash1, SimHash hash2) {
    // 使用异或操作计算SimHash之间的汉明距离
    SimHash xorResult = hash1 ^ hash2;

    return bitCount(xorResult);
}

int bitCount(unsigned long long n) {
    // 计算一个长整型数的二进制位中1的个数
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

SimHash hash(char* word) {
    // 使用简单的哈希函数计算单词的哈希值
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*word) {
        hash = hash * seed + (*word++);
    }

    return hash & 0x7FFFFFFFFFFFFFFF;  // 保留64位
}

int main() {
    char text1[] = "This is a sample text.";
    char text2[] = "This is another sample text.";
    char text3[] = "This is a similar text.";

    // 计算SimHash值
    SimHash hash1 = calculateSimHash(text1);
    SimHash hash2 = calculateSimHash(text2);
    SimHash hash3 = calculateSimHash(text3);

    // 计算汉明距离
    int distance1 = hammingDistance(hash1, hash2);
    int distance2 = hammingDistance(hash1, hash3);

    // 计算重复率
    double similarity1 = 1 - (double)distance1 / HASH_SIZE;
    double similarity2 = 1 - (double)distance2 / HASH_SIZE;

    // 打印SimHash、汉明距离和重复率
    printf("Text1: %s\n", text1);
    printf("Text2: %s\n", text2);
    printf("Text3: %s\n", text3);
    printf("SimHash1: %llu\n", hash1);
    printf("SimHash2: %llu\n", hash2);
    printf("SimHash3: %llu\n", hash3);
    printf("Hamming Distance 1: %d\n", distance1);
    printf("Hamming Distance 2: %d\n", distance2);
    printf("Similarity 1: %.2lf%%\n", similarity1 * 100);
    printf("Similarity 2: %.2lf%%\n", similarity2 * 100);

    return 0;
}