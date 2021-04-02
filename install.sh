#!/bin/bash

pacman -S xorg-server xorg-xinit
pacman -S nm-applet
pacman -S alsa-utils pulseaudio pulseaudio-alsa alsa-card-profiles
pacman -S xclip

git clone https://aur.archlinux.org/yay.git
cd yay
makepkg -si
cd ..

pacman -S zsh
## yay oh-my-zsh-git

pacman -S rxvt-unicode
pacman -S rofi
pacman -S feh
pacman -S dunst
pacman -S ranger

## For installing all nerd-fonts, should move it to .local or something
##git clone --depth 1 https://github.com/ryanoasis/nerd-fonts
##./install.sh
