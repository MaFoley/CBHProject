#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include "Vehicle.h"
#include "VehicleFile.h"

using namespace std;
const int RECORDSIZE = 25;
string SSNNoHyphens(const string &);

VehicleFile::VehicleFile():
    _recordSize(RECORDSIZE)
{
    char VEHICLEFILE[] =  "vehicle.db";
    int initZero = 0;

    fstream vehicle1(VEHICLEFILE, ios::in | ios::out | ios::binary);

    if(!vehicle1.is_open())
    {
        ofstream vehicle2(VEHICLEFILE);
        vehicle2.seekp(0);
        vehicle2.write((char *) &initZero, sizeof(initZero));
        vehicle2.close();
    }
    else
    {
        vehicle1.close();
    }


    _vehicleFile.open(VEHICLEFILE, ios::in | ios::out | ios::binary);

    if( !_vehicleFile)
    {
        cerr << "Error opening file: " << VEHICLEFILE << endl;
    }
    else
    {
        _vehicleFile.seekg(0);
        _vehicleFile.read((char *) &_numberVehicles, sizeof(_numberVehicles));
    }
}
/*
void VehicleFile::AddVehicle(Vehicle & aVehicle)
{
    ++_numberVehicles;
    _currentRecordNumber = _numberVehicles;
    _vehicleFile.seekp(0);
    _vehicleFile.write((char *) &_numberVehicles, sizeof(_numberVehicles));
    UpdateVehicle(aVehicle);
    SortBySSN();
}
*/
void VehicleFile::UpdateVehicle(Vehicle & aVehicle)
{
    string record;
    record = aVehicle.Recordify();
    _vehicleFile.seekp(_currentRecordNumber*RECORDSIZE);
    _vehicleFile.write(record.c_str(), RECORDSIZE);
}

void VehicleFile::SortBySSN()
{
    bool sorted;
    char input1[RECORDSIZE];
    char input2[RECORDSIZE];
    int numPass;
    int i;

    numPass = 1;
    sorted = false;

    while(!sorted)
    {
        sorted = true;
        for( i = 1; i <= _numberVehicles - numPass; ++i)
        {
            _vehicleFile.seekg(i * _recordSize);
            _vehicleFile.read(input1, _recordSize);
            _vehicleFile.seekg((i+1) * _recordSize);
            _vehicleFile.read(input2, _recordSize);
            
            if(strncmp(input1,input2,9) < 0)
               continue;
            //Beyond this point only runs if input1 > input2


            _vehicleFile.seekp(i * _recordSize);
            _vehicleFile.write(input2, _recordSize);
            _vehicleFile.seekp((i+1) * _recordSize);
            _vehicleFile.write(input1, _recordSize);
            sorted = false;
        }
    }
    ++numPass;
}
VehicleFile::~VehicleFile()
{
    _vehicleFile.close();
}

Vehicle VehicleFile::SearchBySSN(const string & aSSN)
{
    int first;
    int last;
    int midpoint;
    int icompare;
    char dataRecord[RECORDSIZE];
    string ssnSearch;
    Vehicle foundVehicle;

    foundVehicle.SetFound(false);
    ssnSearch = SSNNoHyphens(aSSN);
    first=1;
    last=_numberVehicles;

    while(true)
    {
        if(first > last) return foundVehicle;
        midpoint=(first+last)/2;
        _vehicleFile.seekg(midpoint*RECORDSIZE);
        _vehicleFile.read(dataRecord,RECORDSIZE);
        icompare =  strncmp(ssnSearch.c_str(),dataRecord,9);

        if(icompare < 0) last=midpoint-1;
        if(icompare > 0) first=midpoint+1;
        if(icompare == 0)
        {
            _currentRecordNumber=midpoint;
            foundVehicle.MakeVehicle(dataRecord);
            if(foundVehicle.IsDeleted())
                foundVehicle.SetFound(false);
            return foundVehicle;
        }
    }
}
Vehicle VehicleFile::SearchByRecordNumber(const int & inRecordNumber)
{
    char dataRecord[RECORDSIZE];
    int icompare;
    Vehicle foundVehicle;
    if(inRecordNumber < 1 || inRecordNumber > _numberVehicles)
    {
        foundVehicle.SetFound(false);
        return foundVehicle;
    }

    _vehicleFile.seekg(inRecordNumber*RECORDSIZE);
    _vehicleFile.read(dataRecord, RECORDSIZE);

    _currentRecordNumber = inRecordNumber;
    foundVehicle.MakeVehicle(dataRecord);
    if(foundVehicle.IsDeleted())
        foundVehicle.SetFound(false);
    return foundVehicle;
}
    
        
