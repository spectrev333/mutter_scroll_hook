# Mutter Scroll Fix

A lightweight `LD_PRELOAD` hook to set per-application touchpad scroll speed in GNOME/Mutter.

## Features

* **Adaptive Speed:** Custom scroll multiplier based on the focused window `WM_CLASS`.
* **Simple:** Single C file, you can read and understand in under 2 minutes.

## Build

```bash
gcc -O3 -fPIC -shared -D_GNU_SOURCE libmutterhook.c -o libmutterhook.so -ldl
```

## Usage

Run GNOME Shell with the hook:

```bash
export LD_PRELOAD=/path/to/libmutterhook.so
```

*Note: To make it permanent, add it to `/etc/ld.so.preload`.

## Requirements

* `libmutter` (tested on GNOME 49)
