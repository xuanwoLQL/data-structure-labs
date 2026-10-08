#include<stdio.h>
#include<stdlib.h>
#include"Link_List.h"
#include"Set.h"
int main()
{
    int choice;

    do {
        system("cls");
        Menu();
        scanf("%d", &choice);
        system("cls");
        switch(choice)
        {
            case 1:
                Function1();
                break;
            case 2:
                Function2();
                break;
            case 3:
                Function3();
                break;
            case 4:
                Function4();
                break;
            case 0:
                printf("谢谢使用！\n");
                break;
            default:
                printf("输入错误，请重新选择！\n");
        }
        if(choice != 0) {
            WaitForEnter();
        }
    } while(choice != 0);

    return 0;
}
