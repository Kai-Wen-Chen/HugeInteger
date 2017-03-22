#include <iostream>
#include "function.h"

HugeInteger::HugeInteger()
{
}

HugeInteger::HugeInteger(const std::string &S)
{
	int i;
	
	noOfDigits = S.size();
	
	for (i=0;i<42;i++)
	integer[i] = 0;
	
	for (i=0;i<S.size();i++)
	integer[i] = S[S.size()-i-1] - '0';
}

HugeInteger HugeInteger::operator+(const HugeInteger &H) const
{
	HugeInteger ans;
	int i,j,carry=0;
	
	ans.noOfDigits = (noOfDigits >= H.noOfDigits) ? noOfDigits : H.noOfDigits;
	
	for (i=0;i<=ans.noOfDigits;i++)
	{
		if (carry == 1)
		{
			if (integer[i] + H.integer[i] > 8)
			{
				ans.integer[i] = integer[i]+H.integer[i]-9;
				carry = 1;
			}
			
			else
			{
				ans.integer[i] = integer[i]+H.integer[i]+1;
				carry = 0;
			}
		}
		
		else
		{
			if (integer[i] + H.integer[i] > 9)
			{
				ans.integer[i] = integer[i]+H.integer[i]-10;
				carry = 1;
			}
			
			else
			{
				ans.integer[i] = integer[i]+H.integer[i];
				carry = 0;
			}
		}
	}
	
	if (ans.integer[ans.noOfDigits] != 0)
	ans.noOfDigits++;
	
	return ans;
}

HugeInteger HugeInteger::operator+( const std::string &S) const
{
	HugeInteger tmp,ans;
	
	tmp = HugeInteger(S);
	ans = HugeInteger::operator+(tmp);
	
	return ans;
}

HugeInteger HugeInteger::operator-(const HugeInteger &H) const
{
	HugeInteger ans;
	int i,j,carry=0;
	
	ans.noOfDigits = (noOfDigits >= H.noOfDigits) ? noOfDigits : H.noOfDigits;
	
	for (i=0;i<=ans.noOfDigits;i++)
	{
		if (carry == 1)
		{
			if (integer[i] - H.integer[i] <= 0)
			{
				ans.integer[i] = integer[i]-H.integer[i]+9;
				carry = 1;
			}
			
			else
			{
				ans.integer[i] = integer[i]-H.integer[i]-1;
				carry = 0;
			}
		}
		
		else
		{
			if (integer[i] - H.integer[i] < 0)
			{
				ans.integer[i] = integer[i]-H.integer[i]+10;
				carry = 1;
			}
			
			else
			{
				ans.integer[i] = integer[i]-H.integer[i];
				carry = 0;
			}
		}
	}
	
	if (ans.integer[ans.noOfDigits-1] == 0)
	ans.noOfDigits--;
	
	return ans;
}

HugeInteger HugeInteger::operator-(const std::string &S) const
{
	HugeInteger ans,tmp;
	
	tmp = HugeInteger(S);
	ans = HugeInteger::operator-(tmp);
	
	return ans;
}

HugeInteger HugeInteger::operator*( const HugeInteger &H) const
{
	int i,j,reg1,reg2;
	int Large[42],Less[42];
	HugeInteger ans;
	
	reg1 = (noOfDigits >= H.noOfDigits) ? noOfDigits : H.noOfDigits;
	reg2 = (noOfDigits>= H.noOfDigits) ? H.noOfDigits : noOfDigits;
	
	for (int k=0;k<42;k++)
	{
		Large[k] = 0;
		Less[k] = 0;
		ans.integer[k] = 0;
	}
	
	if (noOfDigits >= H.noOfDigits)
	{
		for (int k=0;k<42;k++)
		Large[k] = integer[k];
		
		for (int k=0;k<42;k++)
		Less[k] = H.integer[k];
	}
	
	else
	{
		for (int k=0;k<42;k++)
		Large[k] = H.integer[k];
		
		for (int k=0;k<42;k++)
		Less[k] = integer[k];
		
	}
	
	for (i=0;i<reg2;i++)
	{
		for (j=0;j<reg1;j++)
		{
			ans.integer[j+i] += Large[j]*Less[i];
			
			if (ans.integer[j+i]/10 > 0) 
			{
				ans.integer[j+i+1] += ans.integer[j+i]/10;
				ans.integer[j+i] = ans.integer[j+i]%10;
			}
		}
	}
	
	for (int k=0;k<42;k++)
	{
		if (ans.integer[k] > 10)
		{
			ans.integer[k+1] += ans.integer[k]/10;
			ans.integer[k] = ans.integer[k]%10;
		}
	}
	
	for (int k=41;k>=0;k--)
	{
		if (ans.integer[k] != 0)
		{
			ans.noOfDigits = k+1;
			break;
		}
	}
	
	return ans;
}

HugeInteger HugeInteger::operator*( const std::string &S) const
{
	HugeInteger tmp,ans;
	
	tmp = HugeInteger(S);
	ans = HugeInteger::operator*(tmp); 
}

HugeInteger HugeInteger::operator/( const HugeInteger &H ) const
{
	HugeInteger w,x,y,z,a,b,c,d;

    int i;
    for(i=0;i<42;i++)
    {
        w.integer[i]=0;
        x.integer[i]=0;
        y.integer[i]=0;
        z.integer[i]=0;
        a.integer[i]=0;
        b.integer[i]=0;
        c.integer[i]=0;
        d.integer[i]=0;
    }
    
	for(i=0;i<this->noOfDigits;i++)
    {
        d.integer[i] = this->integer[i];
        z.integer[i] = this->integer[i];
    }
    
    d.noOfDigits = this->noOfDigits;
    z.noOfDigits =this->noOfDigits;
    a.noOfDigits = 1 ;
    y.integer[0] = 1;
    y.noOfDigits = 1;


    while((d>a)&&((a>d)==0))
    {
        x = d + a;
        
		for(i=x.noOfDigits-1;i>=0;i--)
        {
            if(x.integer[i]%2 ==1&& i!=0)
            {
                x.integer[i-1] += 10;
            }
            x.integer[i]/=2;
        }

        for(i=x.noOfDigits-1;i>=0;i--)
        {
            if(x.integer[i]==0)
			{
                x.noOfDigits--;
            }
            else{
                break ;
            }
        }
        c = H * x;
        
		if(c > z)
        {
            d = x - y ;
        }
        
		else if(z>c)
        {
            a = x + y ;
        }
        
		else 
		{
            return x ;
        }
    }

    return d;
}

HugeInteger HugeInteger::operator/(const std::string &S) const
{
	HugeInteger tmp,ans;
	
	tmp = HugeInteger(S);
	ans = HugeInteger::operator/(tmp);
	
	return ans;
}
bool HugeInteger::operator>(const HugeInteger &H) const
{
	int i,j,reg;
	
	i = noOfDigits;
	j = H.noOfDigits;
	
	if (i > j) return 1;
	else if (i < j) return 0;
	else
	{
		reg = i;
		for (int k=reg-1;k>=0;k--)
		{
			if (integer[k] > H.integer[k]) return 1;
			else if (integer[k] < H.integer[k]) return 0;
		}
		
		return 0;
	}
}
std::ostream &operator<< (std::ostream &output, const HugeInteger &H)
{
	for (int i=H.noOfDigits-1;i>=0;i--)
	std::cout << H.integer[i];
	
	return output;
}
