typedef struct {
    char first[30],last[30];
}name;
typedef struct{
    int building;
    char street[30],city[30];

}address;
typedef struct{
    name fullName;
    int id;
    address home;
    int phoneNum;
    int age;
    char email[30];
    int borrowedBooks;
}member;
member readMemberData(member m){
    printf("\nEnter all user data\n");
    printf("First Name: ");
    scanf ("%s", m.fullName.first);
    printf("Last Name: ");
    scanf ("%s", m.fullName.last);
    printf("id: ");
    scanf ("%d",&m.id);
    printf("Home Building number: ");
    scanf ("%d",&m.home.building);
    printf("Home street name: ");
    getchar();
    scanf("%[^\n]%*c",m.home.street);
    printf("city name: ");
    scanf("%[^\n]%*c",m.home.city);
    printf("phone number: ");
    scanf("%d",&m.phoneNum);
    printf("age: ");
    scanf("%d",&m.age);
    printf("Email: ");
    scanf("%s",m.email);
    getchar();
    return m;
}
int numberOfLinesOfMemberFile(FILE* Members){
    Members = fopen("files/Members.txt","r");
    int x=1;
    char numOfLines[100];
    if(fgets(numOfLines,100,Members)==NULL)
        return 0;
    while(!feof(Members))
    {
        fgets(numOfLines,100,Members);
                x++;
    }
     fclose(Members);
    return x;
}
void readMembersDataFromFile(int nMembers,int i,FILE* Members,member membersArray[]){
    Members = fopen("files/Members.txt","r");
    char *ch;
    char input[100];
    for(i=0;i<nMembers;i++){
        fgets(input,100,Members);
        ch=strtok(input,",");
        strcpy(membersArray[i].fullName.first,ch);
        ch=strtok(NULL,",");
        strcpy(membersArray[i].fullName.last,ch);
        ch=strtok(NULL,",");
        membersArray[i].id=atoi(ch);
        ch=strtok(NULL,",");
        membersArray[i].home.building=atoi(ch);
        ch=strtok(NULL,",");
        strcpy(membersArray[i].home.street,ch);
        ch=strtok(NULL,",");
        strcpy(membersArray[i].home.city,ch);
        ch=strtok(NULL,",");
        membersArray[i].phoneNum=atoi(ch);
        ch=strtok(NULL,",");
        membersArray[i].age=atoi(ch);
        ch=strtok(NULL,",");
        strcpy(membersArray[i].email,ch);
        ch=strtok(NULL,"\n");
        membersArray[i].borrowedBooks=atoi(ch);
    }
    fclose(Members);
}
void memberOptions(){
    int process;
    printf("\n1)Add a new user:\n2)Remove existing user\n3)back: ");
    scanf("%d",&process);
    getchar();
    switch(process){
        case 1:addNewUser();break;
        case 2:removeMember();break;
        case 3:turnBack();break;
    }
}
int borrowNewBook(int ID,int i,int nMembers,member membersArray[]){
    int check=0;
    for(i=0;i<nMembers;i++){
        if(membersArray[i].id==ID){
            if(membersArray[i].borrowedBooks<3){
                membersArray[i].borrowedBooks++;
                check=1;
                break;
            }
            else {
            check=2;
            break;
            }
        }
    }
    if(check==1)
        return 1;
    else if(check==2)
        return 2;
    else
        return -1;
}
void returnMemberBorrwedBook(int ID,int i,int nMembers,member membersArray[]){
    for(i=0;i<nMembers;i++){
        if(membersArray[i].id==ID){
            membersArray[i].borrowedBooks--;
            break;
        }
    }
}
void showAllMembers(int nMembers,int i,member membersArray[]){
    printf("\nMembers at the Library are:\n");
    for(i=0;i<nMembers;i++)
        printf("%s %s\t%d\n",membersArray[i].fullName.first,membersArray[i].fullName.last,membersArray[i].id);

}

