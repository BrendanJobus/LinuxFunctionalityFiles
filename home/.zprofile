# Profile file. Runs on login. Environmental variables are set here.

# Adds `~/.local/bin` to $PATH
export PATH="$PATH:$(du "$HOME/.local/bin/" | cut -f2 | tr '\n' ':' | sed 's/:*$//')"

# Adds `~/.local/bin/oldscripts` to $PATH
export PATH="$PATH:$(du "$HOME/.local/bin/oldscripts/"| cut -f2 | tr '\n' ':' | sed 's/:*$//')"

# Adds polybar/scripts to path
export PATH="$PATH:$(du "$HOME/.config/polybar/scripts/"| cut -f2 | tr '\n' ':' | sed 's/:*$//')"

# Default programs:
export EDITOR="nvim"
export TERMINAL="st"
export BROWSER="firefox"
export READER="zathura"

# ~/ Clean-up:
export XAUTHORITY="$XDG_RUNTIME_DIR/Xauthority" # This line will break some DMs.
#export NOTMUCH_CONFIG="$HOME/.config/notmuch-config"
export GTK2_RC_FILES="$HOME/.config/gtk-2.0/gtkrc-2.0"
export LESSHISTFILE="-"
#export WGETRC="$HOME/.config/wget/wgetrc"
#export INPUTRC="$HOME/.config/inputrc"
export ZDOTDIR="$HOME/.config/zsh"
#export PASSWORD_STORE_DIR="$HOME/.local/share/password-store"
export ATOM_HOME="$HOME/.config/Atom"

# Start graphical server on tty1 if not already running.
[ "$(tty)" = "/dev/tty1" ] && ! pgrep -x Xorg >/dev/null && exec startx

# Switch escape and caps if tty and no password required:
#sudo -n loadkeys ~/.local/share/maps/ttymaps.kmap 2>/dev/null
