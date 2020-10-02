#include<stdio.h>
#include<conio.h>
int main(void)
{

    float a,b,result;
    char operator;
     printf("Enter the operator:");
    scanf("%c",&operator);
    printf("Enter the 1st number:");
    scanf("%f",&a);
    printf("Enter the 2nd number:");
    scanf("%f",&b);
    switch(operator)
    {
        case '+':result=a+b;
                    break;
        case '-':result=a-b;
                    break;
        case '*':result=a*b;
                    break;
        case '/':result=a/b;
                    break;
        default:printf("PLEASE ENTER A CORRECT OPERATOR!");
                    break;
    }
    printf("The result is:%f",result);
    return 0;
}
