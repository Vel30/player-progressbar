#include <player-progressbar>

new PlayerProgressBar: PlayerProgressBar[MAX_PLAYERS][4] = { { PlayerProgressBar: INVALID_PLAYER_PROGRESS_BAR_ID, ... }, ... };

public OnPlayerConnect(playerid) {
  PlayerProgressBar[playerid][0] = CreatePlayerProgressBar(playerid, 320.0, 240.0);
  SetPlayerProgressBarSize(playerid, PlayerProgressBar[playerid][0], 20.0, 80.0);
  SetPlayerProgressBarAlign(playerid, PlayerProgressBar[playerid][0], ALIGN_CENTER);
  SetPlayerProgressBarValign(playerid, PlayerProgressBar[playerid][0], VALIGN_BOTTOM);
  SetPlayerProgressBarFgColor(playerid, PlayerProgressBar[playerid][0], 0xFF52C0FF);
  SetPlayerProgressBarMgColor(playerid, PlayerProgressBar[playerid][0], 0);
  SetPlayerProgressBarFillMode(playerid, PlayerProgressBar[playerid][0], FILL_BOTTOM_TO_TOP);
  SetPlayerProgressBarValue(playerid, PlayerProgressBar[playerid][0], 77.0);

  PlayerProgressBar[playerid][1] = CreatePlayerProgressBar(playerid, 320.0, 240.0);
  SetPlayerProgressBarSize(playerid, PlayerProgressBar[playerid][1], 20.0, 80.0);
  SetPlayerProgressBarAlign(playerid, PlayerProgressBar[playerid][1], ALIGN_CENTER);
  SetPlayerProgressBarValign(playerid, PlayerProgressBar[playerid][1], VALIGN_TOP);
  SetPlayerProgressBarFgColor(playerid, PlayerProgressBar[playerid][1], 0x1EE76AFF);
  SetPlayerProgressBarMgColor(playerid, PlayerProgressBar[playerid][1], 0);
  SetPlayerProgressBarFillMode(playerid, PlayerProgressBar[playerid][1], FILL_TOP_TO_BOTTOM);
  SetPlayerProgressBarValue(playerid, PlayerProgressBar[playerid][1], 33.5);

  new Float: x;

  GetPlayerProgressBarSize(playerid, PlayerProgressBar[playerid][0], x);

  x /= 2.0;

  PlayerProgressBar[playerid][2] = CreatePlayerProgressBar(playerid, 320.0 - x, 240.0);
  SetPlayerProgressBarSize(playerid, PlayerProgressBar[playerid][2], 80.0, 20.0);
  SetPlayerProgressBarAlign(playerid, PlayerProgressBar[playerid][2], ALIGN_RIGHT);
  SetPlayerProgressBarValign(playerid, PlayerProgressBar[playerid][2], VALIGN_CENTER);
  SetPlayerProgressBarFgColor(playerid, PlayerProgressBar[playerid][2], 0x0095EDFF);
  SetPlayerProgressBarBgColor(playerid, PlayerProgressBar[playerid][2], 0);
  SetPlayerProgressBarFillMode(playerid, PlayerProgressBar[playerid][2], FILL_RIGHT_TO_LEFT);
  SetPlayerProgressBarValue(playerid, PlayerProgressBar[playerid][2], 25.3);

  PlayerProgressBar[playerid][3] = CreatePlayerProgressBar(playerid, 320.0 + x, 240.0);
  SetPlayerProgressBarSize(playerid, PlayerProgressBar[playerid][3], 80.0, 20.0);
  SetPlayerProgressBarAlign(playerid, PlayerProgressBar[playerid][3], ALIGN_LEFT);
  SetPlayerProgressBarValign(playerid, PlayerProgressBar[playerid][3], VALIGN_CENTER);
  SetPlayerProgressBarFgColor(playerid, PlayerProgressBar[playerid][3], 0xFF992CFF);
  SetPlayerProgressBarBgColor(playerid, PlayerProgressBar[playerid][3], 0);
  SetPlayerProgressBarFillMode(playerid, PlayerProgressBar[playerid][3], FILL_LEFT_TO_RIGHT);
  SetPlayerProgressBarValue(playerid, PlayerProgressBar[playerid][3], 43.0);

  for (new i; i < 4; i++) {
    ShowPlayerProgressBar(playerid, PlayerProgressBar[playerid][i]);
  }
}
