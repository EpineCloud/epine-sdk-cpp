# Intro

Architecture is taken from https://github.com/socketio/socket.io-client-cpp/

# Install

1) Clone repo with submodules
```
  git clone --recurse-submodules -j8  git@github.com:EpineCloud/epine-sdk-cpp.git
```

2) Build and install dependency library `sioclient`

```
  cd lib/sio
  cmake -DCMAKE_INSTALL_PREFIX=. .
  make install
```

3) Build library
```
  cmake .
  make
```

# Notes

## Unreal Engine build

Additional Unreal Engine build configuration included in `EpineSDK.Build.cs`

## Compilation on Mac with arm64

To generate `x86_64` libraries use prefix `-DCMAKE_OSX_ARCHITECTURES=x86_64`

## Compilation on newer OSX for Unreal Engine

To change OSX deployment target use prefix `-DCMAKE_OSX_DEPLOYMENT_TARGET=10.14`


## Examples combined
Build dependency
```
  cd lib/sio
  cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.14  -DCMAKE_OSX_ARCHITECTURES=x86_64 -DCMAKE_INSTALL_PREFIX=. .
  make install
```

Build library
```
  cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.14  -DCMAKE_OSX_ARCHITECTURES=x86_64 .
  make
```
