#include "BigInt.h"

BigInt::BigInt() {
}

BigInt::BigInt(const vector<char>& myvec) {
	if (myvec.size()==0) {
                cerr<<"Vector empty. Failed to create object.\n";
                exit(1);
        }
	if (myvec.size()==1) {
                if (myvec.front()=='-') {
                        cerr<<"Only a sign is given, no numbers. "
                        <<"program failed\n";
                        exit(1);
                }
	}
	for (int i=0;i<myvec.size();i++) {
                if (myvec.at(i)=='-') {
                        if (i!=0) {
                                cerr<<"negative sign in middle found."
                                        <<" Only give one at beginning.";
                                exit(1);
                        }
                }
        }
	int val=0;
         for (int i=0;i<myvec.size();i++) {
                val=myvec.at(i)-'0';
                if (val<0||val>9) {
                        if (myvec.at(i)!='-') {
                                cerr<<"char out of 0-9 found."
                                <<"Constructor failed\n";
                                exit(1);
                        }
                        continue;
                }
                big_vec.push_back(val);
         }
        if (myvec.at(0)=='-') {
                big_vec.at(0)*=(-1);
        }


}

BigInt::BigInt(const vector<int>& myvec) {
	if (myvec.size()==0) {
       		cerr<<"Vector empty. Failed to create object.\n";
		exit(1);
	}
	for (int i=0;i<myvec.size();i++) {
		if (myvec.at(i)<0) {
			if (i!=0) {
				cerr<<"only first element can be negative.\n";
				exit(1);
			}
		}
	}
	int val=0;
	for (int i=0;i<myvec.size();i++) {
		if (i==0&&myvec.at(i)<0) {
			val=myvec.at(i)*(-1);
			big_vec.push_back(myvec.at(i));
		}
		else { 
               		val=myvec.at(i);
			big_vec.push_back(val);
		}
         }
}

BigInt::BigInt(const char arr[], int arr_sz) {
	int reverse=0;
	if (arr_sz==0) {
	       cerr<<"Array empty. Failed to create object.\n";
	       exit(1);
	}	       
	
	if (arr_sz==1) {
		if (arr[0]=='-') {
               		cerr<<"no value is given, only a sign is invalid\n";
               		exit(1);
		}
        }
	
	int val=0;
	for (size_t i=0;i<arr_sz;i++) {
		val=arr[i]-'0';
		if (val<0||val>9) {
                        if (arr[i]!='-') {
                                cerr<<"char out of 0-9 found."
                                <<"Constructor failed\n";
                                exit(1);
                        }
                        continue;
                }
                big_vec.push_back(val);
	}
	if (arr[0]=='-') {
		big_vec.at(0)*=(-1);
	}
}

