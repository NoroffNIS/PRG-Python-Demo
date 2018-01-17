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
#include "bigint.h"

#ifndef UINT64_MAX
#include <limits>
#define UINT64_MAX std::numeric_limits<uint64_t>::max()
#endif

#define N_MAX_LENGTH 256
#define N_MIN_LENGTH 64
#define L_MAX_LENGTH 3072

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
char bigintHex[BIGINTSIZE*8];

void clearWBuffert(uint32* buffer){
	for(int pos = 16; --pos >=0;){
		buffer[pos] = 0;
	}
}
uint32  leftrotate(uint32 bits, uint32 cons){
	return (((cons << bits) & 0xFFFFFFFF) | ((cons & 0xFFFFFFFF) >> (32-bits)));
}

const char* toHex(const unsigned char* hash, char* hexString){
	const char hexDig[] = {"0123456789abcdef"};
	for(int byte=20; byte>=0;byte--){
		hexString[byte << 1] = hexDig[(hash[byte]>>4) & 0xF];
		hexString[(byte << 1) +1] = hexDig[hash[byte] & 0xF];
	}
	hexString[60] = 0;
	return hexString;
}
string bigint_ToHex(bigint number){
	const char hexDig[] = {"0123456789abcdef"};
	int length = 0;
	BIGINT_BASE data[BIGINTSIZE];
	for(int byte=0;byte<BIGINTSIZE; byte++){
		if(data[byte] > 0)
			length = byte;
	}
	
	string bigintHex = "0x";
	for(;length>=0;length--){
		bigintHex.append(1, hexDig[(data[length]>>28) & 0xF]);
		bigintHex.append(1, hexDig[(data[length]>>24) & 0xF]);
		bigintHex.append(1, hexDig[(data[length]>>20) & 0xF]);
		bigintHex.append(1, hexDig[(data[length]>>16) & 0xF]);
		bigintHex.append(1, hexDig[(data[length]>>12) & 0xF]);
		bigintHex.append(1, hexDig[(data[length]>>8) & 0xF]);
		bigintHex.append(1, hexDig[(data[length]>>4) & 0xF]);
		bigintHex.append(1, hexDig[data[length] & 0xF]);
	}
	return bigintHex;
}
int bitLength(bigint num){
	int length = 0;
	bigint temp;
	temp = num;
	while(temp>bigint(0)){
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
}
bigint toBigint(){
	bigint temp = 0;
	temp[0] = digsetHash[4];
	temp[1] = digsetHash[3];
	temp[2] = digsetHash[2];
	temp[3] = digsetHash[1];
	temp[4] = digsetHash[0];
	return temp;
}

bigint random_number(){
	bigint random=1;
	for(int i=0; i<BIGINTSIZE; i++){
		random[i] = rand();
		srand(71623+time(NULL) + i + random[i]);
	}
	srand(1);
	return random;
}

bigint random_number_seed(unsigned int seed){
	srand(88929+seed+time(NULL));
	bigint random = random_number();
	srand(1);
	return random;

}
bigint random_number_seed_limit(unsigned int seed,unsigned int bitlength){
	srand(78727+seed+time(NULL));
	bigint limit = bigint(1);
	unsigned int i=2;
	while(i<bitlength){
		limit = limit <<1;
		limit |=bigint(1);
		i++;
	}
	bigint random = random_number()%limit+limit;
	srand(1);	
	return random;
}
bigint modulo(bigint number, bigint pow, bigint mod){
	bigint result;
	for(result=bigint(1);pow;pow>>=bigint(1)){
		if(pow&bigint(1))
			result = (result * number)%mod;
		number = (number * number)%mod;
	}
	return result;
}
void extEA(bigint &a, bigint &b, bigint &d, bigint &x, bigint &y){
	if(b == bigint(0)){
		d = a;
		x = bigint(1);
		y = bigint(0);
		return;
	}
	else{ 
		bigint r = a % b;
		bigint q = a / b;
		extEA(b, r, d, x, y);
		bigint tmp = x;
		x = y;
		y = tmp-q*y;
		return;
	}
}
bigint modMultiInvers(bigint a,bigint b){
	bigint d, x, y;
	extEA(a,b,d,x,y);
	if(bigint(1)%d!=bigint(0))cout<<"Error in modMultiIvers calulation"<<endl;
	return (x+b)%b;
}
bool is_prime(bigint number, int accurancy){
	if((number == bigint(0)) ||( number == bigint(1))) return false;
	if(number%bigint(2) == bigint(0)) return false;
	if(number%bigint(3) == bigint(0)) return false;
	for(int i=0; i<accurancy; i++){
		bigint a = random_number_seed(i*543+949)%(number-bigint(1))+bigint(2);
		if(a != modulo(a,number, number)) return false;
		}
	return true;
}

bigint random_prime(unsigned int seed,unsigned int bitLength){
	srand(seed);
	bigint limit = bigint(1);
	int i =2;
	while(i<bitLength){
		limit <<=1;
		limit += bigint(1);
		i++;
	}
	bigint prime = random_number() % limit + limit;
	if(prime%bigint(2) == bigint(0)){
		prime=(prime++ % limit)+limit;
	}
	while(!is_prime(prime,3)){
		prime=((prime+bigint(2))%limit)+limit;
	}
	return prime;
}

void keyGenerating(unsigned int seed, unsigned int bitLengthN, unsigned int bitLengthL){
	if(bitLengthN > N_MAX_LENGTH) bitLengthN = N_MAX_LENGTH;
	if(bitLengthN < N_MIN_LENGTH) bitLengthN = N_MIN_LENGTH;
	if(bitLengthL > L_MAX_LENGTH) bitLengthN = L_MAX_LENGTH;
	if(bitLengthL <= N_MAX_LENGTH) bitLengthL = N_MAX_LENGTH*2;
	
	bigint q = random_prime(72727+seed, bitLengthN);
	bigint p = bigint(12);
	int counter = 0;
	while(!is_prime(p,3) || bitLength(p) != bitLengthL){
		p = random_number_seed_limit(89797+seed+counter, bitLengthL);
		p = p - ((p - bigint(1))%q);
		counter++;
		cout<<counter<<endl;
	}
	
	bigint h = bigint(2);
	bigint g = bigint(0);
	while(g<=bigint(1)){
		g = modulo(h,(p-bigint(1))/q,p);
		h++;
	}
	bigint x;
	while(x<bigint(0) || x>q){
		x = random_number_seed(77392+seed+counter);
		cout<<x<<endl;
	}
	bigint y = modulo(g,x,p);
	
	ofstream outputfile("PublicKeys");
	if(!outputfile.is_open()) cout<<"Could not open PublicKeys"<<endl;
	outputfile<<bigint_ToHex(p).c_str()<<endl;
	outputfile<<bigint_ToHex(q).c_str()<<endl;
	outputfile<<bigint_ToHex(g).c_str()<<endl;
	outputfile<<bigint_ToHex(y).c_str()<<endl;
	
	outputfile.flush();
	outputfile.close();

	
	ofstream privateKeyOut("PrivateKey");
	if(!privateKeyOut.is_open()) cout<<"Could not open PrivateKeys"<<endl;
	privateKeyOut<<x<<endl;

	privateKeyOut.flush();
	privateKeyOut.close();
}
bigint fromHex(const char* value){
	bigint temp = 0;
	
	int length = strlen(value);
	int counter = 0;
	for(int i=length-1; i>=0; i--){
		if(value[i] >47 && value[i] <58){
			temp[counter/8] |= ( value[i] - 48) <<(counter %8) *4;
			counter++;
		}else if(value[i]>96 && value[i] <103){
			temp[counter/8] |= (value[i]-87)<<(counter%8)*4;
		}
	}
	return temp;
}		
void signing(string filename){
	string line;

	ifstream publickeys("PublicKeys");
	if(!publickeys.is_open()) cout<<"Could not open PublicKeys"<<endl;
	getline(publickeys,line);
	bigint p = fromHex(line.c_str());
	getline(publickeys,line);
	bigint q = fromHex(line.c_str());
	getline(publickeys,line);
	bigint g = fromHex(line.c_str());
	publickeys.close();
	
	ifstream privatekey("PrivateKey");
	if(!privatekey.is_open()) cout<<"Could not open PrivateKey"<<endl;
	getline(publickeys,line);
	bigint x = fromHex(line.c_str());
	privatekey.close();
	
	
	sha1((const char*) filename.c_str());
	bigint hashInt = toBigint();
	cout<<hashInt<<endl;

	bigint k = 0;
	bigint r = 0;
	bigint s = 0;

	while(r==bigint(0) || s==bigint(0)){
		cout<<"in"<<endl;
	/*	while(k>q){
			cout<<"in k"<<endl;
			k = random_number_seed(9987692);
			cout<<"K: "<<k<<endl;
		}*/
		k = (random_number_seed(8877808)%(q-bigint(1)))+bigint(1);
		r = modulo(g,k,p) % q;
		cout<<"R: "<<endl;
		s = modMultiInvers(k,q)*(hashInt + (x*r)) % q;
		cout<<"S: "<<endl;
	}
	ofstream outputfile("signature");
	if(!outputfile.is_open()) cout<<"Could not open signature file"<<endl;
	outputfile<<r<<endl;
	outputfile<<s<<endl;
	outputfile.flush();
	outputfile.close();
}

void verifying(string filename){
	string line;

	ifstream publickeys("PublicKeys");
	if(!publickeys.is_open()) cout<<"Could not open PublicKeys"<<endl;
	getline(publickeys,line);
	bigint p = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	bigint q = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	bigint g = strtoull(line.c_str(),NULL,0);
	getline(publickeys,line);
	bigint y = strtoull(line.c_str(),NULL,0);
	publickeys.close();
	
	ifstream signature("signature");
	if(!signature.is_open())cout<<"Cloud not open Signature"<<endl;
	getline(signature, line);
	bigint r = strtoull(line.c_str(),NULL,0);
	getline(signature, line);
	bigint s = strtoull(line.c_str(),NULL,0);
	signature.close();


	if(r < bigint(0) || r > q) cout<<"R in signature in not satisfied"<<endl; 
	if(s < bigint(0) || s > q) cout<<"S in signature in not satisfied"<<endl;

	sha1((const char*) filename.c_str());
	bigint hashInt = toBigint();
	cout<<hashInt<<endl;

	bigint w = modMultiInvers(s,q);
	bigint u1 = (hashInt*w)%q;
	bigint u2 = (r*w)%q;
	bigint v = (modulo(g,u1,p)*modulo(y,u2,p))%q;
	
	if(v==r)
		cout<<"The file is verifyed corect"<<endl;

	
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
			cout<<"Type in a key length L(32)"<<endl;
			input.clear();
			while(input.empty()){
				getline(cin,input);
			}
			unsigned int bitLengthL = strtoull(input.c_str(),NULL, 0);
			cout<<"Type in a key length N(16)"<<endl;
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
				input.clear();
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
			verifying(input.c_str());
		}else{
			cout<<"You have to type K, S or V." <<endl;
		}

	}

	
	
//sha1((const char*)"storedMsg");
	

}
