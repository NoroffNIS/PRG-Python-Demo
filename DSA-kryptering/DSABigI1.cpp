#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "bigint/BigIntegerLibrary.hh"



using namespace std;
typedef unsigned long int uint32;
typedef unsigned long long uint64;

static const unsigned int BLOCK_INTS = 16;
static const unsigned int BLOCK_BYTES = BLOCK_INTS*4;

uint32 h0 = 0x67452301;
uint32 h1 = 0xEFCDAB89;
uint32 h2 = 0x98BADCFE;
uint32 h3 = 0x10325476;
uint32 h4 = 0xC3D2E1F0;

string input="";
bool _write;
string buffer="";
uint32 chunks[1000];
char hexString[60];
unsigned char hash[20];
long unsigned int digsetHash[5];

void clearWBuffert(uint32* buffer){
	for(int pos = 16; --pos >=0;){
		buffer[pos] = 0;
	}
}
uint32  leftrotate(uint32 bits, uint32 cons){
	return ((cons << bits) | (cons >> (32-bits)));
}

int bitLength(BigUnsigned num){
	int length = 0;
	BigUnsigned temp;
	temp = num;
	while(temp>BigUnsigned(0)){
		temp >>=1;
		length++;
	}
	return length;
}

void transform(uint32* w, uint32* digset){

	uint32 a = h0;
	uint32 b = h1;
	uint32 c = h2;
	uint32 d = h3;
	uint32 e = h4;
	
	for(int i=0;i<80;i++){
		unsigned func = 0;
		uint32 cons = 0;
		if(i <=16){
			func = (b&c) |((~b)&d);
			cons = 0x5a827999;
		}else if(i<19){
			w[i] = leftrotate(1, (w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]));
			func = (b&c) | ((~b)&d);
			cons = 0x5a827999;
		}else if(i<=39){
			w[i] = leftrotate(1, (w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]));
			func = (b^c^d);
			cons = 0x6ed9eba1;
		}else if(i<=59){
			w[i] = leftrotate(1, (w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]));
			func = (b&c)|(b&d)|(c&d);
			cons = 0x8F1bbcdc;
		}else if(i<=79){
			w[i] = leftrotate(1, (w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16]));
			func = (b^c^d);
			cons = 0xca62c1d6;
		}
		
		uint32 temp = leftrotate(5,a)+func+e+cons+w[i];
		e=d;
		d=c;
		c=leftrotate(30,b);
		b=a;
		a=temp;
	} 
	
	h0 +=a;
	h1 +=b;
	h2 +=c;
	h3 +=d;
	h4 +=e;

	digsetHash[0] = h0;
	digsetHash[1] = h1;
	digsetHash[2] = h2;
	digsetHash[3] = h3;
	digsetHash[4] = h4;
}

void sha1(const char* file){
	ifstream inputfile(file, ios::binary);
	if(!inputfile.is_open())
		cout<<"Could not open the file"<<endl;
	
	inputfile.seekg(0,inputfile.end);
	int length = inputfile.tellg();
	inputfile.seekg(0,inputfile.beg);
	int i = 0;
	char* buffertext = new char[length];
	inputfile.read(buffertext, length);
	uint32 digset[5] = {h0,h1,h2,h3,h4};

	const unsigned char* sarray = (const unsigned char*) buffertext;
	uint32 w[80];
	const int end_of_full_block = length-BLOCK_BYTES;
	int end_current_block;
	int current_block = 0;
	
	while(current_block <= end_of_full_block){
		end_current_block = current_block + BLOCK_BYTES;
		
		for(int round_pos = 0; current_block < end_current_block; current_block +=4){
			w[round_pos++] = (uint32) sarray[current_block + 3]
					| (((uint32) sarray[current_block +2]) << 8)
					| (((uint32) sarray[current_block +1]) << 16)
					| (((uint32) sarray[current_block]) << 24);
		
		}
		transform(w, digset);
		
	}
	end_current_block = length - current_block;
	clearWBuffert(w);
	int last_block_bytes = 0;
	for(;last_block_bytes < end_current_block; last_block_bytes++){
		w[last_block_bytes >>2] |= (uint32) sarray[last_block_bytes + current_block] <<((3-(last_block_bytes & 3))<<3);
	}
	w[last_block_bytes >> 2] |= 0x80 << ((3 - (last_block_bytes &3))<<3);
	if(end_current_block >= 56){
		transform(w,digset);
		clearWBuffert(w);
	}
	w[15] = length << 3;
	transform(w,digset);

	for(int byte=20; byte>=0;byte--){
		hash[byte] = (digsetHash[byte >> 2 ] >> (((3-byte)&0x3) << 3))&0xFF;
	}
}

BigUnsigned random_number(int bit){
	BigUnsigned random=1;
	for(int i=0; i<bit; i++){
		random <<= 32;
		random ^= BigUnsigned(rand());
		srand(71623+time(NULL) + i);
	}
	srand(1);
	return random;
}

