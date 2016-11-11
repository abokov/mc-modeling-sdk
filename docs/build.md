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

### Trouble shooting
It might happened that previously build description won't work for you, so please refer then to more detailed step-by-step instruction below.
1) Install all the needed build tools and libraries
```
sudo apt-get install g++ git make libboost-all-dev libssl-dev cmake
```
Minimum versions required:
    g++: 4.8
    libboost: 1.54
    libssl: 1.0.0
2) Clone the project using Git (it will be stored in the folder "casablanca") - just in case, actually it should work without mentioning 'casablanca' but sometimes i know it might be helpful.
```
git clone https://github.com/Microsoft/cpprestsdk.git casablanca
```
3) Build SDK in Debug mode
```
cd casablanca/Release
mkdir build.debug
cd build.debug
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```
4) Build SDK in Release mode
```
cd casablanca/Release
mkdir build.debug
cd build.debug
cmake .. -DCMAKE_BUILD_TYPE=Release
make
```
5) Build the SDK in static libs ( my favorite option :-))
```
cd casablanca/Release
mkdir build.debug
cd build.debug
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=0
make
```
6) Checkout test_runner inside binaries folder:
```
cd Binaries
./test_runner *_test.so
```

7) To install on your system run: 
```
sudo make install
```

8) You can check your first program by compiling it using necessary command line arguments
( this one i took from C++ rest doc, need to fix to refer into mc-modeling-sdk )
```
g++ -std=c++11 my_file.cpp -o my_file -lboost_system -lcrypto -lssl -lcpprest
./my_file
```


