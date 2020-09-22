--TEST--
realpath_turbo: Option realpath_turbo.open_basedir (set; without open_basedir set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
open_basedir=
realpath_turbo.open_basedir="/tmp/realpath_turbo-test"
--FILE--
<?php
var_dump(ini_get("realpath_turbo.open_basedir"));
var_dump(ini_get("open_basedir"));
/* should fails */
require_once('skipif.inc');
--EXPECTF--
string(24) "/tmp/realpath_turbo-test"
string(24) "/tmp/realpath_turbo-test"

Warning: require_once(): open_basedir restriction in effect. %A
