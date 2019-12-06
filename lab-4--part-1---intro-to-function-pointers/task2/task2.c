#include <stdio.h>
#include <stdlib.h>

/* IMPLEMENT ME: Declare your functions here */
int add (int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int division(int a, int b);
int exit_program(int a, int b);
int main ()
{
  
  int user_input, a=4, b = 4;
  int (*func_ptr_arr[])(int, int) = {add, subtract, multiply, division, exit_program}; 
  
	/* IMPLEMENT ME: Insert your algorithm here */
  printf("Operand ‘a’ : 4 | Operand ‘b’ : 4. Specify the operation to perform (0 : add | 1 : subtract | 2 : Multiply | 3 : divide | 4 : Exit  \n");
  scanf("%d", &user_input);
  (*func_ptr_arr[user_input])(a, b);
  
	return 0;

}
/* IMPLEMENT ME: Define your functions here */
int add (int a, int b) { 
  printf ("Adding 'a' and 'b'\n");
  int x=a+b;
  printf("x = %d\n",x);
  return a + b; 
}
int subtract(int a, int b) {
  printf ("Subtracting 'a' and 'b'\n");
  int x=a-b;
  printf("x = %d\n",x);
  return a - b; 
}
int multiply(int a, int b) {
  printf ("Multiplying 'a' and 'b'\n");
  int x=a*b;
  printf("x = %d\n",x);
  return a * b; 
}
int division(int a, int b) {
  printf ("Divding 'a' and 'b'\n");
  int x=a/b;
  printf("x = %d\n",x);
  return a / b; }
int exit_program(int a, int b){
  printf("Exiting Program... \n");
  exit(0);
  return(0);
}