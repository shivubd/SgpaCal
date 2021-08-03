#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
    char name[15];
    char usn[12];
    int marks[8];
    float perc, sgpa;
    struct node *link;
}*NODE;
typedef struct node2
{
    char name[15];
    char usn[12];
    float sgpa[8];
    float cgpa;
    struct node2 *link;
}*NODE2;
int n,sn,credit[8];
NODE create()
{
    NODE first,p,q;
    int i;
    printf("Enter the no of students:  ");
    scanf("%d",&n);
    p=(NODE)malloc(sizeof(struct node));
    first=p;
    p->link=NULL;
    if(n>1)
    {
        for(i=1;i<n;i++)
        {
         q=(NODE)malloc(sizeof(struct node));
         p->link=q;
         p=p->link;
        }
        p->link=NULL;
    }
    return(first);
}
NODE2 create2()
{
    NODE2 first,p,q;
    int i;
    printf("Enter the no of students:  ");
    scanf("%d",&n);
    p=(NODE2)malloc(sizeof(struct node2));
    first=p;
    p->link=NULL;
    if(n>1)
    {
        for(i=1;i<n;i++)
        {
         q=(NODE2)malloc(sizeof(struct node2));
         p->link=q;
         p=p->link;
        }
        p->link=NULL;
    }
    return(first);
}
void inputfromfilesgpa(NODE first)
{
    FILE *fr;
    NODE p;
    int i;
    char filename[10];
    printf("\n\nNOTE: Create a .txt file with all input records of students\n");
    printf("FORMAT: NAME(TAB)USN(TAB)SUB1(TAB)SUB2(TAB)SUB3(TAB)SUB4(TAB)SUB5(TAB)SUB6(TAB)SUB7(TAB)SUB8(TAB)\n\n");
    printf("Enter the filename/Path with extension for input\n");
    scanf("%s",filename);
    fr=fopen(filename,"r");
    if(fr==NULL)
    {
        printf("\nERROR:FILE NOT FOUND\nCheck if the filename is correct \n and the file is present in the folder which contains this program\n");
        exit(0);
    }
    else
    {
        for(p=first;p!=NULL;p=p->link)
        {
            fscanf(fr,"%s\t%s\t",p->name,p->usn);
            for(i=0;i<8;i++)
                fscanf(fr,"%d\t",&p->marks[i]);
        }
    }
    fclose(fr);
}
void inputfromfilecgpa(NODE2 first)
{
    FILE *fr;
    NODE2 p;
    int i;
    char filename[10];
    printf("\n\nNOTE: Create a .txt file with all input records of students\n");
    printf("FORMAT: NAME(TAB)USN(TAB)SUB1(TAB)SUB2(TAB)SUB3(TAB)SUB4(TAB)SUB5(TAB)SUB6(TAB)SUB7(TAB)SUB8(TAB)\n\n");
    printf("Enter the filename/Path with extension for INPUT\n");
    scanf("%s",filename);
    fr=fopen(filename,"r");
    if(fr==NULL)
    {
        printf("\nERROR:FILE NOT FOUND\nCheck if the filename is correct \n and the file is present in the folder which contains this program\n");
        exit(0);
    }
    else
    {
        for(p=first;p!=NULL;p=p->link)
        {
            fscanf(fr,"%s\t%s\t",p->name,p->usn);
            for(i=0;i<8;i++)
                fscanf(fr,"%f\t",&p->sgpa[i]);
        }
    }
    fclose(fr);
}
void getcred()
{
    int i;
    printf("Enter the Credits");
    for(i=0;i<8;i++)
    {
        printf("\nSub%d: ",i+1);
        scanf("%d",&credit[i]);
    }
}
void calculatesgpa(NODE first)
{
    NODE p;
    int gradep[8];
    int sum,totalmarks,sumcg,sumcred,i;
    getcred();
    p=first;
    totalmarks=800;
    while(p)
    {
        sum=0;
        sumcg=0;
        sumcred=0;
        //Calculation of Percentage
        for(i=0;i<8;i++)
        {
            sum=sum+p->marks[i];
        }
        p->perc=(float)sum/totalmarks*100;
        //Calculation of SGPA
        for(i=0;i<8;i++)
        {
            if(p->marks[i]>=90&&p->marks[i]<=100)
                gradep[i]=10;
            else if(p->marks[i]>=80&&p->marks[i]<90)
                gradep[i]=9;
            else if(p->marks[i]>=70&&p->marks[i]<80)
                gradep[i]=8;
            else if(p->marks[i]>=60&&p->marks[i]<70)
                gradep[i]=7;
            else if(p->marks[i]>=50&&p->marks[i]<60)
                gradep[i]=6;
            else if(p->marks[i]>=45&&p->marks[i]<50)
                gradep[i]=5;
            else if(p->marks[i]>=40&&p->marks[i]<45)
                gradep[i]=4;
            else if(p->marks[i]<40&&p->marks[i]>=0)
                gradep[i]=0;
            else
            {
                printf("ERROR:Check marks of Student-%s, USN-%s\n",p->name,p->usn);
                exit(0);
            }
        }
        for(i=0;i<8;i++)
        {
            sumcred=sumcred+credit[i];
            sumcg=sumcg+(credit[i]*gradep[i]);
        }
        p->sgpa=(float)sumcg/sumcred;
        p=p->link;
    }
}
void getsemcred()
{
    int i;
    printf("Enter the Credits of Semester");
    for(i=0;i<8;i++)
    {
        printf("\nSemester%d: ",i+1);
        scanf("%d",&credit[i]);
    }
}
void calculatecgpa(NODE2 first)
{
    NODE2 p;
    int i;
    float sumcg, sumcred;
    getsemcred();
    sumcred=sumcg=0;
    p=first;
    while(p!=NULL)
    {
        for(i=0;i<8;i++)
        {
            sumcred=(float)sumcred+credit[i];
            sumcg=(float)sumcg+(credit[i]*p->sgpa[i]);
        }
        p->cgpa=sumcg/sumcred;
        p=p->link;
    }
}
void writetofilesgpa(NODE first)
{
    FILE *fw;
    int i,count=1;
    NODE p;
    fw=fopen("Results.txt","w");
    fprintf(fw,"Sl.no\tNAME\tUSN\t\tSUB1\tSUB2\tSUB3\tSUB4\tSUB5\tSUB6\tSUB7\tSUB8\tPERC\tSGPA\n");
    for(p=first;p!=NULL;p=p->link,count++)
    {
        fprintf(fw,"%d.\t%s\t%10s",count,p->name,p->usn);
        for(i=0;i<8;i++)
            fprintf(fw,"\t%d",p->marks[i]);
        fprintf(fw,"\t%.2f\t%.2f\n",p->perc,p->sgpa);
    }
    fclose(fw);
}
void writetofilecgpa(NODE2 first)
{
    FILE *fw;
    int i,count=1;
    NODE2 p;
    fw=fopen("ResultsCGPA.txt","w");
    fprintf(fw,"Sl.no\tNAME\tUSN\t\tSEM1\tSEM2\tSEM3\tSEM4\tSEM5\tSEM6\tSEM7\tSEM8\tCGPA\n");
    for(p=first;p!=NULL;p=p->link,count++)
    {
        fprintf(fw,"%d.\t%s\t%s",count,p->name,p->usn);
        for(i=0;i<8;i++)
            fprintf(fw,"\t%.2f",p->sgpa[i]);
        fprintf(fw,"\t%.2f\n",p->cgpa);
    }
    fclose(fw);
}
void destroy(NODE first)
{
    NODE p,q;
    p=first;
    while(p!=NULL)
    {
        q=p->link;
        free(p);
        p=q;
    }
    printf("\nTHANK YOU\n");
}
void destroy2(NODE2 first)
{
    NODE2 p,q;
    p=first;
    while(p!=NULL)
    {
        q=p->link;
        free(p);
        p=q;
    }
    printf("\nTHANK YOU\n");
}
void search(NODE first)
{
    NODE p;
    char id[10];
    int i;
    printf("Enter the NAME or USN of a student: ");
    scanf("%s",id);
    for(p=first;p!=NULL;p=p->link)
    {
        if(!(strcmp(id,p->name))||!(strcmp(p->usn,id)))
        {
            printf("NAME\tUSN\tSUB1\tSUB2\tSUB3\tSUB4\tSUB5\tSUB6\tSUB7\tSUB8\tPERC\tSGPA\n");
            printf("%s\t%s\t",p->name,p->usn);
            for(i=0;i<8;i++)
                printf("%d\t",p->marks[i]);
            printf("%.2f\t%.2f\n",p->perc,p->sgpa);
            strcpy(id,"NULL");
        }
    }
    if(strcmp(id,"NULL"))
        printf("\nSTUDENT NOT FOUND\n");
}
void search2(NODE2 first)
{
    NODE2 p;
    int i;
    char id[10];
    printf("Enter the NAME or USN of a student: ");
    scanf("%s",id);
    for(p=first;p!=NULL;p=p->link)
    {
        if(!(strcmp(id,p->name))||!(strcmp(p->usn,id)))
        {
            printf("NAME\tUSN\tSEM1\tSEM2\tSEM3\tSEM4\tSEM5\tSEM6\tSEM7\tSEM8\tCGPA\n");
            printf("%s\t%s\t",p->name,p->usn);
            for(i=0;i<8;i++)
                printf("%.2f\t",p->sgpa[i]);
            printf("%.2f\n",p->cgpa);
            strcpy(id,"NULL");
        }
    }
    if(strcmp(id,"NULL"))
        printf("\nSTUDENT NOT FOUND\n");
}
void listfailed(NODE first)
{
    NODE p;
    int i;
    FILE *pfail;
    int x[8];
    pfail=fopen("failedstudents.txt","w");
    fprintf(pfail,"NAME\tUSN\t\tFailed Subjects");
    for(p=first;p!=NULL;p=p->link)
    {
        for(i=0;i<8;i++)
            x[i]=0;
        for(i=0;i<8;i++)
        {
            if(p->marks[i]<35)
                x[i]=1;
        }
        if(x[0]!=0||x[1]!=0||x[2]!=0||x[3]!=0||x[4]!=0||x[5]!=0||x[6]!=0||x[7]!=0)
        {
            fprintf(pfail,"\n%s\t%s\t",p->name,p->usn);
            for(i=0;i<8;i++)
            {
                if(x[i]==1)
                fprintf(pfail,"SUB%d\t",i+1);
            }

        }
    }
    printf("Sucessfull:List of failed students in present in failedstudents.txt FILE\n");
    fclose(pfail);
}
void cutoff(NODE2 first, float C)
{
    NODE2 p;
    FILE *pcutoff;
    pcutoff=fopen("cutoffclear.txt","w");
    fprintf(pcutoff,"NAME\tUSN\t\tCGPA\n");
    for(p=first;p!=NULL;p=p->link)
    {
        if(p->cgpa>=C)
        {
            fprintf(pcutoff,"%s\t%s\t%.2f\n",p->name,p->usn,p->cgpa);
        }
    }
    printf("Sucessfull:List of students who cleared cutoff is present in cutoffclear.txt FILE\n");
    fclose(pcutoff);
}
int main()
{
    NODE first;
    NODE2 first2;
    int choice,ch;
    float C;
    printf("\n=============================================================================\n");
    printf("                  \4\4\4\4 SGPA AND CGPA CALCULATION \4\4\4\4\n");
    printf("=============================================================================\n");
    printf("\n1.Calculate SGPA and PERCENTAGE    2.Calculate CGPA    3.Exit\n");
    start:printf("Enter your CHOICE\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        first=create();
        inputfromfilesgpa(first);
        calculatesgpa(first);
        writetofilesgpa(first);
        printf("\nSucessfull:OUTPUT FILE NAME Results.txt\n");
        printf("\nMENU\n1:List of Failed students\t2:Search a student\t3:Exit\n");
        do
        {
            printf("\nEnter your choice: ");
            scanf("%d",&ch);
            switch(ch)
            {
                case 1:listfailed(first);
                       break;
                case 2:search(first);
                       break;
            }
        }while(ch<3);
        destroy(first);
    }
    else if(choice==2)
    {
        first2=create2();
        inputfromfilecgpa(first2);
        calculatecgpa(first2);
        writetofilecgpa(first2);
        printf("\nSucessfull:OUTPUT FILE NAME ResultsCGPA.txt\n");
        printf("\nMENU\n1:List of students with CGPA above\t2:Search a student\t3:Exit\n");
        do
        {
            printf("\nEnter the choice: ");
            scanf("%d",&ch);
            switch(ch)
            {
                case 1:printf("\nEnter the CGPA Cutoff: ");
                       scanf("%f",&C);
                       cutoff(first2,C);
                       break;
                case 2:search2(first2);
                       break;
            }
        }while(ch<3);
        destroy2(first2);
    }
    else if(choice==3)
    {
        exit(0);
    }
    else
    {
        printf("Invalid Choice\n");
        goto start;
    }
    return 0;
}
