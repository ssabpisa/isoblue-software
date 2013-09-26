GCC = gcc 
CFLAGS = -Wall -Wshadow -O3
VALGRIND = valgrind --leak-check=full --track-origins=yes
SIMCAN = bash ../tools/resend_can.sh vcan0 ../tools/combine_can2_2 &> /dev/null

filter: filter.o
	$(GCC) -g filter.o -o filter
filter.o: filter.c
	$(GCC) filter.c -c

sim_all:
	#bash ../tools/resend_can.sh vcan0 ../tools/combine_can2_2 &> /dev/null
	$(SIMCAN)
	./filter vcan0 vcan0
sim_block:
	$(SIMCAN)
	./filter vcan0 vcan0 -f
clean: 
	rm filter
