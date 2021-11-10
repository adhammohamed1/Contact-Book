#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "menus.h"
#include "data.h"
#include "func.h"
#include <ctype.h>
#include <conio.h>

/// This file contains all functions that handle data (save, load, edit, etc..)


//This function reads the file and stores its contents in the global array -contacts-
int load(char *file_name)
{
    count=0; ///reset the count to be incremented during the process of loading
    if(!(f=fopen(file_name,"r"))) return 0;
    reset();
    while(!feof(f))
    {

        fscanf(f," %[^,], ",c[count].lastname);
        if(islower(*c[count].lastname))*c[count].lastname-=32;
        fscanf(f," %[^,], ",c[count].name);
        if(islower(*c[count].name))*c[count].name-=32;
        fscanf(f," %d-%d-%d, ",&c[count].date_of_birth.day,&c[count].date_of_birth.month,&c[count].date_of_birth.year);
        fscanf(f," %[^,], ",c[count].address);
        fscanf(f," %[^,], ",c[count].mobile_number);
        fscanf(f," %s\n ",c[count].email);
        if(c[count].date_of_birth.day!=0)count++;
    }
    fclose(f);
    if(!count) return -1; //The file is empty
    sorta_z();
    return 1; //The file has been loaded successfully
}


//This function calculates the file size (in bytes) and stores it in the global variable -filesize-
void getfilesize(char *filename)
{
    f=fopen(filename,"r");
    int x=ftell(f); //Determine the start position
    fseek(f,0L,SEEK_END); //Seek to the end of the file
    filesize=ftell(f); //Determine file size
    fseek(f,x,SEEK_SET); //Return to start position
}

//This function searches for all records with a given last name and prints the result
void search()
{
    printf("\nPlease enter the last name of the required contact or 0 to cancel: ");
    char s[40];
    gets(s);
    if(*s=='0')
    {
        printf("\n\n\tProcess Canceled.\n\n");
        return;
    }
    int rescount=0;
    for(int i=0; i<count; i++)
        if(!strcasecmp(c[i].lastname,s))
            rescount++;
    if((rescount)==1)printf("====================================================\nFound: 1 result in %s\n\n",filename);
    else printf("====================================================\nFound: %d results in %s\n\n",rescount,filename);
    for(int i=0; i<count ; i++)
        if(!strcasecmp(c[i].lastname,s))
        {
            printf("(ID: %d)\nFirst name:\t%s\n",i+1,c[i].name);
            printf("Date of birth:\t%d/%d/%d\n",c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year);
            printf("Address:\t%s\n",c[i].address);
            printf("Phone Number:\t%s\n",c[i].mobile_number);
            printf("E-mail:\t\t%s\n\n",c[i].email);
        }
}

//This function adds a new entry to the contacts array
void add()
{
    printf("Enter 0 in the first name to cancel.\n");
    printf("\nFirst name: ");
    gets(c[count].name);
    if(*c[count].name=='0')
    {
        printf("\n\n\tProcess Canceled.\n\n");
        return;
    }
    if(islower(*c[count].name))
    {
        *c[count].name-=32;
        printf("\x1b[1A\33[2KFirst name: %s\n",c[count].name);
    }
    printf("\nLast name: ");
    gets(c[count].lastname);
    if(islower(*c[count].lastname))
    {
        *c[count].lastname-=32;
        printf("\x1b[1A\33[2KLast name: %s\n",c[count].lastname);
    }
    printf("\nStreet address: ");
    gets(c[count].address);
    while(1)
    {
        printf("\nE-mail address: ");
        gets(c[count].email);
        if(!emailvalid(c[count].email,count))
        {
            invalidemail();
            continue;
        }
        else if(emailvalid(c[count].email,count)==-1)
        {
            printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
            printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
            printf("\x1b[1BEmail address already in use.\n");
            printf("\x1b[0m");
            continue;
        }
        break;
    }
    printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
    while(1)
    {
        printf("\nDate of birth (dd mm yyyy): ");
        gets(date);
        if(invaliddob(count)) continue;
        break;
    }
    printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
    fflush(stdin);
    while(1)
    {
        printf("\nMobile number: ");
        gets(c[count].mobile_number);
        if(!containchar(c[count].mobile_number))
        {
            invalidnum();
            continue;
        }
        break;
    }
    printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
    printf("\n\n> Contact added successfully. ");
    if(!autosave)printf("Don't forget to save your changes!\n");
    saved=0;
    count++;
    if(autosave)
    {
        save();
        printf("Auto-saved!\n");
    }
}

