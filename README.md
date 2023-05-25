# z80-emu

## About

This is a minimal custom Z80 (LR35902) emulator. It implements the core features and can pass the all of the [Blargg instruction tests](https://github.com/retrio/gb-test-roms/tree/master/cpu_instrs/individual).

Note that the STOP instruction is not implemented (it is not checked in the Blargg instruction tests). Also, any other features such as I/O, memory banks are not yet supported.

## Usage

Prepare the file to be loaded in advance. It must be smaller than 32KiB. Large files can't be read because memory banks are not supported.

```sh
make
make run FILE=<file_path>
```
