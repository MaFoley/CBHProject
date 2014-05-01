#
# Makefile for cbhproj
#
CC=g++
CFLAGS=
OBJ=cbhproj.o UserWait.o opt1.o DisplayRecord.o opt4.o opt5.o opt6.o opt7.o \
	Color.o County.o State.o VMake.o VType.o Upper.o SSNHyphens.o SSNNoHyphens.o \
	Person.o PersonFile.o Vehicle.o VehicleFile.o ZipHyphens.o ZipNoHyphens.o Trim.o

cbhproj: $(OBJ)
	$(CC) -o cbhproj $(OBJ)

cbhproj.o: cbhproj.cpp UserWait.cpp State.cpp
	$(CC) $(CFLAGS) -c cbhproj.cpp

UserWait.o: UserWait.cpp
	$(CC) $(CFLAGS) -c UserWait.cpp

opt1.o: opt1.cpp UserWait.cpp Color.cpp County.cpp State.cpp VMake.cpp VType.cpp
	$(CC) $(CFLAGS) -c opt1.cpp

DisplayRecord.o: DisplayRecord.cpp PersonFile.cpp Person.cpp Vehicle.cpp VehicleFile.cpp \
	UserWait.cpp SSNHyphens.cpp
	$(CC) $(CFLAGS) -c DisplayRecord.cpp

opt4.o: opt4.cpp SSNHyphens.cpp Trim.cpp UserWait.cpp
	$(CC) $(CFLAGS) -c opt4.cpp

opt5.o: opt5.cpp UserWait.cpp SSNHyphens.cpp
	$(CC) $(CFLAGS) -c opt5.cpp

opt6.o: opt6.cpp Trim.cpp UserWait.cpp SSNHyphens.cpp
	$(CC) $(CFLAGS) -c opt6.cpp

opt7.o: opt7.cpp Person.cpp PersonFile.cpp UserWait.cpp
	$(CC) $(CFLAGS) -c opt7.cpp

Person.o: Person.cpp SSNHyphens.cpp ZipHyphens.cpp ZipNoHyphens.cpp State.cpp County.cpp \
   	Trim.cpp Upper.cpp
	$(CC) $(CFLAGS) -c Person.cpp

PersonFile.o: PersonFile.cpp Person.cpp SSNNoHyphens.cpp
	$(CC) $(CFLAGS) -c PersonFile.cpp

Vehicle.o: Vehicle.cpp SSNHyphens.cpp Color.cpp VType.cpp VMake.cpp Trim.cpp Upper.cpp
	$(CC) $(CFLAGS) -c Vehicle.cpp

VehicleFile.o: VehicleFile.cpp Vehicle.cpp SSNNoHyphens.cpp
	$(CC) $(CFLAGS) -c VehicleFile.cpp

SSNHyphens.o: SSNHyphens.cpp
	$(CC) $(CFLAGS) -c SSNHyphens.cpp

ZipHyphens.o: ZipHyphens.cpp
	$(CC) $(CFLAGS) -c ZipHyphens.cpp

SSNNoHyphens.o: SSNNoHyphens.cpp
	$(CC) $(CFLAGS) -c SSNNoHyphens.cpp

ZipNoHyphens.o: ZipNoHyphens.cpp
	$(CC) $(CFLAGS) -c ZipNoHyphens.cpp

Trim.o: Trim.cpp
	$(CC) $(CFLAGS) -c Trim.cpp

clean:
	rm cbhproj *.o *.db core mafoley1.tar mafoley1.tar.gz

wipe:
	rm -v *.db
