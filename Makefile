
all: helloworld attrtest


helloworld: src/helloworld.c
	cc src/helloworld.c -lncurses -o helloworld

attrtest: src/attrtest.c
	cc src/attrtest.c -lncurses -o attrtest

clean:
	rm helloworld attrtest
