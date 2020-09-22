--TEST--
realpath_turbo: Option realpath_turbo.disable_dangerous_functions (enabled; with disable_functions set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
disable_functions=touch
realpath_turbo.disable_dangerous_functions=1
--FILE--
<?php
var_dump(ini_get("realpath_turbo.disable_dangerous_functions"));
var_dump(ini_get("disable_functions"));

// Ensure the symlink function is properly disable
$l = __DIR__ . '/testlink';
try {
    @symlink(PHP_BINARY, $l);
} catch (Error $e) {
    // Expected exception on PHP 8, else only a warning
	if (!strpos($e->getMessage(), 'undefined function symlink')) {
		echo $e->getMessage() . "\n";
	}
}
// If symlink is properly disable, will fail as file doesn't exist
var_dump(@unlink($l));

// Ensure the touch function is also disable
$l = __DIR__ . '/testtouch';
try {
    @touch($l);
} catch (Error $e) {
    // Expected exception on PHP 8, else only a warning
	if (!strpos($e->getMessage(), 'undefined function touch')) {
		echo $e->getMessage() . "\n";
	}
}
// If touch is properly disable, will fail as file doesn't exist
var_dump(@unlink($l));
--EXPECTF--
string(1) "1"
string(%d) "link,symlink,touch"
bool(false)
bool(false)
