export module ModdersDream.Settings;

import ModdersDream.Math;

import std;

using namespace ModdersDream;

// This file is for global settings such as VSync.
export namespace ModdersDream {

// Keep this a struct/class.
// It may inherit from some sorts of "SaveData" abstract class in the future.
struct Settings {
    std::uint32_t vsync = 0;
    Math::Vector2i resolution = {800, 800};
    bool fullscreen = false;
};

} // namespace ModdersDream
