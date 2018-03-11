typedef struct {
    int day,month,year;
}dateBook;
typedef struct{
    char title[30];
    char author[30];
    char publisher[30];
    char ISBN[30];
    dateBook dateOfPublication;
    int numOfCopies;
    int avilableCopies;
    char category[30];
    int timesBorrwed;
}book;
book readBookData(book b,int i){
    printf("\nEnter all Book data\n");
    printf("title: ");
    scanf ("%[^\n]%*c", b.title);
    printf("author: ");
    scanf ("%[^\n]%*c", b.author);
    printf("publisher: ");
    scanf ("%[^\n]%*c", b.publisher);
    printf("ISBN: ");
    scanf ("%[^\n]%*c", b.ISBN);
    printf("day of publication: ");
    scanf("%d",&b.dateOfPublication.day);
    printf("month of publication: ");
    scanf("%d",&b.dateOfPublication.month);
    printf("year of publication: ");
    scanf("%d",&b.dateOfPublication.year);
    printf("number of copies: ");
    scanf("%d",&b.numOfCopies);
    printf("available copies: ");
    scanf("%d",&b.avilableCopies);
    getchar();
    printf("category: ");
    scanf ("%[^\n]%*c", b.category);
    return b;
}
int numberOfLinesOfBookFile(FILE* Books){
    Books = fopen("files/Books.txt","r");
    int x=1;
    char numOfLines[100];
    if(fgets(numOfLines,100,Books)==NULL)
        return 0;
    while(!feof(Books))
    {
        fgets(numOfLines,100,Books);
                x++;
    }
     fclose(Books);
    return x;
}
void readBookDataFromFile(int nBooks,int i,FILE* Books,book booksArray[]){
    Books = fopen("files/Books.txt","r");
    char *ch;
    char input[100];
    for(i=0;i<nBooks;i++){
        fgets(input,100,Books);
        ch=strtok(input,",");
        strcpy(booksArray[i].title,ch);
        ch=strtok(NULL,",");
        strcpy(booksArray[i].author,ch);
        ch=strtok(NULL,",");
        strcpy(booksArray[i].publisher,ch);
        ch=strtok(NULL,",");
        strcpy(booksArray[i].ISBN,ch);
        ch=strtok(NULL,"/");
        booksArray[i].dateOfPublication.day=atoi(ch);
        ch=strtok(NULL,"/");
        booksArray[i].dateOfPublication.month=atoi(ch);
        ch=strtok(NULL,",");
        booksArray[i].dateOfPublication.year=atoi(ch);
        ch=strtok(NULL,",");
        booksArray[i].numOfCopies=atoi(ch);
        ch=strtok(NULL,",");
        booksArray[i].avilableCopies=atoi(ch);
        ch=strtok(NULL,",");
        strcpy(booksArray[i].category,ch);
        ch=strtok(NULL,"\n");
        booksArray[i].timesBorrwed=atoi(ch);
    }
    fclose(Books);
}
void bookOptions(){
    int process;
    printf("\n1)Add a new book\n2)search for a book\n3)add a book copy\n4)delete a book\n5)back: ");
    scanf("%d",&process);
    getchar();
    switch(process){
        case 1:addNewBook();break;
        case 2:searchBook();break;
        case 3:addNewCopy();break;
        case 4:deleteBook();break;
        case 5:turnBack();break;
    }
}
void showAllBooks(int nBooks,int i,book booksArray[]){
    printf("\nAvailable Books at the Library are:\n");
    for(i=0;i<nBooks;i++)
        printf("%s\n",booksArray[i].title);
}
