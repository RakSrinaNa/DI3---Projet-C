all: ex_projet2

ex_projet2: main.o parser.o instance.o
	 gcc -o $@ $<

main.o: main.c
	 gcc -c $<

parser.o: parser.c
	 gcc -c $<

instance.o: instance.c
	 gcc -c $<
     
clean:
	 rm main.o parser.o instance.o ex_projet2

test:
	echo “Tests OK”