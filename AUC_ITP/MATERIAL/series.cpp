/* Program Series Calculation */

# include <iostream>
using namespace std;

int main()
{
float Sum, Term, F; int K,I;

Sum = 0;
K = 0;

do
{
F = 1;

for (I = 1; I<= K; I++) /* Calculate K! */
F = F * I;

Term = 1/F;   /* Calculate Term as 1/K! */
Sum = Sum + Term;

K++;
}
while (Term > 0.001);

cout << "The value of the series = "<< Sum; 

return (0);
}

