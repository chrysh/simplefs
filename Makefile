

# SPDX-License-Identifier: GPL-2.0
#
# Makefile for the linux simplefs-filesystem routines.
#

obj-m += simplefs.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

