#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char* Mn_tms[] = {"",
                "(1). View All Contacts.",
                "(2). Add New Contact.",
                "(3). Search Your Phone Book.",
                "(4). Edit Existing Contact."}; 

typedef struct
{
    char* name;
    char* number;
} cntct;

void INTRO           (void);//THE TEXT FILE WHICH CONTAINS THE INTRO.
void EXIT_CASE       (void);//OPTIONS AFTER FINISHING.
void VIEW_ALL        (FILE* A);//VIEW ALL CONTACTS IN PHONEBOOK.
void ADD_NEW_CONTACT (cntct* b);//TO ADD A NEW CONTACT.
void MENUE           (void);//FUNCTION TO PRINT THE MAIN MENUE OPTIONS AND SERVICES.

int main()
{
    
    FILE* data = fopen("contacts.csv", "r+");
    if (data == NULL)
    {
        printf("error opening .csv data file");
        return 1;
    }
    cntct a = {NULL , NULL};
    
    INTRO();//HEADER OF THE PROGRAME.
    MENUE();//MAIN MENUE.
    int choice = 0;
    scanf("%i", &choice);
    getchar();
    switch (choice)
    {
        case 1://VIEW ALL.
            {
                system("cls");
                VIEW_ALL(data);
                EXIT_CASE(); 
            }
            break;
        
        case 2://ADD NEW CONTACT.
            {
                system("cls");
                printf("%s\n", Mn_tms[choice]);
                ADD_NEW_CONTACT(&a);
                EXIT_CASE();
            }   
            break;
            
        case 3://SEARCH.
            {
                
            }
            break;
            
        default:
            {
                main();//KEEP RUNING THE MAIN FUNCTION IF INPUT != CASE NUMBER.
            } 
        }
        
free(a.name);
free(a.number);
fclose(data);
} 

void INTRO (void)
{
    system("cls");
    FILE* strt = fopen("contacts_intro.txt","r");
    if(strt == NULL)
    {
        printf("Error Opening Intro .txt File");
        return;
    }
    int a;
    while((a = fgetc(strt))!= EOF)
    {
        printf("%c", a);
    }
    printf("\n");
    printf("---------------------------");
    fclose(strt);
}

void ADD_NEW_CONTACT (cntct* b)
{
//--------------------------------------------------------
    b->name = malloc(33);
    b->number = malloc(33);
        if(b->name == NULL || b->number == NULL)
        {
            
            printf("Memory Error Detected");
            free(b->name);
            free(b->number);
            return ;
        }
//--------------------------------------------------------
    printf("enter name  : ");
    fgets(b->name , 33 ,stdin);

        size_t namelen = strlen(b->name);
        if (namelen > 0 && b->name[namelen - 1] == '\n')
        {
            b->name[namelen - 1] = '\0';
        }

    for(size_t j = 0; j < namelen; j++)
    {
        b->name[j] = tolower(b->name[j]);
    }
//------------------------------------------------------
    printf("enter number  : ");
    fgets(b->number , 14 ,stdin);

        size_t numberlen = strlen(b->number);
        if(numberlen > 0 && b->number[numberlen-1] == '\n')
        {
            b->number[numberlen - 1] = '\0';
        }
//-----------------------------------------------------
    printf("%s  %s\n", b->name, b->number);
//-----------------------------------------------------
        int C ;
        printf("Check Your Input Press ""1"" To Save it ""2"" To Re-enter");
        scanf("%i",&C);
        if(C == 1)
        {
            printf("Saved");
        }
        else
        {
            system("cls");
            ADD_NEW_CONTACT(b);
            getchar();
        }
}

void MENUE ()
{
    size_t mn_size = sizeof(Mn_tms)/sizeof(Mn_tms[0]);
    for(size_t m = 0; m < mn_size ; m++)
    {
        printf("%s\n", Mn_tms[m]);
    }
    printf("\n1 >> %i\nENTER PREFERED CHOICE NUMBER THEN PRESS ""ENTER"" >>>  "
    ,mn_size-1);
}

void VIEW_ALL (FILE* A)
{
    printf("%-10s %s\n", "name" , "number");
    char a;
    while((a = getc(A)) != EOF)
    {
        printf("%c", a);
    }
    printf("\n");
}

void EXIT_CASE (void)
{
    printf("\n(1). Main Menue\n(2). Exit The Programe.");
    int e;
    scanf("%i", &e);
        switch(e)
        {
           case 1:
           main();

           case 2:
           system("cls");
           printf("See You Soon");
           return;
        }
}