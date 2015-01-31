# lsvm
A small program to list virtual machines from cli on vSphere

** PLEASE NOTE: whilst this only reads from a number of files, it's not really production ready

This program has the some functionality as the command line:
~~shell
# vim-cmd vmsvc/getallvms
~~~

However in another project I didn't want to rely on having to spawn external commands so developed a rather convoluted method for finding registered virtual machines.
This program will read through the vmInventory.xml file, this uses libxml2 (which luckily is part of vSphere) and returns the full paths to the .vmx files that make up the virtual machines. It will then parse those files and return the virtual machine name, which is specified with the Key "DisplayName".

To compile use the following line:
~~shell
 gcc -Wall -o lsvm -std=c99 $(xml2-config --cflags) $(xml2-config --libs) lsvm.c
~~~
