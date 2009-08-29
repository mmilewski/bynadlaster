print('player.lua: [ LOADING ]');


local tbl_action_names = {
   "Down", "Right", "Left", "Up", "Die"
}


-- first  index = player_type
-- second index = animation type
-- third  index = frame
-- fourth index = x/y
local tbl_players_sprites = {};

g_frame_duration_go  = 175;
g_frame_duration_die = 250;


function InitSprites()
   print('player.lua: [ INITIALIZING SPRITES ]');

   local player_count		= 4;
   local animation_frames	= 20;
   local first_die_frame	= 12;
   
   local sprite_width		= 24;
   local sprite_height		= 24;
   local sprites_start_x	= 0;
   local sprites_start_y	= 219;
   local sprites_in_row		= 13;
   local row_width              = sprites_in_row * sprite_width;

   local sprite_count = 0;

   for player_idx = 0, player_count-1 do
      tbl_players_sprites[player_idx] = { };
      for frame_idx = 0, animation_frames-1 do
	 local offset_x = (sprites_start_x + sprite_width * sprite_count);
	 local offset_y = math.floor(offset_x / row_width);
	 x = offset_x % row_width + sprites_start_x;
	 y = offset_y * sprite_height + sprites_start_y;

	 if frame_idx < first_die_frame then -- does not die
	    local animation = tbl_action_names[math.floor(frame_idx/3)+1];
	    local frame = frame_idx % 3;
	    print("Loading animation " .. animation .. ", frame " .. frame);

	    if frame_idx % 3 == 0 then tbl_players_sprites[player_idx][animation] = { }; end
	    tbl_players_sprites[player_idx][animation][frame] = { };
	    tbl_players_sprites[player_idx][animation][frame].x = x;
	    tbl_players_sprites[player_idx][animation][frame].y = y;

	    sprite_count = sprite_count + 1;
	 else -- dies
	    local animation = "Die";
	    if frame_idx == first_die_frame then tbl_players_sprites[player_idx]["Die"] = { }; end
	    local frame = (frame_idx - first_die_frame) % 8;
	    tbl_players_sprites[player_idx]["Die"][frame] = { };
	    tbl_players_sprites[player_idx]["Die"][frame].x = x;
	    tbl_players_sprites[player_idx]["Die"][frame].y = y;
	    
	    print("Loading animation " .. animation .. ", frame " .. frame);
	    sprite_count = sprite_count + 1;
	 end
      end
   end

   print('player.lua: [ INITIALIZING SPRITES DONE ]');
end


function GetPlayerSprite(player_type, direction, is_dying, duration) 

   local animation = "Down";
   local frame_num = 0;

   if not is_dying then
      
      if direction:x() == 0 and direction:y() == 0 then -- stoi w miejscu
	 animation = "Down";
	 frame_num = 0;
      else
	 frame_num = (math.floor(duration/g_frame_duration_go)) % 2 + 1;

	 if     direction:x() > 0 then animation = "Right";
	 elseif direction:x() < 0 then animation = "Left";
	 elseif direction:y() > 0 then animation = "Up";
	 elseif direction:y() < 0 then animation = "Down"; 
	 else   animation = "Down";
	 end
      end

   else 
      frame_num = (math.floor(duration/g_frame_duration_die)) % 8;
      animation = "Die";
   end

   local tex_x = tbl_players_sprites[player_type][animation][frame_num].x;
   local tex_y = tbl_players_sprites[player_type][animation][frame_num].y;
   return TexCoords(tex_x, tex_y, 24, 24);

end



print('player.lua: [ RUNNING INIT SCRIPTS ]');
InitSprites();
print('player.lua: [ RUNNING INIT SCRIPTS DONE ]');


print('player.lua: [ LOADING DONE ]');
