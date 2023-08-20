
all: helloworld attrtest centering


helloworld: src/1_helloworld.c
	cc src/1_helloworld.c -lncurses -o helloworld

attrtest: src/2_attrtest.c
	cc src/2_attrtest.c -lncurses -o attrtest

centering: src/3_centered.c
	cc src/3_centered.c -lncurses -o centering -ggdb

clean:
	rm helloworld attrtest centering
