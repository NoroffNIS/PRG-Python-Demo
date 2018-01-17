#include<iostream.h>
#include<conio.h>
#include<math.h>
 
int fnIsPrime(int iNumber)
{
                int iCount;
                iCount=2;
                if(iNumber<2)
                    return 0;
                while(iCount<=(iNumber/2))
                {
                                if(iNumber%iCount==0)
                                    return 0;
                                iCount++;
                }
                return 1;
}
 
int fnMultiply(int iNum1,int iNum2)
{
                return iNum1*iNum2;
}
 
int fnFindE(int iNum)
{
                int iCount;
                iCount=2;
                while(iCount<iNum)
                {
                                if(iNum%iCount!=0)
                                    return iCount;
                                iCount++;
                }
                return 0;
}
 
int fnFindD(int iNum1,int iNum2)
{
                int a1,a2,a3,b1,b2,b3,t1,t2,t3,q;
 
                a1=1;
                a2=0;
                a3=iNum1;
 
                b1=0;
                b2=1;
                b3=iNum2;
 
                while(b3!=1)
                {
                                q=a3/b3;
 
                                t1=a1-(q*b1);
                                t2=a2-(q*b2);
                                t3=a3-(q*b3);
 
                                a1=b1;
                                a2=b2;
                                a3=b3;
 
                                b1=t1;
                                b2=t2;
                                b3=t3;
                }
                if(b2<0)
                    b2=b2+iNum1;
                return b2;
}
 
int fnFindText(int iNum1,int iNum2,int iNum3)
{
                int iCount,t;
                iCount=1;
                t=1;
                while(iCount<=iNum2)
                {
                                t=t*iNum1;
                                t=t%iNum3;
                                iCount++;
                }
                return (t%iNum3);
}
 
void main()
{
                long int p,q,n,d,e,pi,pt,ct;
                clrscr();
                cout<<"-----IMPLEMENTATION OF R.S.A ALGORITHM-----";
                cout<<endl<<endl<<"Enter a prime number :";
                cin>>p;
                cout<<"Enter another prime number :";
                cin>>q;
 
                if((fnIsPrime(p))&&(fnIsPrime(q)))
                {
                                n=fnMultiply(p,q);
                                cout<<endl<<"/* Intermediate Catculations...";
                                cout<<endl<<"n :"<<n;
                                pi=fnMultiply(p-1,q-1);
                                cout<<endl<<"pi :"<<pi;
                                e=(fnFindE(pi));
                                cout<<endl<<"e :"<<e;
                                d=fnFindD(pi,e);
                                cout<<endl<<"d :"<<d;
                                cout<<"*/";
                                cout<<endl<<endl<<endl<<"----KEYS----";
                                cout<<endl<<"Public Key : ("<<e<<","<<n<<")";
                                cout<<endl<<"Private Key : ("<<d<<","<<n<<")";
 
                                cout<<endl<<endl<<endl<<"----ENCRYPTION----"<<endl;
                                cout<<"Enter the plain text : ";
                                cin>>pt;
 
                                ct=fnFindText(pt,e,n);
                                pt=fnFindText(ct,d,n);
 
                                cout<<"Cipher Text :"<<ct;
                                
                }
                else
                {
                                cout<<"Error! Enter two prime numbers!";
                }
                getch();
}
