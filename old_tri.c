#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------------
// Declaring functions for Circle (CIRCLE_PERIMETER : Perimeter , CIRLCE_AREA : Area).
float CIRCLE_PERIMETER (float A);
float CIRLCE_AREA      (float A);
//-----------------------------------------------------------------------------------
// Declaring functions for Triangle (TRIANGLE_CHECK : check if its a valid ,
//triangle PMT : Perimeter , TRIANGLE_AREA : Area ,  & EQ to check triangle TYPE BY SIDES).
bool  TRIANGLE_CHECK   (float A[]);
float TRIANGLE_AREA    (float A[]);
bool  ISO              (float A[]);
bool  EQ               (float A[]);
float PMT              (float A, float B[]);
//-----------------------------------------------------------------------------------
// Declaring functions for Square && Rectangle (PM4 : Perimeter , AR4 : Area).
float PM4              (float A, float B);
float AR4              (float A, float B);
//-----------------------------------------------------------------------------------
// Declaring functions for 4++ Shape (PMT : Perimeter , TRIANGLE_AREA : ???? ).
float BT4              (float A, float B[]);
//-----------------------------------------------------------------------------------
int main()
{//----------------------------------------------------------------------------------

    FILE *intro = fopen("intro.txt" , "r");
    char a;
    while((a = fgetc(intro)) != EOF)
    {
        printf("%c" , a);
    }
    printf("\n");
    fclose(intro);

//------getting Number of sides.------------------------------------------------------

    int Nsides = get_int("Sides :");

//------for circle.-------------------------------------------------------------------

    if(Nsides == 1 )
    {
       float X = get_float("enter radius in meters: ");
       printf("\nCIRCLE\n Perimeter = %.3f m , AREA: %.3f m^2\n",
       CIRCLE_PERIMETER(X) , CIRLCE_AREA(X)) ;
    }

//---number two (2) or any negative values are not allowed--------------------------
    else if (Nsides < 3 && Nsides != 1 )
    {
        printf("Can Not Calculate please enter postive values \n");
        return 1;
    }

//------------------------------------------------------------------------------------
//for triangle.

    else if (Nsides == 3 )
    {
//------get the sides-----------------------------------------------------------------

        float VS[Nsides];

        for (int v = 0; v < Nsides; v++)
        {
            VS[v] = get_float("legnth in meters : ");
        }
        string cases [4] = {
             "\nVALID ISOSCELES TRIANGLE\n"
            ,"\nVALID EQUILATERAL TRIANGLE\n"
            ,"\nVALID SCALENE TRIANGLE\n"
            ,"please insert valid legnths for a logical triangle\n"};

        if (TRIANGLE_CHECK(VS)== true)
            {
                if(ISO(VS)== true)
                    {
                        printf("%s" ,cases [0]);
                    }
                else if (EQ(VS) == true)
                    {
                        printf("%s" ,cases [1]);
                    }
                else
                    {
                        printf("%s" ,cases [2]);
                    }
                printf("Perimeter = %.3f m , AREA: %.3f m^2 \n",
                PMT(Nsides, VS) , TRIANGLE_AREA( VS ));
            }
        else
            {
                printf("%s" ,cases [3]);
            }
    }
//------for any shape more than 4 sides.--------------------------------------------
    else if( Nsides > 4 )
    {
        float each_side[Nsides];
        for (int e = 0; e < Nsides; e++)
        {
            each_side [e] = get_int("legnth in meters : ");
        }
        printf("Perimeter = %.3f m \n", BT4(Nsides, each_side));

    }
//for squares or rectangles.
    else if (Nsides == 4)
    {
        int X = get_int("Length : ");
        int Y = get_int("width : ");

        if (X == Y)
         {
            printf("\nSQUARE\n");
         }
        else
         {
            printf("\nRectangle\n");
         }
        printf("Perimeter : %.3f , AREA: %.3f \n ", PM4( X , Y) , AR4( X , Y) );
    }
}
//-----------------------------------------------------------------------------------
// Defing functions  for Circle (CIRCLE_PERIMETER : Perimeter).

   float CIRCLE_PERIMETER (float A)
    {
          float Z = ((double)22/7)*2* A ;
          return Z;
    }
//-----------------------------------------------------------------------------------
// Defing functions for Circle ( CIRLCE_AREA : Area).

   float CIRLCE_AREA (float A)
     {
          float Z = ((double)22/7)*( A * A);
          return Z;
     }

//-----------------------------------------------------------------------------------
//Defing function for Triangle (TRIANGLE_CHECK : check for validity by sides).

    bool TRIANGLE_CHECK (float A[])
    {
        if ( A[0] < A[1] + A[2]
          && A[1] < A[0] + A[2]
          && A[2] < A[1] + A[0] )
         {
            return true;
         }
         else
         {
            return false;
         }
      }

//Defing function for Triangle (PMT : Perimeter).
   float PMT (float A, float B[])
     {
         float sum = 0;
         for (int i = 0; i < A; i++)
         {
             sum += B[i];
         }
         return sum;
     }
//Defing function for Triangle (TRIANGLE_AREA : Area).
   float TRIANGLE_AREA (float A [])
     {
       float  D = A[0] + A[1] + A[2];
       double H = D / 2;
       double ar = sqrt( H * ( H - A[0]) * ( H - A[1]) * (H - A[2]));
       return ar ;
     }

    bool ISO (float A [])
    {
    if ((A[0] == A[1] && A[0] != A[2] )
      ||(A[0] == A[2] && A[0] != A[1] )
      ||(A[1] == A[2] && A[1] != A[0] ) )
    {
        return true;
    }
    else{return false;}
    }

    bool EQ (float A[])
     {
        if(A[0] == A[1]
        && A[1] == A[2])
        {
        return true;
        }
        else
        {return false;}
     }

//Defing function for Square && Rectangle (PM4 : Perimeter).
   float PM4 (float A, float B)
     {
         float Z = A * 2 + B * 2;
         return Z;
     }
//Defing function for Square && Rectangle (AR4 : Area).
   float AR4 (float A, float B)
     {
         float G = A * B;
         return G;
     }
//Defing function for Square && Rectangle (BT4 : Perimeter).
   float BT4 (float A , float B[])
     {
         float sum = 0;
         for (int i = 0 ; i < A ; i++)
         {
             sum += B[i];
         }
         return sum;
     }