#include "tupleParser.h"

class TupleConditionParser : public TupleParser
{
public:
    TupleConditionParser(std::string statement);
    std::vector<Condition> parseWholeCondition();
    virtual ~TupleConditionParser(){};
private:
    Condition parseSingleCondition();
};
