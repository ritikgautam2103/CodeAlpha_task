#include <stdio.h>

int main(void) {
    double a, b, result;
    char op;

    printf("===== Basic Calculator =====\n");
    printf("Enter first number: ");
    scanf("%lf", &a);

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%lf", &b);

    switch (op) {
        case '+':
            result = a + b;
            printf("Result = %.2lf\n", result);
            break;

        case '-':
            result = a - b;
            printf("Result = %.2lf\n", result);
            break;

        case '*':
            result = a * b;
            printf("Result = %.2lf\n", result);
            break;

        case '/':
            if (b == 0)
                printf("Error: Division by zero is not allowed.\n");
            else {
                result = a / b;
                printf("Result = %.2lf\n", result);
            }
            break;

        default:
            printf("Invalid operator.\n");
    }

    return 0;
}
