#include <iostream>
#include <vector>
#include <fstream> //read file
using namespace std;

struct Pool
{
	int cid, sid, sal;
	float g1, g2;
	int result[2];
	bool LR;
};
bool compare_g1(const Pool &l, const Pool &r)
{
	return l.g1 < r.g1;
}
bool compare_g2(const Pool &l, const Pool &r)
{
	return l.g2 < r.g2;
}
bool compare_sid(const Pool &l, const Pool &r)
{
	return l.sid < r.sid;
}
void Combine(vector<Pool> &S, vector<Pool>::iterator first, vector<Pool>::iterator middle, vector<Pool>::iterator last)
{
	cout << "###########" << endl
		 << "進入combine" << endl;
	vector<Pool>::iterator itr = first;
	cout << "左pool" << endl;
	for (; itr <= middle; itr++)
	{
		itr->LR = 0;
		cout << "sid:" << itr->sid << " ,cid:" << itr->cid << " ,g1:" << itr->g1 << " ,g2:" << itr->g2 << " ,sal:" << itr->sal << endl;
		cout << "result:" << itr->result[0] << ' ' << itr->result[1] << endl;
	}
	itr = middle + 1;
	cout << endl
		 << "右pool" << endl;
	for (; itr < last; itr++)
	{
		itr->LR = 1;
		cout << "sid:" << itr->sid << " ,cid:" << itr->cid << " ,g1:" << itr->g1 << " ,g2:" << itr->g2 << " ,sal:" << itr->sal << endl;
		cout << "result:" << itr->result[0] << ' ' << itr->result[1] << endl;
	}
	int record[2] = {0};
	sort(first, last, compare_g2);
	for (itr = first; itr < last; itr++)
	{
		//記錄公司record
		if (itr->LR == 0 && itr->sid == -1)
		{
			if (itr->sal >= record[1] && itr->sal != 0)
			{
				cout << "進入可能更新record record為" << record[0] << ' ' << record[1] << endl;
				if (itr->sal == record[1])
				{
					record[0] = itr->cid < record[0] ? itr->cid : record[0];
					record[1] = itr->cid < record[0] ? itr->sal : record[1];
				}
				else
				{
					record[0] = itr->cid;
					record[1] = itr->sal;
				}
				cout << "現在record為" << record[0] << ' ' << record[1] << endl;
			}
		}
		//學生result
		else if (itr->LR == 1 && itr->cid == -1)
		{
			if (itr->result[1] <= record[1])
			{
				cout << "進入可能更新result" << endl;
				if (itr->result[1] == record[1])
				{
					itr->result[0] = record[0] < itr->result[0] ? record[0] : itr->result[0];
					itr->result[1] = record[0] < itr->result[0] ? record[1] : itr->result[1];
				}
				else
				{
					itr->result[0] = record[0];
					itr->result[1] = record[1];
				}
			}
		}
	}
}
void RankFind(vector<Pool> &S, vector<Pool>::iterator first, vector<Pool>::iterator last)
{
	/*debug::ouput pool
	vector<Pool>::iterator left=first;
	vector<Pool>::iterator right=last;
	cout << "RankFind:"<< last-first<< endl;
	for (; left < right; left++) {
		cout << "sid:"<<left->sid << " ,cid:"<< left->cid << " ,g1:" << left->g1 << " ,g2:" << left->g2 << " ,sal:" << left->sal << endl;
		cout<<"result:"<<left->result[0]<<' '<<left->result[1]<<endl;
	}
	*/
	if (last - first == 1)
		return;
	else
	{
		sort(first, last, compare_g1);
		int splitPos = (last - first - 1) / 2;
		cout << "*********" << first - S.begin() << "****" << last - S.begin() << endl;
		cout << "**************splitPos=" << splitPos << endl;
		RankFind(S, first, first + splitPos + 1);
		RankFind(S, first + splitPos + 1, last);
		Combine(S, first, first + splitPos, last);
		return;
	}
}

int main(int argc, char *argv[])
{
	vector<Pool> pool;

	/* open file and read student and company info*/
	ifstream sfile(argv[1]);
	Pool read_p;
	int sid, sg1, sg2;
	int i = 0;
	while (sfile >> sid >> sg1 >> sg2)
	{
		read_p.cid = -1;
		read_p.sid = sid;
		read_p.g1 = sg1 + 0.01f;
		read_p.g2 = sg2 + 0.01f;
		read_p.sal = -1;
		read_p.result[0] = 0;
		read_p.result[1] = 0;
		pool.push_back(read_p);
		i++;
	}
	sfile.close();

	ifstream cfile(argv[2]);
	int cid, cg1, cg2, sal;
	while (cfile >> cid >> cg1 >> cg2 >> sal)
	{
		read_p.sid = -1;
		read_p.cid = cid;
		read_p.g1 = cg1;
		read_p.g2 = cg2;
		read_p.sal = sal;
		pool.push_back(read_p);
	}
	cfile.close();
	RankFind(pool, pool.begin(), pool.end());
	/*debug::ouput pool
	int pool_total = pool.size();
	cout << "********final result*********"<<pool_total << endl;
	for (int i = 0; i < pool_total; i++) {
		cout << pool[i].sid << ','<< pool[i].cid << ',' << pool[i].g1 << ',' << pool[i].g2 << ',' << pool[i].sal << endl;
		cout<<"result"<<pool[i].sid<<' '<<pool[i].result[0]<<' '<<pool[i].result[1]<<endl;
	}
	*/
	sort(pool.begin(), pool.end(), compare_sid);
	cout << endl
		 << endl
		 << "*********final**********" << endl;
	int num = pool.size();
	for (int i = 0; i < num; i++)
	{
		if (pool[i].cid == -1)
		{
			if (i == num - 1)
				cout << pool[i].sid << " : " << pool[i].result[0];
			else
				cout << pool[i].sid << " : " << pool[i].result[0] << endl;
		}
	}
	ofstream outfile(argv[3]);
	for (int i = 0; i < num; i++)
	{
		if (pool[i].cid == -1)
		{
			if (i == num - 1)
				outfile << pool[i].sid << " : " << pool[i].result[0];
			else
				outfile << pool[i].sid << " : " << pool[i].result[0] << endl;
		}
	}
	outfile.close();
	return 0;
}