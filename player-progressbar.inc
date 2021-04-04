#if defined _playerprogressbar_included
  #endinput
#endif
#define _playerprogressbar_included

#include <a_samp>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_hooks>

#define MAX_PLAYER_PROGRESS_BARS (_: MAX_PLAYER_TEXT_DRAWS / 3)
#define INVALID_PLAYER_PROGRESS_BAR_ID cellmin

#define GetPlayerProgressBarPos GetPlayerProgressBarPosition
#define SetPlayerProgressBarPos SetPlayerProgressBarPosition
#define GetPlayerProgressBarFgColour GetPlayerProgressBarFgColor
#define SetPlayerProgressBarFgColour SetPlayerProgressBarFgColor
#define GetPlayerProgressBarMgColour GetPlayerProgressBarMgColor
#define SetPlayerProgressBarMgColour SetPlayerProgressBarMgColor
#define GetPlayerProgressBarBgColour GetPlayerProgressBarBgColor
#define SetPlayerProgressBarBgColour SetPlayerProgressBarBgColor

#define GivePlayerProgressBarValue(%0,%1,%2) SetPlayerProgressBarValue(%0, %1, GetPlayerProgressBarValue(%0, %1) + %2)
#define ResetPlayerProgressBarValue(%0,%1) SetPlayerProgressBarValue(%0, %1, 0.0)

#define clamp(%0,%1,%2) (%0 < %1 ? (%1) : %0 > %2 ? (%2) : %0)

