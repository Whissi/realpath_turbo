--TEST--
realpath_turbo: Basic tests
--SKIPIF--
<?php
require_once('skipif.inc');
--FILE--
<?php 
var_dump(extension_loaded("realpath_turbo"));
var_dump(phpversion("realpath_turbo"));

// Test for https://github.com/Whissi/realpath_turbo/issues/1
ob_start();
phpinfo(INFO_MODULES);
$phpinfo = ob_get_clean();

$testStr_position = strpos($phpinfo, 'realpath_turbo support');
var_dump(($testStr_position !== false && $testStr_position > 42));

echo "Done\n";
--EXPECTF--
bool(true)
string(%d) "%s"
bool(true)
Done
