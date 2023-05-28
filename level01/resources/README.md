# Level01

# context
after solving level00 and logged in with `level01` user. you get back to an empty home directory.

now you need to gain privilege of user `flag01` to get the flag.

# Steps to repreduce

I searched on some stratiges/best Practices to gain super user privilege, called **Linux Privilege Escalation**.

first I need to check if I have access to `/etc/shadow` this file contain data about users lile uid and password hash in normal cases this file has to be protected so only super user can read or write:
let's check if i can read this file
```
level01@SnowCrash:~$ cat /etc/shadow
cat: /etc/shadow: Permission denied
level01@SnowCrash:~$
```

as you can see I can't read this file:
```
level01@SnowCrash:~$ ls -la /etc/shadow
-rw-r----- 1 root shadow 4428 Mar  6  2016 /etc/shadow
level01@SnowCrash:~$
```
because this file is protected I need to check another file named `/etc/passwd` this file also contain some info about users.

you may wonder what is the deffirent between `/etc/shadow` and `/etc/passwd`, the first one **aims** at user's password details, while the second **aims** at user account details.
but in some cases they leave hashed password or plain password in `/etc/passwd` and this is an exploit.

let's check if i have access to the `/etc/passwd`:
```
level01@SnowCrash:~$ ls -la /etc/passwd
-rw-r--r-- 1 root root 2477 Mar  5  2016 /etc/passwd
level01@SnowCrash:~$
```

bingo, I can read it, let's check it's containt:
```
level01@SnowCrash:~$ cat /etc/passwd
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
sys:x:3:3:sys:/dev:/bin/sh
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/bin/sh
man:x:6:12:man:/var/cache/man:/bin/sh
lp:x:7:7:lp:/var/spool/lpd:/bin/sh
mail:x:8:8:mail:/var/mail:/bin/sh
news:x:9:9:news:/var/spool/news:/bin/sh
uucp:x:10:10:uucp:/var/spool/uucp:/bin/sh
proxy:x:13:13:proxy:/bin:/bin/sh
www-data:x:33:33:www-data:/var/www:/bin/sh
backup:x:34:34:backup:/var/backups:/bin/sh
list:x:38:38:Mailing List Manager:/var/list:/bin/sh
irc:x:39:39:ircd:/var/run/ircd:/bin/sh
gnats:x:41:41:Gnats Bug-Reporting System (admin):/var/lib/gnats:/bin/sh
nobody:x:65534:65534:nobody:/nonexistent:/bin/sh
libuuid:x:100:101::/var/lib/libuuid:/bin/sh
syslog:x:101:103::/home/syslog:/bin/false
messagebus:x:102:106::/var/run/dbus:/bin/false
whoopsie:x:103:107::/nonexistent:/bin/false
landscape:x:104:110::/var/lib/landscape:/bin/false
sshd:x:105:65534::/var/run/sshd:/usr/sbin/nologin
level00:x:2000:2000::/home/user/level00:/bin/bash
level01:x:2001:2001::/home/user/level01:/bin/bash
level02:x:2002:2002::/home/user/level02:/bin/bash
level03:x:2003:2003::/home/user/level03:/bin/bash
level04:x:2004:2004::/home/user/level04:/bin/bash
level05:x:2005:2005::/home/user/level05:/bin/bash
level06:x:2006:2006::/home/user/level06:/bin/bash
level07:x:2007:2007::/home/user/level07:/bin/bash
level08:x:2008:2008::/home/user/level08:/bin/bash
level09:x:2009:2009::/home/user/level09:/bin/bash
level10:x:2010:2010::/home/user/level10:/bin/bash
level11:x:2011:2011::/home/user/level11:/bin/bash
level12:x:2012:2012::/home/user/level12:/bin/bash
level13:x:2013:2013::/home/user/level13:/bin/bash
level14:x:2014:2014::/home/user/level14:/bin/bash
flag00:x:3000:3000::/home/flag/flag00:/bin/bash
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash <======= THIS WHAT I WAS LOOKING FOR
flag02:x:3002:3002::/home/flag/flag02:/bin/bash
flag03:x:3003:3003::/home/flag/flag03:/bin/bash
flag04:x:3004:3004::/home/flag/flag04:/bin/bash
flag05:x:3005:3005::/home/flag/flag05:/bin/bash
flag06:x:3006:3006::/home/flag/flag06:/bin/bash
flag07:x:3007:3007::/home/flag/flag07:/bin/bash
flag08:x:3008:3008::/home/flag/flag08:/bin/bash
flag09:x:3009:3009::/home/flag/flag09:/bin/bash
flag10:x:3010:3010::/home/flag/flag10:/bin/bash
flag11:x:3011:3011::/home/flag/flag11:/bin/bash
flag12:x:3012:3012::/home/flag/flag12:/bin/bash
flag13:x:3013:3013::/home/flag/flag13:/bin/bash
flag14:x:3014:3014::/home/flag/flag14:/bin/bash
level01@SnowCrash:~$
```

as you can see in the this line `flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash` they left the password in this file.

befor moving on let's take a moment to explain the structure of the `/etc/passwd` file:
![file structure](https://www.cyberciti.biz/media/ssb.images/uploaded_images/passwd-file-791527.png)

From the above image:
1. `Username`: It is used when user logs in. It should be between 1 and 32 characters in length.
2. `Password`: An x character indicates that encrypted password is stored in /etc/shadow file. Please note that you need to use the passwd command to computes the hash of a password typed at the CLI or to store/update the hash of the password in /etc/shadow file.
3. `User ID (UID)`: Each user must be assigned a user ID (UID). UID 0 (zero) is reserved for root and UIDs 1-99 are reserved for other predefined accounts. Further UID 100-999 are reserved by system for administrative and system accounts/groups.
4. `Group ID (GID)`: The primary group ID (stored in /etc/group file)
5. `User ID Info (GECOS)`: The comment field. It allow you to add extra information about the users such as user’s full name, phone number etc. This field use by finger command.
6. `Home directory`: The absolute path to the directory the user will be in when they log in. If this directory does not exists then users directory becomes /
7. `Command/shell`: The absolute path of a command or shell (/bin/bash). Typically, this is a shell. Please note that it does not have to be a shell. For example, sysadmin can use the nologin shell, which acts as a replacement shell for the user accounts. If shell set to /sbin/nologin and the user tries to log in to the Linux system directly, the /sbin/nologin shell closes the connection

the improtant for us is the first `username` and `password` because the user `flag01` has password instead of an `x`.

let's try to login with the given passwrod:
```
level01@SnowCrash:~$ su flag01
Password:
su: Authentication failure
level01@SnowCrash:~$
```

as I expected the password is hashed.

using tool like `john the ripper`, I managed to crack the password;
```
➜  resources git:(main) cat password.txt
42hDRfypTqqnw
➜  resources git:(main) ✗ john password.txt
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 64/64])
Press 'q' or Ctrl-C to abort, almost any other key for status
abcdefg          (?)
1g 0:00:00:00 100% 2/3 100.0g/s 76800p/s 76800c/s 76800C/s veronica..bigman
Use the "--show" option to display all of the cracked passwords reliably
Session completed
➜  resources git:(main) ✗ 
```

finaly now I have password (`abcdefg`) to loggin
```
level01@SnowCrash:~$ su flag01
Password:
Don't forget to launch getflag !
flag01@SnowCrash:~$ getflag
Check flag.Here is your token : f2av5il02puano7naaf6adaaf
flag01@SnowCrash:~$
```
