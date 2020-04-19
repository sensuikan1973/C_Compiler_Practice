[![Format](https://github.com/sensuikan1973/C_Compiler_Practice/workflows/Format/badge.svg)](https://github.com/sensuikan1973/C_Compiler_Practice/actions)
[![Format](https://github.com/sensuikan1973/C_Compiler_Practice/workflows/Test/badge.svg)](https://github.com/sensuikan1973/C_Compiler_Practice/actions)

# C_Compiler_Practice

https://www.sigbus.info/compilerbook

## x86 and amd64 instruction reference

https://www.felixcloutier.com/x86/

## Development with [Docker](https://www.sigbus.info/compilerbook#docker)

### setup

```sh
# See: https://www.sigbus.info/compilerbook#%E3%82%BB%E3%83%83%E3%83%88%E3%82%A2%E3%83%83%E3%83%97%E6%89%8B%E9%A0%86
docker build -t compilerbook https://www.sigbus.info/compilerbook/Dockerfile
```

### interactive

```sh
./scripts/connect.sh
```

### build

```sh
./scripts/build.sh
```

### test

```sh
./scripts/test.sh
```

## Inquiry

- https://github.com/TomoyukiSugiyama/C_Compiler_Practice/issues/4

## Tips

- [Online Compiler](https://godbolt.org/z/RyNqgE)
