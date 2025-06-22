#include <iostream>
#include <cstdlib>

int main() {

    // Run commands inside WSL Ubuntu
    system("wsl -d Ubuntu -- bash -c 'echo Hello from C++; sudo apt-get install figlet -y ;figlet HELLO WORLD;ifconfig;sudo apt-get install nmap;nmap --version;cmd;dir; echo hello vi; mkdir abcd_kingkhan;'");

    return 0;
}

