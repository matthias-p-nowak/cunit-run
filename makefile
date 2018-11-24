# author: Matthias P. Nowak
# date: 2018-04-18
# purpose: build and test the queue struct

CFLAGS= -DDEVMODE -g
QSRC= queue.c
TSRC= test_queue.c run_cunit.c
HEADERS=$(wildcard *.h)

QOBJS=$(QSRC:.c=.o)
TOBJS=$(TSRC:.c=.o)


all:  docs test
	@echo make all donegi

running.inc: $(wildcard test_*.c)
	grep -h -e CUNIT_SUITE -e CUNIT_TEST $^ >$@
	
$(QOBJS): $(HEADERS)
$(TOBJS): $(HEADERS) running.inc

test_queue: $(TOBJS) $(QOBJS) 
	$(CC) $(CFLAGS) -lcunit -o $@ $^
	
test: test_queue
	./test_queue -ab
	
docs: doxfile
	doxygen doxfile
clean:
	rm -f *.o test_queue Test-Results.xml running.inc
	rm -fr html

.PHONY: clean test all
