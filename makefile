#For x86_64 bois
CC=gcc
CFLAGS=-Wall
LIBS=-lcurl -lpthread
LFLAGS=-L/usr/lib/x86_64-linux-gnu

#For ARM bois
#B_ROOT_HOME=/home/franku/Downloads/buildroot-2018.02
#CC=$(B_ROOT_HOME)/output/host/usr/bin/arm-linux-gcc
#CFLAGS=--sysroot=$(B_ROOT_HOME)/output/staging
#LFLAGS=
#LIBS=-lcurl -uClibc -lc

SRC=requestor.c
OBJ=$(SRC:.c=.o)
MAIN=hw

RM=rm -rf

all: $(MAIN)

$(MAIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJ) $(LFLAGS) $(LIBS)

clean:
	$(RM) *o $(MAIN)
