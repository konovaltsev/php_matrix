PHP_ARG_ENABLE(matrix, Enable matrix support,
[ --enable-matrix Enable matrix support])

if test "$PHP_MATRIX" = "yes"; then
   AC_DEFINE(HAVE_MATRIX, 1, [You have matrix extension])
   PHP_NEW_EXTENSION(matrix, src/matrix.c src/utils/functions.c src/matrix/version.c src/matrix/dump.c src/matrix/is_valid.c src/matrix/transpose.c src/matrix/add.c src/matrix/mul_elementwise.c src/matrix/mul_scalar_matrix.c src/matrix/mul.c, $ext_shared)
fi
