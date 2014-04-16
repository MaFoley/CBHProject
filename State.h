class State
{
    public:
        State();
        ~State();
        int GetMinCode() const {return _minCode; }
        int GetMaxCode() const { return _maxCode; }
        int GetRecordLength() const { return _recordLength; }
        int GetNumberStates() const { return _numberStates; }
        char * GetStates() const { return _pStates; }
        /*
        char * GetState( int inStateCode; ) const;
        void DisplayStates() const;
        */
    private:
        int _minCode;
        int _maxCode;
        int _recordLength;
        int _numberStates;
        char * _pStates;
        char * _pState;
};
