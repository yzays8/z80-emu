SRCDIR = src
FILE_PATH = $(abspath $(if $(filter /%,$(FILE)),$(FILE),$(dir $(lastword $(MAKEFILE_LIST)))$(FILE)))

.PHONY: all
all:
	make -C $(SRCDIR)

.PHONY: clean
clean:
	make clean -C $(SRCDIR)

.PHONY: run
run:
	make run FILE=$(FILE_PATH) -C $(SRCDIR)

.PHONY: debug
debug:
	make debug FILE=$(FILE_PATH) -C $(SRCDIR)

.PHONY: header
header:
	make header FILE=$(FILE_PATH) -C $(SRCDIR)
