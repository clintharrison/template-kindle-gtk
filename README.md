# Toolchain setup

This is mostly written assuming `kindlehf`, but `kindlepw2` works too.
It's available as a build arg for the devcontainer too: see [`devcontainer.json`](.devcontainer/devcontainer.json)'s `build.args`.

## Running with a devcontainer

Set up the devcontainer. This will happen automatically if using the VS Code extension.

```
devcontainer up --workspace-folder .
```

You can exec a shell in the container, and follow the next steps the same way. (You'll need to run it _outside_ of the devcontainer for the UI, though, and to SSH/SCP the binary to your Kindle.)

```bash
host$ devcontainer exec --workspace-folder . bash

root ➜ /workspaces/template-kindle-gtk (master) $ meson compile -C builddir_$_KINDLE_TARGET_PLATFORM
```

Alternately, you can exec one-off build commands instead.

```bash
kindle_ip=192.168.0.141

# target=kindlepw2 or kindlehf -- check what the container was built with
target=$(devcontainer exec --workspace-folder . bash -c 'echo $_KINDLE_TARGET_PLATFORM')

# cross-compile setup
devcontainer exec --workspace-folder . bash -c 'meson setup builddir_${_KINDLE_TARGET_PLATFORM} --cross-file /root/x-tools/arm-${_KINDLE_TARGET_PLATFORM}-linux-*/meson-crosscompile.txt'

# cross-compile build
devcontainer exec --workspace-folder . bash -c 'meson compile -C builddir_${_KINDLE_TARGET_PLATFORM}'

# copy to device
scp builddir_${target}/template_kindle_gtk root@${kindle_ip}:/mnt/us/extensions/
```

## Building the application

#### Build and run locally

Run once-ish:
```
meson setup builddir
```

Rebuild and run:
```
meson compile -C builddir && ./builddir/template_kindle_gtk
```

#### Build locally, run on Kindle

Run once-ish:

```
meson setup builddir_kindlehf --cross-file ~/x-tools/arm-kindlehf-linux-gnueabihf/meson-crosscompile.txt
```

Rebuild:
```
meson compile -C builddir_kindlehf
```

Copy to Kindle (note your own IP!):

```
scp builddir_kindlehf/template_kindle_gtk root@192.168.0.141:/mnt/us/extensions/
```

Now SSH to your Kindle and run it:

```
/mnt/us/extensions/template_kindle_gtk
```
