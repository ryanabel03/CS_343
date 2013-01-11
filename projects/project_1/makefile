CC = gcc
CFLAGS = -g -Wall

c4_objects = connect4.o connect4_engine.o
c4: $(c4_objects)
	gcc $(CFLAGS) $(c4_objects) -o $@

c4_test_objects = connect4_engine.o CuTest.o c4_engine_test.o
c4_test: $(c4_test_objects)
	gcc $(CFLAGS) $(c4_test_objects) -o $@
