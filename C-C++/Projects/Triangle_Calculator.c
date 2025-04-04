#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//USING THE #DEFINE FOR USING THE NUMBER OF ELEMENTS FOR THE TRIANGLE.
#define T 3

//ARRAY CONTAINS THE THREE LOGICAL TYPES FOR THE TRINAGLE BY ANGELS.
char* T_B_A[] ={"RIGHT","OBTUSE","ACUTE"};

//ARRAY CONTAINS THE THREE LOGICAL TYPES FOR THE TRINAGLE BY SIDES.
char* T_B_S[] ={"EQUILATERAL","ISOSCELES","SCEALENE","triangle"};
//-----------------------------------------------------------------
void  INTRO             (void);// FUNCTION PRINTS THE INTRODUCTION FOR THE PROGRRAM.
int   CHECKING_VALIDITY (float SIDES[]);//FUNCTION CHECKS IF THE TRIANGLE HAS VALID LENGTHS.
void  SORT              (float SIDES[]);//FUNCTION SORTING THE THREE ELEMENTS TO GET THE LONGEST AND THE SHORTEST.
float T_PERIMETER       (float SIDES[]);//FUNCTION TO CALCULATE TRIANGLE PERIMETER.
float T_AREA            (float SIDES[]);//FUNCTION TO CALCULATE TRIANGLE AREA.
int   TYPE_BY_SIDES     (float SIDES[]);//FUNCTION RERTURNS THE TRIANGLE TYPE BY SIDES.
int   TYPE_BY_ANGELS    (float SIDES[]);//FUNCTION RERTURNS THE TRIANGLE TYPE BY ANGLES.
void  HISTORY_CSV       (float S[], float P, float SIDES, int TBS, int TBA);//PRINTS HISTORY FOR CACULATED TRIANGLES.

int main()
{
//PROGRAM INTRODUCTION.
    INTRO();
//IMPLEMNTING AN ARRAY OF FLOATS FOR SIDES AND INTIALIZING IT. 
    float sides[ T ];

    //LOOP TO GET THE THREE SIDES OF THE TRIANGLE FROM USER
    for (int i = 0 ; i < T ; i++)
    {   
        int valid_input = 0;
        do
        {
            //PROMPT USER TO ENTER SIDE LENGTH
            printf("Enter length of side %c: ", i + 65);
            
            //CLEAR INPUT BUFFER TO REMOVE ANY LEFTOVER CHARACTERS
            while (getchar() != '\n');
            
            //CHECK IF INPUT IS A VALID NUMBER
            if (scanf("%f", &sides[i]) != 1) {
                printf("Error: Please enter a valid number\n");
                continue;
            }
            
            //CHECK IF THE ENTERED NUMBER IS ZERO
            if (sides[i] == 0) {
                printf("Error: Side length cannot be zero\n");
                continue;
            }
            
            //CONVERT TO ABSOLUTE VALUE USING FABS FOR FLOATING POINT NUMBERS
            sides[i] = fabs(sides[i]);
            
            //SET FLAG TO INDICATE VALID INPUT
            valid_input = 1;
        }
        //CONTINUE LOOP UNTIL VALID INPUT IS RECEIVED
        while (!valid_input);
    }

//ERROR MSG IF SIDES ARE INVALID ACCORDING TO TRIANGLE RULES.
    if(CHECKING_VALIDITY (sides) == 10)
    {
        printf("not a valid triangle\n");
        return 1;
    }

//SORTING SIDES FOR GETTING THE LARGEST SIDE.
    SORT(sides);

//CALCULATING AREA.
 float area = T_AREA( sides );
//CALCULATING PERIMETER.
 float perimeter = T_PERIMETER( sides );
//CHECKING THE TRINAGLE TYPE BY SIDES.
 int type_BS = TYPE_BY_SIDES  (sides);
//CHECKING THE TRINAGLE TYPE BY ANGELS.
 int type_BA = TYPE_BY_ANGELS (sides);

printf("%s %s, %s\n" , T_B_S[type_BS - T ] , T_B_A[type_BA - T ] ,T_B_S[ T ] );
printf("Perimeter = %.2f cm\nArea = %.2f cm^2\n", perimeter , area );

//SAVING HISTORY FOR VALID TRIANGLES IN .CSV FILE.
HISTORY_CSV(sides,perimeter,area,type_BS,type_BA);
}
//END OF MAIN------------------------------------------------------

