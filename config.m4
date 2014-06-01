PHP_ARG_ENABLE(turbo_realpath, whether to enable turbo realpath module,
[ --enable-turbo-realpath   Enable turbo realpath module])

if test "$PHP_TURBO_REALPATH" = "yes"; then
  AC_DEFINE(HAVE_TURBO_REALPATH, 1, [Whether you have turbo realpath module])
  PHP_NEW_EXTENSION(turbo_realpath, turbo_realpath.c, $ext_shared)
fi

cp modules/*.so /usr/lib/php/modules
