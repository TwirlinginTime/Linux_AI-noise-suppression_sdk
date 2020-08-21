#common makefile header

DIR_INC = ../include
DIR_BIN = ../bin
DIR_LIB = ../libs

TARGET	= twirlingCaptureSample
BIN_TARGET = $(DIR_BIN)/$(TARGET)

CROSS_COMPILE = 
CFLAGS = -I$(DIR_INC)

LDFLAGS := -L$(DIR_LIB)

LDFLAGS += -lTwirlingCapture -lpthread -lrt -ldl

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

$(BIN_TARGET) : $(OBJECTS)
	$(CROSS_COMPILE)g++ $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o : %.c
	$(CROSS_COMPILE)g++ -c $(CFLAGS) $< -o $@
clean:
	@rm -f *.o $(BIN_TARGET)

.PHONY:clean

#common makefile foot
