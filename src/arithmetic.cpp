#include "arithmetic.h"

Arithmetic::Arithmetic()
{
	RPN = NULL;
}

Arithmetic::Arithmetic(char* str)
{
	int i = 0, j = 0;
	bool flag_abs = 0;												// ���� ��� �������� ������ 
	bool flag_var = 0;												// ���� ��� �������� ������� ���������� � ���������

	RPN = new char[2 * strlen(str) + 1];

	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))						// ���� ������ - �����
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
			{
				RPN[j++] = str[i++];
			}
			RPN[j++] = ' ';
		}
		else
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))					// ���� ������ - ����������
			{
				RPN[j++] = str[i++];
				RPN[j++] = ' ';
			}
			else													// ���� ������ - ��������
			{
				if (ch_s.empty())
				{

					if ((str[i] != '(') && (i == 0))
						throw 1;
					ch_s.push(str[i++]);
				}
				else
				{
					switch (str[i])
					{
					case '+':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('+');
						break;

					case '-':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('-');
						break;

					case '*':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('*');
						break;

					case '/':
						if (priority(str[i]) <= priority(ch_s.top()))
						{
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.push('/');
						break;

					case '(':
						ch_s.push('(');
						break;

					case ')':
						while (ch_s.top() != '(')
						{
							if ((ch_s.top() == '|') && (flag_abs == 1))
								throw 1;
							RPN[j++] = ch_s.top();
							RPN[j++] = ' ';
							ch_s.pop();
						}
						ch_s.pop();
						break;
					}
					++i;
				}
			}
		}
	}


	while (!ch_s.empty())
	{
		if ((ch_s.top() == '(') || (ch_s.top() == ')'))
			throw 1;
		RPN[j++] = ch_s.top();
		ch_s.pop();
		if (!ch_s.empty())
			RPN[j++] = ' ';
	}
	RPN[j] = '\0';
}

Arithmetic::~Arithmetic()
{
	delete[] RPN;
	RPN = NULL;
}

int Arithmetic::priority(char op)
{
	switch (op)
	{
	case '(':
	case ')':
		return 0;
		break;
	case '+':
	case '-':
		return 1;
		break;
	case '*':
	case '/':
		return 2;
		break;
	default:break;
	}
}

double Arithmetic::calculation(char* str, Variable* arr, int size)
{
	int i = 0;
	double temp = 0;
	double op1 = 0, op2 = 0;
	bool flag_var = 0;

	while (str[i] != '\0')
	{
		if ((str[i] >= '0') && (str[i] <= '9'))						// ���� ������ - �����
		{
			while ((str[i] >= '0') && (str[i] <= '9'))
			{
				temp = temp * 10 + str[i++] - '0';
			}
			d_s.push(temp);
			temp = 0;
		}
		else
		{
			if ((str[i] >= 'a') && (str[i] <= 'z'))					// ���� ������ - ����������
			{
				flag_var = 1;
				for (int k = 0; k < size; ++k)
					if (str[i] == (arr[k].name))
					{
						d_s.push(arr[k].value);
						flag_var = 0;
					}
				if (flag_var == 1)
					throw 1;
				++i;
			}
			else													// ���� ������ - ��������
			{
				if (d_s.empty())
					throw 1;
				else
					switch (str[i])
					{
					case '+':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw 1;
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 + op2);
						break;

					case '-':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw 1;
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 - op2);
						break;

					case '*':
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw 1;
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 * op2);
						break;

					case '/':
						if (d_s.top() == 0)
							throw 1;
						op2 = d_s.top();
						d_s.pop();
						if (d_s.empty())
							throw 1;
						op1 = d_s.top();
						d_s.pop();
						d_s.push(op1 / op2);
						break;
					}
				++i;
			}
		}
	}
	return d_s.top();
}