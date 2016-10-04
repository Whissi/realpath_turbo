#ifndef PHP_REALPATH_TURBO_H
#define PHP_REALPATH_TURBO_H

#include "php.h"
#include "main/php_config.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define PHP_REALPATH_TURBO_VERSION "2.0.0 Beta 1"
#define PHP_REALPATH_TURBO_EXTNAME "realpath_turbo"

PHP_RINIT_FUNCTION(realpath_turbo);
PHP_MINIT_FUNCTION(realpath_turbo);

PHP_MINFO_FUNCTION(realpath_turbo);
PHP_MSHUTDOWN_FUNCTION(realpath_turbo);

PHP_FUNCTION(realpath_turbo);

extern zend_module_entry realpath_turbo_module_entry;
#define phpext_realpath_turbo_ptr &realpath_turbo_module_entry

#endif
