//test
#include <fstream>
#include <iostream>
#include <cstdlib>
#define min 1
#define max 100
#define salary_min 70
#define salary_max 1000
#define size 1000
using namespace std;

void merge(int arr[], int left[], int right[], int s, int m, int e)
{
    int i, j;
    for (i = 0; i <= m - s; i++)
        arr[i] = left[i];
    for (j = 0; j < e - m; j++)
        arr[i + j] = right[j];
}

void split(int arr[], int left[], int right[], int s, int m, int e)
{
    for (int i = 0; i <= m - s; i++)
        left[i] = arr[i * 2];
    for (int i = 0; i < e - m; i++)
        right[i] = arr[i * 2 + 1];
}

void WorstCase(int arr[], int s, int e)
{
    if (s < e)
    {
        int m = s + (e - s) / 2;
        int left[m - s + 1];
        int right[e - m];

        split(arr, left, right, s, m, e);
        WorstCase(left, s, m);
        WorstCase(right, m + 1, e);
        merge(arr, left, right, s, m, e);
    }
}

int main(int argc, char *argv[])
{
    int score[size];
    for (int i = 0; i < size; i++)
        score[i] = i + 1;

    WorstCase(score, 0, size - 1);

    for (int i = 0; i < size; i++)
        cout << score[i] << " ";
    cout << endl;
    FILE *company_fptr;
    company_fptr = fopen(argv[2], "w");
    for (int j = 1; j <= size / 2; j++)
    {
        char *comstr = new char[50];
        int id = j;
        int integrity = j;
        int salary = j * 10;
        sprintf(comstr, "%d %d %d %d\n", id, integrity, score[j - 1], salary);
        fputs(comstr, company_fptr);
        delete[] comstr;
    }

    FILE *student_fptr;
    student_fptr = fopen(argv[1], "w");

    for (int j = size / 2 + 1; j <= size; j++)
    {
        char *studstr = new char[50];
        int id = j;
        int integrity = j;
        sprintf(studstr, "%d %d %d\n", id, integrity, score[j - 1]);
        fputs(studstr, student_fptr);
        delete[] studstr;
    }

    fclose(company_fptr);
    fclose(student_fptr);
    return 0;
}