int CHECKING_VALIDITY(float SIDES[])//CHECKING ACCORDING TRIANGLE RULES.
{
    if( SIDES[ 0 ] >= SIDES[ 1 ] + SIDES[ 2 ]
    ||  SIDES[ 1 ] >= SIDES[ 0 ] + SIDES[ 2 ]
    ||  SIDES[ 2 ] >= SIDES[ 1 ] + SIDES[ 0 ] )

    { return 10; }//IF VALUES ARE INVALID.

    else

    { return 11; }//IF VALID VALUES.
}
//------------------------------------------------------------
void  SORT(float SIDES[]) //SORTING THE SIDES WITH BUBBLE SORT.(NO NEED FOR MORE ADVANCED ALGORITHM).
{
    for(int j = 0 ; j < T-1 ; j++)
    {
        for(int i = 0 ; i < T-1 ; i++)
        {
            if(SIDES[i] > SIDES[i+1])
            {
                float temp = SIDES[i];
                SIDES[i] = SIDES[i+1];
                SIDES[i+1] = temp;
            }
        }
    }
}//------------------------------------------------------------------------
int TYPE_BY_SIDES(float SIDES[]) //RETURN SIDES SPCEFIC VALUE TO LET THE MAIN FUNCTION FIND THE TYPE.
{
    if(SIDES[0] == SIDES[1] && SIDES[1] == SIDES[2])
    { return 3; }//EQUILATERAL.

    else if (SIDES[0] == SIDES[1] || SIDES[0] == SIDES[2] || SIDES[1] == SIDES[2])
    { return 4; }//ISOSCELES.

    else
    { return 5; }//SCEALENE
}
//--------------------------------------------------
int TYPE_BY_ANGELS(float SIDES[])///RETURN SIDES SPCEFIC VALUE TO LET THE MAIN FUNCTION FIND THE TYPE.
{
    if(pow(SIDES[2],2) == pow(SIDES[0],2) + pow(SIDES[1],2))
    {return 3;}

    else if(pow(SIDES[2],2) > pow(SIDES[0],2) + pow(SIDES[1],2))
    {return 4;}

    else {return 5;}
}
//---------------------------------------------------------
float T_PERIMETER(float SIDES[])//CALCULATING PERIMEETER.
{
    float sum = 0;
    for (int i = 0 ; i < T ; i++)
    { sum += SIDES[i]; }
    return sum ;
}
//-------------------------------------------------------------
float T_AREA(float SIDES[])//CALCULATING AREA.
{
    float perimeter = T_PERIMETER(SIDES);
    float s = perimeter/2;
    float ar = sqrt (s*(s - SIDES[ 0 ])*( s - SIDES[ 1 ])*( s -SIDES[ 2 ])) ;
    return ar;
}
//----------------------------------------------------------------
void INTRO (void)//PRINTS ON THE SCREEN THE INTRODUCTION WRIITEN IN .TXT FILE.
{
    FILE* file = fopen("intro.txt" , "r");
        if(file == NULL)
        {
            printf("can not open file");
            return;
        }
        char a;
        while((a = fgetc(file)) != EOF)
        {
            printf("%c" , a);
        }
        printf("\n");
        fclose(file);
}
//--------------------------------------------------------------
//PRINTS THE HISTORY FOR VALID CALCULATED TRIANGELES.
void HISTORY_CSV(float S[], float P, float SIDES,int TBS, int TBA)
{
    FILE*his = NULL;
    his = fopen("history.csv", "a");
    
    fprintf(his,"%.2f,%.2f,%.2f,%.2f,%.2f,%s,%s\n"
    ,S[0],S[1],S[2],P , SIDES ,T_B_S[TBS - T] , T_B_A[TBA - T]);
    fclose(his);
}