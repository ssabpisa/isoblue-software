GCC = gcc 
CFLAGS = -Wall -Wshadow -O3
VALGRIND = valgrind --leak-check=full --track-origins=yes
SIMCAN = bash ../tools/resend_can.sh vcan0 ../tools/combine_can2_2 &> /dev/null

filter: filter.o setup.o
	$(GCC) -g filter.o -o filter
	$(GCC) -g setup.o -o setup -lbluetooth
	
filter.o: filter.c
	$(GCC) filter.c -c

setup.o: setup.c
	$(GCC) setup.c -c

sview: 
	$(GCC) viewsetting.c -o viewsetting
	./viewsetting isoblue_setting.config

sim_all:
	#bash ../tools/resend_can.sh vcan0 ../tools/combine_can2_2 &> /dev/null
	$(SIMCAN)
	./filter vcan0 vcan0 bad isoblue_setting.config
sim_block:
	$(SIMCAN)
	./filter vcan0 vcan0 -f isoblue_setting.config
clean: 
	rm filter
	rm *.o
