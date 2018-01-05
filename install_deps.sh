#!/bin/bash

# Function declared with round parens are executed in a subshell
function install_git_repo() (
	cd /tmp
	# Fetch the project
	git clone -v "'https://github.com/Moonstroke/C-$1" "$1"
	cd "$1"
	# Build
	make
	# Install
	make install

	cd ..
	# Remove the cloned repo
	rm -rfv "$1"
)

install_git_repo log
install_git_repo array
