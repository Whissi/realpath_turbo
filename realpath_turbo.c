#include "realpath_turbo.h"
#include "realpath_turbo_private.h"

static zend_function_entry realpath_turbo_functions[] = {
	{NULL, NULL, NULL}
};

zend_module_entry realpath_turbo_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	REALPATH_TURBO_EXTNAME,
	realpath_turbo_functions,
	PHP_MINIT(realpath_turbo),
	PHP_MSHUTDOWN(realpath_turbo),
	PHP_RINIT(realpath_turbo),
	NULL,
	PHP_MINFO(realpath_turbo),
#if ZEND_MODULE_API_NO >= 20010901
	REALPATH_TURBO_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};

ZEND_DECLARE_MODULE_GLOBALS(realpath_turbo)

#ifdef COMPILE_DL_REALPATH_TURBO
ZEND_GET_MODULE(realpath_turbo)
#endif

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("realpath_turbo.open_basedir",                  NULL, PHP_INI_SYSTEM, OnUpdateString, open_basedir, zend_realpath_turbo_globals, realpath_turbo_globals)
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	STD_PHP_INI_BOOLEAN("realpath_turbo.safe_mode",                   "0", PHP_INI_SYSTEM, OnUpdateBool, safe_mode, zend_realpath_turbo_globals, realpath_turbo_globals)
#endif
	STD_PHP_INI_BOOLEAN("realpath_turbo.disable_dangerous_functions", "1", PHP_INI_SYSTEM, OnUpdateBool, disable_dangerous_functions, zend_realpath_turbo_globals, realpath_turbo_globals)
PHP_INI_END()

PHP_RINIT_FUNCTION(realpath_turbo)
{
	char *rpt_open_basedir = INI_STR("realpath_turbo.open_basedir");
#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	zend_bool *do_safe_mode = INI_BOOL("realpath_turbo.safe_mode");
#endif
	char *disabled_functions = INI_STR("disable_functions");
	char *disabled_functions_new;
	char *risky_functions = "link,symlink";
	zend_bool do_disable_dangerous_functions = INI_BOOL("realpath_turbo.disable_dangerous_functions");
#if PHP_MAJOR_VERSION >= 7
	zend_string *ini_name, *ini_value;
#endif

	if (rpt_open_basedir && *rpt_open_basedir) {
		if (PG(open_basedir) && *PG(open_basedir)) {
			php_error_docref(NULL, E_WARNING, "open_basedir already set! Please unset open_basedir and only use realpath_turbo.open_basedir option. realpath_turbo will not have any effect when open_basedir is already set.");
			return FAILURE;
		}
#if PHP_MAJOR_VERSION < 7
		zend_alter_ini_entry("open_basedir", sizeof("open_basedir"), rpt_open_basedir, strlen(rpt_open_basedir), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
#else
		ini_name  = zend_string_init(ZEND_STRL("open_basedir"), 0);
		ini_value = zend_string_init(rpt_open_basedir, strlen(rpt_open_basedir), 0);

		zend_alter_ini_entry(ini_name, ini_value, PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
		zend_string_release(ini_name);
		zend_string_release(ini_value);
#endif
	}

#if (PHP_MAJOR_VERSION == 5) && (PHP_MINOR_VERSION < 4)
	if (do_safe_mode) {
		zend_alter_ini_entry("safe_mode", sizeof("safe_mode"), "1", 1, PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
	}
#endif

	if (do_disable_dangerous_functions) {
		// check disabled functions for symlink and link entries
		if(strlen(disabled_functions) > 0) {
			disabled_functions_new = emalloc(strlen(disabled_functions) + strlen(risky_functions) + 2);
			strcpy(disabled_functions_new, risky_functions);
			strcat(disabled_functions_new, ",");
			strcat(disabled_functions_new, disabled_functions);
		} else {
			disabled_functions_new = emalloc(strlen(risky_functions) + 1);
			strcpy(disabled_functions_new, risky_functions);
		}
#if PHP_MAJOR_VERSION < 7
		zend_alter_ini_entry("disable_functions", sizeof("disable_functions"), disabled_functions_new, strlen(disabled_functions_new), PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
#else
		ini_name   = zend_string_init(ZEND_STRL("disable_functions"), 0);
		ini_value  = zend_string_init(disabled_functions_new, strlen(disabled_functions_new), 0);

		zend_alter_ini_entry(ini_name, ini_value, PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
		zend_string_release(ini_name);
		zend_string_release(ini_value);
#endif
		efree(disabled_functions_new);
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
	php_info_print_table_row(2, "Version", REALPATH_TURBO_VERSION);
	php_info_print_table_row(2, "Build Date", __DATE__ " " __TIME__);
	php_info_print_table_row(2, "Creator", "Artur Graniszewski");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
