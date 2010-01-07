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

#include <iostream>
#include <string>
#include <cstdlib>
#include "XKeyboard.h"

using namespace std;

void print_usage(string progname)
{
    cerr << endl
         << "xkblayout-state v1" << endl
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

void print_status(XKeyboard& xkb, string format) {
    for (size_t i = 0; i < format.length(); ++i) {
        if (format[i] == '%' && i < format.length()-1) {
            switch (format[i+1]) {
                case 'c':
                    cout << xkb.currentGroupNum();
                    break;
                case 'n':
                    cout << xkb.currentGroupName();
                    break;
                case 's':
                    cout << xkb.currentGroupSymbol();
                    break;
                case 'v':
                    cout << xkb.currentGroupVariant();
                    break;
                case 'e':
                    if (xkb.currentGroupVariant().empty())
                        cout << xkb.currentGroupSymbol();
                    else
                        cout << xkb.currentGroupVariant();
                    break;

                case 'C':
                    cout << xkb.groupCount();
                    break;
                case 'N':
                    for (size_t j = 0; j < xkb.groupNames().size(); ++j)
                        cout << xkb.groupNames()[j] << endl;
                    break;
                case 'S':
                    for (size_t j = 0; j < xkb.groupSymbols().size(); ++j)
                        cout << xkb.groupSymbols()[j] << endl;
                    break;
                case 'V':
                    for (size_t j = 0; j < xkb.groupVariants().size(); ++j)
                        cout << xkb.groupVariants()[j] << endl;
                    break;
                case 'E':
                    for (size_t j = 0; j < xkb.groupVariants().size(); ++j)
                        if (xkb.groupVariants()[j].empty())
                            cout << xkb.groupSymbols()[j] << endl;
                        else
                            cout << xkb.groupVariants()[j] << endl;
                    break;

                default:
                    cout << format[i+1];
                    break;
            }
            ++i;
        } else { // not '%'
            cout << format[i];
        }
    }
}

bool set_group(XKeyboard& xkb, string group) {
    bool relative = (group[0] == '+' || group[0] == '-');
    int group_int = atoi(group.c_str());
    if (relative)
        return xkb.changeGroup(group_int);
    else
        return xkb.setGroupByNum(group_int);
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
                print_status(xkb, string(argv[2]));
                return EXIT_SUCCESS;
            } else if (command == "set") {
                if (!set_group(xkb, string(argv[2]))) {
                    cerr << "Failed to set layout" << endl;
                    return EXIT_FAILURE;
                }
            } else {
                print_usage(string(argv[0]));
                return EXIT_FAILURE;
            }
        }
    }
    catch (exception e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
}
