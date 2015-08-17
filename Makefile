TEST = driver
CSON_PARSER = cson_parser.o
CSON_OBJ = cson_obj.o
HASH = hash.o
ARRAY = array.o

CC = gcc
CFLAGS = -std=gnu99 -pthread -g

all: $(TEST)

$(TEST): $(CSON_PARSER) $(CSON_OBJ) $(HASH) $(ARRAY)
	$(CC) $(CFLAGS) -o test driver.c $(CSON_PARSER) $(CSON_OBJ) $(HASH) $(ARRAY)

$(CSON_PARSER): cson_parser.c cson_parser.h cson_obj.h array.h
	$(CC) $(CFLAGS) -c cson_parser.c -o $(CSON_PARSER)

$(CSON_OBJ): cson_obj.c cson_obj.h array.h hash.h
	$(CC) $(CFLAGS) -c cson_obj.c -o $(CSON_OBJ)

$(HASH): hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c -o $(HASH)

$(ARRAY): array.c array.h
	$(CC) $(CFLAGS) -c array.c -o $(ARRAY)

clean:
	rm *.o
	rm driver 
