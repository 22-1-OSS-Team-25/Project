#include "uledger.h"

int main() {
    #ifdef DEBUG
    printf("ULedger > Debug Mode\n");
    #endif
    Entry *ledger[100];
    int count = loadData(ledger);

    while(1) {
        int choice = mainMenu();
        #ifdef DEBUG
        printf("ULedger > mainMenu() > return = %d\n", choice);
        #endif
        if(choice == 1) {
            count = addData(ledger, count);
        }
        else if(choice == 2) {
            int print;
            printf("> 출력 유형을 선택해 주세요.\n (1: 전체 데이터, 2: 카테고리별, 3: 날짜별): ");
            scanf("%d", &print);
            if(print == 1) {
                printData(ledger, count);
            }
            else if(print == 2) {
                int category;
                printf("> 카테고리를 선택해 주세요.\n (0: 이체, 1: 교통, 2: 식비, 3: 쇼핑, 4: 여가, 5: 교육, 6: 기타): ");
                scanf("%d", &category);
                printByCategory(ledger, count, category);
            }
            else if(print == 3) {
                int date[3];
                printf("> 날짜를 입력해 주세요.\n (예: 2022 01 01): ");
                scanf("%d %d %d", &date[0], &date[1], &date[2]);
                printByDate(ledger, count, date);
            }
            else {
                printf("> 잘못된 입력입니다.\n");
            }  
        }
        else if(choice == 3) {
            updateData(ledger, count);
        }
        else if(choice == 4) {
            count = deleteData(ledger, count);
        }
        else if(choice == 5) {
            searchData(ledger, count);
        }
        else if(choice == 6) {
            saveData(ledger, count);
        }
        else if(choice == 0) {
            #ifdef DEBUG
            printf("ULedger > Exit\n");
            #endif
            printf("> 종료!\n");
            
            

        }
    }
}