enum e_PLAYER_PROGRESS_BAR_ALIGN {
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

enum e_PLAYER_PROGRESS_BAR_VALIGN {
  VALIGN_TOP,
  VALIGN_CENTER,
  VALIGN_BOTTOM
};

enum e_PLAYER_PROGRESS_BAR_FILL_MODE {
  FILL_LEFT_TO_RIGHT,
  FILL_RIGHT_TO_LEFT,
  FILL_TOP_TO_BOTTOM,
  FILL_BOTTOM_TO_TOP
};

enum E_PLAYER_PROGRESS_BAR_DATA {
  bool: E_PLAYER_PROGRESS_BAR_VISIBLE,
  Float: E_PLAYER_PROGRESS_BAR_MAX_VALUE,
  Float: E_PLAYER_PROGRESS_BAR_VALUE,
  e_PLAYER_PROGRESS_BAR_ALIGN: E_PLAYER_PROGRESS_BAR_ALIGN,
  e_PLAYER_PROGRESS_BAR_VALIGN: E_PLAYER_PROGRESS_BAR_VALIGN,
  Float: E_PLAYER_PROGRESS_BAR_POS_X,
  Float: E_PLAYER_PROGRESS_BAR_POS_Y,
  Float: E_PLAYER_PROGRESS_BAR_SIZE_X,
  Float: E_PLAYER_PROGRESS_BAR_SIZE_Y,
  e_PLAYER_PROGRESS_BAR_FILL_MODE: E_PLAYER_PROGRESS_BAR_FILL_MODE,
  Float: E_PLAYER_PROGRESS_BAR_BG_PAD,
  E_PLAYER_PROGRESS_BAR_FG_COLOR,
  E_PLAYER_PROGRESS_BAR_MG_COLOR,
  E_PLAYER_PROGRESS_BAR_BG_COLOR,
  Timer: E_PLAYER_PROGRESS_BAR_F_TIMER,
  PlayerText: E_PLAYER_PROGRESS_BAR_FG_TD,
  PlayerText: E_PLAYER_PROGRESS_BAR_MG_TD,
  PlayerText: E_PLAYER_PROGRESS_BAR_BG_TD
};

static PlayerProgressBarData[MAX_PLAYERS][MAX_PLAYER_PROGRESS_BARS][E_PLAYER_PROGRESS_BAR_DATA];

new Iterator: PlayerProgressBar[MAX_PLAYERS]<MAX_PLAYER_PROGRESS_BARS>;

forward PlayerProgressBar: CreatePlayerProgressBar(playerid, Float: x, Float: y);
forward bool: IsValidPlayerProgressBar(playerid, PlayerProgressBar: id);
forward bool: DestroyPlayerProgressBar(playerid, PlayerProgressBar: id);
forward bool: RenderPlayerProgressBar(playerid, id);
forward Float: GetPlayerProgressBarPercentage(playerid, id);
forward bool: IsPlayerProgressBarVisible(playerid, PlayerProgressBar: id);
forward Float: GetPlayerProgressBarMaxValue(playerid, PlayerProgressBar: id);
forward Float: GetPlayerProgressBarValue(playerid, PlayerProgressBar: id);
forward e_PLAYER_PROGRESS_BAR_ALIGN: GetPlayerProgressBarAlign(playerid, PlayerProgressBar: id);
forward e_PLAYER_PROGRESS_BAR_VALIGN: GetPlayerProgressBarValign(playerid, PlayerProgressBar: id);
forward bool: GetPlayerProgressBarPosition(playerid, PlayerProgressBar: id, &Float: x = 0.0, &Float: y = 0.0);
forward bool: GetPlayerProgressBarSize(playerid, PlayerProgressBar: id, &Float: x = 0.0, &Float: y = 0.0);
forward e_PLAYER_PROGRESS_BAR_FILL_MODE: GetPlayerProgressBarFillMode(playerid, PlayerProgressBar: id);
forward Float: GetPlayerProgressBarBgPadding(playerid, PlayerProgressBar: id);
forward GetPlayerProgressBarFgColor(playerid, PlayerProgressBar: id);
forward GetPlayerProgressBarMgColor(playerid, PlayerProgressBar: id);
forward GetPlayerProgressBarBgColor(playerid, PlayerProgressBar: id);
forward ShowPlayerProgressBar(playerid, PlayerProgressBar: id);
forward HidePlayerProgressBar(playerid, PlayerProgressBar: id);
forward bool: SetPlayerProgressBarMaxValue(playerid, PlayerProgressBar: id, Float: set);
forward bool: SetPlayerProgressBarValue(playerid, PlayerProgressBar: id, Float: set);
forward bool: SetPlayerProgressBarAlign(playerid, PlayerProgressBar: id, e_PLAYER_PROGRESS_BAR_ALIGN: set);
forward bool: SetPlayerProgressBarValign(playerid, PlayerProgressBar: id, e_PLAYER_PROGRESS_BAR_VALIGN: set);
forward bool: SetPlayerProgressBarPosition(playerid, PlayerProgressBar: id, Float: x, Float: y);
forward bool: SetPlayerProgressBarSize(playerid, PlayerProgressBar: id, Float: x, Float: y);
forward bool: SetPlayerProgressBarFillMode(playerid, PlayerProgressBar: id, e_PLAYER_PROGRESS_BAR_FILL_MODE: set);
forward bool: SetPlayerProgressBarBgPadding(playerid, PlayerProgressBar: id, Float: set);
forward bool: SetPlayerProgressBarFgColor(playerid, PlayerProgressBar: id, set);
forward bool: SetPlayerProgressBarMgColor(playerid, PlayerProgressBar: id, set);
forward bool: SetPlayerProgressBarBgColor(playerid, PlayerProgressBar: id, set);
forward FlashPlayerProgressBar(playerid, PlayerProgressBar: id);
forward StopFlashPlayerProgressBar(playerid, PlayerProgressBar: id);
forward bool: IsPlayerProgressBarFlashing(playerid, PlayerProgressBar: id);
forward DestroyAllPlayerProgressBars(playerid);
forward PlayerText: CreatePlayerTextDrawBox(playerid, color, Float: x, Float: y, Float: sizex, Float: sizey);

stock PlayerProgressBar: CreatePlayerProgressBar(playerid, Float: x, Float: y) {
  new id = Iter_Free(PlayerProgressBar[playerid]);

  if (id == ITER_NONE) {
    return PlayerProgressBar: INVALID_PLAYER_PROGRESS_BAR_ID;
  }

  Iter_Add(PlayerProgressBar[playerid], id);

  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_TD] = PlayerText: INVALID_TEXT_DRAW;
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_TD] = PlayerText: INVALID_TEXT_DRAW;
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] = PlayerText: INVALID_TEXT_DRAW;

  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_POS_X] = x;
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_POS_Y] = y;

  // defaults
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MAX_VALUE] = 100.0;
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_COLOR] = 0;
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_PAD] = 2.0;
  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_COLOR] = 0x000000FF;
  return PlayerProgressBar: id;
}

stock bool: IsValidPlayerProgressBar(playerid, PlayerProgressBar: id) {
  return Iter_Contains(PlayerProgressBar[playerid], _: id);
}

