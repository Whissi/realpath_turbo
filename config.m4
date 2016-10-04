PHP_ARG_ENABLE(realpath_turbo, whether to enable realpath_turbo module,
[ --enable-realpath_turbo   Enable realpath_turbo module])

if test "$PHP_REALPATH_TURBO" = "yes"; then
	AC_DEFINE(HAVE_REALPATH_TURBO, 1, [Whether you have realpath_turbo module])
	PHP_NEW_EXTENSION(realpath_turbo, realpath_turbo.c, $ext_shared)
fi
