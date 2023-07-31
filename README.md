# z80-emu

## Overview

This is a minimal custom Z80 (LR35902) emulator. It implements the core features and can pass the all of the [Blargg instruction tests](https://github.com/retrio/gb-test-roms/tree/master/cpu_instrs/individual).

## Build

```sh
make
```

## Run

### Standard mode

```sh
make run FILE=<file_path>
```

### Debug mode (Show current state)

```sh
make debug FILE=<file_path>
```

### Header mode (Only parse the header)

```sh
make header FILE=<file_path>
```
