--TEST--
realpath_turbo: Option realpath_turbo.disable_dangerous_functions (enabled; with disable_functions set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
disable_functions=date
realpath_turbo.disable_dangerous_functions=1
--FILE--
<?php
var_dump(ini_get("realpath_turbo.disable_dangerous_functions"));
var_dump(ini_get("disable_functions"));
--EXPECTF--
string(1) "1"
string(17) "link,symlink,date"
