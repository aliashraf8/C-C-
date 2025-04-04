#include<math.h>
#include<stdio.h>
#include<ctype.h>

const int T = 3;
char* T_B_A[] ={"RIGHT", "OBTUSE" ,"ACUTE"};
char* T_B_S[] ={"EQUILATERAL","ISOSCELES","SCEALENE","triangle"};

void  SORT              (float A[]);
float T_AREA            (float A[]);
float T_PERIMETER       (float A[]);
int   TYPE_BY_SIDES     (float A[]);
int   TYPE_BY_ANGELS    (float A[]);
int   CHECKING_VALIDITY (float A[]);
//----------------------------------------------
int main()
{
    float sides[ T ];

    for (int i = 0 ; i < T ; i++)
    {   do
        {//PROMPT USER TO INPUT FOR ONLY POSTIVE NUMBERS.
            printf("SIDE %c " , i+65);//based on ASCI.

            scanf("%f" , &sides[i]);
            if(sides [ i ] <= 0)
            { printf(" please enter postive value\n"); }

        }while (sides [ i ] <= 0);
    }//-------------------------------------------
    SORT(sides);
    //--------------------------------------------
    if(CHECKING_VALIDITY (sides) == 10)
    {
        printf("not a valid triangle\n");
        return 1;}

    int type_BS = TYPE_BY_SIDES(sides);
    int type_BA = TYPE_BY_ANGELS(sides);
    printf("%s %s, %s\n" , T_B_S[type_BS - T] , T_B_A[type_BA - T] ,T_B_S[T] );
    //----------------------------------------------
    printf("Perimeter = %.2f cm\nArea = %.2f cm^2\n"
    , T_PERIMETER( sides ) , T_AREA( sides ) );
}//----------------------------------------------
int   CHECKING_VALIDITY(float A[])
{
    if( A[ 0 ] >= A[ 1 ] + A[ 2 ]
    ||  A[ 1 ] >= A[ 0 ] + A[ 2 ]
    ||  A[ 2 ] >= A[ 1 ] + A[ 0 ] )

    { return 10; }
    else
    { return 11; }}//---------------------------------------------------------------------------
void  SORT(float A[])
{
    for(int j = 0 ; j < T-1 ; j++)
    {
        for(int i = 0 ; i < T-1 ; i++)
        {
            if(A[i] > A[i+1])
            {
                float temp = A[i];
                A[i] = A[i+1];
                A[i+1] = temp;
            }
        }
    }}//------------------------------------------------------------------------
int   TYPE_BY_SIDES(float A[])
{
    if(A[0] == A[1] && A[1] == A[2])
    { return 3; }//EQUILATERAL

    else if (A[0] == A[1] || A[0] == A[2] || A[1] == A[2])
    { return 4; }//ISOSCELES

    else
    { return 5; }}//SCEALENE//--------------------------------------------------
int   TYPE_BY_ANGELS(float A[])
{
    if(pow(A[2],2) == pow(A[0],2) + pow(A[1],2))
    {return 3;}

    else if(pow(A[2],2) > pow(A[0],2) + pow(A[1],2))
    {return 4;}

    else {return 5;}}//---------------------------------------------------------
float T_PERIMETER(float A[])
{
    float sum = 0;
    for (int i = 0 ; i < T ; i++)
    { sum += A[i]; }
    return sum ;}//-------------------------------------------------------------
float T_AREA(float A[])
{
    float perimeter = T_PERIMETER(A);
    float s = perimeter/2;
    float ar = sqrt (s*(s - A[ 0 ])*( s - A[ 1 ])*( s -A[ 2 ])) ;
    return ar;}//----------------------------------------------------------------
