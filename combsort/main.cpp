#include <QCoreApplication>
#include <QTextStream>
#include <math.h>

const int MAXN = 1000;
const int t1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
const int t2[10] = {4, 7, 9, 2, 5, 0, 1, 3, 6, 8};

int comps = 0;
int swaps = 0;
unsigned int sort_time = 0;

void swap (int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void sort (int *A, int N) {
    unsigned int start_time = clock();

    comps = 0;
    swaps = 0;

    int step = N - 1;
    double factor = 1.2473309;

    while (step >= 1) {
        for (int i = 1; i + step < N; ++i) {
            comps++;
            if (A[i] > A[i + step]) {
                swap(&A[i], &A[i + step]);
                swaps++;
            }
        }
        step /= factor;
    }

    for (int i = 1; i < N; i++) {
        int x = A[i];
        int j;
        for (j = i; j > 0; j--) {
            comps++;
            if (!(A[j-1] > x)) {
                break;
            }
            A[j] = A[j-1];
            swaps++;
        }
        A[j] = x;
    }
    sort_time = clock() - start_time;
}

int main()
{
    QTextStream cout(stdout);
    QTextStream cin(stdin);

    int A[MAXN];
    int N;

    int option = 0;
    cout << QString("Введите 1: массив <9, 8, 7, 6, 5, 4, 3, 2, 1, 0>") << endl;
    cout << QString("Введите 2: массив <4, 7, 9, 2, 5, 0, 1, 3, 6, 8>") << endl;
    cout << QString("Введите 3: массив из 100 случайных чисел") << endl;
    cout << QString("Введите 4: массив из 1000 случайных чисел") << endl;
    cin >> option;

    srand(time(NULL));

    switch (option)
    {
        case 1:
            N = 10;
            for (int i = 0; i < N; i++) A[i] = t1[i];
            break;

        case 2:
            N = 10;
            for (int i = 0; i < N; i++) A[i] = t2[i];
            break;

        case 3:
            N = 100;
            for (int i = 0; i < N; i++) A[i] = rand() % 100;
            break;

        case 4:
            N = 1000;
            for (int i = 0; i < N; i++) A[i] = rand() % 1000;
            break;

        default:
            cout << QString("Неверное значение") << endl;
            return 1;
    }

    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    cout << QString("\nсортировка...\n") << endl;

    sort(A, N);

    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;

    cout << QString("\nСравнений: ") << comps << endl;
    cout << QString("Перестановок: ") << swaps << endl;
    cout << QString("Время выполнения: ") << sort_time << QString("мс") << endl;

    return 0;
}
