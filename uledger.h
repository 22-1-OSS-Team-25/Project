#ifndef ULEDGER_H
#define ULEDGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int date[3]; // 0: year, 1: month, 2: day
    int isIncome; // 0: False, 1: True
    int money;
    int category;
    char memo[100];
} Entry;

int mainMenu();
int addData(Entry *p[], int count);
void printData(Entry *p[], int count);                      // 전체 데이터 출력
void printByCategory(Entry *p[], int count, int category);  // 카테고리별 데이터 출력
void printByDate(Entry *p[], int count, int date[]);        // 날짜 별 데이터 출력
void updateData(Entry *p[], int count);
int deleteData(Entry *p[], int count);
void searchData(Entry *p[], int count);
void analyzeData(Entry *p[], int count);                    // printData()와 함께 실행
int loadData(Entry *p[]);
void saveData(Entry *p[], int count);

#endif