--TEST--
realpath_turbo: Basic functionality (enabled)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
open_basedir=
realpath_turbo.open_basedir=.
--FILE--
<?php
var_dump(ini_get("realpath_turbo.open_basedir"));
var_dump(ini_get("open_basedir"));
require_once("test_realpath_turbo_effect.php");
--EXPECTF--
string(1) "."
string(1) "."
bool(false)
bool(true)
string(1) "."