stock bool: DestroyPlayerProgressBar(playerid, PlayerProgressBar: id) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  if (PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER]) {
    stop PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER];
  }

  PlayerTextDrawDestroy(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_TD]);
  PlayerTextDrawDestroy(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_TD]);
  PlayerTextDrawDestroy(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_TD]);

  static const data[E_PLAYER_PROGRESS_BAR_DATA];

  PlayerProgressBarData[playerid][_: id] = data;

  Iter_Remove(PlayerProgressBar[playerid], _: id);
  return true;
}

stock static bool: RenderPlayerProgressBar(playerid, id) {
  if (!IsValidPlayerProgressBar(playerid, PlayerProgressBar: id)) {
    return false;
  }

  if (PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_TD] != PlayerText: INVALID_TEXT_DRAW) {
    PlayerTextDrawDestroy(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_TD]);
    PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_TD] = PlayerText: INVALID_TEXT_DRAW;
  }

  if (PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_TD] != PlayerText: INVALID_TEXT_DRAW) {
    PlayerTextDrawDestroy(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_TD]);
    PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_TD] = PlayerText: INVALID_TEXT_DRAW;
  }

  if (PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] != PlayerText: INVALID_TEXT_DRAW) {
    PlayerTextDrawDestroy(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD]);
    PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] = PlayerText: INVALID_TEXT_DRAW;
  }

  new Float: x = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_POS_X],
    Float: y = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_POS_Y],
    Float: sizex = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_SIZE_X],
    Float: sizey = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_SIZE_Y],
    Float: bgpadding = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_PAD],
    e_PLAYER_PROGRESS_BAR_ALIGN: align = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_ALIGN],
    e_PLAYER_PROGRESS_BAR_VALIGN: valign = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_VALIGN];

  x = align == ALIGN_LEFT ? x : align == ALIGN_CENTER ? x - sizex / 2 : x - sizex;
  y = valign == VALIGN_TOP ? y : valign == VALIGN_CENTER ? y - sizey / 2 : y - sizey;

  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_TD] = CreatePlayerTextDrawBox(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_COLOR], x, y, sizex, sizey);

  x += bgpadding;
  y += bgpadding;

  sizex -= bgpadding * 2;
  sizey -= bgpadding * 2;

  PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_TD] = CreatePlayerTextDrawBox(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_COLOR], x, y, sizex, sizey);

  switch (PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FILL_MODE]) {
    case FILL_LEFT_TO_RIGHT: {
      PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] = CreatePlayerTextDrawBox(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_COLOR], x, y, GetPlayerProgressBarPercentage(playerid, id), sizey);
    }
    case FILL_RIGHT_TO_LEFT: {
      PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] = CreatePlayerTextDrawBox(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_COLOR], x + sizex, y, GetPlayerProgressBarPercentage(playerid, id), sizey);
    }
    case FILL_TOP_TO_BOTTOM: {
      PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] = CreatePlayerTextDrawBox(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_COLOR], x, y, sizex, GetPlayerProgressBarPercentage(playerid, id));
    }
    case FILL_BOTTOM_TO_TOP: {
      PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD] = CreatePlayerTextDrawBox(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_COLOR], x, y + sizey, sizex, GetPlayerProgressBarPercentage(playerid, id));
    }
  }

  if (PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_VISIBLE]) {
    PlayerTextDrawShow(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_TD]);
    PlayerTextDrawShow(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MG_TD]);
    PlayerTextDrawShow(playerid, PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FG_TD]);
  }
  return true;
}

stock static Float: GetPlayerProgressBarPercentage(playerid, id) {
  new e_PLAYER_PROGRESS_BAR_FILL_MODE: fillmode = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_FILL_MODE],
    Float: bgpadding = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_BG_PAD],
    Float: sizex = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_SIZE_X] - bgpadding * 2,
    Float: sizey = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_SIZE_Y] - bgpadding * 2,
    Float: value = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_VALUE],
    Float: maxvalue = PlayerProgressBarData[playerid][id][E_PLAYER_PROGRESS_BAR_MAX_VALUE];
  return !IsValidPlayerProgressBar(playerid, (PlayerProgressBar: id)) ? 0.0 : fillmode == FILL_LEFT_TO_RIGHT || fillmode == FILL_TOP_TO_BOTTOM ? ((fillmode == FILL_LEFT_TO_RIGHT || fillmode == FILL_RIGHT_TO_LEFT ? sizex : sizey) * value) / maxvalue : -((fillmode == FILL_LEFT_TO_RIGHT || fillmode == FILL_RIGHT_TO_LEFT ? sizex : sizey) * value) / maxvalue;
}

