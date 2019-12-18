#include<limits>
#include<iostream>

using namespace std;

int add(const string&str, int& pos, int sum, int mul, int& error);
int mult(const string&str, int& pos, int sum, int mul, int& error);
int div(const string&str, int& pos, int sum, int mul, int& error);
int sub(const string&str, int& pos, int sum, int mul, int& error);

int toint(const string&str, int& pos, int & error) {
	int flag = 0;
	string numax = to_string(numeric_limits<int>::max());
	string numin = to_string(numeric_limits<int>::min());
	int deg = 0;
	deg = numax.length();
	while (str[pos] == '-') {
		pos++;
		flag++;
	}
	if (pos == str.length()) {
		error = 1;
		return -1;
	}
	int num = 0;
	int len = 0;
	bool bigger = false;
	if (flag % 2 == 0)
		flag = 1;
	else
		flag = -1;
	while (str[pos] != ' ' and str.length() != pos) {
		if (str[pos] < '0' or str[pos] > '9'){
			error = 2;
			return -1;
		}
		if ((str[pos] > numax[len] and flag == 1) or str[pos] > numin[len+1])
			bigger = true;
		len++;
		if (len > deg or (len == deg and bigger)) {
			error = 3;
			return -1;
		}
		num = num*10 + flag*(str[pos] - '0');
		pos++;
	}
	if (str[pos - len] == ' ') {
		error = 1;
		return 0;
	}
	return num;
}

int mult(const string&str,int& pos,int sum,int mul, int& error) {
	int a = toint(str,pos, error);
	if (error != 0) {
		return -1;
	}
	if (pos == str.length()) {
		return sum + mul*a;
	}
	if (pos+3 > str.length()) {
		error = 2;
		return -1;
	}
	if (str[pos] == ' ' and str[pos+2] == ' ') {
		if (str[pos+1] == '+') {
			pos = pos+3;
			int ans = add(str, pos, sum+a*mul, 0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '-') {
			pos = pos+3;
			int ans = sub(str,pos, sum+a*mul,0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '*') {
			pos = pos + 3;
			int ans = mult(str, pos,sum,a*mul, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '/') {
			pos = pos + 3;
			int ans = div(str, pos,sum,a*mul, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else {
			error = 4;
			return -1;
		}
	}
	error = 2;
	return -1;
}
int add(const string&str,int& pos,int sum,int mul, int& error) {
	int a = toint(str,pos, error);
	if (error != 0) {
		return -1;
	}
	if (pos == str.length()) {
		return sum + a;
	}
	if (pos+3 > str.length()) {
		error = 2;
		return -1;
	}
	if (str[pos] == ' ' and str[pos+2] == ' ') {
		if (str[pos+1] == '+') {
			pos = pos+3;
			int ans = add(str, pos, sum+a, 0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '-') {
			pos = pos+3;
			int ans = sub(str,pos, sum+a,0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '*') {
			pos = pos + 3;
			int ans = mult(str, pos,sum,a, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '/') {
			pos = pos + 3;
			int ans = div(str, pos,sum,a, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else {
			error = 4;
			return -1;
		}
	}
	error = 2;
	return -1;
}
int sub(const string&str,int& pos,int sum,int mul, int & error) {
	int a = toint(str,pos, error);
	if (error != 0) {
		return -1;
	}
	if (pos == str.length()) {
		return sum - a;
	}
	if (pos+3 > str.length()) {
		error = 2;
		return -1;
	}
	if (str[pos] == ' ' and str[pos+2] == ' ') {
		if (str[pos+1] == '+') {
			pos = pos+3;
			int ans = add(str, pos, sum-a, 0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '-') {
			pos = pos+3;
			int ans = sub(str,pos, sum-a,0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '*') {
			pos = pos + 3;
			int ans = mult(str, pos,sum,-a, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '/') {
			pos = pos + 3;
			int ans = div(str, pos,sum,-a, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else {
			error = 4;
			return -1;
		}
	}
	error = 2;
	return -1;
}
int div(const string&str,int& pos,int sum,int mul, int& error) {
	int a = toint(str,pos, error);
	if (error != 0) {
		return -1;
	}
	if (a == 0) {
		error = 5;
		return -1;
	}
	if (pos == str.length()) {
		return sum + mul/a;
	}
	if (pos+3 > str.length()) {
		error = 2;
		return -1;
	}
	if (str[pos] == ' ' and str[pos+2] == ' ') {
		if (str[pos+1] == '+') {
			pos = pos+3;
			int ans = add(str, pos, sum+mul/a, 0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '-') {
			pos = pos+3;
			int ans = sub(str,pos, sum+mul/a,0, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '*') {
			pos = pos + 3;
			int ans = mult(str, pos,sum,mul/a, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else if (str[pos+1] == '/') {
			pos = pos + 3;
			int ans = div(str, pos,sum,mul/a, error);
			if (error != 0) 
				return -1;
			else
				return ans;
		}
		else {
			error = 4;
			return -1;
		}
	}
	error = 2;
	return -1;
}
int start(const string&str, int& error) {
	int pos = 0;
	int a = toint(str,pos, error);
	if (error != 0)
		return -1;
	if (pos == str.length()) {
		return a;
	}
	if (pos+3 > str.length()) {
		error = 2;
		return -1;
	}
	if (str[pos] == ' ' and str[pos+2] == ' ') {
		if (str[pos+1] == '+') {
			pos = pos+3;
			int ans = add(str, pos,a,0, error);
			if (error != 0)
				return -1;
			return ans;
		}
		else if (str[pos+1] == '-') {
			pos = pos+3;
			int ans = sub(str, pos,a,0, error);
			if (error != 0)
				return -1;
			return ans;
		}
		else if (str[pos+1] == '*') {
			pos = pos + 3;
			int ans = mult(str, pos,0,a, error);
			if (error != 0)
				return -1;
			return ans;
		}
		else if (str[pos+1] == '/') {
			pos = pos + 3;
			int ans = div(str, pos,0,a, error);
			if (error != 0) 
				return -1;
			return ans;
		}
		else {
			error = 4;
			return -1;
		}
	}
	error = 2;
	return -1;
}
;
int main(int argc, char** argv)
{
	if (argc == 1) {
		cout << "there is no argument";
		return -1;
	}

	string str(argv[1]);
	if (argc > 2) {
		for (int i = 2; i<argc;i++) {
			str = str + ' ' + argv[i];
		}
	}
	//cout << str << endl;
	//getline(cin,str,'\n');
	int error = 0;
	int answer = start(str,error);
	switch(error)
	{
		case 0:
			cout << answer;
			break;
		case 1:
			cout << "there is a number missing";
			break;
		case 2:
			cout << "wrong input";
			break;
		case 3:
			cout << "too big number";
			break;
		case 4:
			cout << "can't recognize the operation";
			break;
		case 5:
			cout << "division by zero";
			break;
	}
	return 0;
}