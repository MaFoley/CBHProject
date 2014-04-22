class VType
{
    public:
        VType();
        ~VType();
        int GetMinCode() const {return _minCode; }
        int GetMaxCode() const { return _maxCode; }
        int GetRecordLength() const { return _recordLength; }
        int GetNumberVTypes() const { return _numberVTypes; }
        char * GetVTypes() const { return _pVTypes; }
        char * GetVType(int inVTypeCode) const;
        void DisplayVTypes() const;
    private:
        int _minCode;
        int _maxCode;
        int _recordLength;
        int _numberVTypes;
        char * _pVTypes;
        char * _pVType;
};
