#include <stdio.h>

#define MAX 10

void readMatrix(int a[MAX][MAX], int rows, int cols, const char *name) {
    int i, j;
    printf("Enter elements of Matrix %s:\n", name);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%s[%d][%d] = ", name, i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void displayMatrix(int a[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++)
            printf("%5d", a[i][j]);
        printf("\n");
    }
}

void addMatrix(int a[MAX][MAX], int b[MAX][MAX],
               int sum[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            sum[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrix(int a[MAX][MAX], int b[MAX][MAX],
                    int product[MAX][MAX],
                    int r1, int c1, int c2) {
    int i, j, k;

    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            product[i][j] = 0;

            for (k = 0; k < c1; k++)
                product[i][j] += a[i][k] * b[k][j];
        }
    }
}

void transpose(int a[MAX][MAX], int t[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            t[j][i] = a[i][j];
}

int main(void) {
    int a[MAX][MAX], b[MAX][MAX];
    int sum[MAX][MAX], product[MAX][MAX], t[MAX][MAX];
    int r1, c1, r2, c2;
    int choice;

    printf("===== Matrix Operations =====\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Transpose\n");
    printf("Choose an operation: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter rows and columns: ");
        scanf("%d %d", &r1, &c1);

        if (r1 <= 0 || r1 > MAX || c1 <= 0 || c1 > MAX) {
            printf("Invalid matrix size.\n");
            return 0;
        }

        readMatrix(a, r1, c1, "A");
        readMatrix(b, r1, c1, "B");

        addMatrix(a, b, sum, r1, c1);

        printf("\nA + B =\n");
        displayMatrix(sum, r1, c1);
    }
    else if (choice == 2) {
        printf("Enter rows and columns of Matrix A: ");
        scanf("%d %d", &r1, &c1);

        printf("Enter rows and columns of Matrix B: ");
        scanf("%d %d", &r2, &c2);

        if (r1 <= 0 || r1 > MAX || c1 <= 0 || c1 > MAX ||
            r2 <= 0 || r2 > MAX || c2 <= 0 || c2 > MAX) {
            printf("Invalid matrix size.\n");
            return 0;
        }

        if (c1 != r2) {
            printf("Matrix multiplication is not possible.\n");
            printf("Number of columns of A must equal rows of B.\n");
            return 0;
        }

        readMatrix(a, r1, c1, "A");
        readMatrix(b, r2, c2, "B");

        multiplyMatrix(a, b, product, r1, c1, c2);

        printf("\nA x B =\n");
        displayMatrix(product, r1, c2);
    }
    else if (choice == 3) {
        printf("Enter rows and columns: ");
        scanf("%d %d", &r1, &c1);

        if (r1 <= 0 || r1 > MAX || c1 <= 0 || c1 > MAX) {
            printf("Invalid matrix size.\n");
            return 0;
        }

        readMatrix(a, r1, c1, "A");
        transpose(a, t, r1, c1);

        printf("\nTranspose of A =\n");
        displayMatrix(t, c1, r1);
    }
    else {
        printf("Invalid choice.\n");
    }

    return 0;
}
