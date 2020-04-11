#include <windows.h>
#include<stdio.h>
#include<conio.h>                   //contains delay(),getch(),gotoxy(),etc.
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>
#define SIZE 0x100
//'note that every thing is ok but some validations in input i didnt finish so dont put wrong entries until it all handled'
//'i am thinking also of adding back option using backspace also not implemented yet'
//'enjoyyyyyyy'
//list of function prototype
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void addnewcopy(void);
void addmembers(void);
void borrowbooks(void);
void returnbook(void);
void removemeber(void);
void read_books_file(void);
void read_members_file(void);
void read_borrows_file(void);
void save_books_file(void);
void save_members_file(void);
void save_borrows_file(void);
void overdue(void);
void mostpopular(void);

COORD coord = {0, 0}; // sets coordinates to 0,0
//COORD max_buffer_size = GetLargestConsoleWindowSize(hOut);
COORD max_res,cursor_size;
void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void t(void)
{
time_t t = time(NULL);
struct tm tm = *localtime(&t);

    printf("Date: %d/%d/%d \n\t\t\t\t\t\t     Time: %.2d:%.2d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}
int findpart(char s1[50],char s2[50])
{

    int count1 = 0, count2 = 0, i, j, flag;

    while (s1[count1]!= NULL)
        count1++;
    while (s2[count2] != NULL)
        count2++;
    for (i = 0; i <= count1 - count2; i++)
    {
        for (j = i; j < i + count2; j++)
        {
            flag = 1;
            if (s1[j] != s2[j - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    if (flag == 1)
        return 1;
    else
        return 0;

}

typedef struct {
    int day, month, year;
} Date;
typedef struct
{
    char isbn[20];
    char title[50];
    char Author[20];
    char publisher[20];
    char category[50];
    int copies; //book copies
    int bcount; //book borrowing counter
    Date pubdate;
}book;
typedef struct
{
    int id;
    char name[50];
    char memaddress[200];
    int age;
    char phonenum[20];
    char email[50];
    int mbcount;  //member books borrowing counter
}member;
typedef struct
{
    char isbn[20];
    int id;
   Date dborrow;
   Date dduereturn;
   Date dreturn;
}borrow;
//function to compare dates
int compare_dates (Date d1,Date d2)
{
    if (d1.year < d2.year)
       return -1;

    else if (d1.year > d2.year)
       return 1;

    if (d1.year == d2.year)
    {
         if (d1.month<d2.month)
              return -1;
         else if (d1.month>d2.month)
              return 1;
         else if (d1.day<d2.day)
              return -1;
         else if(d1.day>d2.day)
              return 1;
         else
              return 0;
    }
}
//list of global files that can be acceed form anywhere in program
FILE *fp;

//list of global variable and arrays
int s;
int n1,n2,n3;
book books[100];
member m[100];
borrow br[100];

int main()

{
   read_books_file();
   read_members_file();
   read_borrows_file();
    mainmenu();
    return 0;

}
void read_books_file(void)
{
    int i;
 fp=fopen("books.txt","rt");
 if (fp!=NULL)
        {fscanf(fp,"%d",&n1);
    fscanf(fp,"\n");
    for(i=0;i<(n1);i++)
    {
fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d/%d/%d,%d,%[^,],%d",books[i].title,books[i].Author,books[i].publisher,books[i].isbn,&books[i].pubdate.day,&books[i].pubdate.month,&books[i].pubdate.year,&books[i].copies,books[i].category,&books[i].bcount);
fscanf(fp,"\n");
 }fclose(fp);}
else
printf("error opening file books");
}
void read_members_file(void)
{
    int i;
    fflush(stdin);
     fp=fopen("members.txt","rt");
 if (fp!=NULL)
    {fscanf(fp,"%d",&n2);
    fscanf(fp,"\n");
    for(i=0;i<n2;i++)
    {
    fscanf(fp,"%[^,],%d,%[^,],%[^,],%d ,%[^,],%d",m[i].name,&m[i].id,m[i].memaddress,m[i].phonenum,&m[i].age,m[i].email,&m[i].mbcount);
    fscanf(fp,"\n");
    }
    fclose(fp);}
 else
   printf("File not found");

}
void read_borrows_file(void)
{
     int i;
     fp=fopen("borrows.txt","rt");
 if (fp==NULL)
    printf("error opening file borrows.txt");
 else
    fscanf(fp,"%d",&n3);
    fscanf(fp,"\n");
    for(i=0;i<(n3);i++)
    {
fscanf(fp,"%[^,],%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",&br[i].isbn,&br[i].id,&br[i].dborrow.day,&br[i].dborrow.month,&br[i].dborrow.year,&br[i].dduereturn.day,&br[i].dduereturn.month,&br[i].dduereturn.year,&br[i].dreturn.day,&br[i].dreturn.month,&br[i].dreturn.year);
  fscanf(fp,"%\n");
    }
    fclose(fp);
}
void mainmenu()
{
    system("cls");
    //textbackground
    gotoxy(48,1);
    printf(".:!|  MAIN MENU  |!:.");
    gotoxy(35,5);
    gotoxy(45,3);
    printf("<<     a. Add Books      >>");
    gotoxy(45,5);
    printf("<<    b. Search books    >>");
    gotoxy(45,7);
    printf("<<    c. Delete Books    >>");
    gotoxy(45,9);
    printf("<<   d. Add New Copies   >>");
    gotoxy(45,11);
    printf("<<   e. Add New Member   >>");
    gotoxy(45,13);
    printf("<<   f. Remove A Member  >>");
    gotoxy(45,15);
    printf("<<    g. Borrow Books    >>");
    gotoxy(45,17);
    printf("<<    h. Return a Book   >>");
    gotoxy(45,19);
    printf("<<    i. Overdue books   >>");
    gotoxy(45,21);
    printf("<< j. Most popular books >>");
    gotoxy(45,23);
    printf("<<         k. Exit       >>");
    gotoxy(45,25);
    printf("<<    l. Save and Exit   >>");
    gotoxy(35,26);
    printf("==============================================");
    gotoxy(50,27);
    t();
    gotoxy(50,29);
    printf("Enter your choice : ");
    switch(getch())
    {
    case 'a':
        addbooks();
        break;
    case 'b':
        searchbooks();
        break;
    case 'c':
        deletebooks();
        break;
    case 'd':
        addnewcopy();
        break;
    case 'e':
        addmembers();
        break;
    case 'f':
        removemeber();
        break;
    case 'g':
        borrowbooks();
        break;
    case 'h':
        returnbook();
        break;
        case 'j':
        system("cls");
        mostpopular();
        break;
        case 'i':
        system("cls");
        overdue();
        break;
    case 'k':
    {
        system("cls");
        gotoxy(40,15);
        printf("<<<<<  Thanks for using the Program :)  >>>>>");
        gotoxy(40,27);
        exit(0);
    }
    case 'l':
        system("cls");
        save_books_file();
        save_members_file();
        save_borrows_file();
        gotoxy(47,9);
            printf("=====  SAVING SUCCESSFUL !!  =====");
            gotoxy(52,10);
            printf("------------------------");
        gotoxy(42,15);
        printf("<<<<<  Thanks for using the Program :)  >>>>>");
        gotoxy(0,27);
        exit(0);
    default:
    {
        system ("cls");
        gotoxy(30,9);
        printf("\a<<<<<  Please enter a letter from the mentioned :(  >>>>>");
        gotoxy(37,15);
        printf("Press Any Key To Return To The Main Menu :D");
        if(getch())
            mainmenu();
    }

    }
}
void addbooks(void)    //a)funtion that add books
{
    system("cls");
   gotoxy (45,1);
    printf("<<      Add Books      >>");
     book b1;
     gotoxy(20,5);
    printf("Book ISBN: ");
    gets(b1.isbn);
     gotoxy(20,7);
    printf("Book title: ");
    gets(b1.title);
     gotoxy(20,9);
    printf("Book author name: ");
    gets(b1.Author);
     gotoxy(20,11);
    printf("Book copies: ");
    scanf("%d",&b1.copies);
     gotoxy(20,13);
    printf("Book published in : ");
    scanf("%d/%d/%d,",&b1.pubdate.day,&b1.pubdate.month,&b1.pubdate.year);
    gotoxy(20,15);
     printf("Book category : ");
    scanf("%s",b1.category);
    gotoxy(20,17);
    printf("book publisher name : ");
    scanf("%s",b1.publisher);
    fflush(stdin);
    b1.bcount=0;
    books[n1] = b1;
      (n1)++;
      system("cls");
      gotoxy(43,9);
      printf("====  ADDING SUCCESSFUL!!  ====");
        gotoxy(43,12);
        printf("-------------------------------");
     gotoxy(41,15);
     printf("<<<<<  Add another book?(Y/N)  >>>>>");
        if(getch()=='y')
        {
            getchar();
       addbooks();
        }
        else
        mainmenu();

}
void searchbooks(void) //b)
{
      system("cls");
    gotoxy(45,1);
    printf("<<  Search Books  >>");
    gotoxy(20,10);
    printf(":::| a. Search By ISBN");
    gotoxy(20,12);
    printf(":::| b. Search By title");
    gotoxy(20,14);
    printf(":::| c. Search By Category");
    gotoxy(35,25);
    printf("Press Any OTHER Key To Return to Main menu");
    gotoxy(20,17);
    printf("Enter Your Choice");
     switch(getch())
    {
      case 'a':
    {

         system("cls");
           gotoxy(48,1);
        printf("<< Search Books By Isbn >>");
   int i,x,k=-1;
    char s[20];
    getchar();
    gotoxy(20,10);
        printf("Enter book ISBN to search: ");
    gets(s);
    for(i=0;i<(n1);i++)
    {
        x=strcmp((s),books[i].isbn);
        if (x==0)
        {
            k=i;
            break;
        }
    }
    if(k==-1)
    {
             gotoxy(40,12);
            printf("<<<<< Book is not available !! >>>>>");
    }
    else
    {
       system("cls");
            gotoxy(20,7);
            printf("The Book is available");
            gotoxy(20,8);
            printf("||||||||||||||");
            printf("||||||||||||||");
            gotoxy(20,9);
            printf("| ISBN:%s",books[i].isbn);
            gotoxy(47,9);
            printf("|");
            gotoxy(20,10);
            printf("| Title:%s",books[i].title);
            gotoxy(47,10);
            printf("|");
            gotoxy(20,11);
            printf("| Author:%s ",books[i].Author);
            gotoxy(47,11);
            printf("|");
            gotoxy(20,12);
            printf("| Qantity:%d ",books[i].copies);
            gotoxy(47,12);
            printf("|");
            gotoxy(20,13);
            printf("| Pub date:%d/%d/%d",books[i].pubdate.day,books[i].pubdate.month,books[i].pubdate.year);
            gotoxy(47,13);
            printf("|");
            gotoxy(20,14);
            printf("||||||||||||||");
            printf("||||||||||||||");
    }
    gotoxy(20,20);
    printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        mainmenu();
        break;
    }
  case 'b':
    {
      char s[50];
      int i;
        system("cls");
         system("cls");
        gotoxy(46,1);
        printf("<<  Search Books By Title or part of Title  >>");
        gotoxy(20,5);
        printf("Enter Book title: ");
        fflush(stdin);
        gets(s);
        int d=0;
        for(i=0;i<n1;i++)
        {
         if(findpart(books[i].title,(s))==1) //checks whether name is equal to s or not
        {
            printf(" %d)- ISBN: %s Title: %s \n",i,books[i].isbn,books[i].title);

            d++;
        }
      }
        if(d==0)
        {
            system("cls");
            gotoxy(47,8);
            printf("|||||||||||||||||||");
            gotoxy(47,10);
            printf("|||||||||||||||||||");
            gotoxy(47,9);
            printf("\a| No Record Found |");
        }
        gotoxy(20,17);
        printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        mainmenu();
        break;
    }
     case 'c':
    {
      char s[50];
      int i;
        system("cls");
         gotoxy(46,1);
        printf("<<  Search Books By Category  >>");
        gotoxy(20,5);
        printf("Enter Book Category: ");
        fflush(stdin);
        gets(s);
        int d=0;
        for(i=0;i<n1;i++)
        {
         if(findpart(books[i].category,(s))==1) //checks whether name is equal to s or not
        {
            printf(" \n%d)- ISBN: %s Title: %s \n",i,books[i].isbn,books[i].title);

            d++;
        }
      }
        if(d==0)
        {
         system("cls");
            gotoxy(47,8);
            printf("|||||||||||||||||||");
            gotoxy(47,10);
            printf("|||||||||||||||||||");
            gotoxy(47,9);
            printf("\a| No Record Found |");
        }
        gotoxy(20,17);
        printf("Try another search?(Y/N)");
        if(getch()=='y')
        searchbooks();
        else
        mainmenu();
        break;
    }
    default :
    getch();
    mainmenu();
    }

}
void deletebooks(void) //c)
{
    system("cls");
     gotoxy(45,1);
    printf("<<<< Delete Books >>>>");
    int i,j,x,k=-1;
    char s[20];
    getchar();
     gotoxy(20,5);
    printf("Enter book isbn to delete :");
    gets(s);
    for(i=0;i<(n1);i++)
    {
        x=strcmp((s),books[i].isbn);
        if (x==0)
        {
            k=i;
            break;
        }
    }
    if(k==-1)
    {
         gotoxy(20,7);
        printf("Book is not available");
    }
    else
    {

    for(j=k;j<(n1-1);j++)
    {
        books[j]=books[j+1];
    }
    n1--;
      gotoxy(20,7);
    printf("Deleted");
    }
     gotoxy(20,9);
    printf("Delete another book?(Y/N)");
        if(getch()=='y')
       deletebooks();
        else
        mainmenu();
}
void addnewcopy(void) //d)
{
    system("cls");
          gotoxy(45,1);
        printf("<< Add a copy of Book >>");
   int c,i,x,k=-1;
    char s[20];
    getchar();
     gotoxy(21,3);
    printf("Enter book isbn to add new copy = ");
    gets(s);
    for(i=0;i<(n1);i++)
    {
        x=strcmp((s),books[i].isbn);
        if (x==0)
        {
            k=i;
            break;
        }
    }
    if(k==-1)
    {
         gotoxy(21,5);
        printf("<< book is not available !! >>");
    }
    else
    {
        gotoxy(21,5);
        printf("This book is available :)");
        gotoxy(21,7);
        printf("please enter number of copies you want to add = ");
        scanf("%d",&c);
        books[k].copies=(books[k].copies)+c;
    }
    gotoxy(21,9);
     printf("<< Add another copies?(Y/N) >>");
        if(getch()=='y')
       addnewcopy();
        else
        mainmenu();
}
void addmembers(void) //e)
{
     system("cls");
     gotoxy(45,1);
    printf("<<<< Add Members >>>>");
   member b2;
     gotoxy(10,2);
    printf("Member name = ");
    gets(b2.name);
     gotoxy(10,4);
    printf("Member age = ");
    scanf("%d",&b2.age);
     gotoxy(10,6);
    printf("Member phonenumber = ");
    scanf("%s",b2.phonenum);
     gotoxy(10,8);
    printf("Member email =");
    fflush(stdin);
    gets(b2.email);
    gotoxy(10,10);
    printf("Member address (buildingnum-street-city)");
    gets(b2.memaddress);
     gotoxy(10,12);
     (b2.id) = 1000 + n2;
    printf("the id of this member is set to be %d  ",b2.id);
    b2.mbcount=0;
     m[n2] = b2;
      (n2)++;
       gotoxy(10,14);
     printf("<< add another member?(Y/N) >>");
        if(getch()=='y')
        {
            fflush(stdin);
      addmembers();
        }
        else
        mainmenu();

}
void removemeber(void)//f)
{
system("cls");
gotoxy(45,1);
printf("<< Member removing section >>");
int i,id,flag=0,j,k;
gotoxy(20,5);
printf("enter id of member you want to remove :");
fflush(stdin);
scanf("%d",&id);
for(i=0;i<n2;i++)
{
if(m[i].id==id && m[i].mbcount==0)
{
 flag=1;
 k=i;
 break;
}
}
if(flag==0)
{
    gotoxy(20,7);
    printf("Error in Entry Can't Remove Member ( member may be didn't return borrowed book)!");
}
else
{
gotoxy(20,7);
  printf("checking if he has books that he didnt return");
  gotoxy(20,9);
  printf("Removed!");
  fflush(stdin);
  getchar();
    for(j=k;j<(n2-1);j++)
  {
      m[j] = m[j+1];
  }

  (n2)--;
}
  gotoxy(20,12);
  printf("remove another member?(Y/N)");
        if(getch()=='y')
        {
            getchar();
       removemeber();
        }
        else
        mainmenu();
}
void borrowbooks(void)//g)
{
    system("cls");
    gotoxy(45,1);
    printf("<< borrowing a book >>");
    int i,j,flag=0,flag2=0,flag3=0;
    time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   gotoxy(20,5);
    printf("enter id (Note : you have to be a member) = ");
    fflush(stdin);
   scanf("%d",&br[n3].id);
    for(i=0;i<n2;i++)
    {
        if(m[i].id==br[n3].id && m[i].mbcount<=3)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        gotoxy(20,7);
        printf("member cant borrow!");
        fflush(stdin);
         getchar();
        mainmenu();
    }
    else
        {gotoxy(20,7);
    printf("Borrower Name = %s enter isbn of book : ",m[i].name);
    fflush(stdin);
    scanf("%s",br[n3].isbn);
    }
    for(j=0;j<(n1);j++)
    {
        if(strcmp(books[j].isbn,br[n3].isbn)==0 && books[j].copies!=0)
            flag3=1;
            break;
    }
    if(flag3==0)
    {
        gotoxy(20,11);
        printf("book is not found or No Copies");
    }
    else
    {
        gotoxy(20,9);
    br[n3].dborrow.day=tm.tm_mday; br[n3].dborrow.month=(tm.tm_mon + 1); br[n3].dborrow.year=(tm.tm_year + 1900);
    printf("the borrowing date = ");
    gotoxy(22,11);
    printf("%d/%d/%d\n",br[n3].dborrow.day,br[n3].dborrow.month,br[n3].dborrow.year);
    while(flag2==0)
    {
    gotoxy(20,13);
    printf("enter the date due to return = ");
    scanf("%d/%d/%d",&br[n3].dduereturn.day,&br[n3].dduereturn.month,&br[n3].dduereturn.year);
    if(compare_dates(br[n3].dduereturn,br[n3].dborrow)==-1 )
    {
    gotoxy(20,15);
    printf("wrong entry please delete and re-enter again");
    }
    else
        flag2=1;
    }
    br[n3].dreturn.day==NULL; br[n3].dreturn.month==NULL; br[n3].dreturn.year==NULL;
    gotoxy(20,15);
     printf("Done!");
     n3++;
    m[i].mbcount++;
    books[j].copies--;
    books[j].bcount++;
    }

    gotoxy(20,17);
     printf("Borrow another book?(Y/N)");
        if(getch()=='y')
        {
            getchar();
       borrowbooks();
        }
        else
        mainmenu();

}
void returnbook(void) //h)
  {
    system("cls");
    gotoxy(45,1);
    printf("<< Return a book >>");
    char s[20];
    int i,j,z,flag=0;
    gotoxy(20,5);
    printf("enter book isbn you want to return = ");
    fflush(stdin);
    gets(s);
    for(i=0;i<n3;i++)
    {
        if(strcmp(br[i].isbn,(s))==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        gotoxy(20,7);
        printf("wrong isbn or this book isn't borrowed");
        getchar();
        mainmenu();
    }
    else
    {
        gotoxy(20,7);
        printf("book borrowed at %d/%d/%d",br[i].dborrow.day,br[i].dborrow.month,br[i].dborrow.year);
        gotoxy(20,9);
        printf("date due to return is %d/%d/%d",br[i].dduereturn.day,br[i].dduereturn.month,br[i].dduereturn.year);
        gotoxy(20,11);
        printf("enter the return date = ");
        scanf("%d/%d/%d",&br[i].dreturn.day,&br[i].dreturn.month,&br[i].dreturn.year);
        //comparing dates
         gotoxy(20,13);
    if(compare_dates(br[i].dduereturn,br[i].dreturn)==0)
        printf("<< THANK YOU !! book is returned in expected return date >>");
    else
    printf("<< book returning is late ! >>");
    }
    for(j=0;j<(n1);j++)
    {
        if(strcmp(books[j].isbn,(s))==0)
            flag=1;
        break;
    }
    if(flag==0)
    {
        printf("book is not borrowed");
        returnbook();
    }
    else
    {
        books[j].copies++;
    }
for(z=0;z<(n2);z++)
{
    if(m[z].id==br[i].id)

        flag=1;
        break;

}
if(flag==0)
{
    printf("book not found");
    returnbook();
}
else
 m[z].mbcount--;
gotoxy(20,17);
printf("return another book?(Y/N) = ");
        if(getch()=='y')
        {
            getchar();
       returnbook();
        }
        else
        mainmenu();
}
void save_books_file(void)
{
    int i;
 fp=fopen("books.txt","wt");
 if (fp==NULL)
    printf("error opening file books");
 else
 {
    fprintf(fp,"%d",n1);
    fprintf(fp,"\n");
    for(i=0;i<(n1);i++)
    {
  fprintf(fp,"%s,%s,%s,%s,%d/%d/%d,%d,%s,%d",books[i].title,books[i].Author,books[i].publisher,books[i].isbn,books[i].pubdate.day,books[i].pubdate.month,books[i].pubdate.year,books[i].copies,books[i].category,books[i].bcount);
     fprintf(fp,"\n");
    }}
    fclose(fp);
}
void save_members_file(void)
{
    int i;
   fp=fopen("members.txt","wt");
   if(fp==NULL)
      printf("error saving in members.txt");
  else
  {
   fprintf(fp,"%d",n2);
   fprintf(fp,"\n");
   for(i=0;i<n2;i++)
   {
    fprintf(fp,"%s,%d,%s,%s,%d,%s,%d",m[i].name,m[i].id,m[i].memaddress,m[i].phonenum,m[i].age,m[i].email,m[i].mbcount);
    fprintf(fp,"\n");
   }
  }
  fclose(fp);
}
void save_borrows_file(void)
{
    int i;
   fp=fopen("borrows.txt","wt");
   if(fp==NULL)
      printf("error saving in borrows.txt");
  else
  {
   fprintf(fp,"%d",n3);
   fprintf(fp,"\n");
   for(i=0;i<n3;i++)
   {
fprintf(fp,"%s,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d",br[i].isbn,br[i].id,br[i].dborrow.day,br[i].dborrow.month,br[i].dborrow.year,br[i].dduereturn.day,br[i].dduereturn.month,br[i].dduereturn.year,br[i].dreturn.day,br[i].dreturn.month,br[i].dreturn.year);
  fprintf(fp,"\n");
}}
fclose(fp);
}
void mostpopular(void)
{
    system("cls");
    int i,j,k;
    gotoxy(45,1);
    printf("<< list of most popular 5 books >>");
    book b[100];
    book a;
    for(k=0;k<n1;k++)
 {
       b[k]=books[k];
 }
for (i = 0; i < n1; ++i)
{
for (j = i + 1; j < n1; ++j)
{
if (b[i].bcount < b[j].bcount)
{
a = b[i];
b[i] = b[j];
b[j] = a;
}
}
}
 for(i=0;i<5;i++)
 {
       gotoxy(20,3+i);
       printf("%d) book title = %s :  borrowed %d times",i+1,b[i].title,b[i].bcount);
 }
gotoxy(21,i+4);
printf("Press any key to Go to Main menu ");
        getchar();
        mainmenu();
}
void overdue(void)
{
      system("cls");
    gotoxy(45,1);
    printf("<<  overdue Books  >>");
    int i;
time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   Date d;
   d.day=tm.tm_mday; d.month=(tm.tm_mon + 1); d.year=(tm.tm_year + 1900);
for(i=0;i<n3;i++)
    {
        gotoxy(21,3+i);
   if( compare_dates(br[i].dduereturn,d)==-1)
   {
       printf("Book isbn : %s didnt return yet and return date passed !! \n",br[i].isbn);
   }
}
gotoxy(21,i+4);
printf("Press any key to Go to Main menu ");
        getchar();
        mainmenu();
}