BigInt BigInt::operator +(const BigInt& other) {
	BigInt left=*this;
	BigInt right=other;
	BigInt result;
	int sum=0;
	int carry=0;
	auto it=(result.big_vec).begin();
	auto ct=(left.big_vec).crbegin();
	auto ct2=(right.big_vec).crbegin();
	if (((left.big_vec).front()==0)&&(right.big_vec).front()==0) {
		if ((left.big_vec).size()==(right.big_vec).size()) {
			(result.big_vec).push_back(0);
			return result;
		}
	}//0 minus 0
	
	else if (((left.big_vec).front()==0)&&((right.big_vec).front()!=0)) {
		result=other;
		return other;
	}//0+right
	else if (((left.big_vec).front()!=0)&&(right.big_vec).front()==0) {
		result=*this;
		return result;
	}//left+0
	

	if (big_vec.front()<0) {
		(left.big_vec).at(0)=-(big_vec.front());
	}
	if ((other.big_vec).front()<0) {
		(right.big_vec).at(0)=-((other.big_vec).front());
	}
	if ((left.big_vec).size()>(right.big_vec).size()) {
		//plus
		if ((big_vec.front()>=0&&(other.big_vec).front()>=0)||
				(big_vec.front()<=0&&
				 (other.big_vec).front()<=0))
				{
		while (ct2!=(right.big_vec).crend()) {
			sum=*ct+*ct2+carry;
                        if (sum>9) {
                            	sum-=10;
                               	carry=1;
                   	} 
			else {carry=0;}
                      	it=(result.big_vec).insert(it,sum);
                       	ct++;
                      	ct2++;
		}
		while (ct!=(left.big_vec).crend()) {
			sum=*ct+carry;
			if (sum>9) {
				sum-=10;
				carry=1;
			}
			else {
				carry=0;
			}
			it=(result.big_vec).insert(it,sum);
			ct++;
		}
	}
		//minus
		else if ((big_vec.front()>0&&(other.big_vec).front()<0)||
                                (big_vec.front()<0&&
                                 (other.big_vec).front()>0))
                                {
		while (ct2!=(right.big_vec).crend()) {
                        sum=*ct-*ct2-carry;
                        if (sum<0) {
                                sum+=10;
                                carry=1;
                        }
                        else {carry=0;}
                        it=(result.big_vec).insert(it,sum);
                        ct++;
                        ct2++;
                }
                while (ct!=(left.big_vec).crend()) {
                        sum=*ct-carry;
			if (sum<0) {
				sum+=10;
				carry=1;
			}
			else {
				carry=0;
			}
                        it=(result.big_vec).insert(it,sum);
			ct++;
                }
		}
		if (carry==1) {
                        it=(result.big_vec).insert(it,carry);
                }
		 if ((big_vec).front()<0) {
                        (result.big_vec).at(0)*=(-1);
                }
	}
	else if ((left.big_vec).size()==(right.big_vec).size()) {
		//same sign
		if ((big_vec.front()>0&&(other.big_vec).front()>0)||
                                (big_vec.front()<0&&
                                 (other.big_vec).front()<0)) {
			while (ct!=(left.big_vec).crend()) {
				sum=*ct+*ct2+carry;
				if (sum>9) {
                                sum-=10;
                                carry=1;
                        	}
                       		else {carry=0;}
                        	it=(result.big_vec).insert(it,sum);
                        	ct++;
                        	ct2++;
			}
			if (carry==1) {
				it=(result.big_vec).insert(it,carry);	
			}
			if (big_vec.front()<0) {
				(result.big_vec).at(0)*=(-1);
			}
		}
		//different sign
		else {
			if (left<right) {
				while (ct!=(left.big_vec).crend()) {
                                sum=*ct2-*ct-carry;
                                if (sum<0) {
                                sum+=10;
                                carry=1;
                                }
                                else {carry=0;}
                                it=(result.big_vec).insert(it,sum);
                                ct++;
                                ct2++;
                        }	
				if (big_vec.front()>0) {
					(result.big_vec).at(0)*=(-1);
				}
			}
			else {
				while (ct!=(left.big_vec).crend()) {
                                sum=*ct-*ct2-carry;
                                if (sum<0) {
                                sum+=10;
                                carry=1;
                                }
                                else {carry=0;}
                                it=(result.big_vec).insert(it,sum);
                                ct++;
                                ct2++;
                                }
                                if (big_vec.front()<0) {
                                        (result.big_vec).at(0)*=(-1);
                                }
			}
			if (carry==1) {
                        	it=(result.big_vec).insert(it,carry);
                	}
		}
	}
	else {
		if ((big_vec.front()>0&&(other.big_vec).front()>0)||
                                (big_vec.front()<0&&
                                 (other.big_vec).front()<0))
                                {
                while (ct!=(left.big_vec).crend()) {
                        sum=*ct2+*ct+carry;
                        if (sum>9) {
                                sum-=10;
                                carry=1;
                        }
                        else {carry=0;}
                        it=(result.big_vec).insert(it,sum);
                        ct++;
                        ct2++;
                }
                while (ct2!=(right.big_vec).crend()) {
                        sum=*ct2+carry;
			if (sum>9) {
				sum-=10;
				carry=1;
			}
			else {
				carry=0;
			}
                        it=(result.big_vec).insert(it,sum);
			ct2++;
                }
		if (carry==1) {
                        it=(result.big_vec).insert(it,carry);
                }
		if ((big_vec).front()<0) {
                        (result.big_vec).at(0)*=(-1);
                }
        }
		else if ((big_vec.front()>=0&&(other.big_vec).front()<0)||
                                (big_vec.front()<=0&&
                                 (other.big_vec).front()>0)) {
			while (ct!=(left.big_vec).crend()) {
                        sum=*ct2-*ct-carry;
                        if (sum<0) {
                                sum+=10;
                                carry=1;
                        }
                        else {carry=0;}
                        it=(result.big_vec).insert(it,sum);
                        ct++;
                        ct2++;
                }
                while (ct2!=(right.big_vec).crend()) {
                        sum=*ct2-carry;
			if (sum<0) {
				sum+=10;
				carry=1;
			}
			else {
				carry=0;
			}
                        it=(result.big_vec).insert(it,sum);
			ct2++;
                }
		if (carry==1) {
			it=(result.big_vec).insert(it,carry);
		}
                if ((big_vec).front()>0) {
                        result.big_vec.at(0)*=(-1);
                }
		}	
	}
	while (*it==0) {
		if ((result.big_vec).size()!=1) {
			it=(result.big_vec).erase(it);
		}
		else {
			break;
		}
	}
	return result;	
}

