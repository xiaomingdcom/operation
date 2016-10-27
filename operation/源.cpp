#include <stdio.h>
#include <cstdlib>
#include<iostream>
using namespace std;
void add(char*num1, char*num2, char*result, int len1, int len2);
int sub(char*num1, char*num2, char*result, int len1, int len2);
void mul(char*num1, char*num2, char*result, int len1, int len2);
void muln1(char*num1, char*num2, int j, char*result, int len1, int len2);
void div1(char*res, char*num2, int len2, char*result, int k, char*remainder);
void div(char*num1, char*num2, char*result, char*remainder, int len1, int len2);
int check(char*num);//检查是否有错并返回数组长度
void copy(char*num1, char*num2, int len);
void adjust(char*num, int len, int len1);//调整长度位len1的数组到len，前位补0
int throwaway0(char*result, int len);//丢掉多余的0，返回之后长度，最后补'\0'

int check(char*num)
{
	int i = 0;
	for (i = 0; i <= 100000; i++) {
		if (num[i] == '\0') {
			return i;
		}
		else {
			if (num[i] > '9' || num[i] < '0') {
				printf("error0\n");
				return 0;//错误
			}
		}
	}
}

void adjust(char*num, int len, int len1)
{
	int i = 0;
	for (i = 0; i <= len1; i++) {
		num[len - i] = num[len1 - i];//'\0'也转移
	}
	for (i = 0; i < len - len1; i++) {
		num[i] = '0';
	}
}

int throwaway0(char*result, int len)
{
	int i = 0;
	int j = 0;
	for (j = 0; result[j] == '0'; j++);
	if (j != 0 && len != 1) {
		for (i = j; i <= len; i++) {
			result[i - j] = result[i];//'\0'也转移
		}
	}
	len = len - j;
	return len;
}

void add(char*num1, char*num2, char*result, int len1, int len2) //加法
{
	int i = 0;
	int jinwei = 0;
	int test = 0;
	int len = 0;
	if (len1 >= len2)
	{
		len = len1;
		adjust(num2, len1, len2);
	}
	else
	{
		len = len2;
		adjust(num1, len2, len1);
	}
	for (i = len - 1; i >= 0; i--) {
		test = num1[i] + num2[i] + jinwei - 96;
		if (test >= 10)
		{
			test = test - 10;
			jinwei = 1;
		}
		else
			jinwei = 0;
		result[i] = test + 48;
	}
	if (jinwei == 1) {
		for (i = 0; i < len; i++) {
			result[len - i] = result[len - i - 1];
		}
		result[0] = '1';
		result[len + 1] = '\0';
	}
	else
		result[len] = '\0';
}

int sub(char*num1, char*num2, char*result, int len1, int len2)//减法
{
	int i = 0;
	int jiewei = 0;
	int test = 0;
	int len = 0;
	int sign = 0;
	if (len1 > len2)
	{
		len = len1;
		sign = 1;
		adjust(num2, len, len2);
	}
	else {
		if (len1 == len2) {
			for (i = 0; i < len1; i++) {
				if (num1[i] < num2[i]) {
					sign = -1;
					len = len2;
					break;
				}
				else {
					if (num1[i] > num2[i]) {
						sign = 1;
						len = len1;
						break;
					}
				}
			}
			if (i == len1) {
				sign = 0;
				result[0] = '0';
				result[1] = '\0';
				return 0;
			}
		}
		else {
			sign = -1;
			len = len2;
			adjust(num1, len, len1);
		}
	}
	for (i = len - 1; i >= 0; i--) {
		if (sign == 1) {
			test = num1[i] - num2[i] + jiewei;
		}
		else {
			test = num2[i] - num1[i] + jiewei;
		}
		if (test < 0) {
			test = 10 + test;
			jiewei = -1;
		}
		else {
			jiewei = 0;
		}
		result[i] = test + 48;
	}
	result[len] = '\0';
	len = throwaway0(result, len);//可优化
	if (sign == -1) {
		for (i = 0; i <= len; i++) {//'\0'
			result[len - i + 1] = result[len - i];
		}
		result[0] = '-';
	}
	return sign;
}

void muln1(char*num1, char*num2, int j, char*result, int len1, int len2) {//n位于1位相乘
	int i = 0;
	int test = 0;
	int jinwei = 0;
	for (i = 0; i < len2 - 1 - j; i++) {
		result[len1 + 1 + i] = '0';
	}
	result[len1 + len2 - j] = '\0';
	for (i = len1; i > 0; i--) {
		test = (num1[i - 1] - 48) * (num2[j] - 48) + jinwei;
		jinwei = test / 10;
		test = test % 10;
		result[i] = test + 48;
	}
	if (jinwei>0) {
		result[0] = jinwei + 48;
	}
	else {
		result[0] = '0';
	}
}

void mul(char*num1, char*num2, char*result, int len1, int len2) {
	int i = 0;
	int test = 0;
	int len = 1;
	char lre[100000];//2
	lre[0] = '0';
	lre[1] = '\0';
	result[0] = '0';
	result[1] = '\0';
	muln1(num1, num2, len2 - 1, result, len1, len2);
	len = len1 + 1;
	for (i = len2 - 2; i >= 0; i--) {
		muln1(num1, num2, i, lre, len1, len2);
		add(result, lre, result, len, len + 1);
		len = len + 1;
	}
	throwaway0(result, len);
}

void copy(char*num1, char*num2, int len2) {
	int i = 0;
	for (i = 0; i < len2; i++) {
		num1[i] = num2[i];
	}
	num1[i] = '\0';
}

