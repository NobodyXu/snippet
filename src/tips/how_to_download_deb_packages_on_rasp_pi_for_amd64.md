First, run `dpkg --add-architecture arch_you_want && apt update` (optionally, you can add a proxy) then use the following function to download:

```
Download() {
    list="$@"

    while [ -n "$list" ]; do
	dependencies=""

        for each in $list; do
            apt-get download "$each"
            dependencies+=$(apt-cache depends "$each" |  grep -E 'Depends' | cut -d ':' -f 2,3 | sed -e s/'<'/''/ -e s/'>'/''/)
	done
        list="$dependencies"
    done
}
```

or a faster `bash` but fail if one package does not find:

```
Download() {
    list="$@"

    while [ -n "$list" ]; do
	apt-get download "$list"
        dependencies=$(apt-cache depends "$list" |  grep -E 'Depends' | cut -d ':' -f 2,3 | sed -e s/'<'/''/ -e s/'>'/''/)
        list="$dependencies"
    done
}
```

or a more efficient `python3` script wit deduplication:

```
#!/usr/bin/env python3

import sys
import subprocess

if len(sys.argv) == 1:
    print("Usage", sys.argv[0], "package ....")
    print("E.x.,", sys.argv[0], "perl:amd64")
    sys.exit()

Set = set()                # All packages processed
List = set(sys.argv[1 : ]).remove(" ") # To Remove duplicate

while len(List) != 0:
    dependencies = set()

    for each in List:
        command = ["/usr/bin/apt-get", "download", each]
	print("Running", command)
        download = subprocess.Popen(command, stdin = subprocess.DEVNULL, close_fds = True, restore_signals = True)

        command = ["/usr/bin/apt-cache", "depends", each]
	print("Running", command)
        cache = subprocess.Popen(command, stdout = subprocess.PIPE, close_fds = True, restore_signals = True)

	command = ["/bin/grep", "-E", "Depends"]
	print("Running", command)
        grep = subprocess.Popen(command, stdin = cache.stdout, stdout = subprocess.PIPE, close_fds = True, restore_signals = True)

	command = ["/usr/bin/cut", "-d", ":", "-f", "2,3"]
	print("Running", command)
        cut = subprocess.Popen(command, stdin = grep.stdout, stdout = subprocess.PIPE, close_fds = True, restore_signals = True)

	command = ["/bin/sed", "-e", "s/<//", "-e", "s/>//"]
	print("Running", command)
        sed = subprocess.Popen(command, stdin = cut.stdout, stdout = subprocess.PIPE, close_fds = True, restore_signals = True)

	out = str(sed.stdout.read())[3 : -1]   # Convert byte string into string
	dependencies_set = { each.strip() for each in out.strip().split("\\n") } # Split into list and convert into set
	dependencies |= dependencies_set

        sed.wait()
	cache.wait()
	grep.wait()
	cut.wait()

	download.wait() # Wait for the download to finish

    Set |= List         # All items in the List have already been processed.
    dependencies -= Set # Remove package already processed.
    List = dependencies
```

If you want to download larget set of packages and is bored of doing this, check out [apt-cross-download](https://github.com/NobodyXu/apt-corss-download]/

# Reference:

 1. https://askubuntu.com/questions/430705/how-to-use-apt-get-to-download-multi-arch-library
 2. https://unix.stackexchange.com/questions/115272/download-package-via-apt-for-another-architecture
