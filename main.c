#include "library.h"

int main()
{
    loadbook();
    loadmember();
    loadissue();
    while(1)
    {
        int choice;

        printf("\n*********************************************\n");
        printf("          LIBRARY MANAGEMENT SYSTEM\n");
        printf("*********************************************\n");

        printf("\n1. Student\n");
        printf("2. Library Admin\n");
        printf("3. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

 if(choice == 1)
{
    while(1)
    {
        int stu_ch;

        printf("\n---------- STUDENT MENU ----------\n");
        printf("1. Display Books\n");
        printf("2. Rent a Book\n");
        printf("3. Return Book\n");
        printf("4. Change Choice\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &stu_ch);

        switch(stu_ch)
        {
            case 1:
                displaybook();
                break;

            case 2:
                issuebook();
                break;

            case 3:
                returnbook();
                break;

            case 4:
                goto mainmenu;

            case 5:
                freelibrary();

            default:
                printf("Enter valid choice\n");
        }
    }
}
        else if(choice == 2)
        {
            char *p[5] = {
                "Mohit chauhan",
                "Prashant Kumar",
                "Gaurav Chauhan",
                "Neha Chauhan",
                "Suresh Chauhan"
            };

            char name[50], password[30];
            int found = 0, i;

            printf("\nEnter Your Name: ");
            scanf(" %49[^\n]", name);

            for(i = 0; i < 5; i++)
            {
                if(strcmp(name, p[i]) == 0)
                {
                    found = 1;
                    break;
                }
            }

            if(found != 1)
            {
                printf("You are wrong person!\n");
            }
            else
            {
                printf("You are Library Admin\n");

                printf("Enter Password: ");
                scanf("%29s", password);

                if(strcmp(password, "admin12345") == 0)
                {
                    printf("\nWelcome Sir!\n");

                    while(1)
                    {
                        int admin_ch;

                        printf("\n---------- ADMIN MENU ----------\n");
                        printf("1. Add Book\n");
                        printf("2. Display All Books\n");
                        printf("3. Delete Book\n");
                        printf("4. Update Book Details\n");
                        printf("5. Issue Book\n");
                        printf("6. Return Book\n");
                        printf("7. Check Issued Books\n");
                        printf("8. Check Member Details\n");
                        printf("9. Exit\n");

                        printf("\nEnter your choice: ");
                        scanf("%d", &admin_ch);

                        switch(admin_ch)
                        {
                            case 1:
                                addbook();
                                break;

                            case 2:
                                displaybook();
                                break;

                            case 3:
                                deletebook();
                                break;

                            case 4:
                                updatebook();
                                break;

                            case 5:
                                issuebook();
                                break;

                            case 6:
                                returnbook();
                                break;

                            case 7:
                                checkissuedbook();
                                break;

                            case 8:
                                checkmemberdetails();
                                break;

                            case 9:
                                printf("Thank You!\n");
                                goto mainmenu;

                            default:
                                printf("Enter valid choice\n");
                        }
                    }
                }
                else
                {
                    printf("Wrong Password!\n");
                }
            }
        }
        else if(choice == 3)
        {
            printf("Thank You for using Library Management System!\n");
            break;
        }
        else
        {
            printf("Enter valid choice!\n");
        }

        mainmenu:
        continue;
    }

    return 0;
}