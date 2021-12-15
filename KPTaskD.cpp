#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pers 
{
	int id;
	int scan = 1;
	float min_n_a = 3.402823466E38;
	float max_n_a = 0;
	float delta = max_n_a - min_n_a;
	
Pers(int id, float n_a){
this->id = id;
if (this->min_n_a > n_a) this->min_n_a = n_a;
if (this->max_n_a < n_a) this->max_n_a = n_a;
};

};

int main () {
	int N, time, id;
	vector<Pers> A;
	vector<int> d;
	float a, s, u, f, n_a;
	cin >> N;
	for (int j = 0; j < N; j++) 
	{
		cin >> time >> id >> a >> s >> u >> n_a >> f;
		bool b = false;
		for (int i = 0; i < A.size(); i++) 
		{
			if (id == A[i].id) {
			A[i].scan++;
			if (n_a < A[i].min_n_a) A[i].min_n_a = n_a;
			if (n_a > A[i].max_n_a) A[i].max_n_a = n_a;
			b = true;
			A[i].delta = A[i].max_n_a - A[i].min_n_a;
		}
	}
	if (!b) 
	{
	Pers p(id, n_a);
	A.push_back(p);
	}
	}

	float min_delta = 3.402823466E38;
	int i_id, min_id = -1;
	for (int i = 0; i < A.size(); i++) 
	{
		if ((A[i].scan > 1) && (A[i].delta < min_delta)) 
		{
		min_id = A[i].id;
		min_delta = A[i].delta;
		i_id = i;
		}
	}
	A.erase(A.begin() + i_id);
	d.push_back(min_id);

	if (min_id != -1)
	{
		min_id = -1;
		min_delta = 3.402823466E38;
		for (int i = 0; i < A.size(); i++) 
		{
			if ((A[i].scan > 1) && (A[i].delta < min_delta)) 
			{
				min_id = A[i].id;
				min_delta = A[i].delta;
				i_id = i;
			}
		}
		A.erase(A.begin() + i_id);
		if (min_id != -1) d.push_back(min_id);
		}

	if (min_id != -1)
	{
		min_id = -1;
		min_delta = 3.402823466E38;
		for (int i = 0; i < A.size(); i++) 
		{
			if ((A[i].scan > 1) && (A[i].delta < min_delta)) 
			{
			min_id = A[i].id;
			min_delta = A[i].delta;
			i_id = i;
			}
		}
		A.erase(A.begin() + i_id);
		if (min_id != -1) d.push_back(min_id);
	}
sort(d.begin(), d.end());
for (int i = 0; i < d.size(); i++) 
{
cout << d[i] << " ";
}

return 0;}