//This function deletes all records with given first and last names
void delete_record()
{
    char _first[40],_last[40];
    int n=0;
    printf("Enter 0 in the first name to cancel.\n\n");
    printf("First Name: ");
    gets(_first);
    if(*_first=='0')
    {
        printf("\n\n\tProcess Canceled.\n\n");
        return;
    }
    printf("Last Name: ");
    gets(_last);
    for(int i=0; i<=count; i++)
        if((!strcasecmp(c[i].lastname,_last))&&(!strcasecmp(c[i].name,_first)))
        {
            *(c[i].lastname)=0;
            count--;
            n++;
            for(int j=i; j<count; j++)
                c[j]=c[j+1];
        }
    if(n) saved=0;
    if(n>1)printf("\n<!> Successfully deleted %d records.\n",n);
    else if(n==1) printf("\n<!> Successfully deleted 1 record.\n");
    else printf("\n<!> No matches found.\n");
    if(n && autosave)
    {
        save();
        printf("\nAuto-saved!\n");
    }
}

//This function saves all changes to the file
void save()
{
    f=fopen(filename,"w");
    for(int i=0; i<count; i++)
    {
        fprintf(f,standard_format,c[i].lastname,c[i].name,c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year,c[i].address,c[i].mobile_number,c[i].email);
    }
    fclose(f);
    saved=1;
}

