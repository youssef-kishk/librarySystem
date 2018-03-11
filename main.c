#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Book.h"
#include "Member.h"
#include "Borrowed.h"
FILE* Books;
FILE* Members;
FILE* Borrowing;
book booksArray[100];
member membersArray[100];
borrowed borrowedArray[100];
int nBooks,nMembers,nBorrwing,i;
int main(){
    filesDataReading();
    int choice,ex=0;
    printf("->Welcome to Library system<-\n");
    printMostBorrwed();
    while(1){
    printf("\nPlease determine which process do you like to use:\nTo clear screen<0>");
    printf("\nFor Book Management<1>\nFor Member Management<2>\n");
    printf("For Borrow Management<3>\nAdministrative actions<4>\n");
    printf("Save changes<5>\nPrinting data<6>\nFor Exit<7>: ");
    scanf("%d",&choice);
    getchar();
    switch(choice){
        case 0:clr();break;
        case 1:bookOptions();break;
        case 2:memberOptions();break;
        case 3:borrowOptions();break;
        case 4:PrintOverdueBooks();break;
        case 5:save();break;
        case 6:printSpecificData(ex);break;
        case 7:
            printf("Do you want to save before exiting? <1> for yes <0> for no: ");
            scanf("%d",&ex);
            getchar();
            if(ex==1)
                save();
            printf("\n->Thank for using our library<-\n");
            return 0;
        }
    }
    return 0;
}
void filesDataReading(){
    nBooks=numberOfLinesOfBookFile(Books);
    readBookDataFromFile(nBooks,i,Books,booksArray);
    nMembers=numberOfLinesOfMemberFile(Members);
    readMembersDataFromFile(nMembers,i,Members,membersArray);
    nBorrwing=numberOfLinesOfBorrowFile(Borrowing);
    readBorrowDataFromFile(nBorrwing,i,Borrowing,borrowedArray);
}
void addNewBook(){
    book b;
    b=readBookData(b,i);
    booksArray[nBooks]=b;
    booksArray[nBooks].timesBorrwed=0;
    nBooks++;
    printf("Book is added\n");
}
void searchBook(){
    int x,check=0;
    char search[30];
    printf("\nTo search by book title type (1), by author name (2),by ISBN (3),by category(4),back(5): ");
    scanf("%d",&x);
    getchar();
    switch(x){
    case 1:
        printf("Type Book name: ");
        scanf ("%[^\n]%*c", search);
        toLowerLetter(search,i,strlen(search));
        for(i=0;i<nBooks;i++){
            toLowerLetter(booksArray[i].title,i,strlen(booksArray[i].title));
            if(strcmp(booksArray[i].title,search)==0||strstr(booksArray[i].title,search)){
                printf("Book (%s) is found\n",booksArray[i].title);
                check=1;
               // break;
            }
        }
            if(check==0)
                printf("Book (%s) is not found\n",search);
        break;
    case 2:
        printf("Type Book author name: ");
        scanf ("%[^\n]%*c", search);
        toLowerLetter(search,i,strlen(search));
        for(i=0;i<nBooks;i++){
            toLowerLetter(booksArray[i].author,i,strlen(booksArray[i].author));
            if(strcmp(booksArray[i].author,search)==0){
                printf("author (%s) has written (%s) which is available book\n",booksArray[i].author,booksArray[i].title);
                check=1;
            }
        }
            if(check==0)
                printf("author (%s) is not found\n",search);
        break;
    case 3:
        printf("Type Book ISBN: ");
        scanf ("%[^\n]%*c", search);
        for(i=0;i<nBooks;i++){
            if(strcmp(booksArray[i].ISBN,search)==0){
                printf("Book (%s) is found\n",booksArray[i].title);
                check=1;
                break;
            }
        }
        if(check==0)
            printf("Book if ISBN (%s) is not found\n",search);
        break;
    case 4:
        printf("Type Book Category: ");
        scanf ("%[^\n]%*c", search);
        toLowerLetter(search,i,strlen(search));
        for(i=0;i<nBooks;i++){
            toLowerLetter(booksArray[i].category,i,strlen(booksArray[i].category));
            if(strcmp(booksArray[i].category,search)==0){
                printf("Book (%s) is found in this category\n",booksArray[i].title);
                check=1;
            }
        }
        if(check==0)
            printf("No founded book in (%s) category\n",search);
        break;
    case 5:turnBack();break;

    }
}
void addNewCopy(){
    char isbn[30];
    char name[30];
    int copies,check=0;
    printf("Enter Book name and number of copies to be added: ");
    scanf ("%[^\n]%*c %d", name,&copies);
    toLowerLetter(name,i,strlen(name));
    for(i=0;i<nBooks;i++){
        toLowerLetter(booksArray[i].title,i,strlen(booksArray[i].title));
        if(strcmp(booksArray[i].title,name)==0){
            strcpy(isbn,booksArray[i].ISBN);
        }
    }
    getchar();
    if(copies<=0)
        printf("Invalid Input\n");
        for(i=0;i<nBooks;i++){
            if(strcmp(booksArray[i].ISBN,isbn)==0){
                booksArray[i].numOfCopies+=copies;
                printf("Copies added\n");
                check=1;
                break;
            }
        }
        if(check==0)
            printf("No book matches this name\n");
}
void deleteBook(){
    char isbn[30];
    printf("Enter Book ISBN: ");
    scanf ("%[^\n]%*c", isbn);
    int k = -1;
        for(i=0;i<nBooks;i++) {
            if(strcmp(booksArray[i].ISBN,isbn)==0)
                k=i;
        }
    if(k!=-1){
        for(i=k;i<nBooks-1;i++){
            booksArray[i] = booksArray[i+1];
        }
        printf("Book Deleted\n");
        nBooks--;
    }
    else
        printf("Book not found\n");
}
void addNewUser(){
    member m;
    m=readMemberData(m);
    membersArray[nMembers]=m;
    membersArray[nMembers].borrowedBooks=0;
    nMembers++;
    printf("User is added\n");

}
void borrowBook(){
    char title[30];
    int ID,check=0;
    printf("Enter Book name and your personal ID: ");
    scanf("%[^\n]%*c %d",title,&ID);
    toLowerLetter(title,i,strlen(title));
    getchar();
    check=borrowNewBook(ID,i,nMembers,membersArray);
    if(check==-1){
        printf("Wrong ID\n");
        return;
    }
    else if(check==2){
        printf("you have already borrowed 3 books\n");
        return;
    }
        //current date
        check=0;
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[20];
        strftime(s, sizeof(s), "%c", tm);
        char *ch=strtok(s," ");
        ch=strtok(s,"/");
    for(i=0;i<nBooks;i++){
            toLowerLetter(booksArray[i].title,i,strlen(booksArray[i].title));
            if(strcmp(booksArray[i].title,title)==0){
                if(booksArray[i].avilableCopies==0){
                    printf("No available copies\n");
                    membersArray[i].borrowedBooks--;
                    return;
                }
                booksArray[i].avilableCopies--;
                booksArray[i].timesBorrwed++;
                strcpy(borrowedArray[nBorrwing].ISBN,booksArray[i].ISBN);
                borrowedArray[nBorrwing].id=ID;
                borrowedArray[nBorrwing].dateBorrowed.month=atoi(ch);
                ch=strtok(NULL,"/");
                borrowedArray[nBorrwing].dateBorrowed.day=atoi(ch);
                ch=strtok(NULL,"\n");
                borrowedArray[nBorrwing].dateBorrowed.year=atoi(ch);
                borrowedArray[nBorrwing].dateDueToReturn.year=borrowedArray[nBorrwing].dateBorrowed.year;
                if(borrowedArray[nBorrwing].dateBorrowed.day<=26){
                    borrowedArray[nBorrwing].dateDueToReturn.day=borrowedArray[nBorrwing].dateBorrowed.day+5;
                    borrowedArray[nBorrwing].dateDueToReturn.month=borrowedArray[nBorrwing].dateBorrowed.month;
                }
                else{
                   borrowedArray[nBorrwing].dateDueToReturn.day=1;
                   borrowedArray[nBorrwing].dateDueToReturn.month=borrowedArray[nBorrwing].dateBorrowed.month+1;
                }
                check=1;
                break;
            }
        }
        if(check==1){
        printf("Book is Borrowed,please notice that you will return book by its name\n");
        nBorrwing++;
        fclose(Borrowing);
        }
        else
            printf("Invalid Book Name\n");

}
void returnBook(){
    char isbn[30];
    char name[30];
    int ID,check=0;
    printf("Enter Book name and your personal ID: ");
    scanf("%[^\n]%*c %d",name,&ID);
    getchar();
    toLowerLetter(name,i,strlen(name));
    for(i=0;i<nBooks;i++){
        toLowerLetter(booksArray[i].title,i,strlen(booksArray[i].title));
        if(strcmp(booksArray[i].title,name)==0){
            strcpy(isbn,booksArray[i].ISBN);
            booksArray[i].avilableCopies++;
        }
    }
    for(i=0;i<nBorrwing;i++){
            if((strcmp(borrowedArray[i].ISBN,isbn)==0)&&borrowedArray[i].id==ID&& borrowedArray[i].dateReturned.month==0){
                time_t t = time(NULL);
                struct tm *tm = localtime(&t);
                char s[20];
                strftime(s, sizeof(s), "%c", tm);
                char *ch=strtok(s," ");
                ch=strtok(s,"/");
                borrowedArray[i].dateReturned.month=atoi(ch);
                ch=strtok(NULL,"/");
                borrowedArray[i].dateReturned.day=atoi(ch);
                ch=strtok(NULL,"\n");
                borrowedArray[i].dateReturned.year=atoi(ch);
                check=1;
                break;
            }
    }
    if(check==1){
        printf("Book returned\n");
        returnMemberBorrwedBook(ID,i,nMembers,membersArray);
    }
    else
        printf("Invalid name or id\n");
}
void removeMember(){
    int ID,k=-1;
    printf("\nEnter you ID: ");
    scanf("%d",&ID);
    getchar();
    for(i=0;i<nMembers;i++){
        if(membersArray[i].id==ID){
                k=i;
                break;
        }
        k=-2;
    }
        if(membersArray[k].borrowedBooks!=0)
            printf("Sorry you must return borrowed books first\n");
        else if(k==-2)
            printf("Invalid ID\n");
        else if(k!=-1){
            for(i=k;i<nMembers-1;i++){
            membersArray[i] = membersArray[i+1];
            }
            printf("Member Deleted\n");
            nMembers--;
        }


}
void save(){
    Books=fopen("files/Books.txt","w");
    for(i=0;i<nBooks;i++){
    fprintf(Books,"%s,%s,%s,%s,%d/%d/%d,%d,%d,%s,%d",booksArray[i].title,booksArray[i].author,booksArray[i].publisher,booksArray[i].ISBN,
    booksArray[i].dateOfPublication.day,booksArray[i].dateOfPublication.month,booksArray[i].dateOfPublication.year,
    booksArray[i].numOfCopies,booksArray[i].avilableCopies,booksArray[i].category,booksArray[i].timesBorrwed);
    if(i<nBooks-1)
        fprintf(Books,"\n");
    }
    Members=fopen("files/Members.txt","w");
    for(i=0;i<nMembers;i++){
    fprintf(Members,"%s,%s,%d,%d,%s,%s,%d,%d,%s,%d",membersArray[i].fullName.first,membersArray[i].fullName.last,
    membersArray[i].id,membersArray[i].home.building,membersArray[i].home.street,membersArray[i].home.city,
    membersArray[i].phoneNum,membersArray[i].age,membersArray[i].email,membersArray[i].borrowedBooks);
    if(i<nMembers-1)
        fprintf(Members,"\n");
    }
    Borrowing=fopen("files/Borrowing.txt","w");
    for(i=0;i<nBorrwing;i++){
fprintf(Borrowing,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",borrowedArray[i].ISBN,borrowedArray[i].id,
borrowedArray[i].dateBorrowed.day,borrowedArray[i].dateBorrowed.month,borrowedArray[i].dateBorrowed.year,
borrowedArray[i].dateDueToReturn.day,borrowedArray[i].dateDueToReturn.month, borrowedArray[i].dateDueToReturn.year,
borrowedArray[i].dateReturned.day,borrowedArray[i].dateReturned.month,borrowedArray[i].dateReturned.year);
    if(i<nBorrwing-1)
        fprintf(Borrowing,"\n");
    }
    printf("Saved successfully\n");
    fclose(Books);
    fclose(Members);
    fclose(Borrowing);

}
void printSpecificData(int ex){
    printf("\nDetermine which data you like to view:\n1)books\n2)members\n3)borrowing\n4)back: ");
            scanf("%d",&ex);
            switch(ex){
                case 1:showAllBooks(nBooks,i,booksArray);break;
                case 2:showAllMembers(nMembers,i,membersArray);break;
                case 3:showAllBorrowings(nBorrwing,i,borrowedArray);
                case 4:turnBack();
            }
}
void toLowerLetter(char* c,int i,int size){
    for(i = 0; i<strlen(c); i++){
        c[i] = tolower(c[i]);
        }
}
void PrintOverdueBooks(){
    int j,check,c=0;
    time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[20];
        strftime(s, sizeof(s), "%c", tm);
        char *ch=strtok(s," ");
        ch=strtok(s,"/");
        char* day =strtok(NULL,"/");
        printf("\nList of OverdueBooks:\n");
        for(i=0;i<nBorrwing;i++){
                check=0;
            if(borrowedArray[i].dateReturned.day==0&&borrowedArray[i].dateDueToReturn.month<=atoi(ch)){
                if(borrowedArray[i].dateDueToReturn.day<atoi(day)){
                    for(j=0;j<nBooks;j++){
                        if(strcmp(borrowedArray[i].ISBN,booksArray[j].ISBN)==0){
                            c=1;
                            printf("<%s> borrowed by user of ID <%d>\n",booksArray[j].title,borrowedArray[i].id);
                            check=1;
                        }
                        if(check==1)
                            break;
                    }
                }
            }
        }
        if(c==0)
                printf("<No Books Found>\n");
}
void printMostBorrwed(){
    int mostPop[nBooks];
    for(i=0;i<nBooks;i++)
            mostPop[i]=booksArray[i].timesBorrwed;
    int pass;
    int temp;
    //bubble sort
    for(pass = 1; pass < nBooks; pass++)
    {
        for (i = 0; i < nBooks - 1; i++)
        {
            if (mostPop[i] < mostPop[i + 1])
                {
            temp = mostPop[i];
            mostPop[i] = mostPop[i + 1];
            mostPop[i + 1] = temp;
            }
        }
    }
    printf("The most favorite books in the library are:\n");
    int count=0;
    for(pass=0;pass<nBooks;pass++){
        if(count==5)
            break;
        for(i=0;i<nBooks;i++){
            if(mostPop[pass]==booksArray[i].timesBorrwed&&mostPop[pass]!=mostPop[pass-1]){
                printf("%d)%s\n",count+1,booksArray[i].title);
                count++;
                break;
            }
        }

    }
}
void clr(){
    system("cls");
}
void turnBack(){}

