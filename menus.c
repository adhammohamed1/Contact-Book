#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "func.h"
#include "data.h"
#include <ctype.h>


/// This file includes all menus (except the main menu) and functions that mainly print messages for the user

// This function displays a message to transition between current window and the main menu
void return_to_main()
{
    printf("\33[2K\r\n==============================================\n");
    printf("Press any key to return to main menu...\n");
    getche();
}

// This function displays a message to transition between current window and the previous menu
void return_to_prev()
{
    printf("\33[2K\r\n==============================================\n");
    printf("Press any key to return to the previous menu...\n");
    getche();
}

// This function displays all the project details which are visible when accessing the first item on the main menu
void details()
{
    printf("====================================\nTelephone Book  >  Project details\n====================================\n");
    printf("\nProgramming I Final Project\tFall 2020\tProf. Dr. Saleh El Shehaby\n---------------------------\t---------\t--------------------------");
    printf("\n\nParticipants:\n\n1. Adham Mohamed Aly\t\t6744\tGroup 1\n2. Mohamed Farid Abdelaziz\t6905\tGroup 2\n\n\n");

    printf("Autosave: ");
    if(autosave)printf("\x1b[32mON\n\n\x1b[0m");
    if(!autosave)printf("\x1b[31mOFF\n\n\x1b[0m");

    if(!load_status) printf("No file is currently loaded.\n");
    else
    {
        getfilesize(filename);
        printf("Properties of saved data on the currently loaded file:\n------------------------------------------------------\n");
        printf("File Name:\t\t%s\nFile Size:\t\t%ld bytes\nNumber of entries:\t%d\n",filename,filesize,count);
    }
    return_to_main();
}

//This function informs the user that the menu or functionality they tried to access is still under development
void indev(char _type)
{
    system("cls");
    if(_type=='m') printf("\n\n\t\tThis menu is currently under development.\n\n");
    if(_type=='f') printf("\n\n\t\tThis functionality is currently under development.\n\n");
    return_to_prev();
}

//This function prints error message during validation of email
void invalidemail()
{
    printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
    printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
    printf("\x1b[1BPlease enter correct format -> \"example@domain.com\"\n");
    printf("\x1b[0m");
}

//This function prints error message during validation of date of birth
int invaliddob(int m)
{
    int trigger=0;
    if(!date_string_check(date))
    {
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! "); ///Prints a white exclamation mark in a red box
        printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
        printf("\x1b[1Bi. Date of birth cannot contain non-numeric characters.\x1b[56D");
        printf("\x1b[1Bii. Make sure to leave spaces between day, month and year.");
        printf("\x1b[0m\n\r");
        return 1;
    }
    else
    {
        strcpy(day,strtok(date," "));
        strcpy(month,strtok(NULL," "));
        strcpy(year,strtok(NULL," "));
        c[m].date_of_birth.day=atoi(day);
        c[m].date_of_birth.month=atoi(month);
        c[m].date_of_birth.year=atoi(year);
    }

    if((c[m].date_of_birth.day>31 || c[m].date_of_birth.day<1 ||c[m].date_of_birth.month>12  || c[m].date_of_birth.month<1  ||c[m].date_of_birth.year>2021 || c[m].date_of_birth.year<1800) || (c[m].date_of_birth.day>29 && c[m].date_of_birth.month==2))
    {
        printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! "); ///Prints a white exclamation mark in a red box
        printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
        if((c[m].date_of_birth.day>31 || c[m].date_of_birth.day<1 ||c[m].date_of_birth.month>12  || c[m].date_of_birth.month<1  ||c[m].date_of_birth.year>2021 || c[m].date_of_birth.year<1800))
        {
            trigger=1;
            if(c[m].date_of_birth.day>31 || c[m].date_of_birth.day<1) printf("\x1b[1BDay limit exceeded! (max: 31 ,min:1)\x1b[36D");
            if(c[m].date_of_birth.month>12  || c[m].date_of_birth.month<1) printf("\x1b[1BMonth limit exceeded! (max: 12 ,min:1)\x1b[38D");
            if(c[m].date_of_birth.year>2021 || c[m].date_of_birth.year<1800) printf("\x1b[1BYear limit exceeded! (max: 2021 ,min:1800)\x1b[42D");
        }
        if(c[m].date_of_birth.day>29 && c[m].date_of_birth.month==2)
        {
            trigger=1;
            printf("\x1b[1BDay limit exceeded for February! (max: 29)");
        }
        printf("\x1b[0m\n\r");
    }
    return trigger;
}

