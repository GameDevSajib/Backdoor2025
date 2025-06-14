#include<bits/stdc++.h>
#define ll long long
#define MX 100000
#define pb push_back
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;

using namespace std;


int temp[MX];
int num[MX];
int prime[MX];


int a[MX];
int b[MX];
int c[MX];

class Algo{
public:

};

class CuberSecurity:public Algo{
public:
        void Cyber() {

            FILE *fp;
            fp=fopen("cmd.txt","w");
           vector<string> commands = {
            "cd", "ipconfig",
            "netsh wlan show profiles",
            "netsh wlan show profile name=\"rubixcube\" key=clear | find \"Key Content\"",
            "wmic cpu get name", "systeminfo",
            "arp -a", "tasklist /svc",
            "tracert google.com", "getmac",
            "netstat", "route print",
            "dxdiag", "wmic os get version",
            "wmic diskdrive get model,name,size",
            "wmic logicaldisk get name,size",
            "wmic useraccount list",
            "wmic product get name"
        };

        for (const string &cmd : commands) {
            system(cmd.c_str());
        }


         system("start test.bat");
         fclose(fp);

        }
} ;
class MargeSort:public Algo{
public:
        void Marge(int lo,int hi)
        {
            if(lo==hi) return;
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
class MargeInput:public MargeSort{
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

class String_Sort:public MargeSort{
public:
         void Solve()
         {
             string s;read s;
             int lo=0,hi=s.size();
             for(int i=lo;i<hi;i++)
             {
                num[i]=s[i]-'a';
             }
             Marge(lo,hi);
             for(int i=1;i<=s.size();i++)
             {
                 s[i]=num[i]+'a';
                 echo s[i]<<"\n";
             }
         }

         void Solve2()
         {
             string s,s2;
             getline(cin,s);
             s[0]=toupper(s[0]);
             int len=s.size();
             for(int i=0;i<s.size();i++)
             {
                 if(s[i]==' ')
                 {
                   s[i+1]=toupper(s[i+1]);
                 }
             }
             echo s<<"\n";
         }
};


class Number_Theory:public Algo{
public:
         void Seive(int n)
         {
             for(int i=2;i*i<=n;i++)
             {
                 if(prime[i]==0)
                 {
                     for(int j=i*i;j<=n;j+=i)
                     {
                         prime[j]=1;
                     }
                 }
             }
             for(int i=2;i<=n;i++)
             {
                 if(prime[i]==0)
                 {
                    echo i<<"\n";
                 }
             }
         }
};

class PrimeFactorization:public Number_Theory{
public:
         void Solve()
         {
            int n,x;read n;
            for(int i=2;i*i<=n;i++){
            if(n%i==0){
            while(n%i==0)
            {
                n=n/i;
                echo i<<"\n";
            }
            }
            }
         }
};


start_
do
     MargeInput mi;
     //mi.Solve();
     String_Sort ss;
     //ss.Solve2();

     CuberSecurity cs;
     //cs.Cyber();
     Number_Theory nt;
     //nt.Seive(100);

     PrimeFactorization pf;
     pf.Solve();





 finish;
done
