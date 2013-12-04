matrix
======

PHP extension for matrix operations

Features
--------

* Addition
* Scalar multiplication
* Transposition
* Matrix multiplication
* Elementwise multiplication
* Matrix dump

Getting started
---------------

### Build (linux):
~~~
$ cd ext/
$ phpize && ./configure && make && make test
$ make install
$ make clean; phpize --clean
~~~
And enable the extension in php.ini via "extension=/path/to/matrix.so"
