GrabCut: functions.o main.o
	g++ -O2 -m64 functions.o main.o -o GrabCut `pkg-config opencv --cflags --libs`

main.o: main.cpp main.hpp
	gcc -O2 -m64 -c main.cpp -o main.o
functions.o: functions.cpp functions.hpp
	gcc -O2 -m64 -c functions.cpp -o functions.o

clean :
	/bin/rm -rf *.o *~
	/bin/rm -rf $(C_EX) $(CPP_EX)
	/bin/rm -rf *.mps *.ord *.sos *.lp *.sav *.net *.msg *.log