BigUnsigned random_number_seed(unsigned int seed){
	srand(88929+seed+time(NULL));
	BigUnsigned random = random_number(10);
	srand(1);
	return random;

}
BigUnsigned random_number_seed_limit(unsigned int seed,unsigned int bitlength){
	srand(78727+seed+time(NULL));
	BigUnsigned limit = BigUnsigned(1);
	unsigned int i=2;
	while(i<bitlength){
		limit = limit <<1;
		limit +=BigUnsigned(1);
		i++;
	}
	BigUnsigned random = random_number(10)%limit+limit;
	srand(1);	
	return random;
}

bool is_prime(BigUnsigned number, int accurancy){
	if((number == BigUnsigned(0)) ||( number == BigUnsigned(1))) return false;
	if(number%BigUnsigned(2) == BigUnsigned(0)) return false;
	if(number%BigUnsigned(3) == BigUnsigned(0)) return false;
	for(int i=0; i<accurancy; i++){
		BigUnsigned x = random_number_seed(i*543+949)%(number-BigUnsigned(1))+BigUnsigned(2);
		if(x != modexp(x,number, number)) return false;
		}
	return true;
}

BigUnsigned random_prime(unsigned int seed,unsigned int bitLength){
	srand(seed);
	BigUnsigned limit = BigUnsigned(1);
	int i =2;
	while(i<bitLength){
		limit <<=1;
		limit += BigUnsigned(1);
		i++;
	}
	BigUnsigned prime = random_number(10) % limit + limit;
	if(prime % BigUnsigned(2) == BigUnsigned(0)){
		prime++;
		prime = (prime % limit)+limit;
	}
	while(!is_prime(prime,3)){
		prime=((prime+BigUnsigned(2))%limit)+limit;
	}
	return prime;
}

void keyGenerating(unsigned int seed, unsigned int bitLengthN, unsigned int bitLengthL){
	
	BigUnsigned q = random_prime(72727+seed, bitLengthN);
	BigUnsigned p = BigUnsigned(12);
	unsigned int counter = 0;
	while(!is_prime(p,3) || bitLength(p) != bitLengthL){
		p = random_number_seed_limit(89797+seed+counter, bitLengthL);
		p = p - ((p - BigUnsigned(1))%q);
		counter++;
	}
	
	BigUnsigned h = BigUnsigned(2);
	BigUnsigned g = BigUnsigned(0);
	while(g<=BigUnsigned(1)){
		g = modexp(h,((p-BigUnsigned(1))/q),p);
		h++;
		if(h>p-1) cout<<"h>p-1"<<endl;
	}

	ofstream outputfile("GlobalKeys");
	if(!outputfile.is_open()) cout<<"Could not open GlobalKeys"<<endl;
	outputfile<<bigUnsignedToString(p)<<endl;
	outputfile<<bigUnsignedToString(q)<<endl;
	outputfile<<bigUnsignedToString(g)<<endl;

	outputfile.flush();
	outputfile.close();
}

void userKeys(BigUnsigned p, BigUnsigned q, BigUnsigned g, unsigned int seed){
	BigUnsigned x = (random_number_seed(77392+seed) % (q-BigUnsigned(2)))+BigUnsigned(1);
	BigUnsigned y = modexp(g,x,p);
	
	ofstream publicKeyOut("PublicKey");
	if(!publicKeyOut.is_open()) cout<<"Could not open PublicKey"<<endl;
	publicKeyOut<<bigUnsignedToString(y)<<endl;
	publicKeyOut.flush();
	publicKeyOut.close();

	
	ofstream privateKeyOut("PrivateKey");
	if(!privateKeyOut.is_open()) cout<<"Could not open PrivateKeys"<<endl;
	privateKeyOut<<bigUnsignedToString(x)<<endl;

	privateKeyOut.flush();
	privateKeyOut.close();
}

void signing(string filename, unsigned int seed){
	string line;

	ifstream globalKey("GlobalKeys");
	if(!globalKey.is_open()) cout<<"Could not open GlobalKeys"<<endl;
	getline(globalKey,line);
	BigUnsigned p = stringToBigUnsigned(line);
	getline(globalKey,line);
	BigUnsigned q = stringToBigUnsigned(line);
	getline(globalKey,line);
	BigUnsigned g = stringToBigUnsigned(line);
	globalKey.close();
	
	userKeys(p,q,g, seed);
	
	ifstream privatekey("PrivateKey");
	if(!privatekey.is_open()) cout<<"Could not open PrivateKey"<<endl;
	getline(privatekey,line);
	BigUnsigned x = stringToBigUnsigned(line);
	privatekey.close();
	
	sha1((const char*) filename.c_str());	
	BigUnsigned shaHash;
	for(int i=0; i<5;i++){
		shaHash <<= 32;
		shaHash ^= digsetHash[i];
	}

	BigUnsigned k;
	BigUnsigned r = 0;
	BigUnsigned s = 0;
	while(r==BigUnsigned(0) || s==BigUnsigned(0)){
		k = (random_number_seed(seed+=98928) % (q-BigUnsigned(2))) +BigUnsigned(1);
		if(k>p)cout<<"k>p"<<endl;
		r = ((modexp(g,k,p)) %q);
		s = ((modinv(k,q)*(shaHash + (x*r))) %q);
	}
	
	ofstream outputfile("signature");
	if(!outputfile.is_open()) cout<<"Could not open signature file"<<endl;
	outputfile<<r<<endl;
	outputfile<<s<<endl;
	outputfile.flush();
	outputfile.close();
	
	cout<<"The signature of the message is done"<<endl;
}

