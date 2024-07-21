# pwbrk
gcc -ggdb pwbrk.c pwbrk-utils.c -o brkit -I/usr/include/openssl -l crypto

Edit pwbrk.c and enter the password you'd like to 'guess'
It will eventually just take a pw hash of some type then generate the password.
On my outdated system (over ten years old) a 6 character pw takes a good while to break.
