#include "library.h"

struct Book *book = NULL;
struct Member *member = NULL;
struct Issue * issue = NULL;
int countissue = 0;
int countbook = 0;
int countmember  = 0;


void loadbook(){
    struct Book temp;
    struct Book * btemp;
    FILE * fp = fopen("book.dat","rb");
    if(fp == NULL){
        printf("Book not found..\n");
        return;
    }
    
    while(fread(&temp,sizeof(struct Book),1,fp)==1){
    btemp = realloc(book,(countbook+1)*sizeof(struct Book));
    if(btemp == NULL){
        printf("Memory not allocated\n");
        fclose(fp);
        fp = NULL;
        return;
    }
    book = btemp;
    book[countbook] = temp;
    countbook++;
    }

    fclose(fp);
}

void loadmember(void){
    struct Member m;
    struct Member * mtemp;
    FILE * fm = fopen("member.dat","rb");
    if(fm == NULL){
        printf("File not found\n");
        return;
    }
    while(fread(&m,sizeof(struct Member),1,fm)==1){
        mtemp = realloc(member,(countmember+1)*sizeof(struct Member));
        if(mtemp == NULL){
            printf("Memory is not allocated\n");
            fclose(fm);
            fm = NULL;
            return;
        }
        member = mtemp;
        member[countmember] = m;
        countmember++;
    }
    fclose(fm);
}

void loadissue(void){
    struct Issue i,* itemp;
    FILE * fi = fopen("issue.dat","rb");
    if(fi == NULL){
        printf("File not found\n");
        fclose(fi);
        fi = NULL;
        return;
    }
    while(fread(&i,sizeof(struct Issue),1,fi)==1){
        itemp = realloc(issue,(countissue+1)*sizeof(struct Issue));
        if(itemp == NULL){
            printf("Memory not allocated\n");
            return;
        }

        issue = itemp;
        issue[countissue] = i;
        countissue++;
    }
}

