#include "tupleParser.h"
#include "lindaTuple.h"

class TupleValuesParser : public TupleParser
{
public:
    TupleValuesParser(std::string statement);
    TupleValues parseAllValues();
    virtual ~TupleValuesParser(){};
private:
    SingleTupleValue parseSingleValue();
};
