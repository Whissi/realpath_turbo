--TEST--
realpath_turbo: Option realpath_turbo.open_basedir (set; with open_basedir already set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
open_basedir="/tmp/previous-value"
realpath_turbo.open_basedir="/tmp/realpath_turbo-test"
--FILE--
<?php
var_dump(ini_get("realpath_turbo.open_basedir"));
var_dump(ini_get("open_basedir"));
--EXPECTF--
Warning: %s: open_basedir already set! Please unset open_basedir and only use realpath_turbo.open_basedir option. realpath_turbo will not have any effect when open_basedir is already set. in %s on line %d

Warning: request_startup() for realpath_turbo module failed in %s on line %d
