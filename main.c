#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include <conio.h>
#include "func.h"
#include "data.h"

/// This file contains the code of the program's main menu


int main()
{
    autosave=0;
    load_status=0;
    saved=1;
    strcpy(sort_type,"11");
    while(1)
    {
        system("cls");
        printf("===============\nTelephone Book\n===============\n");
        printf("1. Project details\n2. Create new directory\n3. Load directory\n4. Edit directory\n5. Search\n6. Print directory\n7. Save directory\n8. Quit\n >");
        switch(getche())
        {
        case '1': // To "Project details" menu
            system("cls");
            details();
            break;
        case '2':// To "Create new directory" menu
            system("cls");
            create();
            break;
        case '3': // To "Load directory" menu
            system("cls");
            load_menu();
            break;
        case '4': // To "Edit directory" menu
            system("cls");
            edit_menu('m');
            break;
        case '5': // To "Search entry" menu
            system("cls");
            searche();
            break;
        case '6': // To "Print directory" menu
            system("cls");
            print_dir();
            break;
        case '7': // Save all changes
            system("cls");
            save_menu();
            break;
        case '8': // To the exit menu
            system("cls");
            exit_menu();
        }
    }
    return 0;
}
