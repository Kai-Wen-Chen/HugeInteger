#include <iostream>
#include <string>
using namespace std;

typedef struct HugeInteger {
	short num[500];
	string s_num;
	int digit;
	bool neg;
	
	void initial() {
		for (int i=0; i<500; i++) num[i] = 0;
		s_num.clear();
		digit = 0;
		neg = false;
	}
	
	void setNum(string input) {
		s_num = input;
		
		for (int i=s_num.length()-1; i>=0; i--) {
			//if (s_num[i] == ' ') break;
			num[i] = s_num[s_num.length() - i - 1] - 48;
		}
		
		digit = s_num.length();
	}
	
	void getNum() {
		if (neg) cout << "-";
		
		for (int i=digit-1; i>=0; i--) {
			cout << num[i];
		}
		//cout << s_num;
		cout << endl;
	}
} huge;

huge add(huge*, huge*);
huge sub(huge*, huge*);
huge mul(huge*, huge*);
huge div(huge*, huge*);

int main() {
	string input;
	huge h1, h2;
	char symbol;
	int inCount = 0;
	
	while (getline(cin, input)) {
		if (inCount == 0) {
			h1.initial();
			h2.initial();
			
			h1.setNum(input.substr(0, input.length()-2)); //get number 1
			symbol = input[input.length()-1]; //get symbol
			
			inCount++;
		} else {
			huge h3;
			h2.setNum(input); //get number 2
			
			switch (symbol) {
				case '+':
					h3 = add(&h1, &h2);
					break;
				case '-':
					h3 = sub(&h1, &h2);
					break;
				case '*':
					h3 = mul(&h1, &h2);
					break;
				/*case '/':
					h3 = div(h1, h2);
					break;*/
				default:
					h3.initial();
					break;
			}
			inCount = 0;
			
			//h1.getNum();
			//h2.getNum();
			h3.getNum();
		}
	}
}

huge add(huge* h1, huge* h2) {
	huge ans;
	int carry = 0;
	int digit = (h1->digit >= h2->digit) ? h1->digit : h2->digit;
	
	ans.initial();
	
	for (int i=0; i<=digit; i++) {
		if (carry == 1) {
			if (h1->num[i] + h2->num[i] > 8) {
				ans.num[i] = h1->num[i] + h2->num[i] - 9; 
			} else {
				ans.num[i] = h1->num[i] + h2->num[i] + 1;
				carry = 0;
			}
		} else {
			if (h1->num[i] + h2->num[i] > 9) {
				ans.num[i] = h1->num[i] + h2->num[i] - 10;
				carry = 1;
			} else {
				ans.num[i] = h1->num[i] + h2->num[i];
			}
		}
	}
	
	if (ans.num[digit] != 0) ans.digit = digit + 1;
	else ans.digit = digit;
	
	return ans;
}

huge sub(huge* h1, huge* h2) {
	huge ans;
	int carry = 0;
	int digit = (h1->digit >= h2->digit) ? h1->digit : h2->digit;
	
	ans.initial();
	
	if (h2->digit > h1->digit || 
	(h2->digit == h1->digit && h2->num[h2->digit-1] > h1->num[h1->digit-1])) {
		for (int i=0; i<=digit; i++) {
			if (carry == 1) {
				if (h2->num[i] - h1->num[i] <= 0) {
					ans.num[i] = h2->num[i] - h1->num[i] + 9; 
				} else {
					ans.num[i] = h2->num[i] - h1->num[i] - 1;
					carry = 0;
				}
			} else {
				if (h2->num[i] - h1->num[i] < 0) {
					ans.num[i] = h2->num[i] - h1->num[i] + 10;
					carry = 1;
				} else {
					ans.num[i] = h2->num[i] - h1->num[i];
				}
			}
		}
		
		ans.neg = true;
	} else {
		for (int i=0; i<=digit; i++) {
			if (carry == 1) {
				if (h1->num[i] - h2->num[i] <= 0) {
					ans.num[i] = h1->num[i] - h2->num[i] + 9; 
				} else {
					ans.num[i] = h1->num[i] - h2->num[i] - 1;
					carry = 0;
				}
			} else {
				if (h1->num[i] - h2->num[i] < 0) {
					ans.num[i] = h1->num[i] - h2->num[i] + 10;
					carry = 1;
				} else {
					ans.num[i] = h1->num[i] - h2->num[i];
				}
			}
		}
	}
	
	if (ans.num[digit-1] == 0) ans.digit = digit - 1;
	else ans.digit = digit;
	
	return ans;
}

huge mul(huge* h1, huge* h2) {
	huge ans;
	int i,j,reg1,reg2;
	int Large[500],Less[500];
	ans.initial();
	
	reg1 = (h1->digit >= h2->digit) ? h1->digit : h2->digit;
	reg2 = (h1->digit >= h2->digit) ? h2->digit : h1->digit;
	
	for (int k=0;k<reg1+reg2;k++) {
		Large[k] = 0;
		Less[k] = 0;
	}
	
	if (h1->digit >= h2->digit)
	{
		for (int k=0;k<reg1+reg2;k++)
		Large[k] = h1->num[k];
		
		for (int k=0;k<reg1+reg2;k++)
		Less[k] = h2->num[k];
	}
	
	else
	{
		for (int k=0;k<reg1+reg2;k++)
		Large[k] = h2->num[k];
		
		for (int k=0;k<reg1+reg2;k++)
		Less[k] = h1->num[k];
		
	}
	
	for (i=0;i<reg2;i++)
	{
		for (j=0;j<reg1;j++)
		{
			ans.num[j+i] += Large[j]*Less[i];
			
			if (ans.num[j+i]/10 > 0) 
			{
				ans.num[j+i+1] += ans.num[j+i]/10;
				ans.num[j+i] = ans.num[j+i]%10;
			}
		}
	}
	
	for (int k=0;k<reg1+reg2;k++)
	{
		if (ans.num[k] > 10)
		{
			ans.num[k+1] += ans.num[k]/10;
			ans.num[k] = ans.num[k]%10;
		}
	}
	
	for (int k=reg1+reg2-1;k>=0;k--)
	{
		if (ans.num[k] != 0)
		{
			ans.digit = k+1;
			break;
		}
	}
	
	return ans;
}

huge div(huge* h1, huge* h2) {
	huge ans;
	int digit;
	
	ans.initial();
	
	if (h2->digit > h1->digit ||
	(h2->digit == h1->digit && h2->num[h2->digit-1] > h1->num[h1->digit-1])) {
		ans.digit = 1;
		ans.s_num = "0";
		ans.num[0] = 0;
	} else {
		/*TODO*/
	}
	
	return ans;
}
