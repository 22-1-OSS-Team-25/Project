#include "uledger.h"

int mainMenu() {
    int choice;
    printf("\n==< ULedger >=======\n");
    printf("1. 데이터 추가\n");
    printf("2. 데이터 출력\n");
    printf("3. 데이터 수정\n");
    printf("4. 데이터 삭제\n");
    printf("5. 데이터 검색\n");
    printf("6. 데이터 저장\n");

    scanf("%d", &choice);
    return choice;
}

int addData(Entry *p[], int count) {
    p[count] = (Entry *)malloc(sizeof(Entry));

    printf("> 날짜를 입력하세요 (YYYY MM DD): ");
    scanf("%d %d %d", p[count]->date[0], p[count]->date[1], p[count]->date[2]);

    printf("> 지출 / 수입 여부 (0: 지출, 1: 수입): ");
    scanf("%d", &p[count]->isIncome);

    printf("> 금액을 입력하세요: ");
    scanf("%d", &p[count]->money);

    if(p[count]->isIncome == 0) {
        printf("> 카테고리를 선택하세요:\n (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타)\n");
        scanf("%d", &p[count]->category);
    }
    else p[count]->category = -1;

    int choice;
    printf("> 메모를 입력하실래요? (0: 예, 1: 아니오): ");
    scanf("%d", &choice);

    if(choice == 0) {
        printf("> 메모를 입력하세요 (최대 100자):\n");
        scanf("%[^\n]s", p[count]->memo);
    }

    printf("> 데이터가 저장되었습니다.\n")

    return count + 1;
}

void printData(Entry *p[], int count) {

}

void printByCategory(Entry *p[], int count, int category) {

}

void printByDate(Entry *p[], int count, int date[]) {

}

void updateData(Entry *p[]) {

}

int deleteData(Entry *p[], int count) {

}

void searchData(Entry *p[], int count) {

}

void analyzeData(Entry *p[], int count) {

}

int loadData(Entry *p[]) {

}

void saveData(Entry *p[], int count) {

}