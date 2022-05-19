#include "lindaCommand.h"
#include <variant>

namespace cmd_interpreter {
    std::string LindaCommand::tupleToString(const uxp::Tuple &tuple) {
        std::string tuple_str = "(";
        for(auto &tuple_element: tuple.getValues()) {
            if(std::holds_alternative<u_int32_t>(tuple_element))
                tuple_str += std::to_string(std::get<u_int32_t>(tuple_element));
            else if(std::holds_alternative<float>(tuple_element))
                tuple_str += std::to_string(std::get<float>(tuple_element));
            else
                tuple_str += "\"" + std::get<std::string>(tuple_element) + "\"";
            tuple_str += ", ";
        }
        if(!tuple.getValues().empty())
            tuple_str.erase(tuple_str.end() - 2, tuple_str.end());
        tuple_str.push_back(')');
        return tuple_str;
    }
} // namespace cmd_interpreter