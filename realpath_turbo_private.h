#ifndef REALPATH_TURBO_PRIVATE_H
#define REALPATH_TURBO_PRIVATE_H

#include <php.h>
#include "main/php_config.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef ZTS
#  include "TSRM.h"
#endif

#include <php_ini.h>           /* for PHP_INI_* constant */
#include <ext/standard/info.h> /* for php_info_print_table_* */

ZEND_BEGIN_MODULE_GLOBALS(realpath_turbo)
	char      *open_basedir;
	zend_bool  safe_mode;
	zend_bool  disable_dangerous_functions;
ZEND_END_MODULE_GLOBALS(realpath_turbo)

PHP_RINIT_FUNCTION(realpath_turbo);
PHP_MINIT_FUNCTION(realpath_turbo);
PHP_MINFO_FUNCTION(realpath_turbo);
PHP_MSHUTDOWN_FUNCTION(realpath_turbo);

#ifdef ZTS
#define MEMC_G(v) TSRMG(realpath_turbo_globals_id, zend_realpath_turbo_globals *, v)
#else
#define MEMC_G(v) (realpath_turbo_globals.v)
#endif

extern ZEND_DECLARE_MODULE_GLOBALS(realpath_turbo);

#endif /* REALPATH_TURBO_PRIVATE_H */
