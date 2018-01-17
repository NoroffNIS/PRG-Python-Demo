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

#ifndef UINT64_MAX
#include <limits>
#define UINT64_MAX std::numeric_limits<uint64_t>::max()
#endif

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
uint64 digsetHash[5];

void clearWBuffert(uint32* buffer){
	for(int pos = 16; --pos >=0;){
		buffer[pos] = 0;
	}
}
uint32  leftrotate(uint32 bits, uint32 cons){
	return (((cons << bits) & 0xFFFFFFFF) | ((cons & 0xFFFFFFFF) >> (32-bits)));
}

void toHex(const unsigned char* hash, char* hexString){
	const char hexDig[] = {"0123456789abcdef"};
	for(int byte=20; byte>=0;byte--){
		hexString[byte << 1] = hexDig[(hash[byte]>>4) & 0xF];
		hexString[(byte << 1) +1] = hexDig[hash[byte] & 0xF];
	}
	hexString[60] = 0;

}
int bitLength(int num){
	int zeros = 0;
	int ones = 0;

	zeros = __builtin_ctz(num);
	ones = __builtin_popcount(num);

	return zeros + ones;
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
		if(i <=19){
			func = (b&c) |((~b)&d);
			cons = 0x5A827999;
		}else if(i<=39){
			func = (b^c^d);
			cons = 0x6ED9EBA1;
		}else if(i<=59){
			func = (b&c)|(b&d)|(c&d);
			cons = 0x8F1BBCDC;
		}else if(i<=79){
			func = (b^c^d);
			cons = 0xCA62C1D6;
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

string sha1(const char* file){
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
					| (((uint32) sarray[current_block +0]) << 24);

		}
		transform(w, digset);

	}
	end_current_block = length - current_block;
	clearWBuffert(w);
	int last_block_bytes = 0;
	for(;last_block_bytes < end_current_block; ++last_block_bytes){
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
	toHex(hash, hexString);
	cout<<hexString<<endl;
	return hexString;

}

uint64 random_number(){
	uint64 r[1000];
	for(int i=0; i<1000; i++){
		r[i] = rand();
		srand(time(NULL) + i + r[i]);
	}
	srand(1);
	return r[999];
}
uint64 random_number_seed_limit(uint64 seed, int bitLength){
	srand(seed+time(NULL));
	uint64 limit = 1;
	for(int i=2; i<bitLength; i++){
		limit <<=1;
		limit |=1;
	}
	uint64 random = random_number()%limit+limit;
	srand(1);
	return random;
}
uint64 modulo(uint64 a, uint64 b, uint64 e){
	uint64 c=1;
	uint64 d=1;
	while(d<b){
		d++;
		c=(a*c)%e;
	}
	return c;
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
		uint64_t q = a / b;
		extEA(b, r, d, x, y);
		uint64_t tmp = x;
		x = y;
		y = tmp-q*y;
		return;
	}
}
uint64_t modMultiInvers(uint64_t a,uint64_t b){
	uint64_t d, x, y;
	extEA(a,b,d,x,y);
	if(1%d!=0)cout<<"Error in modMultiIvers calulation"<<endl;
	return (x+b)%b;
}
bool is_prime(uint64 number, int accurancy){
	if((number == 0) ||( number == 1)) return false;
	if(number%2 == 0) return false;
	if(number%3 == 0) return false;

	for(int i=0; i<accurancy; i++){
		uint64 a = random_number()%(number-1)+1;
		if(modulo(a,number-1, number) !=1) return false;
	}
	return true;
}

uint64 random_prime(uint64 seed, int bitLength){
	srand(seed);
	uint64 limit = 1;
	for(int i =2; i<bitLength; i++){
		limit <<=1;
		limit |= 1;
	}
	uint64 prime = random_number() % limit + limit;
	if(prime%2 == 0){
		prime=(prime++ % limit)+limit;
	}
	while(is_prime(prime,3)){
		prime=((prime+2)%limit)+limit;
	}
	return prime;
}

