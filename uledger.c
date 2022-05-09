#include "uledger.h"

 char categoryList[7][10] = {{"이체"}, {"교통"}, {"식비"}, {"쇼핑"}, {"여가"}, {"교육"}, {"기타"}};

int mainMenu() {
    int choice;
    printf("\n=====< ULedger >=====\n");
    printf("1. 데이터 추가\n");
    printf("2. 데이터 출력\n");
    printf("3. 데이터 수정\n");
    printf("4. 데이터 삭제\n");
    printf("5. 데이터 검색\n");
    printf("6. 데이터 저장\n");
    printf("0. 종료\n\n");

    printf("> 메뉴 선택: ");
    scanf("%d", &choice);
    getchar();
    if(choice < 0 || choice > 6) {
        printf("> 잘못된 입력입니다.\n");
        return mainMenu();
    }
    return choice;
}

int addData(Entry *p[], int count) {
    p[count] = (Entry *)malloc(sizeof(Entry));

    printf("> 날짜를 입력하세요 (YYYY MM DD): ");
    scanf("%d %d %d", &p[count]->date[0], &p[count]->date[1], &p[count]->date[2]);
    getchar();

    printf("> 지출 / 수입 여부 (1: 지출, 2: 수입): ");
    scanf("%d", &p[count]->isIncome);
    getchar();

    printf("> 금액을 입력하세요: ");
    scanf("%d", &p[count]->money);
    getchar();

    if(p[count]->isIncome == 1) {
        printf("> 카테고리를 선택하세요 (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타): ");
        scanf("%d", &p[count]->category);
        getchar();
    }
    else p[count]->category = -1;

    int choice;
    printf("> 메모를 입력할까요? (1: 예, 2: 아니오): ");
    scanf("%d", &choice);
    getchar();

    if(choice == 1) {
        printf("> 메모를 입력하세요 (최대 100자):\n");
        scanf("%[^\n]s", p[count]->memo);
        getchar();
    }

    printf("> 데이터가 저장되었습니다.\n");
    return count + 1;
}

void printData(Entry *p[], int count) {
    int in = 0;
    int out = 0;
    printf("==< 전체 데이터 출력 >============================\n");
    printf("번호\t+/-\t날짜\t금액\t카테고리\n");
    printf("==================================================\n");
    for(int i = 0; i < count; i++) {
        printf("%d\t", i + 1);
        if(p[i]->isIncome == 1) {
            printf("-\t");
            out += p[i]->money;
        }
        else {
            printf("+\t");
            in += p[i]->money;
        }
        printf("%d/%d/%d\t%d\t", p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money);
        if(p[i]->isIncome == 1) printf("%s\n", categoryList[p[i]->category]);
        else printf("\n");
    }
    printf("==================================================\n");
    printf("총 수입: %d\t총 지출: %d\n", in, out);
    printf("결산: %d\n", in - out);
    printf("==================================================\n");

    int choice;
    printf("> 상세 데이터를 조회하시겠습니까? (1: 예, 2: 아니오): ");
    scanf("%d", &choice);
    getchar();

    if(choice == 1) {
        int num;
        printf("> 상세 데이터를 조회할 번호를 입력하세요: ");
        scanf("%d", &num);
        getchar();

        if(num > count || num < 1) {
            printf("> 잘못된 입력입니다.\n");
            return;
        }

        printf("==< %2d번째 데이터 출력 >====================\n", num);
        printf("날짜: %d/%d/%d\n", p[num - 1]->date[0], p[num - 1]->date[1], p[num - 1]->date[2]);
        printf("금액: %d\n", p[num - 1]->money);
        printf("카테고리: ");
        if(p[num - 1]->isIncome == 1) printf("%s\n", categoryList[p[num - 1]->category]);
        else printf("수입\n");
        printf("메모:\n%s\n", p[num - 1]->memo);
        printf("==================================================\n");
    }
}

void printByCategory(Entry *p[], int count, int category) {
    int out = 0;
    printf("==< 카테고리별 데이터 출력 >======================\n");
    printf("번호\t+/-\t날짜\t금액\t카테고리\n");
    printf("==================================================\n");
    for(int i = 0; i < count; i++) {
        if(p[i]->category == category) {
            printf("%d\t-\t%d/%d/%d\t%d\t%s\n", i + 1, p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money, categoryList[p[i]->category]);
        }
    }
    printf("==================================================\n");
    printf("%s 카테고리의 총 지출: %d\n", categoryList[category], out);
    printf("==================================================\n");
}

