
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

using namespace std;

int checkPrime(int number){
	int i=2;
	if(number<2)
		return 0;
	while(i<=(number/2)){
		if(number%i==0)
			return 0;
		i++;
	}
	return 1;
}

int multiply_number(int n1, int n2){
	if((n1*n2)>=UINT64_MAX){
		cout<<"to big"<<endl;
	}
	
	return n1*n2;
}

int find_E(int phi){
	int i=2;
	while(i<phi){
		if(phi%i!=0)
			return i;
		i++;
	}
	return 0;
}


void extEA(uint64_t &a, uint64_t &b, uint64_t &d, uint64_t &x, uint64_t &y){
	if(b == 0){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	else{ 
		uint64_t r = a % b;
		uint64_t q = (a - r) / b;
		extEA(b, r, d, x, y);
		uint64_t tmp = x;
		x = y;
		y = tmp-q*y;
		return;
	}
}

int find_D(int phi,int e){

	uint64_t d, x, y;
	extEA(e,phi,d,x,y);
	if(1%d!=0)
		cout<<"feil"<<endl;
	return (x*(1/d))%phi;
}
/**
	int  x1,x2,x3,y1,y2,y3,t1,t2,t3,w;
	
	x1 = 1;
	x2 = 0;
	x3 = phi;

	y1 = 0;
	y2 = 1;
	y3 = e;

	while(y3!=1){

		w = (int(x3/y3));
		
		
		t1 = x1-(w*y1);
		t2 = x2-(w*y2);
		t3 = x3-(w*y3);
		cout<<x1<<"-"<<(w*y1)<<"="<<t1<<"|"<<w<<"|"<<y1<<endl;
		cout<<x2<<"-"<<(w*y2)<<"="<<t2<<"|"<<w<<"|"<<y2<<endl;
		cout<<x3<<"-"<<(w*y3)<<"="<<t3<<"|"<<w<<"|"<<y3<<endl;

		x1 = y1;
		x2 = y2;
		x3 = y3;
	
		y1 = t1;
		y2 = t2;
		y3 = t3;	
	
	}
	cout<<y2<<endl;	
	if(y2<0){
		y2 = y2 + phi;
	}
	
	return y2;
}
*/

/**
 * encrypt(message, e, n)
 * decrypt(message, d, n)
 */
uint64_t crypt(uint64_t message, uint64_t key, uint64_t n){

	uint64_t i = 1;
	uint64_t t = 1;
	while(i<=key){
		t = (t*message)%n;
		if(t==UINT64_MAX){
			cout<<"A nubmer became to big!"<<endl;
			break;}
		i++;

	}
	return(t%n);

}

int main(){
	
	uint64_t primeone = 0;
	uint64_t primetwo = 0;
	uint64_t n = 0;
	uint64_t phi = 0;
	uint64_t e = 0;
	uint64_t gcd = 0;
	cout<<gcd;
	string input = "";
	string message = "";
	uint64_t encrypt_message = 0;
	uint64_t decrypt_message = 0;
	cout << "------RSA IMPEMENTATION------" << endl;
	while(true){
		cout << "Writh in a prime number:" << endl;
		getline(cin, input);
		stringstream myStream(input);
		if(myStream >> primeone){
			if(checkPrime(primeone)==1){
				break;
			}
			cout << primeone << " is not a prime.\nA prime number (or a prime) is a natural number greater than 1 that has no positive divisors other than 1 and itself.\n";
		}
		cout << "Invalid number! Please try again" << endl;
	}
	while(true){
		cout << "Writh in another prime number:" << endl;
		getline(cin, input);
		stringstream myStream(input);
		if(myStream >> primetwo){
			if(checkPrime(primetwo)==1){
				break;
			}
			cout << primetwo << " is not a prime.\nA prime number (or a prime) is a natural number greater than 1 that has no positive divisors other than 1 and itself.\n";
		}
		cout << "Invalid number! Please try again" <<endl;
	}
	cout << "-------- Calbulations --------" << endl; 
	cout << "First prime: " << primeone << " | Second prime: " << primetwo << endl;
	n = multiply_number(primeone,primetwo);
	cout << "Multiply prime: " << n <<endl;
	phi = multiply_number(primeone-1,primetwo-1);
	cout << "phi: "<< phi<< endl;
	e = find_E(phi);
	cout << "E: "<< e << endl;
	gcd = find_D(phi,e);
	cout << "D: "<< gcd << endl;
	cout << "------------Keys-------------" << endl; 
	cout << "Public key: " << e << "," << n << endl;	
	cout << "Privat key: " << gcd << "," << n << endl;
	
	cout << "----------Encryption-----------" << endl; 
	cout << "Enter the message: " << endl;
	getline(cin, message);
	

	istringstream inputmessage(message);
	uint64_t value;
	inputmessage >> value;
	encrypt_message = crypt(value, e, n);
	cout << "Encrypt: " << encrypt_message << endl;
	//decrypt_message = crypt(encrypt_message, gcd, n);
	cout << "Decrypt: " << decrypt_message << endl;
}

