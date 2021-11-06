README
======


Description
-----------

*xkblayout-state* is a small command-line program to get/set the current XKB keyboard layout.

It's a thin wrapper around a slightly version of Jay Bromley's XKeyboard class, the original of which is included in <http://members.dslextreme.com/users/jbromley/files/ruby-xkb.tar.bz2>.


Compilation and installation
----------------------------

- Make sure x11 development libraries are installed (eg. `apt install libx11-dev` on Ubuntu)
- To compile just say: `make`
- To install copy the resulting executable `xkblayout-state` somewhere in your path

Alternatively with docker: `docker build .`

Usage
-----

*xkblayout-state* can be used to either print keyboard layout information on **stdout** or set the currently active layout.


### Printing keyboard layout information

The command to print keyboard layout information is

	xkblayout-state print format

*format* is printed to **stdout** with the following substitutions (to include a literal *%* use `%%`):

- `%c` -> The number of the currently active layout
- `%n` -> The name of the currently active layout
- `%s` -> The symbol of the currently active layout
- `%v` -> The variant of the currently active layout (*this is empty if no variant is specified*)
- `%e` -> The variant of the currently active layout (*this is the same as `%s` if no variant is specified*)
- `%C` -> The number of defined layouts
- `%N` -> A list containing the names of the layouts (one per line)
- `%S` -> A list containing the symbols of the layouts (one per line)
- `%V` -> A list containing the variants of the layouts (one per line; *an empty line if no variant is specified for the respective layout*)
- `%E` -> A list containing the variants of the layouts (one per line; *if no variant is specified for the respective symbol, the layout symbol is used*)


### Setting the active keyboard layout

The command to set the currently active keyboard layout is

	xkblayout-state set [+-]number

*number* is the number of the layout to activate. It corresponds to the layouts in the order they appear in, for example, `xkblayout-state print %N`, starting from zero. If *number* begins with a plus or minus sign, the *number*'th layout counting from the currently active layout down or up the list is activated. It wraps around if the list is exceeded.


License
-------

*xkblayout-state* is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

*xkblayout-state* is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details. <http://www.gnu.org/licenses/>
