/* Copyright 2020 Marco Stålfors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// place overrides here
#undef BACKLIGHT_BREATHING
#define GRAVE_ESC_CTRL_OVERRIDE // Grave Esc is esc if ctrl pressed
#define NO_ACTION_MACRO // Disable legacy stuff
#define NO_ACTION_FUNCTION // Disable legacy stuff
#define USB_POLLING_INTERVAL_MS 1 // Faster pollig, because why not
//#define QMK_KEYS_PER_SCAN 12 // Moar keys per scan, theoretically faster
