//use 2D ranking concept
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

struct CS
{
    bool isCom; //company or student
    int id;
    int integrity;
    int score;
    int salary;        //company info
    int desire_salary; //student info
    int decision;      //student info
    char side;
};

//integrity sorting function
void I_MERGE(CS Arr[], int s, int e, int m)
{
    int n1 = m - s + 1; //Left[0....n1] = Arr[s...m]
    int n2 = e - m;     //Right[0....n2] = Arr[m+1...e]

    struct CS *Left;
    Left = (struct CS *)malloc(n1 * sizeof(struct CS));
    struct CS *Right;
    Right = (struct CS *)malloc(n2 * sizeof(struct CS));

    //CS Left[n1];
    //CS Right[n2];
    for (int i = 0; i < n1; i++)
        *(Left+i) = Arr[s + i];
    for (int j = 0; j < n2; j++)
        *(Right+j) = Arr[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < n1 && j < n2)
    {
        if ((Left+i)->integrity <= (Right+j)->integrity)
        {
            Arr[k] = *(Left+i);
            i++;
        }
        else
        {
            Arr[k] = *(Right+j);
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Arr[k] = *(Left+i);
        i++;
        k++;
    }
    while (j < n2)
    {
        Arr[k] = *(Right+j);
        j++;
        k++;
    }
    free(Left);
    free(Right);
}
void I_MERGE_SORT(CS Arr[], int s, int e)
{
    if (s < e)
    {
        int m = (s + e) / 2;
        I_MERGE_SORT(Arr, s, m);
        I_MERGE_SORT(Arr, m + 1, e);
        I_MERGE(Arr, s, e, m);
    }
}

//score sorting function
void S_MERGE(CS Arr[], int s, int e, int m)
{
    int n1 = m - s + 1; //Left[0....n1] = Arr[s...m]
    int n2 = e - m;     //Right[0....n2] = Arr[m+1...e]

    struct CS *Left;
    Left = (struct CS *)malloc(n1 * sizeof(struct CS));
    struct CS *Right;
    Right = (struct CS *)malloc(n2 * sizeof(struct CS));

    //CS Left[n1];
    //CS Right[n2];
    for (int i = 0; i < n1; i++)
        *(Left+i) = Arr[s + i];
    for (int j = 0; j < n2; j++)
        *(Right+j) = Arr[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < n1 && j < n2)
    {
        if ((Left+i)->score <= (Right+j)->score)
        {
            Arr[k] = *(Left+i);
            i++;
        }
        else
        {
            Arr[k] = *(Right+j);
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Arr[k] = *(Left+i);
        i++;
        k++;
    }
    while (j < n2)
    {
        Arr[k] = *(Right+j);
        j++;
        k++;
    }
    free(Left);
    free(Right);
}
void S_MERGE_SORT(CS Arr[], int s, int e)
{
    if (s < e)
    {
        int m = (s + e) / 2;
        S_MERGE_SORT(Arr, s, m);
        S_MERGE_SORT(Arr, m + 1, e);
        S_MERGE(Arr, s, e, m);
    }
}

//id sortingh function
void ID_MERGE(CS Arr[], int s, int e, int m)
{
    int n1 = m - s + 1; //Left[0....n1] = Arr[s...m]
    int n2 = e - m;     //Right[0....n2] = Arr[m+1...e]

    struct CS *Left;
    Left = (struct CS *)malloc(n1 * sizeof(struct CS));
    struct CS *Right;
    Right = (struct CS *)malloc(n2 * sizeof(struct CS));

    //CS Left[n1];
    //CS Right[n2];
    for (int i = 0; i < n1; i++)
        *(Left+i) = Arr[s + i];
    for (int j = 0; j < n2; j++)
        *(Right+j) = Arr[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < n1 && j < n2)
    {
        if ((Left+i)->id <= (Right+j)->id)
        {
            Arr[k] = *(Left+i);
            i++;
        }
        else
        {
            Arr[k] = *(Right+j);
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Arr[k] = *(Left+i);
        i++;
        k++;
    }
    while (j < n2)
    {
        Arr[k] = *(Right+j);
        j++;
        k++;
    }
    free(Left);
    free(Right);
}
void ID_MERGE_SORT(CS Arr[], int s, int e)
{
    if (s < e)
    {
        int m = (s + e) / 2;
        ID_MERGE_SORT(Arr, s, m);
        ID_MERGE_SORT(Arr, m + 1, e);
        ID_MERGE(Arr, s, e, m);
    }
}

//Divide and Conquer function (2D concept)
void DC_MERGE(CS Arr[], int start, int mid, int end)
{
    for (int j = start; j < mid + 1; j++)
        Arr[j].side = 'L';
    for (int j = mid + 1; j < end + 1; j++)
        Arr[j].side = 'R';

    S_MERGE_SORT(Arr, start, end);

    int salary_flag = 0;
    int company_id_flag = 0;
    for (int j = start; j < end + 1; j++)
    {
        if (Arr[j].isCom == 1 && Arr[j].side == 'L')
        {
            if (Arr[j].salary > salary_flag || (Arr[j].salary == salary_flag && Arr[j].id < company_id_flag))
            {
                salary_flag = Arr[j].salary;
                company_id_flag = Arr[j].id;
            }
        }
        else if (Arr[j].isCom == 0 && Arr[j].side == 'R')
        {
            if (Arr[j].desire_salary < salary_flag)
            {
                Arr[j].desire_salary = salary_flag;
                Arr[j].decision = company_id_flag;
            }
        }
       
    }
}

void DC(CS Arr[], int start, int end)
{
    if (start >= end)
        return;
    int mid = (start + end) / 2;
    DC(Arr, start, mid);
    DC(Arr, mid + 1, end);
    DC_MERGE(Arr, start, mid, end);
}

int CLines(char *filename)
{
    ifstream RF;
    int n = 0;
    string tmp;
    RF.open(filename, ios::in);
    if (RF.fail())
        return 0;
    else
    {
        while (getline(RF, tmp, '\n'))
            n++;
        RF.close();
        return n;
    }
}

int main(int argc, char *argv[])
{
    int company_num = 0; //Total number of company: m
    int student_num = 0; //Total number of student: s
    //n = m+s

    //step1. calculate number O(n)

    company_num = CLines(*(argv + 2));
    student_num = CLines(*(argv + 1));

    //step3. create mixed array O(n)
    int total_num = company_num + student_num;
    struct CS *X;
    X = (struct CS *)malloc(total_num * sizeof(struct CS));

    //step4. read in company.txt O(c*m)
    int i = 0;
    FILE *com_fptr;
    com_fptr = fopen(argv[2], "r");
    while (!feof(com_fptr))
    {
        fscanf(com_fptr, "%d %d %d %d\r\n",
               &(X + i)->id,
               &(X + i)->integrity,
               &(X + i)->score,
               &(X + i)->salary);
        (X + i)->isCom = 1;
        //(X + i)->desire_salary = 2000;
        //(X + i)->decision = 0;
        i++;
    }

    //step5. read in student.txt O(c*s)
    FILE *stud_fptr;
    stud_fptr = fopen(argv[1], "r");
    while (!feof(stud_fptr))
    {
        fscanf(stud_fptr, "%d %d %d\r\n",
               &(X + i)->id,
               &(X + i)->integrity,
               &(X + i)->score);
        (X + i)->isCom = 0;
        (X + i)->salary = 0;
        (X + i)->desire_salary = 0;
        (X + i)->decision = 0;
        i++;
    }

    fclose(com_fptr);
    fclose(stud_fptr);

    //step6. sort all by integrity O(nlogn)
    I_MERGE_SORT(X, 0, total_num - 1);

    //step7. Divide and Conquer method O(nlog^2n)
    DC(X, 0, total_num - 1);

    //step8. sort all by id O(nlogn)
    ID_MERGE_SORT(X, 0, total_num - 1);

    FILE *output_fptr;
    output_fptr = fopen(argv[3], "w");

    for (int j = 0; j < total_num; j++)
    {

        if ((X + j)->isCom == 0)
        {
            char *outstr = new char[20];
            sprintf(outstr, "%d : %d\n", (X + j)->id, (X + j)->decision);
            fputs(outstr, output_fptr);
            delete[] outstr;
        }
    }
    fclose(output_fptr);
    free(X);

    return 0;
}
