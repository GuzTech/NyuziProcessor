# 
# Copyright (C) 2015 Oguz Meteer
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
# 

TOPDIR=../..
LIBCDIR=$(TOPDIR)/software/libc
LIBOSDIR=$(TOPDIR)/software/libos
LIBRENDERDIR=$(TOPDIR)/software/librender
BINDIR=$(TOPDIR)/bin
COMPILER_DIR=/usr/local/llvm-nyuzi/bin
CC=$(COMPILER_DIR)/clang
ELF2HEX=$(COMPILER_DIR)/elf2hex
EMULATOR=$(BINDIR)/emulator
CFLAGS=-g -Wall -W -O3 -fno-rtti -std=c++11 -I$(LIBCDIR)/include -I$(LIBOSDIR) -I$(LIBRENDERDIR)
BASE_ADDRESS=0
LIBS=$(LIBCDIR)/crt0.o $(LIBCDIR)/libc.a $(LIBOSDIR)/libos.a $(LIBRENDERDIR)/librender.a

all: raytracer.hex
	

raytracer.elf:
	@echo "Building raytracer.cpp"
	$(CC) $(CFLAGS) raytracer.cpp math/sphere.cpp graphics/camera.cpp $(LIBS) -o raytracer.elf

raytracer.hex: raytracer.elf
	@echo "Creating raytracer.hex"
	$(ELF2HEX) -o raytracer.hex raytracer.elf

run: raytracer.hex
	@echo "Starting emulator"
	$(EMULATOR) -f 800x600 -t 1 raytracer.hex

clean:
	rm -f raytracer.elf raytracer.hex *.o

