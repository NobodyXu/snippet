First, run `dpkg --add-architecture arch_you_want && apt update` (optionally, you can add a proxy) then use the following function to download:

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

# Reference:

 1. https://askubuntu.com/questions/430705/how-to-use-apt-get-to-download-multi-arch-library
 2. https://unix.stackexchange.com/questions/115272/download-package-via-apt-for-another-architecture
