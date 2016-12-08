all: ex_projet2

ex_projet2: main.o parser.o instance.o
	 gcc -std=c99 -Wall -Werror -o $@ $<

main.o: main.c
	 gcc -std=c99 -Wall -Werror -c $<

parser.o: parser.c
	 gcc -std=c99 -Wall -Werror -c $<

instance.o: instance.c
	 gcc -std=c99 -Wall -Werror -c $<
     
clean:
	 rm main.o parser.o instance.o ex_projet2

test:
	echo “Tests OK”