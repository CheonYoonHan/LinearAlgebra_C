#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#pragma warning(disable: 4996)

void eignevector(struct matrix x, double value);
void arrayCopy(double(*dst)[3], double(*src)[3], int n);

//행렬 구조식을 정의한다.
typedef struct matrix{
	double mat[3][3];
}matrix;

void main() {
    matrix x;
    //반복문을 위한 변수 선언
    int i = 0, j = 0, k = 0, l = 0, m = 0;
    int n = 3;

    //배열 값 덧셈을 위한 동적 할당
    double* a, * b, * c;
    a = (double*)malloc(sizeof(double));
    b = (double*)malloc(sizeof(double));
    c = (double*)malloc(sizeof(double));

    // 방정식의 근을 구하기 위한 Double형 변수
    double p, q;
    double D;
    double x1, x2, x3;

    printf(" ****************************************************************\n");
    printf(" **                                                            **\n");
    printf(" **    3차 행렬 고유값과 고유벡터 구하기 201611113 천윤한      **\n");
    printf(" **                                                            **\n");
    printf(" ****************************************************************\n");

    //3차 행렬을 입력받는다.
    printf("3차 행렬을 입력하세요. \n");
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %d x %d 행렬의 값: ", i + 1, j + 1);
            scanf("%lf", &x.mat[i][j]);
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %lf\t", x.mat[i][j]);
        }
        printf("\n");
    }
    ////많은 방법들을 생각해 보았지만 프로그래밍 구현상 가장 쉬운 직접 전개하여 방정식에 대입하는 방법으로 하였습니다.
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
        printf("고유 값은%lf, %lf, %lf 입니다.\n\n", x1, x2, x3);
    }
    else if (D == 0)

    {

        x2 = -*b / (2.0 * *a);



        printf("하나의실근%lf 와중근%lf 입니다.\n", x1, x2);

    }


    eignevector(x, x1);
    eignevector(x, x2);
    eignevector(x, x3);

    printf("\n\n");
    //동적할당해제
    free(a);
    free(b);
    free(c);
}
//고유벡터를 구하는 함수
void eignevector(struct matrix x, double value) {
    int i = 0, j = 0, k = 0, l = 0, n = 3;
    double* x1, * x2, * x3;
    x1 = (double*)malloc(sizeof(double));
    x2 = (double*)malloc(sizeof(double));
    x3 = (double*)malloc(sizeof(double));
    double tem[3];
    double temp[3][3];
    double save = 0.0;
    printf("고유값이 %lf일 때, 고유 벡터 전개\n", value);
    //입력받은 행렬의 값을 임시 저장한다.
    arrayCopy(temp, x.mat, n);
    //대각 행렬에 고유 값을 삽입한다.
    temp[0][0] = temp[0][0] - value;
    temp[1][1] = temp[1][1] - value;
    temp[2][2] = temp[2][2] - value;

    //행렬 왼쪽 하단 사각형을 0으로 만드는 가우스 소거법
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
    //소거한 식을 출력한다.
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf(" %lf\t", temp[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    //x2는 1이라고 가정하고 벡터 출력
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
//배열을 복사하는 함수
void arrayCopy(double(*dst)[3], double(* src)[3], int n) {
    int i = 0, j = 0 ;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            dst[i][j] = src[i][j];
        }
    }
}