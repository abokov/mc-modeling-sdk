# How to build

## Linux

### Prerequisites
If you're developer 100% you may skip reading that - I sure that already have git, g++ and all other packets installed. Requirement are standart - g++ compiler and make tool, usually it's enough to install them from standart repository:
```bash
sudo apt-get install g++
```
Also if you will fork/clone that repo from github (recommended way, but you also may download zip by some unknown reason ), so don't forget about that
```
sudo apt-get install git
```
### How to build standalone package

Get sources from github:
```bash
git clone git@github.com:abokov/mc-modeling-sdk.git
```
Compile everything :
```bash
cd mc-modeling-sdk
make clean
make
```
### How to build Azure based packages

In case of build for Azure you need to install and build two SDK - [Azure Storage SDK C++](https://github.com/Azure/azure-storage-cpp) which based on [C++ REST SDK](https://github.com/Microsoft/cpprestsdk).
Let's start from C++ REST SDK - please refer to [C++ REST SDK: How to build for linux](https://github.com/Microsoft/cpprestsdk/wiki/How-to-build-for-Linux) for details
```
git clone git@github.com:Microsoft/cpprestsdk.git
cd cpprestsdk/Release
mkdir build.debug
cd build.debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```

```
```

## Windows
_to_be_done_soon_
I'm working on that - see [Add windows build](../issues/1)


