// Display images inside a terminal
// Copyright (C) 2023  JustKidding
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef __WINDOW__
#define __WINDOW__

#include "image.hpp"

#include <xcb/xproto.h>
#include <xcb/xcb_image.h>
#include <thread>

class Window
{
public:
    Window(xcb_connection_t *connection,
            xcb_screen_t *screen,
            xcb_window_t parent,
            int x, int y, int max_width, int max_height);
    ~Window();

    auto draw(const Image& image) -> void;

private:
    xcb_connection_t *connection;
    xcb_screen_t *screen;
    xcb_window_t parent;
    xcb_window_t window;
    xcb_gcontext_t gc;
    xcb_image_t *xcb_image = nullptr;

    std::unique_ptr<std::jthread> event_handler;
    auto handle_events() -> void;
    auto terminate_event_handler() -> void;
};

#endif