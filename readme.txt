The Octavia Internet Filesystem
===============================

Welcome to Octavia, intrepid hacker. Octavia is an experimental filesystem
for the internet, with potentially spiffy features:

      * Security: confidentiality, integrity, authentication, availability
      * Parallelism for improved? read performance
      * A functional/persistent directory structure, enabling snapshots

Currently, the implementation is incomplete and very bad. Feel free to
submit a patch!

Dependencies
------------

You need a C99 compiler, the FUSE runtime and development files, and the
OpenSSL runtime and development files.

On Ubuntu 10.10, you can get what you need by running:

      $ sudo apt-get install fuse-utils libfuse-dev build-essential libssl-dev

Contents
--------

./
      Notes for hackers, such as this file and the coding standard. The
      code-copyright.txt and doc-copyright.txt files explain your freedoms.
src/
      The source code.
www/
      Propaganda and documentation.
t/
      Test scripts and data.

Feel Free to Submit a Patch
---------------------------

Mail your git diffs to Chris Palmer, chris@noncombatant.org. Thanks!

