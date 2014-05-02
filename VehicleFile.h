#include <fstream>
#include <string>
#include <cstdio>
/*
 *Kissing cousing of PersonFile, only major difference is that VehicleFile does not Search by OLN
 */

using namespace std;
class Vehicle;

class VehicleFile
{
public:
    VehicleFile();
    ~VehicleFile();
    int GetNumberVehicles() const { return _numberVehicles; }
    int GetCurrentRecordNumber() const { return _currentRecordNumber; }
    void SortBySSN();
    Vehicle SearchBySSN(const string & inSSN);
    Vehicle SearchByRecordNumber(const int & inRecordNumber);
    void UpdateVehicle(Vehicle & aVehicle);
    void AddVehicle(Vehicle & aVehicle);
private:
    int _numberVehicles;
    int _recordSize;
    int _currentRecordNumber;
    fstream _vehicleFile;
};
