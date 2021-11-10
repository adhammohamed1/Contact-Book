

/// This header file contains all necessary data to work with (structs, global variables, etc..)





// This is a struct for a date
typedef struct
{
    int day;
    int month;
    int year;
} Date;

//This is a struct for a contact
typedef struct
{
    char name[40];
    char lastname[40];
    char mobile_number[40];
    char email[40];
    char address[50];
    Date date_of_birth;

} Contact;



///CONSTANTS

//This is the standard format for saving entries in the file with fprintf
#define standard_format "%s, %s, %d-%d-%d, %s, %s, %s\n"

FILE *f; ///Pointer to file
Contact c[100]; /// Array of entries
int count; /// Number of entries in the file
char filename[30]; /// File name entered by the user
long filesize; ///Size of the file in bytes
int load_status; /// Indicates whether a file is loaded or not
int saved; ///Global variable to determine whether changes done to the directory have been saved or not [saved=1 by default. It only changes to 0 when the directory has been edited]
char sort_type[3]; ///Global variable to indicate how the directory is sorted
int autosave; ///Global variable to determine whether auto save is turned on or off.
char date[30],day[10],month[10],year[10];
