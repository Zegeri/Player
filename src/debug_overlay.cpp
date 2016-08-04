/*
 * This file is part of EasyRPG Player.
 *
 * EasyRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

// Headers
#include <string>
#include "baseui.h"
#include "bitmap.h"
#include "debug_overlay.h"
#include "graphics.h"
#include "game_map.h"
#include "player.h"
#include "rpg_savepicture.h"
#include "main_data.h"
#include "utils.h"

Debug_Overlay::Debug_Overlay() {
	Graphics::RegisterDrawable(this);
}

Debug_Overlay::~Debug_Overlay() {
	Graphics::RemoveDrawable(this);
}

int Debug_Overlay::GetZ() const {
	return 10000;
}

DrawableType Debug_Overlay::GetType() const {
	return TypeDefault;
}

void Debug_Overlay::SelectNextDebugMode() {
	debug_mode = (DebugMode) ((debug_mode + 1) % END);
}

void Debug_Overlay::Draw() {
	if (debug_mode == DebugMode::None)
		return;

	BitmapRef disp = DisplayUi->GetDisplaySurface();

	// Get position of the upper left tile
	int ox = Game_Map::GetDisplayX() / SCREEN_TILE_WIDTH;
	int oy = Game_Map::GetDisplayY() / SCREEN_TILE_WIDTH;

	// Get the number of tiles that can be displayed on window
	int tiles_x = (int)ceil(DisplayUi->GetWidth() / (float)TILE_SIZE);
	int tiles_y = (int)ceil(DisplayUi->GetHeight() / (float)TILE_SIZE);

	int frame = Player::GetFrames();

	if (debug_mode == DebugMode::Pages) {
		// Select visible events and store pointers to them by tile
		std::map<std::pair<int,int>, std::vector<Game_Event*>> events_by_tile;
		for (Game_Event& ev : Game_Map::GetEvents()) {
			int x = ev.GetX() - ox;
			int y = ev.GetY() - oy;
			if (x < 0 || x > tiles_x)
				continue;
			if (y < 0 || y > tiles_y)
				continue;
			events_by_tile[{x,y}].push_back(&ev);
		}
		// Draw all events of each tile using different colors and alternating
		// their drawing order every 30 frames
		for (const auto& tile_ev : events_by_tile) {
			size_t num_evs = tile_ev.second.size();
			int start_i = (frame / 30) % num_evs;
			for (int i = start_i; i < start_i + num_evs; ++i) {
				Game_Event* ev = tile_ev.second[i % num_evs];
				disp->TextDraw(ev->GetScreenX(), ev->GetScreenY() - TILE_SIZE, 
					i % num_evs, Utils::ToString(ev->GetPageIndex()));
			}
		}
	} else if (debug_mode == DebugMode::Pictures) {
		for (const RPG::SavePicture& pic : Main_Data::game_data.pictures) {
			if (!pic.name.empty())
				disp->TextDraw(pic.current_x, pic.current_y, 1, pic.name);
		}
	}
}
