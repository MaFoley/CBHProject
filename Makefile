#
# Makefile for cbhproj
#
CC=g++
CFLAGS=
OBJ=cbhproj.o UserWait.o opt1.o opt2.o opt3.o opt4.o opt5.o opt6.o opt7.o 

cbhproj: $(OBJ)
	$(CC) -o cbhproj $(OBJ)

cbhproj.o: cbhproj.cpp UserWait.cpp
	$(CC) $(CFLAGS) -c cbhproj.cpp

UserWait.o: UserWait.cpp
	$(CC) $(CFLAGS) -c UserWait.cpp

opt1.o: opt1.cpp
	$(CC) $(CFLAGS) -c opt1.cpp

opt2.o: opt2.cpp
	$(CC) $(CFLAGS) -c opt2.cpp

opt3.o: opt3.cpp
	$(CC) $(CFLAGS) -c opt3.cpp

opt4.o: opt4.cpp
	$(CC) $(CFLAGS) -c opt4.cpp

opt5.o: opt5.cpp
	$(CC) $(CFLAGS) -c opt5.cpp

opt6.o: opt6.cpp
	$(CC) $(CFLAGS) -c opt6.cpp

opt7.o: opt7.cpp
	$(CC) $(CFLAGS) -c opt7.cpp

clean:
	rm cbhproj *.o *.db core mafoley1.tar mafoley1.tar.gz

wipe:
	rm -v *.db
