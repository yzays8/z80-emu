# z80-emu

## About

This is a minimal custom Z80 (LR35902) emulator. It implements the core features and can pass the all of the [Blargg instruction tests](https://github.com/retrio/gb-test-roms/tree/master/cpu_instrs/individual). The I/O features are not yet implemented.

## Usage

Prepare the file to be loaded in advance.

```sh
make
make run FILE=<file_path>
```