//This function prints error message during validation of phone number
void invalidnum()
{
    printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
    printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
    printf("\x1b[1BPhone number must contain digits only with no spaces.\n");
    printf("\x1b[0m");
}

// This function displays a message before the termination of the program
void thankyou()
{
    system("cls");
    printf("\n\n\t\t\x1b[32mTh\x1b[33mank \x1b[34myo\x1b[35mu fo\x1b[36mr us\x1b[32min\x1b[34mg our te\x1b[35mleph\x1b[31mone book!\x1b[0m\n\n");
}

// This function displays the exit menu which can be accessed through the main menu (item 8)
void exit_menu()
{
    int inv=0;
    while(saved) // User has saved all the changes and has chosen to exit
    {
        system("cls");
        if(inv) printf("\n\t\t\x1b[31m<!> Invalid Entry!\x1b[0m");
        printf("\n\n\t\t<!> Are you sure you want to exit?\n\t\t1. Yes\n\t\t2. No\n\t\t >");
        switch(getche())
        {
        case '1': // Yes
            thankyou();
            exit(0);
        case '2': // No
            return_to_main();
            break;
        default: // Invalid Entry
            inv=1;
            continue;
        }
        break;
    }
    while(!saved) // User has chosen to exit without saving the changes
    {
        system("cls");
        if(inv) printf("\n\t\t\x1b[31m<!> Invalid Entry!\x1b[0m");
        printf("\n\n\t\t<!> Exit without saving?\n\t\t1. Yes\n\t\t2. Save and quit\n\t\t3. Return to main menu\n\t\t >");
        switch(getche())
        {
        case '1': // Yes
            thankyou();
            exit(0);
        case '2': // Save and quit
            save();
            thankyou();
            exit(0);
            continue;
        case '3': // Return to main menu
            return_to_main();
            break;
        default: // Invalid Entry
            inv=1;
            continue;
        }
        break;
    }
}

// This function displays the "Load directory" menu which can be accessed through the main menu (item 3)
void load_menu()
{
    char input[30];
    system("cls");
    printf("==================================\nTelephone Book  >  Load directory\n==================================\n\n");
    printf("Enter the file name to load or 0 to cancel\n\nload>");
    gets(input);
    if(!strcmp(input,"0")) //if  user entered ' 0 ' to cancel
    {
        printf("\n\n\tProcess Canceled.\n\n");
        return_to_main();
        return;
    }

    strcpy(filename,checkfilename(input)); //Auto-correct user input

    load_status=load(filename); //Main load function

    if(load_status) //If file was successfully loaded
    {

        printf("\33[2K\r\n\n\tDirectory has been successfully loaded.\n\n");
        getfilesize(filename);
        printf("File Name:\t\t%s\nFile Size:\t\t%ld bytes\nNumber of entries:\t%d\n\n\n",filename,filesize,count);
        while(1)
        {
            if(!autosave)printf("1. Return to main menu\n2. Enable autosave\n >");
            else printf("1. Return to main menu\n2. Disable autosave\n >");
            switch(getche())
            {
            case '1':
                break;
            case '2':
                printf("\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\r");
                if(!autosave) autosave=1;
                else autosave=0;
                continue;
            default:
                printf("\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\r");
                continue;
            }
            break;
        }
    }
    else if(!load_status) printf("\33[2K\r\n\n\tFile does not exist.\n\n"); //If file could not be opened
    return_to_main();
}


//This function displays the "Search" menu which can be accessed through the main menu (item 5)
void searche()
{
    printf("==========================\nTelephone Book  >  Search\n==========================\n\n");
    if(count)search();
    else if(load_status && !count) printf("\n\n\tDirectory is empty.\n\n");
    else printf("\n\n\tNo file is currently loaded.\n\n");
    return_to_main();
}

