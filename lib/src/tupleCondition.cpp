#include "tupleCondition.h"

TupleCondition::TupleCondition(std::vector<Condition> statement)
{
    this->statement = statement;
}

std::string TupleCondition::getShortcut() const
{
    std::string shortcut = "";
    for (int i = 0; i < statement.size(); i++)
    {
        switch (statement[i].valueType)
        {
        case intType:
            shortcut.push_back('I');
            break;
        case floatType:
            shortcut.push_back('F');
            break;
        case stringType:
            shortcut.push_back('S');
            break;
        //default:
        //  throw new Excpetion
        };
    }
    return shortcut;
}

    bool TupleCondition::checkCondition(const uxp::Tuple &tpl) const
    {
        auto values = tpl.getValues();
        for (int i = 0; i < statement.size(); i++)
            if (!checkSingleCondition(values[i], statement[i]))
                return false;
        return true;
    }

    bool TupleCondition::checkSingleCondition(std::variant<std::string, u_int32_t, float> singleValue, Condition singleCondition) const
    {
        switch (singleCondition.operationType)
        {
        case equal:
            return singleCondition.value == singleValue;
        case less:
            return singleCondition.value > singleValue;
        case greater:
            return singleCondition.value < singleValue;
        case less_equal:
            return singleCondition.value >= singleValue;
        case greater_equal:
            return singleCondition.value <= singleValue;
        case everything:
            return true;
        default:
            return false;
        }
    }