void keyGenerating(uint64 seed, int bitLengthN, int bitLengthL){
	uint64 q = random_prime(seed, bitLengthN);
	cout<<"Q:"<<q<<endl;
	uint64 p = 12;
	int counter = 0;
	while(!is_prime(p,3) || bitLength(p) != bitLengthL){
		p = random_number_seed_limit(seed+counter, bitLengthL);
		p = p - ((p - 1)%q);
		counter++;
		cout<<"conter"<<counter<<endl;
	}
	cout<<"P:"<<p<<endl;

	uint64 h = 2;
	uint64 g;
	while(g<=1){
		g = modulo(h,(p-1)/q,p);
		h++;
	}
	uint64 x;
	while(x<0 || x>q){
		x = random_number();
	}
	uint64 y = modulo(g,x,p);

	ofstream outputfile("PublicKeys");
	if(!outputfile.is_open()) cout<<"Could not open PublicKeys"<<endl;
	outputfile<<p<<endl;
	outputfile<<q<<endl;
	outputfile<<g<<endl;
	outputfile<<y<<endl;

	outputfile.flush();
	outputfile.close();


	ofstream privateKeyOut("PrivateKey");
	if(!privateKeyOut.is_open()) cout<<"Could not open PrivateKeys"<<endl;
	privateKeyOut<<x<<endl;

	privateKeyOut.flush();
	privateKeyOut.close();
}

void signing(string filename){
	string line;

	ifstream publickeys("PublicKeys");
	if(!publickeys.is_open()) cout<<"Could not open PublicKeys"<<endl;
	getline(publickeys,line);
	uint64 p = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	uint64 q = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	uint64 g = strtoull(line.c_str(),NULL,0);
	publickeys.close();

	ifstream privatekey("PrivateKey");
	if(!privatekey.is_open()) cout<<"Could not open PrivateKey"<<endl;
	getline(publickeys,line);
	uint64 x = strtoull(line.c_str(),NULL,0);
	privatekey.close();

	string hash = sha1((const char*) filename.c_str());
	char *pEnd;
	uint64 hashInt = strtoull(hash.substr(0,2).c_str(),&pEnd ,10);
	cout<<hashInt<<endl;

	uint64 k = 0;
	uint64 r = 0;
	uint64 s = 0;

	while(r==0 || s==0){
		while(k<0 || k>q){
			k = random_number();
		}

		r = modulo(g,k,p) % q;
	//	s = modMultiInvers(k,q)*(hashInt + (x*r)) % q;
};
	savehash(hash);

	ofstream outputfile("signature");
	if(!outputfile.is_open()) cout<<"Could not open signature file"<<endl;
	outputfile<<r<<endl;
	outputfile<<s<<endl;
	outputfile.flush();
	outputfile.close();
}

void savehash(string hash){
	ofstream outputfilehash("hashsha1");
		if(!outputfile.is_open()) cout<<"Could not open hashsha1 file"<<endl;
		outputfile<<hash<<endl;
		outputfile.flush();
		outputfile.close();
}

void verifying(){
	string line;

	ifstream publickeys("PublicKeys");
	if(!publickeys.is_open()) cout<<"Could not open PublicKeys"<<endl;
	getline(publickeys,line);
	uint64 p = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	uint64 q = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	uint64 g = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	uint64 y = strtoull(line.c_str(),NULL,0);
	publickeys.close();

	ifstream signature("signature");
	if(!signature.is_open())cout<<"Cloud not open Signature"<<endl;
	getline(signature, line);
	uint64 r = strtoull(line.c_str(),NULL,0);
	getline(signature, line);
	uint64 s = strtoull(line.c_str(),NULL,0);
	signature.close();


	if(r < 0 || r > q) cout<<"R in signature in not satisfied"<<endl;
	if(s < 0 || s > q) cout<<"S in signature in not satisfied"<<endl;




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
			uint64 seed = strtoull(input.c_str(),NULL,0);
			cout<<"Type in a key length L(32)"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin,input);
			}
			int bitLengthL = strtoull(input.c_str(),NULL, 0);
			cout<<"Type in a key length N(16)"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin,input);
			}
			int bitLengthN = strtoull(input.c_str(),NULL,0);

			cout<<"Seed: "<<seed<<endl;
			cout<<"Length L: "<<bitLengthL<<endl;
			cout<<"Length N: "<<bitLengthN<<endl;
			keyGenerating(seed,bitLengthN,bitLengthL);

		}else if(input.compare("S")==0 || input.compare("s")==0){
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
				signing("storedMsg");

			}else if(input.compare("O")==0 || input.compare("o")==0){
				cout<<"Write in the name of the file to open:"<<endl;
				while(input.empty()){
					getline(cin,input);
				}
				signing(input);

			}else{
				cout<< "You have to type in: w or o!" <<endl;
			}
		}else if(input.compare("V")==0 || input.compare("v")==0){
			cout<<"White the file name you want to verify."<<endl;
			input.clear();
			while(input.empty()){
				getline(cin, input);
			}
			//verifying(input.c_str());
		}else{
			cout<<"You have to type K, S or V." <<endl;
		}

	}



//sha1((const char*)"storedMsg");


}
