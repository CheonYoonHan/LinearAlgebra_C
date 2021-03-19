#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable: 4996)

void eignevector(struct matrix x, double value);
void arrayCopy(double(*dst)[3], double(*src)[3], int n);

//��� �������� �����Ѵ�.
typedef struct matrix{
	double mat[3][3];
}matrix;

void main() {
    matrix x;
    //�ݺ����� ���� ���� ����
    int i = 0, j = 0, k = 0, l = 0, m = 0;
    int n = 3;

    //�迭 �� ������ ���� ���� �Ҵ�
    double* a, * b, * c;
    a = (double*)malloc(sizeof(double));
    b = (double*)malloc(sizeof(double));
    c = (double*)malloc(sizeof(double));

    // �������� ���� ���ϱ� ���� Double�� ����
    double p, q;
    double D;
    double x1, x2, x3;

    printf(" ****************************************************************\n");
    printf(" **                                                            **\n");
    printf(" **    3�� ��� �������� �������� ���ϱ� 201611113 õ����      **\n");
    printf(" **                                                            **\n");
    printf(" ****************************************************************\n");

    //3�� ����� �Է¹޴´�.
    printf("3�� ����� �Է��ϼ���. \n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %d x %d ����� ��: ", i + 1, j + 1);
            scanf("%lf", &x.mat[i][j]);
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %lf\t", x.mat[i][j]);
        }
        printf("\n");
    }
    ////���� ������� ������ �������� ���α׷��� ������ ���� ���� ���� �����Ͽ� �����Ŀ� �����ϴ� ������� �Ͽ����ϴ�.
    *a = (x.mat[0][0] + x.mat[1][1] + x.mat[2][2]) * -1;
    *b = (-(x.mat[0][0] * x.mat[1][1]) - (x.mat[0][0] * x.mat[2][2]) - (x.mat[1][1] * x.mat[2][2]) + (x.mat[1][2] * x.mat[2][1]) + (x.mat[0][1] * x.mat[1][0]) + (x.mat[0][2] * x.mat[2][0])) * -1;
    *c = ((x.mat[0][0] * x.mat[1][1] * x.mat[2][2]) + (x.mat[0][1] * x.mat[2][0] * x.mat[1][2]) + (x.mat[0][2] * x.mat[1][0] * x.mat[2][1]) - (x.mat[0][0] * x.mat[1][2] * x.mat[2][1]) - (x.mat[0][1] * x.mat[1][0] * x.mat[2][2]) - (x.mat[0][2] * x.mat[1][1] * x.mat[2][0])) * -1;

    p = (-*a * *a / 3.0 + *b) / 3.0;
    q = (2.0 * *a * *a * *a / 27.0 - *a * *b / 3.0 + *c) / 2.0;
    D = p * p * p + q * q;

    if (D < 0) {
        x1 = -2.0 * sqrt(-p) * cos(1.0 / 3.0 * atan(sqrt(-D) / q)) - *a / 3.0;
    }

    else if (D == 0) {
        x1 = -2.0 * pow(q, 1.0 / 3.0) - *a / 3.0;
    }

    else{
        if (p < 0) {
            x1 = -pow(q + sqrt(D), 1.0 / 3.0) - pow(q - sqrt(D), 1.0 / 3.0) - *a / 3.0;
        }
        else if (p == 0) {
            x1 = -pow(2.0 * q, 1.0 / 3.0) - *a / 3.0;
        }
        else {
            x1 = pow(-q + sqrt(D), 1.0 / 3.0) - pow(q + sqrt(D), 1.0 / 3.0) - *a / 3.0;
        }
    }

    *c = (*a + x1) * x1 + *b;
    *b = *a + x1;
    *a = 1.0;

    D = *b * *b - 4.0 * *a * *c;

    if (D > 0){
        x2 = (-*b - sqrt(D)) / (2.0 * *a);
        x3 = (-*b + sqrt(D)) / (2.0 * *a);
        printf("���� ����%lf, %lf, %lf �Դϴ�.\n\n", x1, x2, x3);
    }
    else if (D == 0)

    {

        x2 = -*b / (2.0 * *a);



        printf("�ϳ��ǽǱ�%lf ���߱�%lf �Դϴ�.\n", x1, x2);

    }


    eignevector(x, x1);
    eignevector(x, x2);
    eignevector(x, x3);

    printf("\n\n");
    //�����Ҵ�����
    free(a);
    free(b);
    free(c);
}
//�������͸� ���ϴ� �Լ�
void eignevector(struct matrix x, double value) {
    int i = 0, j = 0, k = 0, l = 0, n = 3;
    double* x1, * x2, * x3;
    x1 = (double*)malloc(sizeof(double));
    x2 = (double*)malloc(sizeof(double));
    x3 = (double*)malloc(sizeof(double));
    double tem[3];
    double temp[3][3];
    double save = 0.0;
    printf("�������� %lf�� ��, ���� ���� ����\n", value);
    //�Է¹��� ����� ���� �ӽ� �����Ѵ�.
    arrayCopy(temp, x.mat, n);
    //�밢 ��Ŀ� ���� ���� �����Ѵ�.
    temp[0][0] = temp[0][0] - value;
    temp[1][1] = temp[1][1] - value;
    temp[2][2] = temp[2][2] - value;

    //��� ���� �ϴ� �簢���� 0���� ����� ���콺 �ҰŹ�
    for (j = 0; j <= n - 1; j++) {
        if (temp[j][j] == 0) {
            for (k = j + 1; k <= n - 1; k++) {
                if (temp[k][j] != 0) {
                    for (l = 0; l <= n; l++) {
                        tem[l] = temp[k][l];
                        temp[k][l] = temp[j][l];
                        temp[j][l] = tem[l];
                    }
                    break;
                }
            }
        }
    }
    for (j = 0; j <= n - 1; j++) {
        for (i = j + 1; i <= n - 1; i++) {
            if (temp[i][j] == 0)
                continue;
            else {
                save = temp[i][j] / temp[j][j];
                for (k = 0; k <= n; k++) {
                    temp[i][k] -= temp[j][k] * save;
                }
            }
        }
    }
    //�Ұ��� ���� ����Ѵ�.
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %lf\t", temp[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    //x2�� 1�̶�� �����ϰ� ���� ���
    *x2 = 1;
    *x3 = (-temp[1][1] * *x2) / temp[1][2];
    *x1 = (-temp[0][1] * *x2 - temp[0][2] * *x3) / temp[0][0];
    printf("| %lf |\n", *x1);
    printf("| %lf |\n", *x2);
    printf("| %lf |\n", *x3);
    printf("\n\n");
    free(x1);
    free(x2);
    free(x3);
}
//�迭�� �����ϴ� �Լ�
void arrayCopy(double(*dst)[3], double(* src)[3], int n) {
    int i = 0, j = 0 ;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}