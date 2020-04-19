[![Format](https://github.com/sensuikan1973/C_Compiler_Practice/workflows/Format/badge.svg)](https://github.com/sensuikan1973/C_Compiler_Practice/actions)
[![Format](https://github.com/sensuikan1973/C_Compiler_Practice/workflows/Test/badge.svg)](https://github.com/sensuikan1973/C_Compiler_Practice/actions)

# C_Compiler_Practice

https://www.sigbus.info/compilerbook

## x86 and amd64 instruction reference

https://www.felixcloutier.com/x86/

## Development with Docker
ref. https://www.sigbus.info/compilerbook#docker

### setup

```sh
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

## Tips

- [Online Compiler](https://godbolt.org/z/RyNqgE)
