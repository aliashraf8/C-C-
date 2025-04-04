#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//STRUCTURE FOR STORING ITEM DETAILS.
typedef struct
{
    char  NAME[30];
    int   QUANTITY;
    float UNIT_PRICE;
    float ITEM_TOTAL;
} item;

//CLEAR MY SCREEN.
void CLEAR_SCREEN()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif   
}

//DECLARING FUNCTION TO PRINT THE BILL IN TERMINAL.
void PRINT_BILL_TERMINAL(item ar[], int x, float S_T, float V, float V_A, float T_A_V);

//DECLARING FUNCTION TO PRINT THE BILL IN .CSV FILE.
void PRINT_BILL_CSV(item ar[], int x, float S_T, float V, float V_A, float T_A_V);

//DECLARING FUNCTION TO PRINT A SEPARATOR BETWEEN BILL DETAILS.
void DIVIDER (void);

//DECLARING FUNCTION TO GET INTEGER INPUT WITH VALIDATION
void GET_INT(int* number);

//DECLARING FUNCTION TO GET STRING INPUT WITH SPACES
void GET_STRING(char* string);

//DECLARING FUNCTION TO GET FLOAT INPUT WITH VALIDATION
void GET_FLOAT(float* number);

int main()
{
    //CLEAR SCREEN BEFORE STARTING PROGRAM.
    CLEAR_SCREEN();

    //DECLARING AN ARRAY OF "ITEMS" WITH LENGTH OF "LENGTH".
    int LENGTH;
     printf("HOW MANY ITEMS IN YOUR BILL : ");
    GET_INT(&LENGTH);  // USING THE NEW FUNCTION WITH PASS BY REFERENCE
    
    item array[LENGTH];

    //DECLARING A FLOAT TO INITIALIZE IT LATER FOR THE SUBTOTAL.
    float Sub_Total = 0;

    //SCANNING VALUES.    
        for(int i = 0; i < LENGTH; i++)
        {
        //PROMPT USER FOR ITEM NAME.
             printf("ITEM -NAME- : ");
            GET_STRING(array[i].NAME);

        //PROMPT USER FOR ITEM QUANTITY.
             printf("ITEM -QUANTITY- : ");
            GET_INT(&array[i].QUANTITY);

        //PROMPT USER FOR ITEM UNIT_PRICE.
             printf("UNIT -PRICE- : ");
            GET_FLOAT(&array[i].UNIT_PRICE);

        //CALCULATING EACH ITEM_TOTAL.  
            array[i].ITEM_TOTAL = array[i].QUANTITY * array[i].UNIT_PRICE;

        //CALCULATING SUB_TOTAL BEFORE -VAT- FOR THE WHOLE BILL. 
            Sub_Total += array[i].ITEM_TOTAL;
        }

    ///SCANNING -VAT- PERCENTAGE.
    float VAT_PERCENTAGE;  
    printf("VAT_PERCENTAGE : ");
    GET_FLOAT(&VAT_PERCENTAGE);

    //SUBTOTAL AFTER VAT.
    float VAT_AMOUNT = (VAT_PERCENTAGE/ 100)* Sub_Total;

    //CALCULATING NET TOTAL.
    float TOTAL = Sub_Total + VAT_AMOUNT;

        PRINT_BILL_TERMINAL (array , LENGTH , Sub_Total , VAT_PERCENTAGE , VAT_AMOUNT ,TOTAL);
        PRINT_BILL_CSV      (array , LENGTH , Sub_Total , VAT_PERCENTAGE , VAT_AMOUNT ,TOTAL);
    }

void PRINT_BILL_TERMINAL(item ar[], int x, float S_T, float V, float V_A, float T_A_V)
    {
        CLEAR_SCREEN();

        DIVIDER();
        //PRINT HEADER ROW FOR TERMINAL PRINTING.
        printf("| %-15s | %5s | %8s | %8s |\n", "ITEM", "QTY", "U_PRICE", "TOTAL");
        DIVIDER();
        //PRINTING ITEMS AND DETAILS IN ROWS FOR EACH ITEM.
        for(int j = 0; j < x; j++)
        {
            printf("| %-15s | %5d | %8.2f | %8.2f |\n",
            ar[j].NAME, ar[j].QUANTITY, ar[j].UNIT_PRICE, ar[j].ITEM_TOTAL);
        }
        DIVIDER();
        //PRINTING THE SUBTOTAL, VAT PERCENTAGE AND AMOUNT, TOTAL. 
        printf("SUBTOTAL : %.2f\nVAT %.1f%% : %.2f \nTOTAL : %.2f\n",
        S_T , V ,V_A, T_A_V);
    }