stock bool: IsPlayerProgressBarVisible(playerid, PlayerProgressBar: id) {
  return IsValidPlayerProgressBar(playerid, id) && PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VISIBLE];
}

stock Float: GetPlayerProgressBarMaxValue(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? 0.0 : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MAX_VALUE];
}

stock Float: GetPlayerProgressBarValue(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? 0.0 : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VALUE];
}

stock e_PLAYER_PROGRESS_BAR_ALIGN: GetPlayerProgressBarAlign(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? ALIGN_LEFT : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_ALIGN];
}

stock e_PLAYER_PROGRESS_BAR_VALIGN: GetPlayerProgressBarValign(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? VALIGN_TOP : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VALIGN];
}

stock bool: GetPlayerProgressBarPosition(playerid, PlayerProgressBar: id, &Float: x = 0.0, &Float: y = 0.0) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return !!(x = y = 0.0);
  }

  x = PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_POS_X];
  y = PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_POS_Y];
  return true;
}

stock bool: GetPlayerProgressBarSize(playerid, PlayerProgressBar: id, &Float: x = 0.0, &Float: y = 0.0) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return !!(x = y = 0.0);
  }

  x = PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_SIZE_X];
  y = PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_SIZE_Y];
  return true;
}

stock e_PLAYER_PROGRESS_BAR_FILL_MODE: GetPlayerProgressBarFillMode(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? FILL_LEFT_TO_RIGHT : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FILL_MODE];
}

stock Float: GetPlayerProgressBarBgPadding(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? 0.0 : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_PAD];
}

stock GetPlayerProgressBarFgColor(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? 0 : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_COLOR];
}

stock GetPlayerProgressBarMgColor(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? 0 : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_COLOR];
}

stock GetPlayerProgressBarBgColor(playerid, PlayerProgressBar: id) {
  return !IsValidPlayerProgressBar(playerid, id) ? 0 : PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_COLOR];
}

stock ShowPlayerProgressBar(playerid, PlayerProgressBar: id) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return 0;
  }

  if (PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VISIBLE]) {
    return -1;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VISIBLE] = true;

  RenderPlayerProgressBar(playerid, _: id);
  return 1;
}

stock HidePlayerProgressBar(playerid, PlayerProgressBar: id) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return 0;
  }

  if (!PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VISIBLE]) {
    return -1;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VISIBLE] = false;

  PlayerTextDrawHide(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_TD]);
  PlayerTextDrawHide(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_TD]);
  PlayerTextDrawHide(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_TD]);
  return 1;
}

stock bool: SetPlayerProgressBarMaxValue(playerid, PlayerProgressBar: id, Float: set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MAX_VALUE] = set;

  SetPlayerProgressBarValue(playerid, id, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VALUE]);
  return true;
}

stock bool: SetPlayerProgressBarValue(playerid, PlayerProgressBar: id, Float: set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VALUE] = clamp(set, 0.0, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MAX_VALUE]);

  switch (PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FILL_MODE]) {
    case FILL_LEFT_TO_RIGHT, FILL_RIGHT_TO_LEFT: {
      PlayerTextDrawTextSize(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_TD], GetPlayerProgressBarPercentage(playerid, _: id), PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_SIZE_Y]);
    }
    case FILL_TOP_TO_BOTTOM, FILL_BOTTOM_TO_TOP: {
      PlayerTextDrawTextSize(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_TD], PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_SIZE_X], GetPlayerProgressBarPercentage(playerid, _: id));
    }
  }

  if (PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VISIBLE]) {
    PlayerTextDrawShow(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_TD]);
  }
  return true;
}

stock bool: SetPlayerProgressBarAlign(playerid, PlayerProgressBar: id, e_PLAYER_PROGRESS_BAR_ALIGN: set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_ALIGN] = e_PLAYER_PROGRESS_BAR_ALIGN: clamp(set, ALIGN_LEFT, ALIGN_RIGHT);

  RenderPlayerProgressBar(playerid, _: id);
  return true;
}

stock bool: SetPlayerProgressBarValign(playerid, PlayerProgressBar: id, e_PLAYER_PROGRESS_BAR_VALIGN: set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_VALIGN] = e_PLAYER_PROGRESS_BAR_VALIGN: clamp(set, VALIGN_TOP, VALIGN_BOTTOM);

  RenderPlayerProgressBar(playerid, _: id);
  return true;
}

