class VMake
{
    public:
        VMake();
        ~VMake();
        int GetMinCode() const {return _minCode; }
        int GetMaxCode() const { return _maxCode; }
        int GetRecordLength() const { return _recordLength; }
        int GetNumberVMakes() const { return _numberVMakes; }
        char * GetVMakes() const { return _pVMakes; }
        char * GetVMake(int inVMakeCode) const;
        void DisplayVMakes() const;
    private:
        int _minCode;
        int _maxCode;
        int _recordLength;
        int _numberVMakes;
        char * _pVMakes;
        char * _pVMake;
};