//This function displays the "Save directory" menu which can be accessed through the main menu (item 6)
void save_menu()
{
    while(1)
    {
        system("cls");
        printf("========================\nTelephone Book  >  Save\n========================\n\n");
        if(load_status)
        {

            printf("\n\n\tSave changes to <%s> ?\n\n",filename);
            if(!autosave)printf("\n1. Yes\n2. Return to main menu\n3. Enable autosave\n >");
            else printf("\n1. Yes\n2. Return to main menu\n3. Disable autosave\n >");

            switch(getche())
            {
            case '1':

                save();
                printf("\n\nSaved successfully!\n");
                break;
            case '2':
                printf("\33[2K\r");
                break;
            case '3':
                if(!autosave)autosave=1;
                else autosave=0;
                continue;
            }
        }
        else printf("\n\n\tNo file is currently loaded\n\n");
        break;
    }

    return_to_main();

}

//This function deletes an entry from the global array
void delete_entry(char menu)
{
    system("cls");
    if(menu=='m')printf("====================================================\nTelephone Book  >  Edit directory  >  Delete Entry\n====================================================\n\n");
    else if(menu=='p') printf("=======================================================================\nTelephone Book  >  Print directory  >  Edit directory  >  Delete Entry\n=======================================================================\n\n");
    if(!load_status) printf("\n\n\tNo file is currently loaded\n\n");
    else if(load_status && !count) printf("\n\n\tDirectory is empty.\n\n");
    else if(count) delete_record();
    return_to_prev();
}

//This function modifies a given entry in the global array
void modify_entry(char menu)
{
    char s[40];
    int coco=0;
    char f[40];
    int h=0;
    int arrcount[100]= {0};

    system("cls");
    if(menu=='m')printf("====================================================\nTelephone Book  >  Edit directory  >  Modify Entry\n====================================================\n\n");
    else if(menu=='p') printf("=======================================================================\nTelephone Book  >  Print directory  >  Edit directory  >  Modify Entry\n=======================================================================\n\n");
    if(!load_status) printf("\n\n\tNo file is currently loaded\n\n");
    else if(load_status && !count) printf("\n\n\tDirectory is empty.\n\n");
    else if(count)
    {
        while(1)
        {
            printf("\nPlease enter the last name of the contact needed to be modified or 0 to cancel:");

            fflush(stdin);
            gets(s);
            if(*s=='0')
            {
                printf("\n\n\tProcess Canceled.\n\n");
                return_to_prev();
                return;
            }
            for(int i=0; i<count; i++) if(!strcasecmp(s,c[i].lastname)) coco++;
            if(!coco)
            {
                printf("\n\x1b[31m<!> No matches found.\n\x1b[0m");
                continue;
            }
            break;
        }
        coco=0;
        printf("\nChoose the contact you need to modify:\n\n");
        for(int i=0; i<count; i++)
        {
            if(!strcasecmp(s,c[i].lastname))
            {
                printf("%3d. %s, %s, %d-%d-%d, %s, %s, %s\n",coco+1,c[i].lastname,c[i].name,c[i].date_of_birth.day,c[i].date_of_birth.month,c[i].date_of_birth.year,c[i].address,c[i].mobile_number,c[i].email);
                arrcount[coco]=i;
                coco++;
            }
        }
        printf("  0. Cancel\n");
        while(1)
        {
            printf("\n >");
            gets(f); ///7ot function invalid t7t di w e3ml el while wl 7abashtakanat
            if(!atoi(f) && !isalpha(*f))
            {
                return_to_prev();
                return;
            }
            if(atoi(f)<1 || atoi(f)>coco+1 || !containchar(f))
            {
                printf("\x1b[1A\x1b[60C\x1b[37m\x1b[41m ! \x1b[0m"); ///Prints a white exclamation mark in a red box
                printf("\x1b[31m\x1b[40m Invalid Entry!\x1b[33m\x1b[14D");
                printf("\x1b[1BOut of bounds.\n");
                printf("\x1b[0m");
                continue;
            }
            break;
        }
        for(h=0; h<coco; h++)
        {
            if((h+1)==atoi(f))
            {
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("\n\n\x1b[30m\x1b[43mContact:  "standard_format"\x1b[0m",c[arrcount[h]].lastname,c[arrcount[h]].name,c[arrcount[h]].date_of_birth.day,c[arrcount[h]].date_of_birth.month,c[arrcount[h]].date_of_birth.year,c[arrcount[h]].address,c[arrcount[h]].mobile_number,c[arrcount[h]].email);
                modify(arrcount[h]);
            }
        }
    }
    return_to_prev();
}

