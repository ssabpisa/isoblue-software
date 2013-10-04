GCC = gcc 
CFLAGS = -Wall -Wshadow -O3
VALGRIND = valgrind --leak-check=full --track-origins=yes
SIMCAN = bash ../tools/resend_can.sh vcan0 ../tools/combine_can2_2 &> /dev/null

client: mock_device.o
	$(GCC) -g mock_device.o -o mock_device -lbluetooth

mock_device.o: mock_device.c
	$(GCC) mock_device.c -c -lbluetooth

testsend: 
	./mock_device 00:01:95:14:97:F8 setfilter 65226 65399 61443 61444 endfilter	
