#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#ifndef UINT64_MAX
#include <limits>
#define UINT64_MAX std::numeric_limits<uint64_t>::max()
#endif

using namespace std;

/**
 *Function that check if the input number is a prime.
 */
uint64_t checkPrime(uint64_t number){
	uint64_t i=2;
	if(number<2)
		return 0;
	while(i<=(number/2)){
		if(number%i==0)
			return 0;
		i++;
	}
	return 1;
}

/**
 *Function that multiply the two prime.
 */
uint64_t multiply_number(uint64_t n1, uint64_t n2){
	if((n1*n2)>=UINT64_MAX){
		cout<<"The multipyed sum is a nubmer to big for a uint64_t"<<endl;
	}
	return n1*n2;
}

/**
 *Function that finds the greatest common divisor.
 */
uint64_t gcd(uint64_t e,uint64_t phi){
	if(phi == 0)return e;
	return gcd(phi, e % phi);
}

/**
 *The function that fids the E.
 */
uint64_t find_E(uint64_t phi){
	uint64_t e=65573;
	while(gcd(e,phi)!=1 || e>=phi){
		 e -= 2;
	}
	return e;
}

/**
 *The recrusive metod that finds the D.
 */
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

/**
 *FUnction that uses a recrusive metode to find multiplicative invers of E.
 */	
uint64_t find_D(uint64_t phi,uint64_t e){
	uint64_t d, x, y;
	extEA(e,phi,d,x,y);
	if(1%d!=0)cout<<""<<endl;
	return (x+phi)%phi;
}

/**
 * Function that encrypt and decrypt the massage
 * encrypt(message, e, n)
 * decrypt(message, d, n)
 */
uint64_t crypt(uint64_t message, uint64_t key, uint64_t n){
	uint64_t i = 1;
	uint64_t t = 1;
	while(i<=key){
		t = (t*message)%n;
		if(t==UINT64_MAX){
			cout<<"The encrypt nubmer is to big for a uint64_t."<<endl;
			break;}
		i++;

	}
	return(t%n);

}
/**
 *Main function were the user wriths in two prime and the text that is going to encrypt.
 */
int main(){
	
	uint64_t primeone = 0;
	uint64_t primetwo = 0;
	uint64_t n = 0;
	uint64_t phi = 0;
	uint64_t e = 0;
	uint64_t d_gcd = 0;
	string input = "";
	string message = "";
	string encrypt_message = "";
	cout << "------RSA IMPEMENTATION------" << endl;
	while(true){
		cout << "Writh in a prime number (3559):" << endl;
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
		cout << "Writh in another prime number (3571):" << endl;
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
	d_gcd = find_D(phi,e);
	cout << "D: "<< d_gcd << endl;
	cout << "------------Keys-------------" << endl; 
	cout << "Public key: " << e << "," << n << endl;	
	cout << "Privat key: " << d_gcd << "," << n << endl;
	
	cout << "----------Encryption-----------" << endl; 
	cout << "Enter the message: " << endl;
	getline(cin, message);
	for(size_t i=0; i<message.size(); i++){
		stringstream temp;
		uint64_t intmsg = static_cast<int>(static_cast<unsigned char>(message[i]));
		uint64_t cryptednumber = crypt(intmsg,e,n);
		temp << cryptednumber;
		encrypt_message.append(temp.str()+' ');
		
	}
	cout << "Encrypt: " << encrypt_message << endl;
	uint64_t number = 0;
	uint64_t encryptnumber;
	uint64_t decryptnumber;
	string numberstring = "";
	string output = "";
	string decrypt_message = "";
	for(size_t i=0; i< encrypt_message.size();i++){
		if(encrypt_message[i] == ' '){
			stringstream temp(numberstring);
			temp >> encryptnumber;
			decryptnumber = crypt(encryptnumber, d_gcd, n);
			decrypt_message += decryptnumber;
			numberstring = "";
		}else{
			numberstring += encrypt_message[i];
		}
}
	cout<<"Decrypt: "<<decrypt_message<<endl;

}

