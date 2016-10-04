#include "realpath_turbo.h"
#include "php_ini.h"
#include "ext/standard/info.h"

static zend_function_entry realpath_turbo_functions[] = {
	{NULL, NULL, NULL}
};

zend_module_entry realpath_turbo_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_REALPATH_TURBO_EXTNAME,
	realpath_turbo_functions,
	PHP_MINIT(realpath_turbo),
	PHP_MSHUTDOWN(realpath_turbo),
	PHP_RINIT(realpath_turbo),
	NULL,
	PHP_MINFO(realpath_turbo),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_REALPATH_TURBO_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(realpath_turbo)

PHP_INI_BEGIN()
	PHP_INI_ENTRY("realpath_turbo.open_basedir",   "", PHP_INI_SYSTEM, NULL)
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	PHP_INI_ENTRY("realpath_turbo.safe_mode", "", PHP_INI_SYSTEM, NULL)
#endif
	PHP_INI_ENTRY("realpath_turbo.disable_dangerous_functions",  "1", PHP_INI_SYSTEM, NULL)
PHP_INI_END()

PHP_RINIT_FUNCTION(realpath_turbo)
{
	char *basedir = INI_STR("realpath_turbo.open_basedir");
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	char *safe_mode = INI_STR("realpath_turbo.safe_mode");
#endif
	char *disabled_functions = INI_STR("disable_functions");
	char *risky_functions = "link,symlink";
	char *new_functions;
	int security = INI_INT("realpath_turbo.disable_dangerous_functions");
#if PHP_MAJOR_VERSION >= 7
	zend_string *ini_name, *ini_value;
#endif

	if(strlen(basedir) > 0) {
#if PHP_MAJOR_VERSION < 7
		zend_alter_ini_entry("open_basedir", sizeof("open_basedir"), basedir, strlen(basedir), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
#else
		ini_name  = zend_string_init(ZEND_STRL("open_basedir"), 0);
		ini_value = zend_string_init(basedir, strlen(basedir), 0);

		zend_alter_ini_entry(ini_name, ini_value, PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
		zend_string_release(ini_name);
		zend_string_release(ini_value);
#endif
	}

#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	if(strlen(safe_mode) > 0) {
		zend_alter_ini_entry("safe_mode", sizeof("safe_mode"), safe_mode, strlen(safe_mode), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
	}
#endif

	if (security) {
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
#if PHP_MAJOR_VERSION < 7
		zend_alter_ini_entry("disable_functions", sizeof("disable_functions"), new_functions, strlen(new_functions), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
#else
		ini_name   = zend_string_init(ZEND_STRL("disable_functions"), 0);
		ini_value  = zend_string_init(new_functions, strlen(new_functions), 0);

		zend_alter_ini_entry(ini_name, ini_value, PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
		zend_string_release(ini_name);
		zend_string_release(ini_value);
#endif
		efree(new_functions);
	}
}

PHP_MINIT_FUNCTION(realpath_turbo)
{
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(realpath_turbo)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}

PHP_MINFO_FUNCTION(realpath_turbo)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "realpath_turbo support", "enabled");
	php_info_print_table_row(2, "Version", PHP_REALPATH_TURBO_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__);
	php_info_print_table_row(2, "Creator", "Artur Graniszewski");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
