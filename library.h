#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Book{
    int book_id;
    char bookname[50];
    char author_name[80];
    int total_quantity;
    int available_qantity;
    char subject[50];
};

struct Member{
    int member_id;
    char member_name[50];
};

struct Issue{
    int member_id;
    int book_id;
    int issue_date;
    int issue_month;
    int issue_year;
    int return_date;
    int return_month;
    int return_year;
    int status;
};


void displaybook(void);
void issuebook(void);
void returnbook(void);
int checkfine(struct Issue);
int calculatedays(int,int,int,int,int,int);
void addbook(void);
void deletebook(void);
void updatebook(void);
void issuebook(void);
void checkissuedbook(void);
void checkmemberdetails(void);
void loadbook(void);
void loadmember(void);
void loadissue(void);
void freelibrary(void);

#endif

