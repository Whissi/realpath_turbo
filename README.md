# *realpath_turbo* – Use realpath cache despite *open_basedir* restriction

When you set PHP's open_basedir restriction, PHP will deactivate the
realpath cache.

This will decrease the performance of any PHP application which uses
multiple files (`include_once`, `require_once`) like WordPress,
Drupal and Magento -- just to mention a few.

The decision to deactivate the realpath cache when using open_basedir
(and the previous safe_mode) restriction was made when the PHP team fixed
CVE-2006-5178. Please see [PHP's bug report 52312](https://bugs.php.net/bug.php?id=52312)
for further information.

The *realpath_turbo* PHP extension, created by Artur Graniszewski, is a
workaround:


## How *realpath_turbo* works

1. Instead of setting `open_basedir` you will set
   `realpath_turbo.open_basedir`.

   Because now `open_basedir` isn't set, PHP will **not** deactivate the
   realpath cache.

2. When the *realpath_turbo* extension will be loaded, it will set the
   `open_basedir` restriction, which won't deactivate the realpath cache
   which will happen if you set the `open_basedir` restriction in your
   `php.ini`.


## How to install *realpath_turbo*

1. Download the *realpath_turbo* source code.

2. Extract and compile the extension

   ```sh
   $ tar -xaf realpath_turbo*
   $ cd realpath_turbo*
   $ phpize
   $ ./configure
   $ make
   # make install
   ```

3. Adjust your `php.ini` to load and configure *realpath_turbo* extension.


## Configuration

```ini
; you have to load the extension first
extension=realpath_turbo.so

; Disable dangerous functions (see the warning in the README file for
; details).
; Possible values:
;   0 - Ignore potential security issues
;   1 - Disable dangerous PHP functions (link,symlink)
realpath_turbo.disable_dangerous_functions = 1

; Set realpath_turbo.open_basedir to whatever you want to set open_basedir to
realpath_turbo.open_basedir = "/var/www/html/drupal:/usr/share/php"

; Disable PHP's open_basedir directive so that the realpath cache won't be
; disabled.
; Remember, realpath_turbo will set this option later to the
; realpath_turbo.open_basedir value.
open_basedir = ""
```


## Warning

It is very important to deactivate **any** PHP function which can be used
to create/manipulate symlinks. If you don't do that, any attacker could
create or manipulate a symlink to bypass the `open_basedir` restriction.

But even if you have disabled those functions in PHP you still maybe at
risk: If you allow your users to create symlinks because they have shell
access, they could do the same.

So it is more than just PHP you have to take care of when you rely on
`open_basedir` restriction and want to use *realpath_turbo*.

Therefore *realpath_turbo* is **not recommended** for any shared hosting
environment. Instead of relying on `open_basedir`, you should create VMs or
use containers (LXC) to safely separate your users without any performance
degradation.

See http://www.php.net/security-note.php for more information.


## Further information

 - http://php.webtutor.pl/en/2011/06/02/running-php-on-nfs-huge-performance-problems-and-one-simple-solution/

 - http://php.webtutor.pl/en/2011/07/01/running-php-on-nfs-new-version-of-turbo_realpath-extension/

 - http://php.webtutor.pl/en/2011/07/12/running-php-on-nfs-version-1-2-of-turbo_realpath-extension/

 - http://php.webtutor.pl/en/2013/05/13/running-php-on-nfs-version-1-3-of-turbo_realpath-extension/
