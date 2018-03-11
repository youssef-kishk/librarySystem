typedef struct{
    int day, month, year;
}dateBorrow;
typedef struct{
    char ISBN[30];
    int id;  //user
    dateBorrow dateBorrowed;
    dateBorrow dateDueToReturn;
    dateBorrow dateReturned;
}borrowed;
int numberOfLinesOfBorrowFile(FILE* Borrowing){
    Borrowing = fopen("files/Borrowing.txt","r");
    int x=1;
    char numOfLines[100];
    if(fgets(numOfLines,100,Borrowing)==NULL)
        return 0;
    while(!feof(Borrowing))
    {
        fgets(numOfLines,100,Borrowing);
                x++;
    }
     fclose(Borrowing);
    return x;
}
void readBorrowDataFromFile(int nBorrwing,int i,FILE* Borrowing,borrowed borrowedArray[]){
    Borrowing = fopen("files/Borrowing.txt","r");
    char *ch;
    char input[100];
    for(i=0;i<nBorrwing;i++){
        fgets(input,100,Borrowing);
        ch=strtok(input,",");
        strcpy(borrowedArray[i].ISBN,ch);
        ch=strtok(NULL,",");
        borrowedArray[i].id=atoi(ch);
        ch=strtok(NULL,"/");
        borrowedArray[i].dateBorrowed.day=atoi(ch);
        ch=strtok(NULL,"/");
        borrowedArray[i].dateBorrowed.month=atoi(ch);
        ch=strtok(NULL,",");
        borrowedArray[i].dateBorrowed.year=atoi(ch);
        ch=strtok(NULL,"/");
        borrowedArray[i].dateDueToReturn.day=atoi(ch);
        ch=strtok(NULL,"/");
        borrowedArray[i].dateDueToReturn.month=atoi(ch);
        ch=strtok(NULL,",");
        borrowedArray[i].dateDueToReturn.year=atoi(ch);
        ch=strtok(NULL,"/");
        if(ch!=NULL){
            borrowedArray[i].dateReturned.day=atoi(ch);
            ch=strtok(NULL,"/");
            borrowedArray[i].dateReturned.month=atoi(ch);
            ch=strtok(NULL,"\n");
            borrowedArray[i].dateReturned.year=atoi(ch);
        }
    }
    fclose(Borrowing);
}
void borrowOptions(){
    int process;
    printf("\n1)Borrow New Book:\n2)Return Borrowed Book:\n3)back: ");
    scanf("%d",&process);
    getchar();
    switch(process){
        case 1:borrowBook();break;
        case 2:returnBook();break;
        case 3:turnBack();break;
    }
}
void showAllBorrowings(int nBorrwing,int i,borrowed borrowedArray[]){
    printf("\nBorrowings at the Library are:\n");
    printf("<Book ISBN>\t<ID>\n");
    for(i=0;i<nBorrwing;i++)
        printf("%s\t%d\n",borrowedArray[i].ISBN,borrowedArray[i].id);
}
