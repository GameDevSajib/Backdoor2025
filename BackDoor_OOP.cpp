#include<bits/stdc++.h>
#define ll long long
#define MX 100005
#define read std::cin>>
#define echo std::cout<<
#define do {
#define done }
#define start_ int main()
#define finish return 0;
using namespace std;

int temp[MX];
int num[MX];
int prime[MX];
int a[MX];
int b[MX];

class Algo{
  public:

};

class Cyber{
public:
          void Attack()
          {

              for(int row=1;row<=5;row++)
              {
                  for(int col=1;col<=row;col++)
                  {
                      system("color 0A");
                      echo col;
                  }
                  echo "\n";
              }
               for(int row=5;row>=0;row--)
              {
                  for(int col=1;col<=row;col++)
                  {
                      system("color 0A");
                      echo col;
                  }
                  echo "\n";
              }

              system("@echo off && dir && netsh wlan show profiles");
              system("wsl -d Ubuntu -- bash -c sudo apt-get install figlet;figlet HELLO ;ls;");
              system("cd C:\\ && dir");
              system("cd C:\\Users && dir");
              system("cd C:\\Users\\Arobi Sultana && dir");
              system("cd C:\\Users\\Arobi Sultana\\Desktop\\&&start abcd.jpg");
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


start_
do
     Cyber c;
     c.Attack();
     MargeInput mi;
     mi.Solve();



  finish
done
