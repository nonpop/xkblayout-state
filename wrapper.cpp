// wrapper.cpp
// A small wrapper program around Jay Bromley's keyboard layout information class.
//
// Compilation:
//   g++ -o xkblayout-state XKeyboard.cpp wrapper.cpp -lX11
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation; either version 2 of the License, or (at your option)
// any later version.

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include "XKeyboard.h"

using namespace std;

void print_usage(string progname)
{
    cerr << endl
         << "xkblayout-state version 1b" << endl
         << endl
         << "Usage: " << endl
         << endl
         << "To get the current layout(s):" << endl
         << "  " << progname << " print format" << endl
         << endl
         << "This causes the 'format' string to be printed on stdout with the following substitutions:" << endl
         << "  %c -> current layout number" << endl
         << "  %n -> current layout name" << endl
         << "  %s -> current layout symbol" << endl
         << "  %v -> current layout variant" << endl
         << "  %e -> current layout variant (equals to %s if %v is empty)" << endl
         << "  %C -> layout count" << endl
         << "  %N -> layout names (one per line)" << endl
         << "  %S -> layout symbols (one per line)" << endl
         << "  %V -> layout variants (one per line)" << endl
         << "  %E -> layout variants (one per line; layout symbol is used if variant is empty)" << endl
         << "  %% -> A literal '%'" << endl
         << endl
         << "For example:" << endl
         << "  " << progname << " print \"Current layout: %s(%e)\"" << endl
         << endl
         << "To set the current layout:" << endl
         << "  " << progname << " set layout_number" << endl
         << endl
         << "Here 'layout_number' is the number of the layout to be set (starting from 0)" << endl
         << "and can be either absolute (default) or relative (if preceded with a plus or minus sign)." << endl
         << endl
         << "For example:" << endl
         << "  " << progname << " set 1" << endl
         << "  " << progname << " set +1" << endl
         << endl;
}

bool print_status(XKeyboard& xkb, string format) {
    stringstream r;     // resulting string

    for (size_t i = 0; i < format.length(); ++i) {
        if (i < format.length()-1 && format[i] == '%') {
            switch (format[i+1]) {
                case 'c':
                    r << xkb.currentGroupNum();
                    break;
                case 'n':
                    r << xkb.currentGroupName();
                    break;
                case 's':
                    r << xkb.currentGroupSymbol();
                    break;
                case 'v':
                    r << xkb.currentGroupVariant();
                    break;
                case 'e':
                    if (xkb.currentGroupVariant().empty())
                        r << xkb.currentGroupSymbol();
                    else
                        r << xkb.currentGroupVariant();
                    break;

                case 'C':
                    r << xkb.groupCount();
                    break;
                case 'N':
                    for (size_t j = 0; j < xkb.groupNames().size(); ++j)
                        r << xkb.groupNames()[j] << endl;
                    break;
                case 'S':
                    for (size_t j = 0; j < xkb.groupSymbols().size(); ++j)
                        r << xkb.groupSymbols()[j] << endl;
                    break;
                case 'V':
                    for (size_t j = 0; j < xkb.groupVariants().size(); ++j)
                        r << xkb.groupVariants()[j] << endl;
                    break;
                case 'E':
                    for (size_t j = 0; j < xkb.groupVariants().size(); ++j)
                        if (xkb.groupVariants()[j].empty())
                            r << xkb.groupSymbols()[j] << endl;
                        else
                            r << xkb.groupVariants()[j] << endl;
                    break;

                case '%':
                    r << '%';
                    break;

                default:
                    cerr << "Unknown format character: " << format[i+1] << endl;
                    return false;
                    break;
            }
            ++i;
        } else { // not '%'
            r << format[i];
        }
    }
    cout << r.str();
    return true;
}

bool set_group(XKeyboard& xkb, string group) {
    bool relative = false;

    // Check that 'group' is a valid integer (and whether it's relative or not)
    size_t i = 0;
    if (group[0] == '+' || group[0] == '-') {
        relative = true;
        ++i;
    }
    for (; i < group.length(); ++i) {
        if (!isdigit(group[i])) {
            cerr << group << " is not an integer" << endl;
            return false;
        }
    }

    int group_int = atoi(group.c_str());
    if (relative) {
        if (!xkb.changeGroup(group_int)) {
            cerr << "Failed to change group" << endl;
            return false;
        }
    } else {
        if (group_int >= xkb.groupCount()) {
            cerr << "layout_number must be between 0 and " << xkb.groupCount()-1 << endl;
            return false;
        } else {
            if (!xkb.setGroupByNum(group_int)) {
                cerr << "Failed to change group" << endl;
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char* argv[])
{
    try {
        XKeyboard xkb;

        if (argc != 3) {
            print_usage(string(argv[0]));
            return EXIT_FAILURE;
        } else {
            string command(argv[1]);
            if (command == "print") {
                if (!print_status(xkb, string(argv[2])))
                    return EXIT_FAILURE;
            } else if (command == "set") {
                if (!set_group(xkb, string(argv[2])))
                    return EXIT_FAILURE;
            } else {
                print_usage(string(argv[0]));
                return EXIT_FAILURE;
            }
        }
    }
    catch (const exception *e) {
        cerr << e->what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