BigInt BigInt::operator -(const BigInt& other) {
	BigInt left=*this;
	BigInt right=other;
	BigInt result;
	int sub=0;
	int carry=0;
	auto it=(result.big_vec).begin();
	auto ct=(left.big_vec).crbegin();
	auto ct2=(right.big_vec).crbegin();
	if (big_vec.front()<0) {
		(left.big_vec).at(0)=-(big_vec.front());
	}
	if ((other.big_vec).front()<0) {
		(right.big_vec).at(0)=-((other.big_vec).front());
	}
	if ((left.big_vec).size()>(right.big_vec).size()) {
		//minus
		if ((big_vec.front()>=0&&(other.big_vec).front()>=0)||
				(big_vec.front()<=0&&
				 (other.big_vec).front()<=0))
				{
		while (ct2!=(right.big_vec).crend()) {
			sub=*ct-*ct2-carry;
                        if (sub<0) {
                            	sub+=10;
                               	carry=1;
                   	} 
			else {carry=0;}
                      	it=(result.big_vec).insert(it,sub);
                       	ct++;
                      	ct2++;
		}
		while (ct!=(left.big_vec).crend()) {
			sub=*ct-carry;
			if (sub<0) {
				sub+=10;
				carry=1;
			}
			else {
				carry=0;
			}
			it=(result.big_vec).insert(it,sub);
			ct++;
		}
		if ((big_vec).front()<0) {
			result.big_vec.at(0)*=(-1);
		}
	}
		//plus
		else if ((big_vec.front()>0&&(other.big_vec).front()<0)||
                                (big_vec.front()<0&&
                                 (other.big_vec).front()>0))
                                {
		while (ct2!=(right.big_vec).crend()) {
                        sub=*ct+*ct2+carry;
                        if (sub>9) {
                                sub-=10;
                                carry=1;
                        }
                        else {carry=0;}
                        it=(result.big_vec).insert(it,sub);
                        ct++;
                        ct2++;
                }
                while (ct!=(left.big_vec).crend()) {
                        sub=*ct+carry;
			if (sub>9) {
				sub-=10;
				carry=1;
			}
			else {
				carry=0;
			}
                        it=(result.big_vec).insert(it,sub);
			ct++;
                }
		}
		if (carry==1) {
                        it=(result.big_vec).insert(it,carry);
                }
		 if ((big_vec).front()<0) {
                        (result.big_vec).at(0)*=(-1);
                }
	}
	else if ((left.big_vec).size()==(right.big_vec).size()) {
		//different sign
		if ((big_vec.front()>0&&(other.big_vec).front()<0)||
                                (big_vec.front()<0&&
                                 (other.big_vec).front()>0)) {
			while (ct!=(left.big_vec).crend()) {
				sub=*ct+*ct2+carry;
				if (sub>10) {
                                sub-=10;
                                carry=1;
                        	}
                       		else {carry=0;}
                        	it=(result.big_vec).insert(it,sub);
                        	ct++;
                        	ct2++;
			}
			if (carry==1) {
				it=(result.big_vec).insert(it,carry);	
			}
			if (big_vec.front()<0) {
				(result.big_vec).at(0)*=(-1);
			}
		}
		//same sign
		else {
			if (left<right) {
				while (ct!=(left.big_vec).crend()) {
                                sub=*ct2-*ct-carry;
                                if (sub<0) {
                                sub+=10;
                                carry=1;
                                }
                                else {carry=0;}
                                it=(result.big_vec).insert(it,sub);
                                ct++;
                                ct2++;
                        }	
				if (big_vec.front()>=0) {
					(result.big_vec).at(0)*=(-1);
				}
			}
			else {
				if (((left.big_vec).front()==0)&&
						(right.big_vec).front()
						==0) {
					(result.big_vec).push_back(0);
					return result;
				}//0 minus 0
				while (ct!=(left.big_vec).crend()) {
                                sub=*ct-*ct2-carry;
                                if (sub<0) {
                                sub+=10;
                                carry=1;
                                }
                                else {carry=0;}
                                it=(result.big_vec).insert(it,sub);
                                ct++;
                                ct2++;
                                }
                                if (big_vec.front()<=0) {
                                        (result.big_vec).at(0)*=(-1);
                                }
			}
			if (carry==1) {
                        	it=(result.big_vec).insert(it,carry);
                	}
		}
	}
	else {
		if ((big_vec.front()>0&&(other.big_vec).front()>0)||
                                (big_vec.front()<0&&
                                 (other.big_vec).front()<0))
                                {
                while (ct!=(left.big_vec).crend()) {
                        sub=*ct2-*ct-carry;
                        if (sub<0) {
                                sub+=10;
                                carry=1;
                        }
                        else {carry=0;}
                        it=(result.big_vec).insert(it,sub);
                        ct++;
                        ct2++;
                }
                while (ct2!=(right.big_vec).crend()) {
                        sub=*ct2-carry;
			if (sub<0) {
				sub+=10;
				carry=1;
			}
			else {
				carry=0;
			}
                        it=(result.big_vec).insert(it,sub);
			ct2++;
                }
		if (carry==1) {
                        it=(result.big_vec).insert(it,carry);
                }
		if ((big_vec).front()>0) {
                        (result.big_vec).at(0)*=(-1);
                }
        }
		else if ((big_vec.front()>=0&&(other.big_vec).front()<0)||
                                (big_vec.front()<=0&&
                                 (other.big_vec).front()>0)) {
			while (ct!=(left.big_vec).crend()) {
                        sub=*ct+*ct2+carry;
                        if (sub>=10) {
                                sub-=10;
                                carry=1;
                        }
                        else {carry=0;}
                        it=(result.big_vec).insert(it,sub);
                        ct++;
                        ct2++;
                }
                while (ct2!=(right.big_vec).crend()) {
                        sub=*ct2+carry;
			if (sub>9) {
				sub-=10;
				carry=1;
			}
			else {
				carry=0;
			}
                        it=(result.big_vec).insert(it,sub);
			ct2++;
                }
		if (carry==1) {
			it=(result.big_vec).insert(it,carry);
		}
                if ((big_vec).front()<0) {
                        result.big_vec.at(0)*=(-1);
                }
		}	
	}
	while (*it==0) {
		if ((result.big_vec).size()!=1) {
			it=(result.big_vec).erase(it);
		}
		else {
			break;
		}
	}
	return result;	
}

