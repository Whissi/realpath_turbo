#ifndef PHP_TURBO_H
#define PHP_TURBO_H

#include "php.h"
#include "main/php_config.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define PHP_TURBO_REALPATH_VERSION "1.3.1"
#define PHP_TURBO_REALPATH_EXTNAME "turbo_realpath"

PHP_RINIT_FUNCTION(turbo_realpath);
PHP_MINIT_FUNCTION(turbo_realpath);

PHP_MINFO_FUNCTION(turbo_realpath);
PHP_MSHUTDOWN_FUNCTION(turbo_realpath);

PHP_FUNCTION(turbo_realpath);

extern zend_module_entry turbo_realpath_module_entry;
#define phpext_turbo_realpath_ptr &turbo_realpath_module_entry

#endif