void addbook(void)
{
    int id, i, found = 0;
    struct Book newbook;
    struct Book *btemp;

    printf("Enter Book ID: ");
    if(scanf("%d", &id) != 1)
    {
        printf("Invalid Book ID\n");
        return;
    }

    printf("Enter Book Name: ");
    scanf(" %59[^\n]", newbook.bookname);

    for(i = 0; i < countbook; i++)
    {
        if(book[i].book_id == id)
        {
            found = 1;

            if(strcmp(book[i].bookname, newbook.bookname) == 0)
            {
                book[i].total_quantity++;
                book[i].available_qantity++;
                printf("Book quantity increased successfully\n");
            }
            else
            {
                printf("This Book ID already belongs to another book\n");
                return;
            }

            break;
        }
    }

    if(found == 1)
    {
        FILE *fp = fopen("book.dat", "wb");

        if(fp == NULL)
        {
            printf("Unable to open file\n");
            return;
        }

        fwrite(book, sizeof(struct Book), countbook, fp);
        fclose(fp);
        return;
    }

    newbook.book_id = id;

    printf("Enter Author Name: ");
    scanf(" %59[^\n]", newbook.author_name);

    printf("Enter Subject: ");
    scanf(" %49[^\n]", newbook.subject);

    newbook.total_quantity = 1;
    newbook.available_qantity = 1;

    btemp = realloc(book, (countbook + 1) * sizeof(struct Book));

    if(btemp == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    book = btemp;
    book[countbook] = newbook;
    countbook++;

    FILE *fp = fopen("book.dat", "wb");

    if(fp == NULL)
    {
        printf("Unable to open file\n");
        return;
    }

    fwrite(book, sizeof(struct Book), countbook, fp);
    fclose(fp);

    printf("New book added successfully\n");
}


void displaybook(void)
{
    int i, j;
    struct Book swap;

    if(countbook == 0)
    {
        printf("No books available!\n");
        return;
    }

    for(i = 0; i < countbook - 1; i++)
    {
        for(j = 0; j < countbook - 1 - i; j++)
        {
            if(book[j].book_id > book[j+1].book_id)
            {
                swap = book[j];
                book[j] = book[j+1];
                book[j+1] = swap;
            }
        }
    }

    for(i = 0; i < countbook; i++)
    {
        printf("\nBook ID: %d\n", book[i].book_id);
        printf("Book Name: %s\n", book[i].bookname);
        printf("Author Name: %s\n", book[i].author_name);
        printf("Subject: %s\n", book[i].subject);
        printf("Total Quantity: %d\n", book[i].total_quantity);
        printf("Available Quantity: %d\n", book[i].available_qantity);
        printf("--------------------------\n");
    }
}

void deletebook(void)
{
    int idd, i, j, found = 0;
    char name[60];
    FILE *fp;

    printf("Enter id and name of book\n");
    scanf("%d %[^\n]", &idd, name);

    for(i = 0; i < countbook; i++)
    {
        if(book[i].book_id == idd &&
           strcmp(book[i].bookname, name) == 0)
        {
            if(book[i].available_qantity < book[i].total_quantity)
            {
                printf("Book can't be deleted... %d books are issued\n",
                       book[i].total_quantity - book[i].available_qantity);
                return;
            }

            found = 1;

            for(j = i; j < countbook - 1; j++)
            {
                book[j] = book[j + 1];
            }

            countbook--;

            fp = fopen("book.dat", "wb");

            if(fp == NULL)
            {
                printf("File opening failed!\n");
                return;
            }

            if(countbook > 0)
            {
                fwrite(book, sizeof(struct Book), countbook, fp);
            }

            fclose(fp);

            printf("Book deleted successfully..\n");
            break;
        }
    }

    if(found == 0)
    {
        printf("Book not found....\n");
    }
}

void updatebook(void)
{
    int i, idd, choice, found = 0;
    FILE *fp;
    char name[60], author[60], subjectname[50];

    printf("Enter book id\n");
    scanf("%d", &idd);

    for(i = 0; i < countbook; i++)
    {
        if(book[i].book_id == idd)
        {
            found = 1;

            printf("What do you want to update? Select your choice\n");
            printf("1. Book name\n");
            printf("2. Author name\n");
            printf("3. Subject name\n");
            printf("Enter your choice\n");
            scanf("%d", &choice);

            if(choice == 1)
            {
                printf("Enter new book name\n");
                scanf(" %59[^\n]", name);
                strcpy(book[i].bookname, name);
                printf("Book name successfully updated..\n");
            }
            else if(choice == 2)
            {
                printf("Enter new book author name\n");
                scanf(" %59[^\n]", author);
                strcpy(book[i].author_name, author);
                printf("Book author name successfully updated..\n");
            }
            else if(choice == 3)
            {
                printf("Enter new subject name\n");
                scanf(" %49[^\n]", subjectname);
                strcpy(book[i].subject, subjectname);
                printf("Book subject name successfully updated..\n");
            }
            else
            {
                printf("Invalid choice!\n");
                return;
            }

            fp = fopen("book.dat", "wb");

            if(fp == NULL)
            {
                printf("File opening failed!\n");
                return;
            }

            if(fwrite(book, sizeof(struct Book), countbook, fp) != countbook)
            {
                printf("Error updating file!\n");
                fclose(fp);
                return;
            }

            fclose(fp);
            break;
        }
    }

    if(found == 0)
    {
        printf("Book not found\n");
    }
}


void issuebook(void)
{
    int i, j, choice, idd, mid;
    int found = 0;
    int memberindex = -1;
    int schoice;

    char searchname[50];
    char temp[100];

    struct Member *tempp;
    struct Issue *temppp;

    FILE *mp, *ip, *bp;

    printf("\nSearch Book...\n");
    printf("1. Search book by subject name\n");
    printf("2. Search book by book name\n");
    printf("3. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 1)
    {
        printf("Enter subject name: ");
        scanf(" %49[^\n]", searchname);
    }
    else if(choice == 2)
    {
        printf("Enter book name: ");
        scanf(" %49[^\n]", searchname);
    }
    else if(choice == 3)
    {
        return;
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    printf("\nAvailable Book Details:\n");

    for(i = 0; i < countbook; i++)
    {
        if(choice == 1)
            strcpy(temp, book[i].subject);
        else
            strcpy(temp, book[i].bookname);

        if(strcmp(temp, searchname) == 0 &&
           book[i].available_qantity > 0)
        {
            found = 1;

            printf("\nBook ID: %d\n", book[i].book_id);
            printf("Book Name: %s\n", book[i].bookname);
            printf("Author: %s\n", book[i].author_name);
            printf("Available Quantity: %d\n",
                   book[i].available_qantity);
            printf("--------------------------\n");
        }
    }

    if(found == 0)
    {
        printf("No available books found!\n");
        return;
    }

    printf("\nEnter book ID to issue: ");
    scanf("%d", &idd);

    found = 0;

    for(i = 0; i < countbook; i++)
    {
        if(choice == 1)
            strcpy(temp, book[i].subject);
        else
            strcpy(temp, book[i].bookname);

        if(book[i].book_id == idd &&
           strcmp(temp, searchname) == 0 &&
           book[i].available_qantity > 0)
        {
            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Invalid Book ID or book unavailable!\n");
        return;
    }

    printf("\n1. New User\n");
    printf("2. Existing User\n");
    printf("Enter your choice: ");
    scanf("%d", &schoice);

    if(schoice == 1)
    {
        printf("Enter new Member ID: ");
        scanf("%d", &mid);

        for(j = 0; j < countmember; j++)
        {
            if(member[j].member_id == mid)
            {
                printf("Member ID already exists!\n");
                return;
            }
        }

        tempp = realloc(member,
                        (countmember + 1) * sizeof(struct Member));

        if(tempp == NULL)
        {
            printf("Member memory allocation failed!\n");
            return;
        }

        member = tempp;

        printf("Enter member name: ");
        scanf(" %49[^\n]", member[countmember].member_name);

        member[countmember].member_id = mid;

        memberindex = countmember;
        countmember++;

        printf("Member registered successfully!\n");
    }
    else if(schoice == 2)
    {
        printf("Enter Member ID: ");
        scanf("%d", &mid);

        for(j = 0; j < countmember; j++)
        {
            if(member[j].member_id == mid)
            {
                memberindex = j;
                break;
            }
        }

        if(memberindex == -1)
        {
            printf("Member not found!\n");
            return;
        }

        printf("\nWelcome %s!\n",
               member[memberindex].member_name);
    }
    else
    {
        printf("Invalid choice!\n");
        return;
    }

    temppp = realloc(issue,
                     (countissue + 1) * sizeof(struct Issue));

    if(temppp == NULL)
    {
        printf("Issue memory allocation failed!\n");
        return;
    }

    issue = temppp;

    issue[countissue].member_id = member[memberindex].member_id;
    issue[countissue].book_id = idd;

    printf("\nEnter issue day: ");
    scanf("%d", &issue[countissue].issue_date);

    printf("Enter issue month: ");
    scanf("%d", &issue[countissue].issue_month);

    printf("Enter issue year: ");
    scanf("%d", &issue[countissue].issue_year);

    issue[countissue].return_date = 0;
    issue[countissue].return_month = 0;
    issue[countissue].return_year = 0;
    issue[countissue].status = 0;

    book[i].available_qantity--;

    countissue++;

    if(schoice == 1)
    {
        mp = fopen("member.dat", "wb");

        if(mp == NULL)
        {
            printf("Member file opening failed!\n");
            return;
        }

        if(fwrite(member, sizeof(struct Member), countmember, mp)
           != countmember)
        {
            printf("Member file writing failed!\n");
            fclose(mp);
            return;
        }

        fclose(mp);
    }

    ip = fopen("issue.dat", "wb");

    if(ip == NULL)
    {
        printf("Issue file opening failed!\n");
        return;
    }

    if(fwrite(issue, sizeof(struct Issue), countissue, ip)
       != countissue)
    {
        printf("Issue file writing failed!\n");
        fclose(ip);
        return;
    }

    fclose(ip);

    bp = fopen("book.dat", "wb");

    if(bp == NULL)
    {
        printf("Book file opening failed!\n");
        return;
    }

    if(fwrite(book, sizeof(struct Book), countbook, bp)
       != countbook)
    {
        printf("Book file writing failed!\n");
        fclose(bp);
        return;
    }

    fclose(bp);

    printf("\nBook issued successfully!\n");
}

void returnbook(void)
{
    int mid, i, j;
    int mfound = 0, ifound = 0;
    int bookid, bookindex = -1;
    FILE *fp;

    printf("Enter member ID: ");
    scanf("%d", &mid);

    for(i = 0; i < countmember; i++)
    {
        if(mid == member[i].member_id)
        {
            printf("Member found: %s\n",
                   member[i].member_name);
            mfound = 1;
            break;
        }
    }

    if(mfound == 0)
    {
        printf("Member not found!\n");
        return;
    }

    printf("\nYour issued books:\n");

    for(i = 0; i < countissue; i++)
    {
        if(issue[i].member_id == mid &&
           issue[i].status == 0)
        {
            printf("Book ID: %d\n", issue[i].book_id);
            ifound = 1;
        }
    }

    if(ifound == 0)
    {
        printf("You have no currently issued books!\n");
        return;
    }

    printf("\nEnter Book ID to return: ");
    scanf("%d", &bookid);

    ifound = 0;

    for(i = 0; i < countissue; i++)
    {
        if(issue[i].member_id == mid &&
           issue[i].book_id == bookid &&
           issue[i].status == 0)
        {
            ifound = 1;
            break;
        }
    }

    if(ifound == 0)
    {
        printf("Invalid Book ID or book already returned!\n");
        return;
    }

    for(j = 0; j < countbook; j++)
    {
        if(book[j].book_id == bookid)
        {
            bookindex = j;
            break;
        }
    }

    if(bookindex == -1)
    {
        printf("Book record not found!\n");
        return;
    }

    printf("Enter return date: ");
    scanf("%d", &issue[i].return_date);

    printf("Enter return month: ");
    scanf("%d", &issue[i].return_month);

    printf("Enter return year: ");
    scanf("%d", &issue[i].return_year);

    printf("You have to pay Rs. %d as fine\n",
           checkfine(issue[i]));

    issue[i].status = 1;
    book[bookindex].available_qantity++;

    fp = fopen("issue.dat", "wb");

    if(fp == NULL)
    {
        printf("Issue file opening failed!\n");
        return;
    }

    if(fwrite(issue, sizeof(struct Issue), countissue, fp)
       != countissue)
    {
        printf("Issue file writing failed!\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    fp = fopen("book.dat", "wb");

    if(fp == NULL)
    {
        printf("Book file opening failed!\n");
        return;
    }

    if(fwrite(book, sizeof(struct Book), countbook, fp)
       != countbook)
    {
        printf("Book file writing failed!\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    printf("\nBook returned successfully!\n");
}


int checkfine(struct Issue p){
    int diff,issued,fine;
    issued  = calculatedays(p.issue_date,p.issue_month,p.issue_year,p.return_date,p.return_month,p.return_year);
    if(issued<7){
        return 0;
    }
    else{
        diff = issued-7;
        fine  = diff*10;
        return fine;
    }
}

int calculatedays(int day1, int month1, int year1,
                  int day2, int month2, int year2)
{
    struct tm date1 = {0};
    struct tm date2 = {0};

    date1.tm_mday = day1;
    date1.tm_mon = month1 - 1;
    date1.tm_year = year1 - 1900;

    date2.tm_mday = day2;
    date2.tm_mon = month2 - 1;
    date2.tm_year = year2 - 1900;

    time_t t1 = mktime(&date1);
    time_t t2 = mktime(&date2);

    return (int)(difftime(t2, t1) / 86400);
}


void checkissuedbook(void)
{
    int i, j, found = 0;

    printf("\n       ISSUED BOOK DETAILS\n");
    printf("--------------------------------\n");

    for(i = 0; i < countissue; i++)
    {
        if(issue[i].status == 0)
        {
            found = 1;

            printf("\nMember ID: %d\n", issue[i].member_id);

            for(j = 0; j < countmember; j++)
            {
                if(member[j].member_id == issue[i].member_id)
                {
                    printf("Member Name: %s\n",
                           member[j].member_name);
                    break;
                }
            }

            printf("Book ID: %d\n", issue[i].book_id);

            for(j = 0; j < countbook; j++)
            {
                if(book[j].book_id == issue[i].book_id)
                {
                    printf("Book Name: %s\n", book[j].bookname);
                    printf("Author: %s\n", book[j].author_name);
                    break;
                }
            }

            printf("Issue Date: %d-%d-%d\n",
                   issue[i].issue_date,
                   issue[i].issue_month,
                   issue[i].issue_year);

            printf("--------------------------------\n");
        }
    }

    if(found == 0)
    {
        printf("No books are currently issued!\n");
    }
}


void checkmemberdetails(void)
{
    int mid, i, j, found = 0;
    int issued = 0, returned = 0;

    printf("Enter member ID to check: ");
    scanf("%d", &mid);

    for(i = 0; i < countmember; i++)
    {
        if(member[i].member_id == mid)
        {
            found = 1;

            printf("\nMember Details\n");
            printf("----------------------\n");
            printf("Member ID: %d\n", member[i].member_id);
            printf("Member Name: %s\n", member[i].member_name);

            break;
        }
    }

    if(found == 0)
    {
        printf("Member not found!\n");
        return;
    }

    printf("\nCurrently Issued Books:\n");

    for(i = 0; i < countissue; i++)
    {
        if(issue[i].member_id == mid && issue[i].status == 0)
        {
            issued = 1;

            for(j = 0; j < countbook; j++)
            {
                if(book[j].book_id == issue[i].book_id)
                {
                    printf("\nBook ID: %d\n", book[j].book_id);
                    printf("Book Name: %s\n", book[j].bookname);
                    printf("Author: %s\n", book[j].author_name);
                    break;
                }
            }

            printf("Issue Date: %d-%d-%d\n",
                   issue[i].issue_date,
                   issue[i].issue_month,
                   issue[i].issue_year);
        }
    }

    if(issued == 0)
    {
        printf("No books currently issued by this member.\n");
    }

    printf("\nPreviously Returned Books:\n");

    for(i = 0; i < countissue; i++)
    {
        if(issue[i].member_id == mid && issue[i].status == 1)
        {
            returned = 1;

            for(j = 0; j < countbook; j++)
            {
                if(book[j].book_id == issue[i].book_id)
                {
                    printf("\nBook ID: %d\n", book[j].book_id);
                    printf("Book Name: %s\n", book[j].bookname);
                    break;
                }
            }

            printf("Issue Date: %d-%d-%d\n",
                   issue[i].issue_date,
                   issue[i].issue_month,
                   issue[i].issue_year);

            printf("Return Date: %d-%d-%d\n",
                   issue[i].return_date,
                   issue[i].return_month,
                   issue[i].return_year);
        }
    }

    if(returned == 0)
    {
        printf("No previous returned books.\n");
    }
}

void freelibrary(void)
{
    free(book);
    free(member);
    free(issue);
}