void div1(char*res, char*num2, int len2, char*result, int k, char*remainder) {//res:len2+1，remainder:len2+1
	int i = 0;
	int l = 0;
	int j = 1;
	int len = 0;
	for (i = 0; i <= 9; i++) {
		for (l = 0; l <= len2; l++) {
			remainder[l] = res[l + 1];
		}
		j = sub(res, num2, res, len2, len2);
		adjust(res, len2, check(res));
		if (j == 0) {
			i++;
			for (l = 0; l <= len2; l++) {
				remainder[l] = res[l + 1];
			}
			break;
		}
		else {
			if (j == -1) {
				break;
			}
		}
	}
	result[k] = i + 48;
	result[k + 1] = '\0';
}

void div(char*num1, char*num2, char*result, char*remainder, int len1, int len2) {
	int i = 0;
	int j = 0;
	int jiewei = 0;
	int test = 0;
	//int len = len2;
	char res[100000];
	result[0] = '\0';
	remainder[0] = '\0';
	if (len1 <= len2) {
		adjust(num1, len2 + 1, len2);
		adjust(num2, len2 + 1, len2);
		div1(num1, num2, len2 + 1, result, 0, remainder);
	}
	else {
		adjust(num2, len2 + 1, len2);
		for (i = 0; i < len2; i++) {
			res[i + 1] = num1[i];
		}
		res[0] = '0';
		res[len2 + 1] = '\0';
		for (i = 1; len1 >= len2; i++) {
			div1(res, num2, len2 + 1, result, i, remainder);
			len1--;
			remainder[len2 + 1] = num1[len2 + i];
			remainder[len2 + 2] = '\0';
			copy(res, remainder, len2);
		}
	}
	throwaway0(remainder, len2 + 1);
}

void main()//主函数
{
	int i = 0;
	int len1 = 0;
	int len2 = 0;
	int len = 0;
	char num1[100000];
	int num1sign = 1;
	char num2[100000];
	int num2sign = 1;
	char result[100000];
	char remainder[100000];
	char lresult[100000];//2
	char ope[100000];
	while(1) {
		i = 0;
		num1[i] = getchar();
		if (num1[i] == EOF) {
			cout << "end" << endl;
			break;
		}
		if (num1[i] == '\n') {
			i = 100000;
		}
		if(num1[i]=='+'){
			num1sign = 1;
		}
		else{
			if (num1[i] == '-') {
				num1sign = 0;
			}
			else {
				i = 1;
			}
		}
		for (; i < 100000; i++) {
			num1[i] = getchar();
			if (num1[i] == '\n') {
				break;
			}
		}
		num1[i] = '\0';
		len1 = i;

		i = 0;
		num2[i] = getchar();
		if (num2[i] == EOF) {
			cout << "end" << endl;
			break;
		}
		if (num2[i] == '\n') {
			i = 100000;
		}
		if (num2[i] == '+') {
			num2sign = 1;
		}
		else {
			if (num2[i] == '-') {
				num2sign = 0;
			}
			else {
				i = 1;
			}
		}
		for (; i < 100000; i++) {
			num2[i] = getchar();
			if (num2[i] == '\n') {
				break;
			}
		}
		num2[i] = '\0';
		len2 = i;

		ope[0] = getchar();
		ope[1] = getchar();
		if (ope[1] != '\n') {
			printf("error4");
			break;
		}
		//scanf("%s", &ope);
		len1 = check(num1);//检查,返回位数
		len2 = check(num2);
		if (len1 == 0 || len2 == 0) {
			printf("error1\n");
			continue;
		}
		switch (ope[0])
		{
			case '+': {
				if (num1sign == 1 && num2sign == 1) {
					add(num1, num2, result, len1, len2);
					printf("%s\n", result);
					break;
				}
				if (num1sign == 1 && num2sign == 0) {
					sub(num1, num2, result, len1, len2);
					printf("%s\n", result);
					break;
				}
				if (num1sign == 0 && num2sign == 1) {
					sub(num2, num1, result, len2, len1);
					printf("%s\n", result);
					break;
				}
				if (num1sign == 0 && num2sign == 0) {
					add(num1, num2, result, len1, len2);
					printf("-%s\n", result);
					break;
				}
			}
			case '-': {
				if (len2 == 1 && num2[0] == '0') {
					printf("error2\n");
					break;
				}
				if (num1sign == 1 && num2sign == 1) {
					sub(num1, num2, result, len1, len2);
					printf("%s\n", result);
					break;
				}
				if (num1sign == 1 && num2sign == 0) {
					add(num1, num2, result, len1, len2);
					printf("%s\n", result);
					break;
				}
				if (num1sign == 0 && num2sign == 1) {
					add(num1, num2, result, len1, len2);
					printf("-%s\n", result);
					break;
				}
				if (num1sign == 0 && num2sign == 0) {
					sub(num2, num1, result, len2, len1);
					printf("%s\n", result);
					break;
				}
			}
			case '*': {
				if ((num1sign == 1 && num2sign == 1)||(num1sign==0&&num2sign==0)) {
					mul(num1, num2, lresult, len1, len2);
					printf("%s\n", lresult);
					break;
				}
				if ((num1sign == 1 && num2sign == 0)||(num1sign==0&&num2sign==1)) {
					mul(num1, num2, lresult, len1, len2);
					printf("-%s\n", lresult);
					break;
				}
			}
			case '/': {
				div(num1, num2, result, remainder, len1, len2);
				printf("%s %s\n", result, remainder);
				break;
			}
			default:printf("error3\n");
		}
		num1sign = 1;
		num2sign = 1;
	}
	system("pause");
}