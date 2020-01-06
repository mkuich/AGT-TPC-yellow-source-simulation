# mkuich simple makefile
CC = g++

USER_SRCS := $(wildcard *.c)
EXE := $(patsubst %.c,%, $(USER_SRCS))

USER_XMLS := $(patsubst %.xml.in,%.xml,$(wildcard *.xml.in))

.PHONY: all depend clean

CFLAGS    :=  -g -Wall `root-config --cflags`
# CXXFLAGS    :=  `root-config --cflags`
# LDFLAGS     :=  `root-config --ldflags`
LDLIBS		:= `root-config --glibs`
CONFIGFILES := --config


all: $(EXE) $(USER_XMLS)

%: %.in
	@echo -n "Generating $@ file..."
	@echo "done"

clean:
	- rm -f $(EXE) $(USER_XMLS)
	
