--TEST--
realpath_turbo: Option realpath_turbo.disable_dangerous_functions (disabled; with disable_functions set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
disable_functions=date
realpath_turbo.disable_dangerous_functions=0
--FILE--
<?php
var_dump(ini_get("realpath_turbo.disable_dangerous_functions"));
var_dump(ini_get("disable_functions"));

// Ensure the symlink function is not disable
$l = __DIR__ . '/testlink';
try {
    symlink(PHP_BINARY, $l);
} catch (Error $e) {
    // Expected exception on PHP 8, else only a warning
	if (!strpos($e->getMessage(), 'undefined function symlink')) {
		echo $e->getMessage() . "\n";
	}
}
var_dump(unlink($l));

--EXPECTF--
string(1) "0"
string(4) "date"
bool(true)
