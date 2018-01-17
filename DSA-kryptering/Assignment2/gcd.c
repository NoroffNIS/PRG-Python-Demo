#include <iostream>

using namespace std;

int gcd(int a, int b){
	cout<<a<<"|"<<b<<endl;	
	if(b == 0)return a;
	return gcd(b, a%b);
}

int main(){
	cout<<gcd(60,14)<<endl;
}
