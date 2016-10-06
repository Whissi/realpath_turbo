<?php
clearstatcache(true);
var_dump(count(realpath_cache_get()) > 0);

require_once('include1.php');
