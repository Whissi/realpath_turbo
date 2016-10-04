#include "turbo_realpath.h"
#include "php_ini.h"
#include "ext/standard/info.h"

static zend_function_entry turbo_realpath_functions[] = {
	{NULL, NULL, NULL}
};

zend_module_entry turbo_realpath_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_TURBO_REALPATH_EXTNAME,
	turbo_realpath_functions,
	PHP_MINIT(turbo_realpath),
	PHP_MSHUTDOWN(turbo_realpath),
	PHP_RINIT(turbo_realpath),
	NULL,
	PHP_MINFO(turbo_realpath),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_TURBO_REALPATH_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(turbo_realpath)

PHP_INI_BEGIN()
	PHP_INI_ENTRY("realpath_cache_basedir",   "", PHP_INI_SYSTEM, NULL)
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	PHP_INI_ENTRY("realpath_cache_safe_mode", "", PHP_INI_SYSTEM, NULL)
#endif
	PHP_INI_ENTRY("realpath_cache_security",  "", PHP_INI_SYSTEM, NULL)
PHP_INI_END()

PHP_RINIT_FUNCTION(turbo_realpath)
{
	char *basedir = INI_STR("realpath_cache_basedir");
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	char *safe_mode = INI_STR("realpath_cache_safe_mode");
#endif
	char *disabled_functions = INI_STR("disable_functions");
	char *risky_functions = "link,symlink";
	char *new_functions;
	int security = INI_INT("realpath_cache_security");

	if(strlen(basedir) > 0) {
		zend_alter_ini_entry("open_basedir", sizeof("open_basedir"), basedir, strlen(basedir), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
	}

#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	if(strlen(safe_mode) > 0) {
		zend_alter_ini_entry("safe_mode", sizeof("safe_mode"), safe_mode, strlen(safe_mode), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
	}
#endif

	switch(security) {
		case 1:
			// check disabled functions for symlink and link entries
			if(strlen(disabled_functions) > 0) {
				new_functions = emalloc(strlen(disabled_functions) + strlen(risky_functions) + 2);
				strcpy(new_functions, risky_functions);
				strcat(new_functions, ",");
				strcat(new_functions, disabled_functions);
			} else {
				new_functions = emalloc(strlen(risky_functions) + 1);
				strcpy(new_functions, risky_functions);
			}
			zend_alter_ini_entry("disable_functions", sizeof("disable_functions"), new_functions, strlen(new_functions), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
			efree(new_functions);
			break;
		default:
			break;
	}
}

PHP_MINIT_FUNCTION(turbo_realpath)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(turbo_realpath)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(turbo_realpath)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "turbo_realpath support", "enabled");
	php_info_print_table_row(2, "turbo_realpath version", PHP_TURBO_REALPATH_VERSION);
	php_info_print_table_row(2, "turbo_realpath creator", "Artur Graniszewski");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
