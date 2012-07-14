CC=gcc

INCS= -I ./include

C_FILES= $(wildcard src/*.c) $(wildcard src/*/*.c)

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT=libC+.so
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -shared
	OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT=C+.dll
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
	LFLAGS= -g -L ./lib -shared
	OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
endif

$(OUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) -o $@
	
test: $(OBJ_FILES) test.c
	$(CC) test.c $(CFLAGS) $(OBJ_FILES) -o test
  
obj/%.o: src/%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@
	
obj:
	mkdir obj
	
clean:
	rm $(OBJ_FILES)