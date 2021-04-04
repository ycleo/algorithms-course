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
    CS Left[n1];
    CS Right[n2];
    for (int i = 0; i < n1; i++)
        Left[i] = Arr[s + i];
    for (int j = 0; j < n2; j++)
        Right[j] = Arr[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < n1 && j < n2)
    {
        if (Left[i].integrity <= Right[j].integrity)
        {
            Arr[k] = Left[i];
            i++;
        }
        else
        {
            Arr[k] = Right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Arr[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        Arr[k] = Right[j];
        j++;
        k++;
    }
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
    CS Left[n1];
    CS Right[n2];
    for (int i = 0; i < n1; i++)
        Left[i] = Arr[s + i];
    for (int j = 0; j < n2; j++)
        Right[j] = Arr[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < n1 && j < n2)
    {
        if (Left[i].score <= Right[j].score)
        {
            Arr[k] = Left[i];
            i++;
        }
        else
        {
            Arr[k] = Right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Arr[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        Arr[k] = Right[j];
        j++;
        k++;
    }
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
    CS Left[n1];
    CS Right[n2];
    for (int i = 0; i < n1; i++)
        Left[i] = Arr[s + i];
    for (int j = 0; j < n2; j++)
        Right[j] = Arr[m + 1 + j];

    int i = 0, j = 0, k = s;
    while (i < n1 && j < n2)
    {
        if (Left[i].id <= Right[j].id)
        {
            Arr[k] = Left[i];
            i++;
        }
        else
        {
            Arr[k] = Right[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        Arr[k] = Left[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        Arr[k] = Right[j];
        j++;
        k++;
    }
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

        if (Arr[j].salary > salary_flag && Arr[j].side == 'L' && Arr[j].isCom == 1)
        {
            salary_flag = Arr[j].salary;
            company_id_flag = Arr[j].id;
        }
        else if (Arr[j].desire_salary < salary_flag && Arr[j].side == 'R')
        {
            Arr[j].desire_salary = salary_flag;
            Arr[j].decision = company_id_flag;
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
int CLines(char *filename){
    ifstream RF;
    int n = 0;
    string tmp;
    RF.open(filename, ios::in);
    if(RF.fail())  return 0;
    else{
	while(getline(RF, tmp, '\n'))  n++;
	RF.close();
	return n;
    }
}

int main(int argc, char *argv[])
{
    double start_t, end_t;
    start_t = clock();

    int company_num = 0; //Total number of company: m
    int student_num = 0; //Total number of student: s
    //n = m+s
    
    //step1. calculate company number O(m)
//    int flag = 0;
//    FILE *com_fptr;
//    com_fptr = fopen(argv[2], "r");
    company_num = CLines(*(argv+2));
    student_num = CLines(*(argv+1));
/*    while (!feof(com_fptr))
    {
        flag = fgetc(com_fptr);
        if (flag == '\n')
            company_num++;
    }*/
    cout << "student_num " << student_num << endl;
    cout << "company_num " << company_num << endl;
/*
    int flag = 0;
    //step2. calculate student number O(s)
    FILE *stud_fptr;
    stud_fptr = fopen(argv[1], "r");
    while (!feof(stud_fptr))
    {
        flag = fgetc(stud_fptr);
        if (flag == '\n')
            student_num++;
    }
    cout << "student_num " << student_num << endl;
  */  //step3. create mixed array O(n)
    int total_num = company_num + student_num;
    struct CS total_arr[total_num];

    //step4. read in company.txt O(c*m)
    int i = 0;
    FILE *com_fptr;
    com_fptr = fopen(argv[2], "r");
    while (!feof(com_fptr))
    {
        fscanf(com_fptr, "%d %d %d %d\r\n",
               &total_arr[i].id,
               &total_arr[i].integrity,
               &total_arr[i].score,
               &total_arr[i].salary);
        total_arr[i].isCom = 1;
        //total_arr[i].desire_salary = 2000;
        //total_arr[i].decision = 0;
        i++;
    }

    cout << "i " << i << endl;

    //step5. read in student.txt O(c*s)
    FILE *stud_fptr;
    stud_fptr = fopen(argv[1], "r");
    while (!feof(stud_fptr))
    {
        fscanf(stud_fptr, "%d %d %d\r\n",
               &total_arr[i].id,
               &total_arr[i].integrity,
               &total_arr[i].score);
        total_arr[i].isCom = 0;
        total_arr[i].salary = 0;
        total_arr[i].desire_salary = 0;
        total_arr[i].decision = 0;
        i++;
    }
    cout << "i " << i << endl;
    cout << "total_num " << total_num << endl;
    fclose(com_fptr);
    fclose(stud_fptr);
    /*
    for (int j = 0; j < i; j++)
    {
        printf("CS id: %-3d, isCom: %d, integrity: %3d, score: %3d, salary: %3d, desire_salary: %3d, decision: %d\n",
               total_arr[j].id,
               total_arr[j].isCom,
               total_arr[j].integrity,
               total_arr[j].score,
               total_arr[j].salary,
               total_arr[j].desire_salary,
               total_arr[j].decision);
    }
*/
    //step6. sort all by integrity O(nlogn)
    I_MERGE_SORT(total_arr, 0, total_num - 1);

    //step7. Divide and Conquer method O(nlog^2n)
    DC(total_arr, 0, total_num - 1);

    //step8. sort all by id O(nlogn)
    ID_MERGE_SORT(total_arr, 0, total_num - 1);

    FILE *output_fptr;
    output_fptr = fopen(argv[3], "w");

    for (int j = 0; j < total_num; j++)
    {

        if (total_arr[j].isCom == 0)
        {
            char *outstr = new char[20];
            sprintf(outstr, "%d : %d\n", total_arr[j].id, total_arr[j].decision);
            fputs(outstr, output_fptr);
            delete[] outstr;
        }
    }
    fclose(output_fptr);

    end_t = clock();
    printf("%f second\n", (end_t - start_t) / 1000);
    return 0;
}
