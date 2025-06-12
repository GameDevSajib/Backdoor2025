#include <iostream>
#include <vector>
using namespace std;

class CyberSecurity {
public:
    void Cyber() {
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
    }
};

int main() {
    CyberSecurity cs;
    cs.Cyber();
    return 0;
}

