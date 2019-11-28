#!/bin/bash

# From <sysexits.h>
declare -r     EX_OK=0   # Everything is fine. No error.
declare -r  EX_ERROR=1   # General error.
declare -r  EX_USAGE=64  # Command line error, e.g. invalid argument
declare -r  EX_IOERR=74  # An error occurred while doing I/O on some file
declare -r EX_CONFIG=78  # Something was found in an unconfigured or misconfigured state.

cleanup() {
	if [[ -n "${D}" && -d "${D}" ]] ; then
		echo ">>> Cleaning working directory ‘${D}’"
		rm -rf "${D}"
	fi
	
	return 0
}

##
# Die.
#
# Usage: die <exit_code> <message>
die() {
	local status=$1
	shift

	cleanup

	print_error ""
	print_error "${@}"

	exit $status
}

##
# Prints an error message to stderr.
print_error() {
	echo >&2 -e "$@"
}

if [ $# != 1 ] ; then
	die ${EX_USAGE} "Need version argument"
fi

if [[ -n ${1/[0-9]*} ]] ; then
	die ${EX_USAGE} "Invalid version argument"
fi

VERSION=$1
NAME="realpath_turbo"
GITREF="HEAD"
DISTPREFIX="${NAME}-${VERSION}"
DISTFILE="${DISTPREFIX}.tar.bz2"

trap "die $? 'Terminated!'" SIGHUP SIGINT SIGQUIT SIGABRT SIGTERM


D=$(mktemp -d)
if [[ $? -ne 0 ]] ; then
	die ${EX_IOERR} "Couldn't create temporary folder!"
fi

WORKING_DIR="${D}/${DISTPREFIX}"
mkdir "${WORKING_DIR}"
if [[ $? -ne 0 ]] ; then
	die ${EX_IOERR} "Failed to create ‘${WORKING_DIR}’!"
fi

echo ">>> Building release tree"
git checkout-index --force --all --prefix="${WORKING_DIR}/"
if [[ $? -ne 0 ]] ; then
	die ${EX_ERROR} "Failed to copy files from the git repository index to the working dir ‘${WORKING_DIR}’!"
fi

if [[ -f "${WORKING_DIR}/${0##*/}" ]] ; then
	echo ">>> Removing myself from release tree"
	rm "${WORKING_DIR}/${0##*/}"
fi

echo ">>> Removing unnecessary files"
rm "${WORKING_DIR}/.gitignore" || die ${EX_ERROR} "Failed to delete .gitignore!"
rm "${WORKING_DIR}/.gitmodules" || die ${EX_ERROR} "Failed to delete .gitmodules!"
rm "${WORKING_DIR}/.travis.yml" || die ${EX_ERROR} "Failed to delete .travis.yml!"
rm "${WORKING_DIR}/gen_travis_yml.php" || die ${EX_ERROR} "Failed to delete gen_travis_yml.php!"
rm -rf "${WORKING_DIR}/travis/" || die ${EX_ERROR} "Failed to delete travis/!"

echo ">>> Creating Changelog"
git log >"${WORKING_DIR}/ChangeLog"
if [[ $? -ne 0 ]] ; then
	die ${EX_ERROR} "Failed to create ChangeLog from git!"
fi

echo ">>> Creating release tarball ‘${DISTFILE}’"
tar -caf "${DISTFILE}" --owner=0 --group=0 --format=posix --mode=a+rX -C "$D" "${DISTPREFIX}"
if [[ $? -ne 0 ]] ; then
	die ${EX_ERROR} "Failed to create tarball!"
fi

cleanup

du -h "$PWD/${DISTFILE}"


exit 0
