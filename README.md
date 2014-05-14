# Coffee++

## Windows

Set up [MSYS2](http://sourceforge.net/p/msys2/wiki/MSYS2%20installation/) and install Python, GCC
and Boost:

```
pacman -S python mingw-w64-x86_64-gcc mingw-w64-x86_64-boost
```

## Build

```
./waf configure
./waf
```

## Usage

```
./build/coffee++ test.cf++
```