stock bool: SetPlayerProgressBarPosition(playerid, PlayerProgressBar: id, Float: x, Float: y) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_POS_X] = x;
  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_POS_Y] = y;

  RenderPlayerProgressBar(playerid, _: id);
  return true;
}

stock bool: SetPlayerProgressBarSize(playerid, PlayerProgressBar: id, Float: x, Float: y) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_SIZE_X] = x;
  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_SIZE_Y] = y;

  RenderPlayerProgressBar(playerid, _: id);
  return true;
}

stock bool: SetPlayerProgressBarFillMode(playerid, PlayerProgressBar: id, e_PLAYER_PROGRESS_BAR_FILL_MODE: set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FILL_MODE] = e_PLAYER_PROGRESS_BAR_FILL_MODE: clamp(set, FILL_LEFT_TO_RIGHT, FILL_BOTTOM_TO_TOP);

  RenderPlayerProgressBar(playerid, _: id);
  return true;
}

stock bool: SetPlayerProgressBarBgPadding(playerid, PlayerProgressBar: id, Float: set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_PAD] = set;

  RenderPlayerProgressBar(playerid, _: id);
  return true;
}

stock bool: SetPlayerProgressBarFgColor(playerid, PlayerProgressBar: id, set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_COLOR] = set;

  if (!PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_COLOR]) {
    PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_COLOR] = ((((set >>> 8) & 0xFFFFFF & 0xFEFEFE) >> 1) << 8) | 0xFF;

    PlayerTextDrawColor(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_TD], PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_COLOR]);
  }

  PlayerTextDrawColor(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_FG_TD], set);
  return true;
}

stock bool: SetPlayerProgressBarMgColor(playerid, PlayerProgressBar: id, set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_COLOR] = set;

  PlayerTextDrawColor(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_MG_TD], set);
  return true;
}

stock bool: SetPlayerProgressBarBgColor(playerid, PlayerProgressBar: id, set) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return false;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_COLOR] = set;

  PlayerTextDrawColor(playerid, PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_BG_TD], set);
  return true;
}

stock FlashPlayerProgressBar(playerid, PlayerProgressBar: id) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return 0;
  }

  if (PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER]) {
    return -1;
  }

  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER] = repeat FlashPlayerProgressBarTimer(playerid, _: id);
  return 1;
}

stock StopFlashPlayerProgressBar(playerid, PlayerProgressBar: id) {
  if (!IsValidPlayerProgressBar(playerid, id)) {
    return 0;
  }

  if (!PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER]) {
    return -1;
  }

  stop PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER];
  PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER] = Timer: 0;

  ShowPlayerProgressBar(playerid, id);
  return 1;
}

stock bool: IsPlayerProgressBarFlashing(playerid, PlayerProgressBar: id) {
  return IsValidPlayerProgressBar(playerid, id) && !!PlayerProgressBarData[playerid][_: id][E_PLAYER_PROGRESS_BAR_F_TIMER];
}

stock static DestroyAllPlayerProgressBars(playerid) {
  foreach (new i : PlayerProgressBar[playerid]) {
    DestroyPlayerProgressBar(playerid, PlayerProgressBar: i);
  }
}

stock static PlayerText: CreatePlayerTextDrawBox(playerid, color, Float: x, Float: y, Float: sizex, Float: sizey) {
  new PlayerText: id = CreatePlayerTextDraw(playerid, x, y, !"LD_SPAC:white");

  PlayerTextDrawFont(playerid, id, TEXT_DRAW_FONT_SPRITE_DRAW);
  PlayerTextDrawColor(playerid, id, color);
  PlayerTextDrawTextSize(playerid, id, sizex, sizey);
  return id;
}

timer FlashPlayerProgressBarTimer[100](playerid, id) {
  if (ShowPlayerProgressBar(playerid, PlayerProgressBar: id) == -1) {
    HidePlayerProgressBar(playerid, PlayerProgressBar: id);
  }
}

hook OnScriptInit() {
  Iter_Init(PlayerProgressBar);
}

hook OnScriptExit() {
  foreach (new i : Player) {
    DestroyAllPlayerProgressBars(i);
  }
}

hook OnPlayerDisconnect(playerid, reason) {
  Iter_Clear(PlayerProgressBar[playerid]);
}
