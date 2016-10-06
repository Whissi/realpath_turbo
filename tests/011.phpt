--TEST--
realpath_turbo: Option realpath_turbo.disable_dangerous_functions (disabled; without disable_functions set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
disable_functions=
realpath_turbo.disable_dangerous_functions=0
--FILE--
<?php
var_dump(ini_get("realpath_turbo.disable_dangerous_functions"));
var_dump(ini_get("disable_functions"));
--EXPECTF--
string(1) "0"
string(0) ""
