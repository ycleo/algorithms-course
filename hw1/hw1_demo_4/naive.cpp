//Brute Force
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
    //
    //    //step1. calculate company number O(m)
    company_num = CLines(*(argv + 2));
    student_num = CLines(*(argv + 1));
    //                cout << "company_num " << company_num << endl;
    //                    cout << "student_num " << student_num << endl;

/*
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
*/
    //step3. create mixed array O(n)

    struct CS *C;
    C = (struct CS *)malloc(company_num*sizeof(struct CS));
    struct CS *S;
    S = (struct CS *)malloc(student_num*sizeof(struct CS));
    /*
    int total_num = company_num + student_num;
    struct CS total_arr[total_num];
*/
    //step4. read in company.txt O(c*m)
    int i = 0;
    FILE *com_fptr;
    com_fptr = fopen(argv[2], "r");
    while (!feof(com_fptr))
    {
        fscanf(com_fptr, "%d %d %d %d\r\n",
               &(C+i)->id,
               &(C+i)->integrity,
               &(C+i)->score,
               &(C+i)->salary);
        (C+i)->isCom = 1;
        //total_arr[i].desire_salary = 2000;
        //total_arr[i].decision = 0;
        i++;
    }

    //step5. read in student.txt O(c*s)
    i = 0;
    FILE *stud_fptr;
    stud_fptr = fopen(argv[1], "r");
    while (!feof(stud_fptr))
    {
        fscanf(stud_fptr, "%d %d %d\r\n",
               &(S+i)->id,
               &(S+i)->integrity,
               &(S+i)->score);
        (S+i)->isCom = 0;
        (S+i)->salary = 0;
        (S+i)->desire_salary = 0;
        (S+i)->decision = 0;
        i++;
    }
    fclose(com_fptr);
    fclose(stud_fptr);

  
    //step6. sort company by salary O(nlogn)
    SALARY_MERGE_SORT(C, 0, company_num - 1);

    //step7. Brute force O(n^2)
    for (int i = 0; i < student_num; i++)
    {
        int salary_tag = 0;
        int decision_tag = 0;
        for (int j = 0; j < company_num; j++)
        {
            if ((S+i)->integrity >= (C+j)->integrity && (S+i)->score >= (C+j)->score)
            {
                if ((C+j)->salary > salary_tag || (C+j)->salary == salary_tag && (C+j)->id < decision_tag)
                {
                    decision_tag = (C+j)->id;
                    salary_tag = (C+j)->salary;
                }
            }
        }
        (S+i)->decision = decision_tag;
        (S+i)->desire_salary = salary_tag;
    }

    free(C);
    //step8. sort student by id O(nlogn)
    ID_MERGE_SORT(S, 0, student_num - 1);

    //step9. output the file
    FILE *output_fptr;
    output_fptr = fopen(argv[3], "w");

    for (int j = 0; j < student_num; j++)
    {

        char *outstr = new char[20];
        sprintf(outstr, "%d : %d\n", (S+j)->id, (S+j)->decision);
        fputs(outstr, output_fptr);
        delete[] outstr;
    }
    fclose(output_fptr);
    
    free(S);

    end_t = clock();
    printf("%f second\n", (end_t - start_t) / 1000);
    return 0;
}
