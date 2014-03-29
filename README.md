
NAME
----

linux-utils - standard Linux utilities rewritten from scratch

DESCRIPTION
-----------

A good way to learn about Linux is to write the standard
system utilities from scratch.  Programs such as `ls`, `cat`,
`dd` and others.  These programs are simple and have less
functionality compared to the original programs but they
nonetheless accomplish the same core functionality.

INDEX
-----

The various programs are organized in to their particular package.
For example the `ls` program is provided by the `coreutils` package
so it is placed in to the `coreutils/` directory.

    coreutils/
      cat
      dd
      echo
      false
      ls
      rm
      touch
      true

    iputils-ping/
      ping

COPYRIGHT
---------

Copyright &copy; 2014, Jeremiah Mahler.  All Rights Reserved.<br>
This project is free software and released under
the [GNU General Public License][gpl].

 [gpl]: http://www.gnu.org/licenses/gpl.html