BigInt BigInt::operator *(const BigInt& other) {
	BigInt result;
	(result.big_vec).push_back(0);
	if ((big_vec.front()==0)||((other.big_vec).front()==0)) {
		(result.big_vec).push_back(0);
		return result;
	}
	BigInt left=*this;
        BigInt right=other;
        int mul=0;
        int carry=0;
        auto it=(result.big_vec).begin();
        auto ct=(left.big_vec).crbegin();
        auto ct2=(right.big_vec).crbegin();
	if (big_vec.front()<0) {
                (left.big_vec).at(0)=-(big_vec.front());
        }
        if ((other.big_vec).front()<0) {
                (right.big_vec).at(0)=-((other.big_vec).front());
        }
	vector<BigInt> vec;
	vector<int> temp;
	temp.push_back(0);
	if (big_vec.size()<=(other.big_vec).size()) {
		while (ct!=(left.big_vec).crend()) {
			BigInt big(temp);
			auto t=(big.big_vec).begin();
			t=big.big_vec.erase(t);
			while (ct2!=((right.big_vec).crend())) {
				mul=(*ct)*(*ct2)+carry;
				carry=0;
				while (mul>9) {
					mul-=10;
					carry++;
				}
				ct2++;
				t=(big.big_vec).insert(t, mul);
			}
			if (carry>0) {
				t=(big.big_vec).insert(t, carry);
			}
			ct++;
			vec.push_back(big);
			ct2=(right.big_vec).crbegin();
			carry=0;
		}
		for (size_t i=0;i<vec.size();i++) {
			for (size_t j=0;j<i;j++) {
				((vec.at(i)).big_vec).push_back(0);
			}
		}
		for (size_t i=0;i<vec.size();i++) {
			result=result+vec.at(i);
		}
	}
	else {
		while (ct2!=(right.big_vec).crend()) {
                        BigInt big(temp);
                        auto t=(big.big_vec).begin();
                        t=(big.big_vec).erase(t);
                        while (ct!=((left.big_vec).crend())) {
                                mul=(*ct)*(*ct2)+carry;
                                carry=0;
                                while (mul>9) {
                                        mul-=10;
                                        carry++;
                                }
                                ct++;
                                t=(big.big_vec).insert(t, mul);
                        }
                        if (carry>0) {
                                t=(big.big_vec).insert(t, carry);
                        }
                        ct2++;
                        vec.push_back(big);
                        ct=(left.big_vec).crbegin();
                        carry=0;
                }
		for (size_t i=0;i<vec.size();i++) {
                        for (size_t j=0;j<i;j++) {
                                ((vec.at(i)).big_vec).push_back(0);
                        }
                }
                for (size_t i=0;i<vec.size();i++) {
                        result=result+vec.at(i);
                }
	}
	if ((big_vec.front()<0&&(other.big_vec).front()>0)||
			(big_vec.front()>0&&(other.big_vec).front()<0)) {
			(result.big_vec).front()*=-1;
	}
	return result;
}

