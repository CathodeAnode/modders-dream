## Build

Run these commands from the repository root.

Debug uses Clang with libc++:

```sh
cmake --preset debug
cmake --build --preset debug
```

Release uses Clang with libc++ and `-O3` optimization:

```sh
cmake --preset release
cmake --build --preset release
```

Both build the game and shaders, including stale shader cleanup. Unchanged shader
outputs are reused; changed shaders and their dependencies are recompiled.

Outputs live in `build/debug/` and `build/release/`, respectively. You can keep
both builds without clearing the build directory when switching configurations.

To build only shaders, use `cmake --build --preset debug --target shaders`
(or substitute `release`).

`cmake --build --preset debug` (or `release`) only builds an already configured
directory; it cannot recreate a deleted build tree.
