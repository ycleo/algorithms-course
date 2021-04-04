//Brute Force
#include <fstream>
#include <iostream>
#include <cstdlib>
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

//salary sorting function
void SALARY_MERGE(CS Arr[], int s, int e, int m)
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
        if (Left[i].salary >= Right[j].salary)
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
void SALARY_MERGE_SORT(CS Arr[], int s, int e)
{
    if (s < e)
    {
        int m = (s + e) / 2;
        SALARY_MERGE_SORT(Arr, s, m);
        SALARY_MERGE_SORT(Arr, m + 1, e);
        SALARY_MERGE(Arr, s, e, m);
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

int main(int argc, char *argv[])
{
    int company_num = 1; //Total number of company: m
    int student_num = 1; //Total number of student: s
    //n = m+s

    //step1. calculate company number O(m)
    int flag = 0;
    FILE *com_fptr;
    com_fptr = fopen(argv[2], "r");
    while (!feof(com_fptr))
    {
        flag = fgetc(com_fptr);
        if (flag == '\n')
            company_num++;
    }
    flag = 0;

    //step2. calculate student number O(s)
    FILE *stud_fptr;
    stud_fptr = fopen(argv[1], "r");
    while (!feof(stud_fptr))
    {
        flag = fgetc(stud_fptr);
        if (flag == '\n')
            student_num++;
    }

    //step3. create mixed array O(n)
    struct CS company_arr[company_num];
    struct CS student_arr[student_num];
    /*
    int total_num = company_num + student_num;
    struct CS total_arr[total_num];
*/
    //step4. read in company.txt O(c*m)
    int i = 0;
    com_fptr = fopen(argv[2], "r");
    while (!feof(com_fptr))
    {
        fscanf(com_fptr, "%d %d %d %d\r\n",
               &company_arr[i].id,
               &company_arr[i].integrity,
               &company_arr[i].score,
               &company_arr[i].salary);
        company_arr[i].isCom = 1;
        company_arr[i].desire_salary = 0;
        company_arr[i].decision = 0;
        i++;
    }

    //step5. read in student.txt O(c*s)
    i = 0;
    stud_fptr = fopen(argv[1], "r");
    while (!feof(stud_fptr))
    {
        fscanf(stud_fptr, "%d %d %d\r\n",
               &student_arr[i].id,
               &student_arr[i].integrity,
               &student_arr[i].score);
        student_arr[i].isCom = 0;
        student_arr[i].desire_salary = 0;
        student_arr[i].decision = 0;
        i++;
    }
    fclose(com_fptr);
    fclose(stud_fptr);

    double start_t, end_t;
    start_t = clock();
    //step6. sort company by salary O(nlogn)
    SALARY_MERGE_SORT(company_arr, 0, company_num - 1);

    //step7. Brute force O(n^2)
    for (int i = 0; i < student_num; i++)
    {
        int salary_tag = 0;
        int decision_tag = 0;
        for (int j = 0; j < company_num; j++)
        {
            if (student_arr[i].integrity >= company_arr[j].integrity && student_arr[i].score >= company_arr[j].score)
            {
                if (company_arr[j].salary > salary_tag || (company_arr[j].salary == salary_tag && company_arr[j].id < decision_tag))
                {
                    decision_tag = company_arr[j].id;
                    salary_tag = company_arr[j].salary;
                }
            }
        }
        student_arr[i].decision = decision_tag;
        student_arr[i].desire_salary = salary_tag;
    }

    //step8. sort student by id O(nlogn)
    ID_MERGE_SORT(student_arr, 0, student_num - 1);

    //step9. output the file
    FILE *output_fptr;
    output_fptr = fopen(argv[3], "w");

    for (int j = 0; j < student_num; j++)
    {

        char outstr[20];
        sprintf(outstr, "%d : %d\n", student_arr[j].id, student_arr[j].decision);
        fputs(outstr, output_fptr);
    }
    fclose(output_fptr);

    end_t = clock();
    printf("%f second\n", (end_t - start_t) / 1000);
    return 0;
}