BigInt& BigInt::operator !() {//unary   
	for (size_t i=0;i<big_vec.size();i++) {
		if (big_vec.at(i)!=0) {
			big_vec.clear();
			big_vec.push_back(0);
			return *this;
		}
	}
	big_vec.clear();
	big_vec.push_back(1);
	return *this;	
} 

bool BigInt::operator ==(const BigInt& other) {
	if (big_vec.size()!=(other.big_vec).size()) {
		return false;
	}
	/*if (big_vec.front()!=(other.big_vec).front()) {
		return false;
	}*/
	auto itt=(other.big_vec).cbegin();
	for (auto it=big_vec.cbegin();it!=big_vec.cend();it++) {
		if (itt!=(other.big_vec).cend()) {
			if (*it!=*itt) {
				return false;
			}
			itt++;
		}
	}
	return true;
}

bool BigInt::operator >=(const BigInt& other) {
	if (big_vec.size()<(other.big_vec).size()) {
		if (big_vec.front()<0) {
			if ((other.big_vec).front()>=0) {
				return false;
			}
			else {
				return true;
			}
		}
		else {
			if ((other.big_vec).front()<0) {
				return true;
			}
			else {
				return false;
			}
		}
	}	
	else if (big_vec.size()==(other.big_vec).size()) {
		if ((*this>other)||(*this==other)) {
			return true;
		}	
	}
	else {	
                if (big_vec.front()<0) {
       		       		return false;
                }
                else {
			return true;
                }
        }
}