//This function modifies a given entry in the global array
void modify(int m)
{
    char mizo[40];
    printf("\n<!> Choose a field to be modified or press 7 to edit the whole contact:\n-----------------------------------------------------------------------\n");
    printf(" 1. First name.\n 2. Last name.\n 3. Street address.\n 4. E-mail address.\n 5. Date of birth.\n 6. Mobile number.\n 7. Whole contact.\n");
    fflush(stdin);
    while(1)
    {
        printf("  ");
        gets(mizo);
        if(atoi(mizo)==1 ||atoi(mizo)==2  ||atoi(mizo)==3  ||atoi(mizo)==4  ||atoi(mizo)==5 ||atoi(mizo)==6 ||atoi(mizo)==7 )
        {
            break;
        }
        else
        {
            printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
            printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
            printf("\x1b[1BInput must be integers between (1,7)\n");
            printf("\x1b[0m");
            continue;
        }
    }
    if(atoi(mizo)==1)
    {
        printf("\nFirst name: ");
        gets(c[m].name);
        if(islower(*c[m].name))
        {
            *c[m].name-=32;
            printf("\x1b[1A\33[2KFirst name: %s\n",c[m].name);
        }


    }
    if(atoi(mizo)==2)
    {
        printf("\nLast name: ");
        gets(c[m].lastname);
        if(islower(*c[m].lastname))
        {
            *c[m].lastname-=32;
            printf("\x1b[1A\33[2KLast name: %s\n",c[m].lastname);
        }
    }
    if(atoi(mizo)==3)
    {
        printf("\nStreet address: ");
        gets(c[m].address);
    }
    if(atoi(mizo)==4)
    {
        while(1)
        {
            printf("\nE-mail address: ");
            gets(c[m].email);
            if(!emailvalid(c[m].email,m))
            {
                invalidemail();
                continue;
            }
            else if(emailvalid(c[m].email,m)==-1)
            {
                printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
                printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
                printf("\x1b[1BEmail address already in use.\n");
                printf("\x1b[0m");
                continue;
            }
            break;
        }
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
    }
    if(atoi(mizo)==5)
    {
        while(1)
        {
            printf("\nDate of birth (dd mm yyyy): ");
            gets(date);
            if(invaliddob(m))continue;
            break;
        }
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
        fflush(stdin);
    }
    if(atoi(mizo)==6)
    {
        while(1)
        {
            printf("\nMobile number: ");
            gets(c[m].mobile_number);
            if(!containchar(c[m].mobile_number))
            {
                invalidnum();
                continue;
            }
            break;
        }
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
    }
    if(atoi(mizo)==7)
    {

        printf("\nFirst name: ");
        gets(c[m].name);
        if(islower(*c[m].name))
        {
            *c[m].name-=32;
            printf("\x1b[1A\33[2KFirst name: %s\n",c[m].name);
        }
        printf("\nLast name: ");
        gets(c[m].lastname);
        if(islower(*c[m].lastname))
        {
            *c[m].lastname-=32;
            printf("\x1b[1A\33[2KLast name: %s\n",c[m].lastname);
        }
        printf("\nStreet address: ");
        gets(c[m].address);
        while(1)
        {
            printf("\nE-mail address: ");
            gets(c[m].email);
            if(!emailvalid(c[m].email,m))
            {
                invalidemail();
                continue;
            }
            else if(emailvalid(c[m].email,m)==-1)
            {
                printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
                printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
                printf("\x1b[1BEmail address already in use.\n");
                printf("\x1b[0m");
                continue;
            }
            break;
        }
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box

        while(1)
        {
            printf("\nDate of birth (dd mm yyyy): ");
            gets(date);
            if(invaliddob(m))continue;
            break;
        }
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
        fflush(stdin);
        while(1)
        {
            printf("\nMobile number: ");
            gets(c[m].mobile_number);
            if(!containchar(c[m].mobile_number))
            {
                invalidnum();
                continue;
            }
            break;
        }
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[42m %c \x1b[32m\x1b[40m Valid!\x1b[0m\n\r",251); ///prints a white tick in a green box
    }
    printf("\n\n> Contact modified successfully. ");
    if(!autosave)printf("Don't forget to save your changes!\n");
    saved=0;
    if(autosave)
    {
        save();
        printf("Auto-saved!\n");
    }
}
//This function sorts entries by last name ( a --> z )
void sorta_z()
{
    int zozo=0;
    int temp=99;
    for(int i=0; i<count-1; i++)
    {
        for(zozo=0; zozo<count-1; zozo++)
        {
            if(strcasecmp(c[zozo].lastname,c[zozo+1].lastname)>0)
            {
                c[temp]=c[zozo];
                c[zozo]=c[zozo+1];
                c[zozo+1]=c[temp];
            }
        }
    }
}

//This function sorts entries by last name ( z --> a )
void sortz_a()
{
    int zozo=0;
    int temp=99;
    for(int i=0; i<count-1; i++)
    {
        for(zozo=0; zozo<count-1; zozo++)
        {
            if(strcasecmp(c[zozo].lastname,c[zozo+1].lastname)<0)
            {
                c[temp]=c[zozo];
                c[zozo]=c[zozo+1];
                c[zozo+1]=c[temp];
            }
        }
    }
}

//This function sorts entries by date of birth ascendingly
void sort_asc()
{
    int zozo=0;
    int temp=99;
    for(int i=0; i<count-1; i++)
    {
        for(zozo=0; zozo<count-1; zozo++)
        {
            if(c[zozo].date_of_birth.year>c[zozo+1].date_of_birth.year)
            {
                c[temp]=c[zozo];
                c[zozo]=c[zozo+1];
                c[zozo+1]=c[temp];
            }
            else if(c[zozo].date_of_birth.year==c[zozo+1].date_of_birth.year)
            {
                if(c[zozo].date_of_birth.month>c[zozo+1].date_of_birth.month)
                {
                    c[temp]=c[zozo];
                    c[zozo]=c[zozo+1];
                    c[zozo+1]=c[temp];
                }
                else if(c[zozo].date_of_birth.month==c[zozo+1].date_of_birth.month)
                {
                    if(c[zozo].date_of_birth.day>c[zozo+1].date_of_birth.day)
                    {
                        c[temp]=c[zozo];
                        c[zozo]=c[zozo+1];
                        c[zozo+1]=c[temp];
                    }
                }
            }
        }
    }
}

//This function sorts entries by date of birth descendingly
void sort_des()
{
    int zozo=0;
    int temp=99;
    for(int i=0; i<count-1; i++)
    {
        for(zozo=0; zozo<count-1; zozo++)
        {
            if(c[zozo].date_of_birth.year<c[zozo+1].date_of_birth.year)
            {
                c[temp]=c[zozo];
                c[zozo]=c[zozo+1];
                c[zozo+1]=c[temp];
            }
            else if(c[zozo].date_of_birth.year==c[zozo+1].date_of_birth.year)
            {
                if(c[zozo].date_of_birth.month<c[zozo+1].date_of_birth.month)
                {
                    c[temp]=c[zozo];
                    c[zozo]=c[zozo+1];
                    c[zozo+1]=c[temp];
                }
                else if(c[zozo].date_of_birth.month==c[zozo+1].date_of_birth.month)
                {
                    if(c[zozo].date_of_birth.day<c[zozo+1].date_of_birth.day)
                    {
                        c[temp]=c[zozo];
                        c[zozo]=c[zozo+1];
                        c[zozo+1]=c[temp];
                    }
                }
            }
        }
    }
}

void reset()
{
    c[0].date_of_birth.day=0;
}
