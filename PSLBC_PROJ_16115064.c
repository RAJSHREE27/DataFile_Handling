#include<stdio.h>
#include<string.h>
#include<stdlib.h>                                  //necessary header files

struct student                                         //structure to declare variables for the program
{
    char name[25];
    int roll;
    float mrk1;
    float mrk2;
    float mrk3;
    float percent;
    char grade;
};
struct student s;                                          /*structure variable declared*/
                                                           /* function definition of all the functions used in program */
void create_file();                                        /*to create a file and to enter a record*/
float calc_percent(float m1,float m2,float m3);            /*to calculate the percentage obtained by a student*/
char calc_grade(float x);                                  /*to calculate grade of a particular student*/
void add_record();                                         /*to add record to a given file*/
void delete_file();                                        /*to delete a complete file*/
void delete_record();                                      /*to delete a particular record from the file*/
void shift_records(int i, int j, struct student s, struct student *nxt);       /*to sort the records*/
void sorting_records();                                    /*to give choice to the user as per which records in a file are sorted*/
int record_order(char file_name[45]);                      /*to count the number of records in a file*/


int main()                                                  //main body
{


    int ch;
    printf("\n this is a program where user can enter a choice:");
    printf("\n the choices are:");                                         //menu-driven  choices are given
    printf("\n 1. adding record to existing file");
    printf("\n 2. deleting the file");
    printf("\n 3.deleting certain record from the file");
    printf("\n 4. sorting records of students ");

    create_file();
    printf("\n enter your choice:");
    scanf("%d",&ch);                                                       //entering the choice
    if(ch==1)
        add_record();
    else if(ch==2)
        delete_file();
    else if(ch==3)
        delete_record();
    else if (ch==4)
        sorting_records();
    return 0;
}
void create_file()                       //for creating records initially
{
    FILE *f;
    char file_name[25];
    printf("\n enter the name of file:");
    scanf("%s",file_name);
    strcat(file_name,".txt");
    int i, n;
    printf("\n enter the number of elements you want to insert in file:");
    scanf("%d",&n);
    f=fopen(file_name,"w");
    for(i=0 ;i<n ; i++)
    {   printf("\n Enter student name:");
        scanf("%s",s.name);
        printf("Enter Roll Number of Student : ");
        scanf("%d", &s.roll);
        printf("Enter Marks in subject1 : ");
        scanf("%f" , &s.mrk1);
        printf("Enter Marks in subject 2: ");
        scanf("%f" , &s.mrk2);
        printf("Enter Marks in subject3 : ");
        scanf("%f" , &s.mrk3);
        s.percent=calc_percent(s.mrk1 , s.mrk2 , s.mrk3);
        s.grade=calc_grade(s.percent);
        fprintf(f,"%s %d %.2f %.2f %.2f %.2f %c\n",s.name, s.roll, s.mrk1, s.mrk2, s.mrk3, s.percent ,s.grade);

    }
    fclose(f);
}
float calc_percent(float m1,float m2,float m3)
{
    float percentage;
    percentage=(m1+m2+m3)/3;
    return percentage;
}
char calc_grade(float x)
{
    if(x>=90)
        return'A';
    else if(x>=80)
        return 'B';
    else if(x>=70)
        return 'C';
    else if(x>=60)
        return 'D';
    else if(x>=50)
        return 'E';
    else
        return 'F';
}
void add_record()        //for appending records
{
    FILE *f;
    char file_name[24];
    int i, n;
    printf("\n enter the number of records you want to enter:");
    scanf("%d",&n);
    printf("\n enter the name of file:");
    scanf("%s", file_name);
    f=fopen(file_name,"a");
    for(i=0; i<n; i++)
    {
        printf("Enter Name of Student : ");
        scanf("%s",&s.name);
        printf("Enter Roll Number of Student : ");
        scanf("%d", &s.roll);
        printf("Enter Marks in subject1 : ");
        scanf("%f" , &s.mrk1);
        printf("Enter Marks in subject 2: ");
        scanf("%f" , &s.mrk2);
        printf("Enter Marks in subject3 : ");
        scanf("%f" , &s.mrk3);
        s.percent=calc_percent(s.mrk1 , s.mrk2 , s.mrk3);
        s.grade=calc_grade(s.percent);
        fprintf(f,"%s %d %.2f %.2f %.2f %.2f %c\n",s.name, s.roll, s.mrk1, s.mrk2, s.mrk3, s.percent ,s.grade);

    }
    fclose(f);
}
void delete_file()                                  /*for deleting a particular  file*/
{
    char file_name[24];
    printf("\n enter the name of file you want to delete completely:");
    scanf("%s", file_name);
    remove(file_name);
    printf("\n FILE DELETED");
}
void delete_record() {                                                   /*for deleting a particular record in a file*/

    FILE *fin, *fout;
    char file_name[45];
    int rno;
    printf("\n enter the name of file from which you want to delete a record:");
    scanf("%s", file_name);
    strcat(file_name,".txt");
    printf("\n the record will be deleted according to the roll number entered by the user");
    fin = fopen(file_name, "r");
    fout = fopen("mid.txt", "w");
    printf("\n enter the roll number of student whose record you want to delete/remove:");
    scanf("%d", &rno);
    while (fscanf(fin, "%s %d %f %f %f %f %c", s.name, &s.roll, &s.mrk1, &s.mrk2, &s.mrk3, &s.percent,
                  &s.grade) != EOF) {
        if (s.roll != rno) {
            fprintf(fout, "%s %d %.2f %.2f %.2f %.2f %c\n", s.name, s.roll, s.mrk1, s.mrk2, s.mrk3, s.percent, s.grade);
        } else {
            continue;
        }
    }
    fclose(fin);
    fclose(fout);
    remove(file_name);
    rename( "mid.txt",file_name);
    printf("\n RECORD DELETED SUCCESSFUL!!!!!");
}
void shift_records(int i , int j, struct student s, struct student *nxt) {
    strcpy(s.name, (nxt + i)->name);
    s.roll = (nxt + i)->roll;
    s.mrk1 = (nxt + i)->mrk1;              /*swapping all the variables using third variable*/
    s.mrk2 = (nxt + i)->mrk2;
    s.mrk3 = (nxt + i)->mrk3;
    s.percent = (nxt + i)->percent;
    s.grade = (nxt + i)->grade;

    strcpy((nxt + i)->name, (nxt + j)->name);
    (nxt + i)->roll = (nxt + j)->roll;
    (nxt + i)->mrk1 = (nxt + j)->mrk1;
    (nxt + i)->mrk2 = (nxt + j)->mrk2;
    (nxt + i)->mrk3 = (nxt + j)->mrk3;
    (nxt + i)->percent = (nxt + j)->percent;
    (nxt + i)->grade = (nxt + j)->grade;

    strcpy((nxt + j)->name, s.name);
    (nxt + j)->roll = s.roll;
    (nxt + j)->mrk1 = s.mrk1;
    (nxt + j)->mrk2 = s.mrk2;
    (nxt + j)->mrk3 = s.mrk3;
    (nxt + i)->percent = s.percent;
    (nxt + i)->grade = s.grade;
}
int record_order(char file_name[25])
{
    int count=0;
    FILE *fpn;
    fpn=fopen(file_name,"r");
    while(fscanf(fpn, "%s %d %f %f %f %f %c", s.name, &s.roll,& s.mrk1, &s.mrk2, &s.mrk3, &s.percent, &s.grade)!=EOF)
    {
        count++;
    }

    fclose(fpn);
    return count;
}

