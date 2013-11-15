php_matrix
==========

PHP extention for matrix operations

### Build (linux):
~~~
$ cd ext/
$ phpize && ./configure && make && make test
$ make install
$ make clean; phpize --clean
~~~
And enable the extension in php.ini via "extension=/path/to/matrix.so"
