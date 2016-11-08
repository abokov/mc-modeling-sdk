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
### How to build

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
## Windows
