#include "uledger.h"

 char categoryList[7][10] = {{"이체"}, {"교통"}, {"식비"}, {"쇼핑"}, {"여가"}, {"교육"}, {"기타"}};

int mainMenu() {
    getchar();
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
    return choice;
}

int addData(Entry *p[], int count) {
    p[count] = (Entry *)malloc(sizeof(Entry));

    printf("> 날짜를 입력하세요 (YYYY MM DD): ");
    scanf("%d %d %d", &p[count]->date[0], &p[count]->date[1], &p[count]->date[2]);
    getchar();

    printf("> 지출 / 수입 여부 (0: 지출, 1: 수입): ");
    scanf("%d", &p[count]->isIncome);
    getchar();

    printf("> 금액을 입력하세요: ");
    scanf("%d", &p[count]->money);
    getchar();

    if(p[count]->isIncome == 0) {
        printf("> 카테고리를 선택하세요:\n (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타)\n");
        scanf("%d", &p[count]->category);
        getchar();
    }
    else p[count]->category = -1;

    int choice;
    printf("> 메모를 입력할까요? (0: 예, 1: 아니오): ");
    scanf("%d", &choice);
    getchar();

    if(choice == 0) {
        printf("> 메모를 입력하세요 (최대 100자):\n");
        scanf("%[^\n]s", p[count]->memo);
        getchar();
    }

    printf("> 데이터가 저장되었습니다.\n");

    return count + 1;
}

void printData(Entry *p[], int count) {
    printf("==< 전체 데이터 출력 >============================\n");
    printf("번호\t수입/지출\t날짜\t금액\t카테고리\n");
    printf("==================================================\n");
    for(int i = 0; i < count; i++) {
        printf("%d ", i + 1);
        if(p[i]->isIncome == 0) printf("- ");
        else printf("+ ");
        printf("%d/%d/%d %d ", p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money);
        if(p[i]->isIncome == 0) printf("%s\n", categoryList[p[i]->category]);
        else printf("\n");
    }
    printf("==================================================\n");

    analyzeData(p, count);
}

void printByCategory(Entry *p[], int count, int category) {
    printf("==< 카테고리별 데이터 출력 >======================\n");
    printf("번호\t수입/지출\t날짜\t금액\t카테고리\n");
    printf("==================================================\n");
    for(int i = 0; i < count; i++) {
        if(p[i]->category == category) {
            printf("%d - %d/%d/%d %d %s\n", i + 1, p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money, categoryList[p[i]->category]);
        }
    }
    printf("==================================================\n");
}

void printByDate(Entry *p[], int count, int date[]) {
    printf("==< 날짜 별 데이터 출력 >=========================\n");
    printf("번호\t수입/지출\t날짜\t금액\t카테고리\n");
    printf("==================================================\n");
    for(int i = 0; i < count; i++) {
        if(p[i]->date == date) {
            printf("%d ", i + 1);
            if(p[i]->isIncome == 0) printf("- ");
            else printf("+ ");
            printf("%d/%d/%d %d ", p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->money);
            if(p[i]->isIncome == 0) printf("%s\n", categoryList[p[i]->category]);
            else printf("\n");
        }
    }
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

    printf("> 카테고리를 입력하세요:\n (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타)\n");
    scanf("%d", &p[num]->category);
    getchar();

    int choice;
    printf("> 메모를 입력할까요? (0: 예, 1: 아니오): ");
    scanf("%d", &choice);
    getchar();

    if(choice == 0) {
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
    int scnt=0;
    int search=100000;
    printf("지출 / 수입 데이터 (0: 지출, 1: 수입):");
    for (int i= 0 ; i < count; i++){
        if(p[i]->money==-1)continue;
        if(p[i]->money==search){
            printf("%2d",i+1);
            printData(p[i],count);
            scnt++;
        }
     }
     if(scnt==0) printf("> 검색된 데이터가 없습니다!\n");
}

void analyzeData(Entry *p[], int count) {
    int sum[7] = {0};
    int sumall = 0;
    double percentage[7];
    for(int i=0;i<count;i++){
        if(p[i]->category==-1)continue;
        if(p[i]->category==0)
            sum[0]+= p[i]->money;
        else if(p[i]->category==1)
            sum[1]+= p[i]->money;
        else if(p[i]->category==2)
            sum[2]+= p[i]->money;
        else if(p[i]->category==3)
            sum[3]+= p[i]->money;
        else if(p[i]->category==4)
            sum[4]+= p[i]->money;
        else if(p[i]->category==5)
            sum[5]+= p[i]->money;
        else if(p[i]->category==6)
            sum[6]+= p[i]->money;

        sumall+= p[i]->money;
    }// 각 카테고리별 sum 계산 + 전체 sum 계산

    for(int i=0;i<7;i++){
        percentage[i]=sum[i]/sumall;
    }//각 카테고리 별 퍼센티지 계산
    printf("> 카테고리 퍼센티지 (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타)\n");
    printf("이체: %f  지출: %d\n",percentage[0],sum[0]);
    printf("교통: %f  지출: %d\n",percentage[1],sum[1]);
    printf("식비: %f  지출: %d\n",percentage[2],sum[2]);
    printf("쇼핑: %f  지출: %d\n",percentage[3],sum[3]);
    printf("여가: %f  지출: %d\n",percentage[4],sum[4]);
    printf("교육: %f  지출: %d\n",percentage[5],sum[5]);
    printf("기타: %f  지출: %d\n",percentage[6],sum[6]);
    printf("전체 지출: %d",sumall);
}
int loadData(Entry *p[]) {
    int count = 0;
    FILE *fp = fopen("uledger.txt","rt");

    while(!feof(fp)) {
        int ret = 0;
        ret += fscanf(fp,"%d %d %d %d %d %d", &p[count ]->date[0], &p[count]->date[1], &p[count]->date[2], &p[count]->isIncome, &p[count]->money, &p[count]->category);
        ret += fscanf(fp,"%[^\n]s",p[count]->memo);
        if(ret == 7) count++;
    }

    printf("> 로딩성공!");
    fclose(fp);
    return count;
}

void saveData(Entry *p[], int count) {
    FILE *fp = fopen("uledger.txt","wt");

    for(int i = 0; i < count; i++) {
        fprintf(fp, "%d %d %d %d %d %d\n", p[i]->date[0], p[i]->date[1], p[i]->date[2], p[i]->isIncome, p[i]->money, p[i]->category);
        fprintf(fp, "%s\n", p[i]->memo);
    }

    fclose(fp);
    printf("> 저장됨!");
}