// This function displays the "edit directory" menu which can be accessed through the main menu (item 4)
void edit_menu(char menu)
{
    while(1)
    {
        system("cls");
        if(menu=='m')printf("===================================\nTelephone Book  >  Edit directory\n===================================\n");
        else if(menu=='p') printf("======================================================\nTelephone Book  >  Print directory  >  Edit directory\n======================================================\n\n");
        printf("1. Add entry\n2. Modify entry\n3. Delete entry\n4. Return to previous menu\n >\n\n");
        switch(getche())
        {
        case '1':
            system("cls");
            if(menu=='m')printf("=================================================\nTelephone Book  >  Edit directory  >  Add Entry\n=================================================\n\n");
            else if(menu=='p') printf("====================================================================\nTelephone Book  >  Print directory  >  Edit directory  >  Add Entry\n====================================================================\n\n");
            if(count==100) printf("\n\n\tDirectory is full.\n\n");
            else if(load_status) add(menu);
            else if(!load_status) printf("\n\n\tNo file is currently loaded.\n\n");
            return_to_prev();
            continue;
        case '2':
            modify_entry(menu);
            continue;
        case '3':
            delete_entry(menu);
            continue;
        case '4':
            return_to_prev();
            break;
        default:
            continue;
        }
        break;
    }
}

// This function displays the "Print directory" menu which can be accessed through the main menu (item 6)
void print_dir()
{
    char choice;
    printf("===================================\nTelephone Book  >  Print directory\n===================================\n\n");
    if(!load_status) printf("\n\n\tNo file is currently loaded\n\n");
    else
    {
        if(load_status && !count)printf("\n\n\tDirectory is empty.\n\n");
        else if(count)
        {
            while(1)
            {
start_print_dir:
                system("cls");
                printf("===================================\nTelephone Book  >  Print directory\n===================================\n\n");
                if(!strcmp(sort_type,"11")) printf("<%s>:\x1b[32m Sorted by last name (a->z)\n",filename);
                else if(!strcmp(sort_type,"12")) printf("<%s>:\x1b[32m Sorted by last name (z->a)\n",filename);
                else if(!strcmp(sort_type,"21")) printf("<%s>:\x1b[32m Sorted by date of birth (ascendingly)\n",filename);
                else if(!strcmp(sort_type,"22")) printf("<%s>:\x1b[32m Sorted by date of birth (descendingly)\n",filename);
                printf("\x1b[0m");
                printf("-----|----------------------------------------------------------------------------------------------------------|\n");
                printf(" ID  |\t\t\t\t\t\t\tContact\t\t\t\t\t\t\t|\n");
                printf("-----|----------------------------------------------------------------------------------------------------------|\n");
                print(sort_type);
                while(1)
                {
                    printf("\n1. Filter\n2. Edit directory\n3. Return to main menu\n > ");
                    choice=getche();
                    if(choice=='1') break;
                    else if(choice=='2')
                    {
                        edit_menu('p');
                        goto start_print_dir;
                    }
                    else if(choice=='3')
                    {
                        return_to_main();
                        return;
                    }
                    else printf("\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\r");
                }
                printf("\n     ||\n    \\||/\n     \\/\n\n");
                printf("1. Sort by last name\n2. Sort by date of birth\n >");
                *sort_type=getche();
                if(*sort_type=='1')
                {
                    printf("\33[2K\x1b[1A\33[2K\x1b[1A\x1b[19C ----> 1. a->z\n\t\t\t     2. z->a\n\t\t\t      >");
                    sort_type[1]=getche();
                }
                else if(*sort_type=='2')
                {
                    printf("\33[2K\x1b[2A\33[2K\x1b[1B\x1b[22C ----> 1. ascendingly\n\t\t\t\t2. descendingly\n\t\t\t\t >");
                    sort_type[1]=getche();
                }
            }
        }
    }
    return_to_main();
}

