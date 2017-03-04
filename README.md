**Description**

Simple pam module that uses usb device as an authentication source.

**How to use**

Get source code.

~~~~
mkdir build
cd build
cmake ../pam_usb/
make
make install
~~~

Create pam_usb.conf in /etc/ with device description:

~~~~
#sample configuration file
manufacturer = LGE
product = Nexus 5
serialNumber = 123456789abcd
idVendor = 3d4c
idProduct = 1a2b
~~~~

Add of the corresponding pam module:
example for sudo:
auth    sufficient      pam_usb_auth.so

