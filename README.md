# Tianmouc SDK miniomum version

## usages

require OS: >= ubuntu_20

### If you have the access to the source code of tianmouc-sdk full version

1. install cyusb, opencv, lib-usb-1.0-dev
2. cp libcyusb.so to ./lib
3. run 'sh compile.sh'
4. run the somple application for tianmouc-v1 by ./build/tianmoucv_app
5. you can also use the ./build/libtianmouc.so for further development

### If you dont have the access

- only x86 supported because the shared .so files are compiled under x86, ubuntu24.04

1. You can find another cmake file in ./lib, use it to replace the defualt one
2. compile this project, you can still get the app


## development log

- init version 20241104
-- bug: memory leak, cannot find where is the bug
-- bug2: bad cone decoded result??
-- bug3: cannot use disableSync api, repost "free( ) invalid xxx"
-- bug4: very dirty stop
- updated version 20240906
- fixed all bugs
- minimum develop kit

# readme for AF demo

### requirements

if you have already install all the support for tianmouc, you would meet the requirments


1. libusb-1.0
$ sudo apt-get install libusb-1.0-0-dev

2. g++
$ sudo apt-get install g++

### usage

1. compile the demo

$ cd demo
$ sh compile.sh

2. run as sudo user
$ sudo ./build/tianmouc_app