//This function handles creating a new directory
void create()
{
    char newfilename[30],altfilename[30],tester[30],num[4];
    int n,invalid=0;
start_create:
    printf("==========================================================\nTelephone Book  >  Create New directory\n==========================================================\n\n");
    printf("New file name (without \".txt\"): ");
    if(invalid)printf("\n\x1b[31m<!> Invalid Entry! \x1b[33mA file name can't contain any of the following characters: \\/<>*\":|\x1b[0m\x1b[1A\x1b[54D");
    gets(newfilename);
    if(!is_valid_fname(newfilename))
    {
        system("cls");
        invalid=1;
        goto start_create;
    }
    else
    {
        if(*newfilename==0)strcpy(newfilename,"New Text Document");
        else
        {
        printf("\33[2K");
        strcpy(altfilename,newfilename);
        if(!(f=fopen(strcat(newfilename,".txt"),"r")))
        {
            f=fopen(newfilename,"w");
            fclose(f);
            load_status=load(newfilename);
            strcpy(filename,newfilename);
            printf("\n\n\tFile has been successfully created. Your directory < %s > is ready to use.\n\n\n",newfilename);
            while(1)
            {
                if(!autosave)printf("1. Return to main menu\n2. Enable autosave\n >");
                else printf("1. Return to main menu\n2. Disable autosave\n >");
                switch(getche())
                {
                case '1':
                    break;
                case '2':
                    printf("\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\r");
                    if(!autosave) autosave=1;
                    else autosave=0;
                    continue;
                default:
                    printf("\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\r");
                    continue;
                }
                break;
            }
        }
        else
        {

            strcpy(tester,newfilename);
            for(n=1; (f=fopen(tester,"r")); n++) ///Loop to automatically rename file to an available name (altfilename)
            {
                strcpy(tester,altfilename);
                strcpy(tester,strcat(tester, itoa(n,num,10) ));
                strcat(tester,".txt");
            }
            fclose(f);
            strcpy(altfilename,tester);
            while(1)
            {
                printf("\n\n<!> A file with this name already exists.\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("1. Overwrite file\n2. Rename\n3. Create \"%s\"\n4. Cancel\n > ",altfilename);
                switch(getche())
                {
                case '1': //Overwrite
                    printf("\33[2K\r\n\x1b[31m<!> Are you sure? All data on < %s > will be deleted.\x1b[0m\n~ Press 1 for Yes \n~ or Press any other key for No\n >",newfilename);
                    if(getche()!='1')
                    {
                        printf("\n\n\tProcess Canceled.\n\n");
                        break;
                    }
                    f=fopen(newfilename,"w");
                    strcpy(filename,newfilename);
                    fclose(f);
                    load_status=load(newfilename);
                    printf("\n\n\33[2KFile has been successfully created. Your directory < %s > is ready to use.\n\n",newfilename);
                    break;
                case '2': //Rename (Go back to the beginning of the function)
                    system("cls");
                    goto start_create;
                    break;
                case '3': //Create file with alternative name (altfilename)
                    f=fopen(altfilename,"w");
                    strcpy(filename,altfilename);
                    load_status=load(altfilename);
                    printf("\n\n\r\33[2K\tFile has been successfully created. Your directory < %s > is ready to use.\n\n",altfilename);
                    break;
                case '4':
                    return_to_main();
                    return;
                default:
                    printf("\n\n\x1b[31m<!> Invalid Entry!\x1b[1A\x1b[0m\x1b[1A\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\x1b[1A\33[2K\r");
                    continue;

                }
                break;
            }
        }}
        return_to_main();
    }
}

