#ifndef __BigInt_h__
#define __BigInt_h__
#include <iostream>
#include <vector>
using namespace std;

class BigInt {
	public:
		BigInt();
		BigInt(const vector<int>& myvec);
		BigInt(const vector<char>&myvec);
		BigInt(const char arr[], int arr_sz);
		//overloadings
		BigInt operator +(const BigInt& other);
		BigInt operator -(const BigInt& other);
		BigInt operator *(const BigInt& other);
		BigInt& operator !();//unary	
		bool operator ==(const BigInt& other);
		bool operator >=(const BigInt& other);
		bool operator >(const BigInt& other);
		bool operator <=(const BigInt& other);
		bool operator <(const BigInt& other);
		BigInt& operator ++();
		BigInt& operator --();
		BigInt operator ++(int post);
		BigInt operator --(int temp);
		friend ostream& operator <<(ostream& out, const BigInt& other) {
			out<<"The big int is: ";
			for (size_t i=0;i<(other.big_vec).size();i++) {
				out<<(other.big_vec).at(i);
			}
			out<<"\n";
			return out;
		}
		friend istream& operator >>(istream& myin, BigInt& other) {
			int val=0;
			cout<<"please assign values to input, "
				<<"when finish entering a digit, press return"
				<<"to continue, "
				<<"and press a non integer key to stop\n";
			while (cin>>val) {
			if (cin.fail()) {
				cerr<<"non integer is given. "
				<<"end of input reached.\n";
				exit(1);
			}
			(other.big_vec).push_back(val);
			}
		}
		
	private:
		vector<int> big_vec;
		
		
};
#endif
