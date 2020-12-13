ParkingLotManagement_exe : main.o myutil.o history.o
	gcc -o ParkingLotManagement_exe main.o myutil.o history.o

main.o : main.c
	gcc -c -o main.o main.c

myutil.o : myutil.c
	gcc -c -o myutil.o myutil.c

history.o : history.c
	gcc -c -o history.o history.c

clean:
	rm *.o ParkingLotManagement_exe