void PRINT_BILL_CSV(item ar[], int x, float S_T, float V, float V_A, float T_A_V)
    {
        //OPENFILE IN WRITING MODE
        FILE *his = fopen("BILL_HIS.CSV" , "w");
        if(his == NULL)
        {
            printf("CANNOT OPEN FILE");
            return ;
        }

        //PRINT THE HEADER ROW IN .CSV FILE.
        fprintf(his , "ITEM NAME,QUANTITY,UNIT_PRICE,TOTAL");

        //PRINT THE BILL ITEMS (NAMES, QUANTITIES, UNIT_PRICE) IN ROWS.
        for(int z = 0; z < x; z++)
        {
            fprintf(his,"%s,%i,%.2f,%.2f\n",ar[z].NAME,ar[z].QUANTITY,ar[z].UNIT_PRICE,ar[z].ITEM_TOTAL);
        }
        //PRINT THE SUBTOTAL FOR THE TOTALS OF ITEMS.
        fprintf(his,"SUBTOTAL,,,%.2f\n",S_T);

        //PRINT THE VAT PERCENTAGE AND AMOUNT.
        fprintf(his,"VAT_PERCENTAGE%.1f%%,,,%.2f\n", V , V_A);
        
        //PRINT THE TOTAL AFTER THE VAT.
        fprintf(his,"TOTAL,,,%.2f", T_A_V);

        //SAFELY CLOSING THE FILE FOR NON-EXPECTED BEHAVIORS.
        fclose(his);
        printf("BILL SAVED TO BILL_HIS.CSV SUCCESSFULLY.\n");
    }

void DIVIDER (void)
{
    printf("-------------------------------------------------\n");
}

//DEFINITION OF GET_INT FUNCTION
void GET_INT(int* number)
{
    do {
        // PROMPT USER FOR INPUT AND CHECK IF IT'S A VALID INTEGER
        if (scanf("%i", number) != 1) 
        {
            // IF INPUT IS INVALID, DISPLAY ERROR MESSAGE AND CLEAR INPUT BUFFER
            printf("INVALID INPUT. PLEASE ENTER A VALID NUMBER.\n");
            while (getchar() != '\n'); // CLEAR INPUT BUFFER
            continue;
        }
        // CHECK IF THE ENTERED NUMBER IS POSITIVE
        if (*number <= 0 )
        {
            // IF NUMBER IS NOT POSITIVE, DISPLAY ERROR MESSAGE
            printf("PLEASE ENTER A POSITIVE NUMBER.\n");
            continue;
        }
        // BREAK THE LOOP IF INPUT IS VALID AND POSITIVE
        break;
    } while (1); // KEEP ASKING UNTIL VALID INPUT IS PROVIDED
}

//DEFINITION OF GET_STRING FUNCTION
void GET_STRING(char* string)
{
    int c;
    do {
        // CLEAR INPUT BUFFER
        while ((c = getchar()) != '\n' && c != EOF);
        
        // GET INPUT
        if (fgets(string, 16, stdin) == NULL) {
            printf("INVALID INPUT. PLEASE TRY AGAIN.\n");
            continue;
        }
        
        // REMOVE TRAILING NEWLINE IF EXISTS
        string[strcspn(string, "\n")] = 0;
        
        // CHECK IF STRING IS EMPTY
        if (strlen(string) == 0) {
            printf("EMPTY INPUT NOT ALLOWED. PLEASE ENTER A NAME.\n");
            continue;
        }
        
        // IF INPUT WAS TOO LONG, JUST CLEAR THE REST OF INPUT
        if (strchr(string, '\n') == NULL) {
            while ((c = getchar()) != '\n' && c != EOF);
        }
        
        break;
    } while (1);  // KEEP ASKING UNTIL USER ENTERS A VALID INPUT
}

//DEFINITION OF GET_FLOAT FUNCTION
void GET_FLOAT(float* number) {
    do {
        // TRY TO READ A FLOAT NUMBER FROM USER
        if (scanf("%f", number) != 1) 
        {
            // IF INPUT IS INVALID (NOT A NUMBER)
            printf("INVALID INPUT. PLEASE ENTER A VALID NUMBER.\n");
            while (getchar() != '\n'); // CLEAR THE INPUT BUFFER TO PREVENT INFINITE LOOP
            continue;
        }
        // CHECK IF THE NUMBER IS POSITIVE
        if (*number <= 0) 
        {
            printf("PLEASE ENTER A POSITIVE NUMBER.\n");
            continue;
        }
        //SUCCESSFULLY INPUT IS VALID AND POSITIVE
        break;
    } while (1);  // KEEP ASKING UNTIL USER ENTERS A VALID INPUT
}