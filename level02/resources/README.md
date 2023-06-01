# Level02

# Context

after logged in with user `level02` a file named `level02.pcap` pops up in home directory

> A PCAP file is a container for packets captured on a computer network, such as a WiFi or Ethernet network

# Steps to repreduce

as I mention this file contain TCP packages so I need tools to dump packages and read it's containt

first I have to transfer the file from VM to host so I can use `wireshark` to dump packages

```
level02@SnowCrash:~$ scp level02.pcap barimehdi77@192.168.64.1:/Users/barimehdi77/Desktop/1337/snowCrash/level01/resources
Could not create directory '/home/user/level02/.ssh'.
The authenticity of host '192.168.64.1 (192.168.64.1)' can't be established.
ECDSA key fingerprint is e2:0b:66:19:a1:c9:06:55:9a:f7:84:9a:d9:b5:b4:b9.
Are you sure you want to continue connecting (yes/no)? yes
Failed to add the host to the list of known hosts (/home/user/level02/.ssh/known_hosts).
Password:
level02.pcap                                                                                                                                                                    100% 8302     8.1KB/s   00:00
level02@SnowCrash:~$
```

opening the file in wireshark this window opens:
![](https://github.com/barimehdi77/SnowCrash/blob/main/level02/resources/openInWireshark.png)

then follow the packages flow:
![](https://github.com/barimehdi77/SnowCrash/blob/main/level02/resources/readData.png)

display data in hex:
![](https://github.com/barimehdi77/SnowCrash/blob/main/level02/resources/dumpdata.png)

now the password is `66 74 5f 77 61 6e 64 72 7f 7f 7f 4e 44 52 65 6c 7f 4c 30 4c 0d` but in hex so i need to decode it to have plaintext password
using a this site the password is `ft_wandrNDRelL0L`

```
level02@SnowCrash:~$ su flag02
Password:
Don't forget to launch getflag !
flag02@SnowCrash:~$ getflag
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
flag02@SnowCrash:~$
```
