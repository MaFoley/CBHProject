class State
{
    public:
        State();
        ~State();
        int GetMinCode() const {return _minCode; }
        int GetMaxCode() const { return _maxCode; }
        int GetRecordLength() const { return _recordLength; }
        int GetNumberStates() const { return _numberStates; }
<<<<<<< HEAD
        char * GetStates() const { return _pStates; }
        /*
        char * GetState( int inStateCode; ) const;
        void DisplayStates() const;
        */
=======

        char * GetStates() const { return _pStates; }
        char * GetState(int inStateCode) const;
        //void DisplayStates() const;
>>>>>>> 52e8a7e133ac800bfbd901e45ab4279a897ff9fe
    private:
        int _minCode;
        int _maxCode;
        int _recordLength;
        int _numberStates;
        char * _pStates;
        char * _pState;
};