void verifying(string filename){
	string line;

	ifstream globalkeys("GlobalKeys");
	if(!globalkeys.is_open()) cout<<"Could not open GlobalKeys"<<endl;
	getline(globalkeys,line);
	BigUnsigned p = stringToBigUnsigned(line);
	getline(globalkeys,line);
	BigUnsigned q = stringToBigUnsigned(line);
	getline(globalkeys,line);
	BigUnsigned g = stringToBigUnsigned(line);


	ifstream publickeys("PublicKey");
	if(!publickeys.is_open()) cout<<"Could not open PublicKeys"<<endl;
	getline(publickeys,line);
	BigUnsigned y = stringToBigUnsigned(line);
	publickeys.close();

	ifstream signature("signature");
	if(!signature.is_open())cout<<"Cloud not open Signature"<<endl;
	getline(signature, line);
	BigUnsigned r = stringToBigUnsigned(line);
	getline(signature, line);
	BigUnsigned s = stringToBigUnsigned(line);
	signature.close();

	if(r < BigUnsigned(0) || r > q) cout<<"R in signature in not satisfied"<<endl; 
	if(s < BigUnsigned(0) || s > q) cout<<"S in signature in not satisfied"<<endl;

	sha1((const char*) filename.c_str());	
	BigUnsigned shahash;
	for(int i=0; i<5;i++){
		shahash <<= 32;
		shahash ^= digsetHash[i];
	}
	BigUnsigned w = modinv(s,q);
	BigUnsigned u1 = ((shahash)*w)%q;
	BigUnsigned u2 = (r*w)%q;
	BigUnsigned v = ( ( (modexp(g,u1,p) * modexp(y,u2,p) ) %p ) %q);
	if(v==r){
		cout<<"The file is verifyed correct"<<endl;
	}else{
		cout<<"The file is NOT verifyed correct"<<endl;
	}
	
}

int main(){
	cout<<"What do you want to do? K for generate keys, S for signe a message, or V for verifying a message"<<endl;
	while(input.empty()){
		getline(cin, input);
		
		if(input.compare("K")==0 || input.compare("k")==0){
			cout<<"Type in a random cellphone number"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin, input);
			}
			unsigned int seed = strtoull(input.c_str(),NULL,0);
			cout<<"Type in a key length L"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin,input);
			}
			unsigned int bitLengthL = strtoull(input.c_str(),NULL, 0);
			cout<<"Type in a key length N"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin,input);
			}
			unsigned int bitLengthN = strtoull(input.c_str(),NULL,0);
				
			cout<<"Seed: "<<seed<<endl;
			cout<<"Length L: "<<bitLengthL<<endl;
			cout<<"Length N: "<<bitLengthN<<endl;
			keyGenerating(seed,bitLengthN,bitLengthL);

		}else if(input.compare("S")==0 || input.compare("s")==0){
			cout<<"Type in a random cellphone number"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin, input);
			}
			unsigned int seed = strtoull(input.c_str(),NULL,0);

			cout<<"Type in W for writhing a message and signe it, or O for signing a file"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin, input);
			}
			if(input.compare("W")==0 || input.compare("w")==0){
				input.clear();
				cout<<"Write in the message:"<<endl;
				while(input.empty()){
					getline(cin, input);
				}
				ofstream outputfile ("storedMsg");
				if(!outputfile.is_open())
				cout<<"Could not store the file"<<endl;
				outputfile<<input;
				outputfile.close();
				signing("storedMsg", seed);

			}else if(input.compare("O")==0 || input.compare("o")==0){
				cout<<"Write in the name of the file to open:"<<endl;
				input.clear();
				while(input.empty()){
					getline(cin,input);
				}
				signing(input, seed);

			}else{
				cout<< "You have to type in: w or o!" <<endl;
			}
		}else if(input.compare("V")==0 || input.compare("v")==0){
			cout<<"White the file name you want to verify.(Name of the file you wrote -> storedMsg)"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin, input);
			}
			verifying(input.c_str());
		}else{
			cout<<"You have to type K, S or V." <<endl;
		}

	}

}
