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


# We need the SDL2 development packages installed
apt-get install -y libasound2-dev libdbus-1-dev libegl1-mesa-dev libgl1-mesa-dev\
                   libgles2-mesa-dev libglu1-mesa-dev libibus-1.0-dev\
                   libmirclient-dev libpulse-dev libsdl2-2.0-0 libsndio-dev\
                   libudev-dev libwayland-dev libx11-dev libxcursor-dev\
                   libxext-dev libxi-dev libxinerama-dev libxkbcommon-dev\
                   libxrandr-dev libxss-dev libxt-dev libxv-dev libxxf86vm-dev\
                   libsdl2-dev


install_git_repo log
install_git_repo array
