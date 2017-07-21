# Coffee++

## Linux

Fedora:

```
sudo dnf install gcc-c++ boost-devel waf-python3
```

Ubuntu:

```
sudo apt install python3 g++ libboost-program-options-dev libboost-test-dev
```

## Windows

Set up [MSYS2](http://www.msys2.org/) and install Waf, GCC and Boost:

```
pacman -S mingw-w64-x86_64-waf mingw-w64-x86_64-gcc mingw-w64-x86_64-boost
```

## Build

```
waf
```

On Ubuntu you'll need to run the included Waf binary instead:

```
./waf
```

## Usage

```
./build/coffee++ test.cf++
```
