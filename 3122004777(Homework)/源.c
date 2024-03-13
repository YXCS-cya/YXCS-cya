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
    // ��ʼ��SimHashΪ0
    SimHash simHash = 0;

    // �����ı���ÿ�����ʵĹ�ϣֵ
    char* token = strtok(text, " ");
    while (token != NULL) {
        SimHash wordHash = hash(token);  // ���㵥�ʵĹ�ϣֵ

        // ���㵥�ʵ�Ȩ��
        int wordWeight = bitCount(wordHash);

        // ���ݵ��ʵ�Ȩ�ظ���SimHash
        if (wordWeight > 0) {
            simHash |= wordHash;
        }

        token = strtok(NULL, " ");
    }

    return simHash;
}

int hammingDistance(SimHash hash1, SimHash hash2) {
    // ʹ������������SimHash֮��ĺ�������
    SimHash xorResult = hash1 ^ hash2;

    return bitCount(xorResult);
}

int bitCount(unsigned long long n) {
    // ����һ�����������Ķ�����λ��1�ĸ���
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

SimHash hash(char* word) {
    // ʹ�ü򵥵Ĺ�ϣ�������㵥�ʵĹ�ϣֵ
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*word) {
        hash = hash * seed + (*word++);
    }

    return hash & 0x7FFFFFFFFFFFFFFF;  // ����64λ
}

int main() {
    char text1[] = "This is a sample text.";
    char text2[] = "This is another sample text.";
    char text3[] = "This is a similar text.";

    // ����SimHashֵ
    SimHash hash1 = calculateSimHash(text1);
    SimHash hash2 = calculateSimHash(text2);
    SimHash hash3 = calculateSimHash(text3);

    // ���㺺������
    int distance1 = hammingDistance(hash1, hash2);
    int distance2 = hammingDistance(hash1, hash3);

    // �����ظ���
    double similarity1 = 1 - (double)distance1 / HASH_SIZE;
    double similarity2 = 1 - (double)distance2 / HASH_SIZE;

    // ��ӡSimHash������������ظ���
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