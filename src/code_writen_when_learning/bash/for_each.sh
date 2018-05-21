#!/bin/bash
content_of_loop() {
    printf "%s\n" $file
    ls -la $file
}
for file in "*"
do
    content_of_loop
done
exit 0;
