CC=clang
LD=ld

LDFLAGS=-lc
CCFLAGS=

EXEC=bin/a.out
OBJECTS=src/main.o \
	src/accumulate.o \
	 
default: run

%.o: %.c
	$(CC) -c $< -o $@ $(CCFLAGS)

$(EXEC): $(OBJECTS)
	$(LD) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

run: $(EXEC)
	$(EXEC)

clean:
	-rm -rf $(EXEC) $(OBJECTS)