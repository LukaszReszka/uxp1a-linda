#include "lindaTuple.h"
#include <iostream>

namespace uxp {
std::string Tuple::getPatternShortcut()
{
    std::string shortcut = "";
    for (int i = 0; i < values.size(); i++)
    {
        switch (values[i].index())
        {
        case 0:
            shortcut.push_back('S');
            break;
        case 1:
            shortcut.push_back('I');
            break;
        case 2:
            shortcut.push_back('F');
            break;
        //default:
        //  throw new Excpetion
        };
    }
    return shortcut;
}}