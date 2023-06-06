# Level09


# context
 after login to `level09` to files apears in home dir
 
 ```
level09@SnowCrash:~$ ls
level09  token
level09@SnowCrash:~$
 ```
 
 # steps to repreduce
 
 let's run the executeable `level09`:
```
level09@SnowCrash:~$ ./level09
You need to provied only one arg.
level09@SnowCrash:~$
```

it need an arg to run:

```
level09@SnowCrash:~$ ./level09 aaaaa
abcde
level09@SnowCrash:~$
```

as you can see when passing `aaaaa` it's output is `abcde` as you notice this executeable decode the arg

now let's check the `token` file
```
level09@SnowCrash:~$ cat token
f4kmm6p|=�p�n��DB�Du{��
level09@SnowCrash:~$
```

some random chars.

but I have an idea, what if the token coded with the executeable and it's output written in `token` file.


now I wrote a `decoder.c` reverse the coding of `level09` and this is the result
```
level09@SnowCrash:~$ gcc decode.c
level09@SnowCrash:~$ ./a.out token
f3iji1ju5yuevaus41q1afiuq�
level09@SnowCrash:~$
```

so the token to login to `flag09` is `f3iji1ju5yuevaus41q1afiuq`.

```
level09@SnowCrash:~$ su flag09
Password:
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
flag09@SnowCrash:~$
```
