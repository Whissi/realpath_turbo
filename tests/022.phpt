--TEST--
realpath_turbo: Option realpath_turbo.open_basedir (unset; with open_basedir set)
--SKIPIF--
<?php
require_once('skipif.inc');
--INI--
open_basedir="/tmp/open_basedir-already-set"
realpath_turbo.open_basedir=
--FILE--
<?php
var_dump(ini_get("realpath_turbo.open_basedir"));
var_dump(ini_get("open_basedir"));
--EXPECTF--
string(0) ""
string(29) "/tmp/open_basedir-already-set"
