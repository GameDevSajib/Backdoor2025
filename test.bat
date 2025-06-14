netsh wlan show profiles
netsh wlan show profile name=\"rubixcube\" key=clear | find "Key Content"

wmic cpu get name
arp -a