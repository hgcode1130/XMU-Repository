#include<iostream>

using namespace std;

int main()
{
	string s;
	while (cin >> s)
	{
		int t = s.size();
		bool f = 0;
		if (t < 81 && t > 0) {
			for (int i = 0; i < t / 2; i++)
			{
				if (s[i] != s[t - i - 1])
				{
					f = 1;
					break;
				}
			}
			if (f)
			{
				cout << "不是回文串" << "\n";
			}
			else cout << "是回文串" << "\n";
		}
		else cout << "长度有误" << "\n";
	}
	return 0;
}