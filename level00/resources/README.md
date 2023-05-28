# Level00:

# Context:

after logged in with user `level00`, I ended up with an empty home directory:

```
level00@SnowCrash:~$ ls
level00@SnowCrash:~$ ls -la
total 12
dr-xr-x---+ 1 level00 level00  100 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-xr-x---+ 1 level00 level00  220 Apr  3  2012 .bash_logout
-r-xr-x---+ 1 level00 level00 3518 Aug 30  2015 .bashrc
-r-xr-x---+ 1 level00 level00  675 Apr  3  2012 .profile
level00@SnowCrash:~$
```

# Steps to reproduce

The point is I have to look up for a file contain the password of user `flag00` so I can login and get the flag using the command `getflag`.

first thing I thinked of is to try find file named `flag00` in the root directory.
```
level00@SnowCrash:~$ find / -iname "flag00" 2>/dev/null
level00@SnowCrash:~$
```
yes, I found nothing cuz it can't be that easy right?

the point is there's no file named `flag00` but user is.

now I have to find a file OWNED by the user `flag00`, but I can't look at all the files and run the command `ls -la` to check the OWNER of the file.... wait that's exactly what I'm doing.

NOT really.

using the command `find` I can run it with the flag `-ls` and will display the lists the contents of a directory recursively.
so I ran the following command: 

```
level00@SnowCrash:~$ find  -ls
  9945    0 dr-xr-x---   1 level00  level00       100 Mar  5  2016 .
  9950    4 -r-xr-x---   1 level00  level00       220 Apr  3  2012 ./.bash_logout
  9952    4 -r-xr-x---   1 level00  level00      3518 Aug 30  2015 ./.bashrc
  9954    4 -r-xr-x---   1 level00  level00       675 Apr  3  2012 ./.profile
level00@SnowCrash:~$
```
now I need to find out (somehow) how to check all the files in the root directory  and check the OWNER user.

running just the command `find / -ls` will display a loooong list of unwanted files, so I added a filler to display only lines with word `flag00`.

the final command is `level00@SnowCrash:~$ find / -ls | grep  'flag00'`.
output is banch of `Permission denied` and process owned by user `flag00`:
```
87749    0 dr-x--x--x   2 flag00   flag00          0 May 28 13:41 /proc/2269/ns
find: /proc/2269/cwd: Permission denied
find: /proc/2269/root: Permission denied
find: /proc/2269/exe: Permission denied
find: `/proc/2360/task/2360/fd': Permission denied
find:  87750    0 dr-xr-xr-x   5 flag00   flag00          0 May 28 13:41 /proc/2269/net
 87751    0 -r--------   1 flag00   flag00          0 May 28 13:41 /proc/2269/environ
 87752    0 -r--------   1 flag00   flag00          0 May 28 13:41 /proc/2269/auxv
 87753    0 -r--r--r--   1 flag00   flag00          0 May 28 13:41 /proc/2269/status
 87754    0 -r--r--r--   1 flag00   flag00          0 May 28 13:41 /proc/2269/personality
 87755    0 -r--r--r--   1 flag00   flag00          0 May 28 13:41 /proc/2269/limits
```
but in the end this apears:
```
find: `/tmp': Permission denied
 13314    4 ----r--r--   1 flag00   flag00         15 Mar  5  2016 /usr/sbin/john
find: `/var/cache/ldconfig': Permission denied
find: `/var/lib/php5': Permission denied
find: `/var/lib/sudo': Permission denied
find: `/var/spool/cron/atjobs': Permission denied
find: `/var/spool/cron/atspool': Permission denied
find: `/var/spool/cron/crontabs': Permission denied
find: `/var/tmp': Permission denied
find: `/var/www/level04': Permission denied
find: `/var/www/level12': Permission denied
find: `/rofs/etc/chatscripts': Permission denied
find: `/rofs/etc/ppp/peers': Permission denied
find: `/rofs/etc/ssl/private': Permission denied
find: `/rofs/home': Permission denied
find: `/rofs/root': Permission denied
 37740    1 ----r--r--   1 flag00   flag00         15 Mar  5  2016 /rofs/usr/sbin/john
find: `/rofs/var/cache/ldconfig': Permission denied
```
yeah, Two files in `bin` directory owned by the user `flag00`.

when I tryed to execute the file I get permission denied OFC.

```
level00@SnowCrash:~$ /usr/sbin/john
bash: /usr/sbin/john: Permission denied
level00@SnowCrash:~$
```

so I tryed to read it's containt using command `cat`:
```
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
level00@SnowCrash:~$
```

![yes Finaly](https://thumbs.gfycat.com/FaithfulAnchoredItalianbrownbear-max-1mb.gif)

FOUND IT. let's login now

```
level00@SnowCrash:~$ su flag00
Password:
su: Authentication failure
level00@SnowCrash:~$
```
![Not That easy](https://media.tenor.com/Bwd7SMI-st8AAAAM/its-not-that-simple-mike-mclusky.gif)

ofc password is decripted.

after decode the password in https://www.dcode.fr/chiffre-cesar, the password is `nottoohardhere`, 

The moment we all waited for 
```
level00@SnowCrash:~$ su flag00
Password:
Don't forget to launch getflag !
flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
flag00@SnowCrash:~$
```
