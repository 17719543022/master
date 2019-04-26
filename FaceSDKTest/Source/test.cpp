#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <array>
#include <algorithm>
#include <iterator>

using namespace std;

void track(int p[][4], int &len)
{
	srand((int)time(0));
	int length = abs(rand())%16 + 1;
	cout << "length: " << length << endl;
	len = length;

	for(int index = 0; index <= length; index++)
	{
		p[index][0] = index*4 + 0;
		p[index][1] = index*4 + 1;
		p[index][2] = index*4 + 2;
		p[index][3] = index*4 + 3;
	}
}

int main()
{
	int size;
	vector<int [4]> vec(16);

	track(vec.data(), size);

	cout << "size: " << size << endl;
	for(int i=0; i<size; i++)
	{
		cout << vec[i][0] << "\t";
		cout << vec[i][1] << "\t";
		cout << vec[i][2] << "\t";
		cout << vec[i][3] << "\t" << endl;
	}
	
	return 0;
}

