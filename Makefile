export CC=gcc
export CFLAGS=-std=c99 -Wall -Werror -W -pedantic
export LDFLAGS=
SRC_DIR=src
EXEC=ex_projet2

all: clall $(EXEC) clean

$(EXEC):
	cd $(SRC_DIR) && $(MAKE) && cd .. && mv $(SRC_DIR)/$(EXEC) .

.PHONY: clean

clean:
	cd $(SRC_DIR) && $(MAKE) $@

clall:
	-rm $(EXEC) && cd $(SRC_DIR) && $(MAKE) $@

test:
	echo “Tests OK”
