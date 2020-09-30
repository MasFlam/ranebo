![GitHub release (latest SemVer)](https://img.shields.io/github/v/release/MasFlam/ranebo?logo=github&sort=semver)

# Ranebo
The colorful shell util  
Ranebo utilizes ANSI escapes to color its arguments rainbow.

# Usage
`ranebo [(option|string)...] [--] [string...]`

Will output all the `string`s in order line after line,
with ANSI terminal color escapes in between the characters
in a way that will make the output rainbow-colored.
If the colors are messed up, it's probably your terminal
color settings, as it might for example display green differently
if the default text is set to be green. You can use the `--truecolor`
option to overcome that, but bear in mind that on some old terminals
the true colors might not be displayed properly either.

Run `ranebo --help` to see the full help.

# Installation
Download a binary from the latest GitHub release, or build from source;
and then place it on your `PATH` and you're set up.

# Building Ranebo
Just run `make` without any arguments and it
should generate an executable named `ranebo`,
given you have GCC installed.

The Makefile is very simple - I think one can easily
figure out how to adjust the compilation process.
