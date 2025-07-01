#include<bits/stdc++.h>
#define ll long long
#define MX 100005
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;

using namespace std;

int temp[MX];
int num[MX];
int a[MX];
int b[MX];
int prime[MX];


class Algo{
 public:

} ;

class Cyber{
public:


};
class PrimeFactorization:public Algo{
public:
         void Solve()
         {
             int n;read n;
             for(int i=2;i<=n;i++)
             {
                 if(n%i==0)
                 {
                     while(n%i==0)
                     {
                         n=n/i;
                         echo i<<"\n";
                     }
                 }
             }
         }
};

class MargeSort:public Algo{
public:
         void Marge(int lo,int hi)
         {
             if(lo==hi)return;
             int mid=(lo+hi)/2;
             Marge(lo,mid);
             Marge(mid+1,hi);
             int i,j,k;
             for(i=lo,j=mid+1,k=lo;k<=hi;k++)
             {
                 if(i==mid+1)temp[k]=num[j++];
                 else if(j==hi+1)temp[k]=num[i++];
                 else if(num[i]<num[j])temp[k]=num[i++];
                 else temp[k]=num[j++];
             }
             for(k=lo;k<=hi;k++)
             {
                 num[k]=temp[k];
             }
         }
};
class MargeSortInput:public MargeSort{
public:
         void Solve()
         {
             int n;read n;
             int lo=1,hi=n;
             for(int i=lo;i<=hi;i++)
             {
                 read num[i];
             }
             Marge(lo,hi);
             for(int i=1;i<=n;i++)
             {
                 echo num[i]<<"\n";
             }
         }
};

class StringSort:public MargeSort{
public:
         void Solve()
         {
             string s,s2;read s;
             int len=s.size();
             for(int i=0;i<s.size();i++)
             {
                 num[i]=s[i]-'a';
             }
             Marge(0,len);
             for(int i=1;i<=len;i++)
             {
                 s2+=num[i]+'a';
             }
             echo s2<<"\n";
         }
};



class FileInput:public MargeSort{
public:
         void Solve()
         {
             string s3,s4;
             FILE *fp;
             char buffer[256];

             fp=fopen("demo.txt","r");

             if(fp!=NULL)
             {
                 fprintf(fp,"mdsajiburrahman");
             }

            while (fgets(buffer, sizeof(buffer), fp))
            {
               //printf("%s", buffer);
               s3+=buffer;
            }
            ///Now sort the string stored in the file
             for(int i=0;i<s3.size();i++)
             {
                 num[i]=s3[i]-'a';
             }
             Marge(0,s3.size());
             for(int i=1;i<=s3.size();i++)
             {
                 s4+=num[i]+'a';
             }
             echo s4<<"\n";
             fclose(fp);
         }
} ;

start_
do
   MargeSortInput msi;
   msi.Solve();


   PrimeFactorization pf;
   pf.Solve();

   StringSort ss;
   ss.Solve();

   FileInput fi;
   fi.Solve();


   finish
done