struct student *nxt;
void sorting_records() {
                                                     /*to sort the record as per choices*/
    FILE  *fin , *fout;
    int n, j, i, x;
    char file_name[25];
    printf("\n enter the name of file whose data you want to sort:");
    scanf("%s", file_name);
    strcat(file_name,".txt");
    printf("\n the number of elements in a record which needs to be sorted is:");
    n = record_order(file_name );
    nxt=(struct student*)malloc(n*sizeof(struct student));
    fin = fopen(file_name, "r");
    for (i = 0; i < n; i++) {
        fscanf(fin, "%s %d %f %f %f %f %c", (nxt + i)->name, &(nxt + i)->roll, &(nxt + i)->mrk1,
               &(nxt + i)->mrk2, &(nxt + i)->mrk3, &(nxt + i)->percent, &(nxt + i)->grade);
    }
    fclose(fin);
    printf("\n enter your choice according to which , user wants to sort the record:");
    printf("\n 1. as per roll numbers");
    printf("\n 2. as per names");
    printf("\n 3. as per percent");
    printf("\n enter the choice->");
    scanf("%d", &x);                           //entering choice
    if (x == 1) {
        for (i = 0; i < n-1; i++) {
            for (j = i+1; j < n; j++) {
                if ((nxt + i)->roll > (nxt + j)->roll) {
                    shift_records(i, j, s, nxt);                /*calling function shift_records to sort further*/
                }
            }
        }
    } else if (x == 2) {
        for (i = 0; i < n-1; i++) {
            for (j = i+1; j < n; j++) {
                if (strcmp((nxt + i)->name, (nxt + j)->name) > 0) {
                    shift_records(i, j, s, nxt);
                }
            }
        }
    } else if (x == 3) {
        for (i = 0; i < n-1; i++) {
            for (j = i+1; j < n; j++) {
                if ((nxt + i)->percent > (nxt + j)->percent) {
                    shift_records(i, j, s, nxt);
                }
            }
        }
    } else
        printf("\n INVALID CHOICE!!!");
    fout=fopen("temp.txt","w");
    for(i=0; i<n; i++)
    {
        fprintf(fout,"%s %d %f %f %f %f %c\n",(nxt + i)->name, (nxt + i)->roll, (nxt + i)->mrk1,
                (nxt + i)->mrk2, (nxt + i)->mrk3, (nxt + i)->percent, (nxt + i)->grade);
    }
    fclose(fout);
    remove(file_name);
    rename("temp.txt",file_name);
    printf("\n sorting successful!");

}



