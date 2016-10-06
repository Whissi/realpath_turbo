#ifndef REALPATH_TURBO_H
#define REALPATH_TURBO_H

#include "php.h"
#include "main/php_config.h"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define REALPATH_TURBO_VERSION "2.0.0 RC 1"
#define REALPATH_TURBO_EXTNAME "realpath_turbo"

extern zend_module_entry realpath_turbo_module_entry;
#define phpext_realpath_turbo_ptr &realpath_turbo_module_entry

#endif /* REALPATH_TURBO_H */
