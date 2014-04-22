class County
{
    public:
        County();
        ~County();
        int GetMinCode() const {return _minCode; }
        int GetMaxCode() const { return _maxCode; }
        int GetRecordLength() const { return _recordLength; }
        int GetNumberCounties() const { return _numberCounties; }
        char * GetCounties() const { return _pCounties; }
        char * GetCounty(int inCountyCode) const;
        void DisplayCounties() const;
    private:
        int _minCode;
        int _maxCode;
        int _recordLength;
        int _numberCounties;
        char * _pCounties;
        char * _pCounty;
};