void printByDate(Entry *p[], int count, int date[]) {
    int in = 0;
    int out = 0;
    printf("==< 날짜 별 데이터 출력 >=========================\n");
    printf("번호\t+/-\t날짜\t금액\t카테고리\n");
    printf("==================================================\n");
    for(int i = 0; i < count; i++) {
        if(p[i]->date == date) {
            printf("%d\t", i + 1);
            if(p[i]->isIncome == 1) {
                printf("-\t");
                out += p[i]->money;
            }
            else {
                printf("+\t");
                in += p[i]->money;
            }
            printf("%d/%d/%d\t%d\t", p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money);
            if(p[i]->isIncome == 1) printf("%s\n", categoryList[p[i]->category]);
            else printf("\n");
        }
    }
    printf("==================================================\n");
    printf("%d/%d/%d의 총 수입: %d\t총 지출: %d\n", date[0], date[1], date[2], in, out);
    printf("결산: %d\n", in - out);
    printf("==================================================\n");
}

void updateData(Entry *p[], int count) {
    printData(p, count);
    int num;
    printf("> 수정할 데이터의 번호를 입력하세요: ");
    scanf("%d", &num);
    num--;
    getchar();

    printf("> 날짜를 입력하세요 (YYYY MM DD): ");
    scanf("%d %d %d", &p[num]->date[0], &p[num]->date[1], &p[num]->date[2]);
    getchar();

    printf("> 금액을 입력하세요: ");
    scanf("%d", &p[num]->money);
    getchar();

    printf("> 카테고리를 입력하세요 (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타): ");
    scanf("%d", &p[num]->category);
    getchar();

    int choice;
    printf("> 메모를 입력할까요? (1: 예, 2: 아니오): ");
    scanf("%d", &choice);
    getchar();

    if(choice == 1) {
        printf("> 메모를 입력하세요 (최대 100자):\n");
        scanf("%[^\n]s", p[num]->memo);
        getchar();
    }

    printf("> 데이터가 수정되었습니다.\n");
}

int deleteData(Entry *p[], int count) {
    printData(p, count);
    int num;
    printf("> 삭제할 데이터의 번호를 입력하세요: ");
    scanf("%d", &num);

    for(int i = num; i < count - 1; i++) {
        p[i] = p[i + 1];
    }

    printf("> 데이터가 삭제되었습니다.\n");
    return count - 1;
}

void searchData(Entry *p[], int count) {
    int choice;
    printf("> 검색 방식을 선택하세요:\n (1: 금액 일치, 2: 금액 이상)\n");
    scanf("%d", &choice);

    if(choice == 1) {
        int money;
        int record = 0;
        printf("> 금액을 입력하세요: ");
        scanf("%d", &money);

        printf("==< 검색: 금액 일치 >=============================\n");
        printf("번호\t+/-\t날짜\t금액\t카테고리\n");
        printf("==================================================\n");
        for(int i = 0; i < count; i++) {
            if(p[i]->money == money) {
                printf("%d - %d/%d/%d %d %s\n", i + 1, p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money, categoryList[p[i]->category]);
                record++;
            }
        }
        printf("==< %2d개의 검색 결과 >==========================\n", record);
    }
    else if(choice == 2) {
        int money;
        int record = 0;
        printf("> 금액을 입력하세요: ");
        scanf("%d", &money);

        printf("==< 검색: 금액 이상 >=============================\n");
        printf("번호\t+/-\t날짜\t금액\t카테고리\n");
        printf("==================================================\n");
        for(int i = 0; i < count; i++) {
            if(p[i]->money >= money) {
                printf("%d - %d/%d/%d %d %s\n", i + 1, p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money, categoryList[p[i]->category]);
                record++;
            }
        }
        printf("==< %2d개의 검색 결과 >==========================\n", record);
    }
    else {
        printf("> 잘못된 입력입니다.\n");
    }
}

int loadData(Entry *p[]) {
    int count = 0;
    FILE *fp = fopen("uledger.txt","rt");

    if(fp == NULL) {
        printf("> 파일이 없습니다.\n");
        return 0;
    }

    while(!feof(fp)) {
        p[count] = (Entry *)malloc(sizeof(Entry));
        int ret = fscanf(fp,"%d %d %d %d %d %d %[^\n]s", &p[count]->date[0], &p[count]->date[1], &p[count]->date[2], &p[count]->isIncome, &p[count]->money, &p[count]->category, p[count]->memo);
        if(ret < 7) continue;
        count++;
    }

    printf("> 로딩성공!");
    fclose(fp);
    return count;
}

void saveData(Entry *p[], int count) {
    FILE *fp = fopen("uledger.txt","wt");

    for(int i = 0; i < count; i++) {
        fprintf(fp, "%d %d %d %d %d %d %s\n", p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->isIncome, p[i]->money, p[i]->category, p[i]->memo);
    }

    printf("> 저장됨!");
    fclose(fp);
}