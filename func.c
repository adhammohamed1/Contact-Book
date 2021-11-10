#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include "menus.h"
#include "data.h"
#include "func.h"

/// This file includes all supplementary functions created to support the main functions of the program



//This function auto-corrects file name in the "Load directory" menu
char *checkfilename(char *entry)
{
    int i=0,flag=0,length=strlen(entry),dots=0;
    char choice;
    for(i=length-1; i>=length-(length/3); i--)
        if(entry[i]=='.')
        {
            flag=1;
            entry[i]='$';
            break;
        }
    for(i=0; i<length; i++)
        if(entry[i]=='.')
        {
            dots++;
        }
    if(entry[length-5]=='.' && entry[length-4]=='t' && entry[length-3]=='x' && entry[length-2]=='t' && !entry[length-1]) return entry; ///The user has entered the file name correctly
    if(!flag) printf("\nDid you mean <%s.txt> ?\n",entry); ///User forgot to write " .txt "
    else printf("\nDid you mean <%s.txt> ?\n",strtok(entry,"$")); ///User wrote a wrong format (ex: " .txc ")
    printf("\n1. Yes\n2. No\n");
    while(1)
    {
        choice = getche();
        if(choice=='1')entry=strcat(entry,".txt"); ///Correct the user's input
        else if(choice!='2')
        {
            printf("\33[2K\r");
            continue; ///Invalid Entry
        }
        break;
    }
    return entry;
}

//This function prints the current directory
void print(char *choice)
{
    switch(*choice)
    {
    case '1': //Sort by last name
        if(*(choice+1)=='1') // a -> z
        {
            sorta_z();
            for(int i=0; i<count; i++)
                printf(" %03d | %s, %s, %d-%d-%d, %s, %s, %s\n",i+1,c[i].lastname,c[i].name,c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year,c[i].address,c[i].mobile_number,c[i].email);

        }
        else // z -> a
        {
            sortz_a();
            for(int i=0; i<count; i++)
                printf(" %03d | %s, %s, %d-%d-%d, %s, %s, %s\n",i+1,c[i].lastname,c[i].name,c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year,c[i].address,c[i].mobile_number,c[i].email);

        }
        break;
    case '2': //Sort by date of birth
        if(*(choice+1)=='1') // ascendingly
        {
            sort_asc();
            for(int i=0; i<count; i++)
                printf(" %03d | %s, %s, %d-%d-%d, %s, %s, %s\n",i+1,c[i].lastname,c[i].name,c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year,c[i].address,c[i].mobile_number,c[i].email);
        }
        else // descendingly
        {
            sort_des();
            for(int i=0; i<count; i++)
                printf(" %03d | %s, %s, %d-%d-%d, %s, %s, %s\n",i+1,c[i].lastname,c[i].name,c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year,c[i].address,c[i].mobile_number,c[i].email);
        }
        break;
    }
}

//This function checks if a string contains a non-numeric character
int containchar(char *s)

{
    int f=0;
    char arr[]="qwertyuiop[]\\\tasdfghjkl;'zxcvbnm,. /=+-_)(*&^%$#@!~QWERTYUIOPASDFGHJKLZXCVBNM?><}{:\"";
    for(int i=0; i<strlen(s); i++)
        for(int k=0; k<strlen(arr); k++)
            if(s[i]==arr[k]) f++;
    if(f==0)
        return 1;
    else return 0;
}

//This function checks if the entered date is in the correct format (a bit similar to containchar() )
int date_string_check(char *s)
{
    int f=0,space=0;
    char arr[]="qwertyuiop[]\\asdfghjkl;'zxcvbnm,./=+-_)(*&^%$#@!~QWERTYUIOPASDFGHJKLZXCVBNM?><}{:\"";
    for(int i=0; i<strlen(s); i++)
        {
        if(s[i]==' ') space++;
        for(int k=0; k<strlen(arr); k++)
            if(s[i]==arr[k])f++;
        }
    if(!f && space==2) return 1;
    else return 0;
}

//This function validates an email <example@domain.com>
int emailvalid(char *s,int index)
{
    int k=0,l=0,t=1,dots=0;
    if(*s=='@')return 0;
    for(int i=0; i<count; i++)
    {
        if(!strcasecmp(c[i].email,s) && (i!=index))
            return -1;
    }
    for(int i=0; i<strlen(s); i++)
    {
        if(s[i]== '@' && (s[i+1]!='.'))
            k++;
        if(k) if(s[i]=='.') dots++;
        if(dots>1)k=0;
    }
    for(int i=0; i<strlen(s); i++)
    {
        if(s[i]==' ')
            t=0;
    }

    for(int i=0; i<strlen(s); i++)
    {
        if(s[i]=='.' && s[i+1]=='c' && s[i+2]=='o' && s[i+3]=='m' && s[i+4]=='\0')
        {
            l=1;
            break;
        }
    }
    if(k+l+t==3) return 1;
    else return 0;
}

int is_valid_fname(char *s)
{
    char restrictions[]="\\/<>*\":|";
    for(int i=0; i<strlen(s); i++)
    {
        for(int h=0; h<strlen(restrictions); h++)
        {
            if(s[i]==restrictions[h]) return 0;
        }
    }
    return 1;
}