bool BigInt::operator >(const BigInt& other) {
	if (big_vec.size()>(other.big_vec).size()) {
		if (big_vec.front()<0) {
			if ((other.big_vec).front()<0) {
				return false;
			}
			else {
				return true;
			}
		}
	}
	else if (big_vec.size()<(other.big_vec).size()){
		if (big_vec.front()<0) {
                      	if ((other.big_vec).front()<0) {
                                return true;
                        }
                        else {
                                return false;
                        }
		}
	}
	else {
		int carry=0;
		int count=0;
                auto i=big_vec.crbegin();
                auto i2=(other.big_vec).crbegin();
                for (;i!=big_vec.crend();i++) {
                        if (*i-*i2-carry<0) {
                                carry=1;
                        }
                        else {
				if (*i==*i2) {
					count++;
				}
                                carry=0;
                        }
                        i2++;
                }
                if (carry==1) {
                        return false;
                }
		else {
			if (count==big_vec.size()) {
				return false; //equal
			}
			else {
				return true;
			}
		}
	}
}

bool BigInt::operator <=(const BigInt& other) {
	if (big_vec.size()<(other.big_vec).size()) {
                if (big_vec.front()<0) {
                        if ((other.big_vec).front()<0) {
                                return false;
                        }
                        else {
                                return true;
                        }
                }
                else {
                        if ((other.big_vec).front()>=0) {
                                return true;
                        }
                        else {
                                return false;
                        }
                }
        }
	else if (big_vec.size()==(other.big_vec).size()) {
		if ((*this<other)||(*this==other)) {
			return true;
		}
	}
	 else {
                if (big_vec.front()<0) {
                                return true;
                }
                else {
                        return false;
                }
        }
}

bool BigInt::operator <(const BigInt& other) {
	if (big_vec.size()>(other.big_vec).size()) {
		if (big_vec.front()<0) {
			if ((other.big_vec).front()<0) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	else if (big_vec.size()<(other.big_vec).size()){
		if (big_vec.front()<0) {
                      	if ((other.big_vec).front()<0) {
                                return false;
                        }
                        else {
                                return true;
                        }
		}
	}
	else {
		int carry=0;
		auto i=big_vec.crbegin();
		auto i2=(other.big_vec).crbegin();
		for (;i!=big_vec.crend();i++) {
			if (*i-*i2-carry<0) {
			       	carry=1;
			}
			else {
				carry=0;
			}
			i2++;
		}
		if (carry==1) {
			return true;
		}
		else {
			return false;
		}
	}
}

BigInt& BigInt::operator ++() {//prefix
	BigInt right;
        (right.big_vec).push_back(1);
        *this=(*this+right);
	return *this;
}

BigInt BigInt::operator ++(int temp) {//postfix
	BigInt post=*this;
	BigInt right;
        (right.big_vec).push_back(1);
        *this=(*this+right);
        return post;
}

BigInt& BigInt::operator --() {//prefix
	BigInt right;
        (right.big_vec).push_back(1);
        *this=(*this-right);
	return *this;
}

BigInt BigInt::operator --(int temp) {//postfix
	BigInt post=*this;
	BigInt right;
	(right.big_vec).push_back(1);
	*this=(*this-right);
	return post;
}

int main() {
	vector<char> big1{'2','1','4','7','4','8','3','6','4','7'};
	vector<char> big2{'-','2','1','4','7','4','8','3','6','4','7'};
	BigInt num1=BigInt(big1);
	BigInt num2=BigInt(big2);
	BigInt mull=num1*num2;
	cout<<mull;	
	return 0;
}

//time complexity: the dominant item is a 3 layer while loop in * operator. The worst case is O(n^3).
//space complexity: constructors create an object that has n elements. The operators create and return an object that has n elements. The space complexity is O(n).
