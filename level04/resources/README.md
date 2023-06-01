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
