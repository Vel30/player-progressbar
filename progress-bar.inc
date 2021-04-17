#if defined _progressbar_included
  #endinput
#endif
#define _progressbar_included

#include <a_samp>
#include <YSI_Data\y_iterate>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_hooks>

#if !defined MAX_PROGRESS_BARS
  #define MAX_PROGRESS_BARS 16
#endif
#if !defined MAX_PLAYER_PROGRESS_BARS
  #define MAX_PLAYER_PROGRESS_BARS 8
#endif
#define INVALID_PROGRESS_BAR_ID ProgressBar: cellmin

#define GetProgressBarPos GetProgressBarPosition
#define SetProgressBarPos SetProgressBarPosition
#define GetProgressBarFgColour GetProgressBarFgColor
#define SetProgressBarFgColour SetProgressBarFgColor
#define GetProgressBarMgColour GetProgressBarMgColor
#define SetProgressBarMgColour SetProgressBarMgColor
#define GetProgressBarBgColour GetProgressBarBgColor
#define SetProgressBarBgColour SetProgressBarBgColor

#define GiveProgressBarValue(%0,%1,%2) SetProgressBarValue(%0, %1, GetProgressBarValue(%0, %1) + %2)
#define ResetProgressBarValue(%0,%1) SetProgressBarValue(%0, %1, 0.0)

#define GET_PROGRESS_BAR_PLAYER_ID(%0) (_: %0 > MAX_PROGRESS_BARS ? (_: %0 - MAX_PROGRESS_BARS) / MAX_PLAYER_PROGRESS_BARS : INVALID_PLAYER_ID)

enum e_PROGRESS_BAR_ALIGN {
  ALIGN_LEFT,
  ALIGN_CENTER,
  ALIGN_RIGHT
};

enum e_PROGRESS_BAR_VALIGN {
  VALIGN_TOP,
  VALIGN_CENTER,
  VALIGN_BOTTOM
};

enum e_PROGRESS_BAR_FILL_MODE {
  FILL_LEFT_TO_RIGHT,
  FILL_RIGHT_TO_LEFT,
  FILL_TOP_TO_BOTTOM,
  FILL_BOTTOM_TO_TOP
};

enum E_PROGRESS_BAR_DATA {
  bool: E_PROGRESS_BAR_VISIBLE,
  Float: E_PROGRESS_BAR_MAX_VALUE,
  Float: E_PROGRESS_BAR_VALUE,
  e_PROGRESS_BAR_ALIGN: E_PROGRESS_BAR_ALIGN,
  e_PROGRESS_BAR_VALIGN: E_PROGRESS_BAR_VALIGN,
  Float: E_PROGRESS_BAR_POS_X,
  Float: E_PROGRESS_BAR_POS_Y,
  Float: E_PROGRESS_BAR_SIZE_X,
  Float: E_PROGRESS_BAR_SIZE_Y,
  e_PROGRESS_BAR_FILL_MODE: E_PROGRESS_BAR_FILL_MODE,
  Float: E_PROGRESS_BAR_BG_PADDING,
  E_PROGRESS_BAR_FG_COLOR,
  E_PROGRESS_BAR_MG_COLOR,
  E_PROGRESS_BAR_BG_COLOR,
  Timer: E_PROGRESS_BAR_FLASH_TIMER_ID,
  E_PROGRESS_BAR_FG_TD_ID,
  E_PROGRESS_BAR_MG_TD_ID,
  E_PROGRESS_BAR_BG_TD_ID
};

static ProgressBarData[MAX_PROGRESS_BARS + (MAX_PLAYER_PROGRESS_BARS * MAX_PLAYERS)][E_PROGRESS_BAR_DATA];

new Iterator: ProgressBar<MAX_PROGRESS_BARS + (MAX_PLAYER_PROGRESS_BARS * MAX_PLAYERS)>;

forward ProgressBar: CreateProgressBar(Float: x, Float: y, playerid = INVALID_PLAYER_ID);
forward bool: IsValidProgressBar(ProgressBar: id);
forward bool: DestroyProgressBar(ProgressBar: id);
forward bool: RenderProgressBar(id);
forward Float: GetProgressBarPercentage(id);
forward bool: IsProgressBarVisible(ProgressBar: id);
forward Float: GetProgressBarMaxValue(ProgressBar: id);
forward Float: GetProgressBarValue(ProgressBar: id);
forward e_PROGRESS_BAR_ALIGN: GetProgressBarAlign(ProgressBar: id);
forward e_PROGRESS_BAR_VALIGN: GetProgressBarValign(ProgressBar: id);
forward bool: GetProgressBarPosition(ProgressBar: id, &Float: x = 0.0, &Float: y = 0.0);
forward bool: GetProgressBarSize(ProgressBar: id, &Float: x = 0.0, &Float: y = 0.0);
forward e_PROGRESS_BAR_FILL_MODE: GetProgressBarFillMode(ProgressBar: id);
forward Float: GetProgressBarBgPadding(ProgressBar: id);
forward GetProgressBarFgColor(ProgressBar: id);
forward GetProgressBarMgColor(ProgressBar: id);
forward GetProgressBarBgColor(ProgressBar: id);
forward ShowProgressBar(ProgressBar: id);
forward HideProgressBar(ProgressBar: id);
forward bool: SetProgressBarMaxValue(ProgressBar: id, Float: set);
forward bool: SetProgressBarValue(ProgressBar: id, Float: set);
forward bool: SetProgressBarAlign(ProgressBar: id, e_PROGRESS_BAR_ALIGN: set);
forward bool: SetProgressBarValign(ProgressBar: id, e_PROGRESS_BAR_VALIGN: set);
forward bool: SetProgressBarPosition(ProgressBar: id, Float: x, Float: y);
forward bool: SetProgressBarSize(ProgressBar: id, Float: x, Float: y);
forward bool: SetProgressBarFillMode(ProgressBar: id, e_PROGRESS_BAR_FILL_MODE: set);
forward bool: SetProgressBarBgPadding(ProgressBar: id, Float: set);
forward bool: SetProgressBarFgColor(ProgressBar: id, set);
forward bool: SetProgressBarMgColor(ProgressBar: id, set);
forward bool: SetProgressBarBgColor(ProgressBar: id, set);
forward FlashProgressBar(ProgressBar: id);
forward StopFlashProgressBar(ProgressBar: id);
forward bool: IsProgressBarFlashing(ProgressBar: id);
forward GetProgressBarFreeSlot(playerid = INVALID_PLAYER_ID);
forward DestroyAllProgressBars();
forward CreateTextDrawBox(color, Float: x, Float: y, Float: sizex, Float: sizey, playerid = INVALID_PLAYER_ID);
forward Float: pb_floatclamp(Float: value, Float: min, Float: max);

stock ProgressBar: CreateProgressBar(Float: x, Float: y, playerid = INVALID_PLAYER_ID) {
  new id = GetProgressBarFreeSlot(playerid);

  if (id == cellmin) {
    return INVALID_PROGRESS_BAR_ID;
  }

  Iter_Add(ProgressBar, id);

  ProgressBarData[id][E_PROGRESS_BAR_POS_X] = x;
  ProgressBarData[id][E_PROGRESS_BAR_POS_Y] = y;

  // defaults
  ProgressBarData[id][E_PROGRESS_BAR_MAX_VALUE] = 100.0;
  ProgressBarData[id][E_PROGRESS_BAR_MG_COLOR] = 0;
  ProgressBarData[id][E_PROGRESS_BAR_BG_PADDING] = 2.0;
  ProgressBarData[id][E_PROGRESS_BAR_BG_COLOR] = 0x000000FF;

  ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID] = INVALID_TEXT_DRAW;
  ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID] = INVALID_TEXT_DRAW;
  ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] = INVALID_TEXT_DRAW;
  return ProgressBar: id;
}

stock bool: IsValidProgressBar(ProgressBar: id) {
  return Iter_Contains(ProgressBar, _: id);
}

stock bool: DestroyProgressBar(ProgressBar: id) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  if (ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID]) {
    stop ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID];
  }

  static const data[E_PROGRESS_BAR_DATA];

  ProgressBarData[_: id] = data;

  Iter_Remove(ProgressBar, _: id);
  return true;
}

stock static bool: RenderProgressBar(id) {
  if (!IsValidProgressBar(ProgressBar: id)) {
    return false;
  }

  new playerid = GET_PROGRESS_BAR_PLAYER_ID(id);

  if (playerid == INVALID_PLAYER_ID) {
    if (ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID] != INVALID_TEXT_DRAW) {
      TextDrawDestroy(Text: ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID]);
    }

    if (ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID] != INVALID_TEXT_DRAW) {
      TextDrawDestroy(Text: ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID]);
    }

    if (ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] != INVALID_TEXT_DRAW) {
      TextDrawDestroy(Text: ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID]);
    }
  } else {
    if (ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID] != INVALID_TEXT_DRAW) {
      PlayerTextDrawDestroy(playerid, PlayerText: ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID]);
    }

    if (ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID] != INVALID_TEXT_DRAW) {
      PlayerTextDrawDestroy(playerid, PlayerText: ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID]);
    }

    if (ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] != INVALID_TEXT_DRAW) {
      PlayerTextDrawDestroy(playerid, PlayerText: ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID]);
    }
  }

  ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID] = INVALID_TEXT_DRAW;
  ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID] = INVALID_TEXT_DRAW;
  ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] = INVALID_TEXT_DRAW;

  new Float: x = ProgressBarData[id][E_PROGRESS_BAR_POS_X],
    Float: y = ProgressBarData[id][E_PROGRESS_BAR_POS_Y],
    Float: sizex = ProgressBarData[id][E_PROGRESS_BAR_SIZE_X],
    Float: sizey = ProgressBarData[id][E_PROGRESS_BAR_SIZE_Y],
    Float: bgpadding = ProgressBarData[id][E_PROGRESS_BAR_BG_PADDING],
    e_PROGRESS_BAR_ALIGN: align = ProgressBarData[id][E_PROGRESS_BAR_ALIGN],
    e_PROGRESS_BAR_VALIGN: valign = ProgressBarData[id][E_PROGRESS_BAR_VALIGN];

  x = align == ALIGN_LEFT ? x : align == ALIGN_CENTER ? x - sizex / 2 : x - sizex;
  y = valign == VALIGN_TOP ? y : valign == VALIGN_CENTER ? y - sizey / 2 : y - sizey;

  ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID] = CreateTextDrawBox(ProgressBarData[id][E_PROGRESS_BAR_BG_COLOR], x, y, sizex, sizey, playerid);

  x += bgpadding;
  y += bgpadding;

  sizex -= bgpadding * 2;
  sizey -= bgpadding * 2;

  ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID] = CreateTextDrawBox(ProgressBarData[id][E_PROGRESS_BAR_MG_COLOR], x, y, sizex, sizey, playerid);

  switch (ProgressBarData[id][E_PROGRESS_BAR_FILL_MODE]) {
    case FILL_LEFT_TO_RIGHT: {
      ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] = CreateTextDrawBox(ProgressBarData[id][E_PROGRESS_BAR_FG_COLOR], x, y, GetProgressBarPercentage(id), sizey, playerid);
    }
    case FILL_RIGHT_TO_LEFT: {
      ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] = CreateTextDrawBox(ProgressBarData[id][E_PROGRESS_BAR_FG_COLOR], x + sizex, y, GetProgressBarPercentage(id), sizey, playerid);
    }
    case FILL_TOP_TO_BOTTOM: {
      ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] = CreateTextDrawBox(ProgressBarData[id][E_PROGRESS_BAR_FG_COLOR], x, y, sizex, GetProgressBarPercentage(id), playerid);
    }
    case FILL_BOTTOM_TO_TOP: {
      ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID] = CreateTextDrawBox(ProgressBarData[id][E_PROGRESS_BAR_FG_COLOR], x, y + sizey, sizex, GetProgressBarPercentage(id), playerid);
    }
  }

  if (playerid == INVALID_PLAYER_ID) {
    TextDrawShowForAll(Text: ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID]);
    TextDrawShowForAll(Text: ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID]);
    TextDrawShowForAll(Text: ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID]);
  } else {
    PlayerTextDrawShow(playerid, PlayerText: ProgressBarData[id][E_PROGRESS_BAR_BG_TD_ID]);
    PlayerTextDrawShow(playerid, PlayerText: ProgressBarData[id][E_PROGRESS_BAR_MG_TD_ID]);
    PlayerTextDrawShow(playerid, PlayerText: ProgressBarData[id][E_PROGRESS_BAR_FG_TD_ID]);
  }
  return true;
}

stock static Float: GetProgressBarPercentage(id) {
  new e_PROGRESS_BAR_FILL_MODE: fillmode = ProgressBarData[id][E_PROGRESS_BAR_FILL_MODE],
    Float: bgpadding = ProgressBarData[id][E_PROGRESS_BAR_BG_PADDING],
    Float: sizex = ProgressBarData[id][E_PROGRESS_BAR_SIZE_X] - bgpadding * 2,
    Float: sizey = ProgressBarData[id][E_PROGRESS_BAR_SIZE_Y] - bgpadding * 2,
    Float: value = ProgressBarData[id][E_PROGRESS_BAR_VALUE],
    Float: maxvalue = ProgressBarData[id][E_PROGRESS_BAR_MAX_VALUE];
  return !IsValidProgressBar((ProgressBar: id)) ? 0.0 : fillmode == FILL_LEFT_TO_RIGHT || fillmode == FILL_TOP_TO_BOTTOM ? ((fillmode == FILL_LEFT_TO_RIGHT || fillmode == FILL_RIGHT_TO_LEFT ? sizex : sizey) * value) / maxvalue : -((fillmode == FILL_LEFT_TO_RIGHT || fillmode == FILL_RIGHT_TO_LEFT ? sizex : sizey) * value) / maxvalue;
}

stock bool: IsProgressBarVisible(ProgressBar: id) {
  return IsValidProgressBar(id) && ProgressBarData[_: id][E_PROGRESS_BAR_VISIBLE];
}

stock Float: GetProgressBarMaxValue(ProgressBar: id) {
  return !IsValidProgressBar(id) ? 0.0 : ProgressBarData[_: id][E_PROGRESS_BAR_MAX_VALUE];
}

stock Float: GetProgressBarValue(ProgressBar: id) {
  return !IsValidProgressBar(id) ? 0.0 : ProgressBarData[_: id][E_PROGRESS_BAR_VALUE];
}

stock e_PROGRESS_BAR_ALIGN: GetProgressBarAlign(ProgressBar: id) {
  return !IsValidProgressBar(id) ? ALIGN_LEFT : ProgressBarData[_: id][E_PROGRESS_BAR_ALIGN];
}

stock e_PROGRESS_BAR_VALIGN: GetProgressBarValign(ProgressBar: id) {
  return !IsValidProgressBar(id) ? VALIGN_TOP : ProgressBarData[_: id][E_PROGRESS_BAR_VALIGN];
}

stock bool: GetProgressBarPosition(ProgressBar: id, &Float: x = 0.0, &Float: y = 0.0) {
  if (!IsValidProgressBar(id)) {
    return !!(x = y = 0.0);
  }

  x = ProgressBarData[_: id][E_PROGRESS_BAR_POS_X];
  y = ProgressBarData[_: id][E_PROGRESS_BAR_POS_Y];
  return true;
}

stock bool: GetProgressBarSize(ProgressBar: id, &Float: x = 0.0, &Float: y = 0.0) {
  if (!IsValidProgressBar(id)) {
    return !!(x = y = 0.0);
  }

  x = ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_X];
  y = ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_Y];
  return true;
}

stock e_PROGRESS_BAR_FILL_MODE: GetProgressBarFillMode(ProgressBar: id) {
  return !IsValidProgressBar(id) ? FILL_LEFT_TO_RIGHT : ProgressBarData[_: id][E_PROGRESS_BAR_FILL_MODE];
}

stock Float: GetProgressBarBgPadding(ProgressBar: id) {
  return !IsValidProgressBar(id) ? 0.0 : ProgressBarData[_: id][E_PROGRESS_BAR_BG_PADDING];
}

stock GetProgressBarFgColor(ProgressBar: id) {
  return !IsValidProgressBar(id) ? 0 : ProgressBarData[_: id][E_PROGRESS_BAR_FG_COLOR];
}

stock GetProgressBarMgColor(ProgressBar: id) {
  return !IsValidProgressBar(id) ? 0 : ProgressBarData[_: id][E_PROGRESS_BAR_MG_COLOR];
}

stock GetProgressBarBgColor(ProgressBar: id) {
  return !IsValidProgressBar(id) ? 0 : ProgressBarData[_: id][E_PROGRESS_BAR_BG_COLOR];
}

stock ShowProgressBar(ProgressBar: id) {
  if (!IsValidProgressBar(id)) {
    return 0;
  }

  if (ProgressBarData[_: id][E_PROGRESS_BAR_VISIBLE]) {
    return -1;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_VISIBLE] = true;

  RenderProgressBar(_: id);
  return 1;
}

stock HideProgressBar(ProgressBar: id) {
  if (!IsValidProgressBar(id)) {
    return 0;
  }

  if (!ProgressBarData[_: id][E_PROGRESS_BAR_VISIBLE]) {
    return -1;
  }

  new playerid = GET_PROGRESS_BAR_PLAYER_ID(id);

  if (playerid == INVALID_PLAYER_ID) {
    TextDrawHideForAll(Text: ProgressBarData[_: id][E_PROGRESS_BAR_BG_TD_ID]);
    TextDrawHideForAll(Text: ProgressBarData[_: id][E_PROGRESS_BAR_MG_TD_ID]);
    TextDrawHideForAll(Text: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID]);
  } else {
    PlayerTextDrawHide(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_BG_TD_ID]);
    PlayerTextDrawHide(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_MG_TD_ID]);
    PlayerTextDrawHide(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID]);
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_VISIBLE] = false;
  return 1;
}

stock bool: SetProgressBarMaxValue(ProgressBar: id, Float: set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_MAX_VALUE] = set;

  SetProgressBarValue(id, ProgressBarData[_: id][E_PROGRESS_BAR_VALUE]);
  return true;
}

stock bool: SetProgressBarValue(ProgressBar: id, Float: set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_VALUE] = pb_floatclamp(set, 0.0, ProgressBarData[_: id][E_PROGRESS_BAR_MAX_VALUE]);

  new playerid = GET_PROGRESS_BAR_PLAYER_ID(id);

  switch (ProgressBarData[_: id][E_PROGRESS_BAR_FILL_MODE]) {
    case FILL_LEFT_TO_RIGHT, FILL_RIGHT_TO_LEFT: {
      if (playerid == INVALID_PLAYER_ID) {
        TextDrawTextSize(Text: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID], GetProgressBarPercentage(_: id), ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_Y] - ProgressBarData[_: id][E_PROGRESS_BAR_BG_PADDING] * 2);
      } else {
        PlayerTextDrawTextSize(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID], GetProgressBarPercentage(_: id), ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_Y] - ProgressBarData[_: id][E_PROGRESS_BAR_BG_PADDING] * 2);
      }
    }
    case FILL_TOP_TO_BOTTOM, FILL_BOTTOM_TO_TOP: {
      if (playerid == INVALID_PLAYER_ID) {
        TextDrawTextSize(Text: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID], ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_X] - ProgressBarData[_: id][E_PROGRESS_BAR_BG_PADDING] * 2, GetProgressBarPercentage(_: id));
      } else {
        PlayerTextDrawTextSize(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID], ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_X] - ProgressBarData[_: id][E_PROGRESS_BAR_BG_PADDING] * 2, GetProgressBarPercentage(_: id));
      }
    }
  }

  if (ProgressBarData[_: id][E_PROGRESS_BAR_VISIBLE]) {
    if (playerid == INVALID_PLAYER_ID) {
      TextDrawShowForAll(Text: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID]);
    } else {
      PlayerTextDrawShow(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID]);
    }
  }
  return true;
}

stock bool: SetProgressBarAlign(ProgressBar: id, e_PROGRESS_BAR_ALIGN: set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_ALIGN] = set;

  RenderProgressBar(_: id);
  return true;
}

stock bool: SetProgressBarValign(ProgressBar: id, e_PROGRESS_BAR_VALIGN: set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_VALIGN] = set;

  RenderProgressBar(_: id);
  return true;
}

stock bool: SetProgressBarPosition(ProgressBar: id, Float: x, Float: y) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_POS_X] = x;
  ProgressBarData[_: id][E_PROGRESS_BAR_POS_Y] = y;

  RenderProgressBar(_: id);
  return true;
}

stock bool: SetProgressBarSize(ProgressBar: id, Float: x, Float: y) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_X] = x;
  ProgressBarData[_: id][E_PROGRESS_BAR_SIZE_Y] = y;

  RenderProgressBar(_: id);
  return true;
}

stock bool: SetProgressBarFillMode(ProgressBar: id, e_PROGRESS_BAR_FILL_MODE: set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_FILL_MODE] = set;

  RenderProgressBar(_: id);
  return true;
}

stock bool: SetProgressBarBgPadding(ProgressBar: id, Float: set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_BG_PADDING] = set;

  RenderProgressBar(_: id);
  return true;
}

stock bool: SetProgressBarFgColor(ProgressBar: id, set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_FG_COLOR] = set;

  new playerid = GET_PROGRESS_BAR_PLAYER_ID(id);

  if (!ProgressBarData[_: id][E_PROGRESS_BAR_MG_COLOR]) {
    ProgressBarData[_: id][E_PROGRESS_BAR_MG_COLOR] = ((((set >>> 8) & 0xFFFFFF & 0xFEFEFE) >> 1) << 8) | 0xFF;

    if (playerid == INVALID_PLAYER_ID) {
      TextDrawColor(Text: ProgressBarData[_: id][E_PROGRESS_BAR_MG_TD_ID], ProgressBarData[_: id][E_PROGRESS_BAR_MG_COLOR]);
    } else {
      PlayerTextDrawColor(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_MG_TD_ID], ProgressBarData[_: id][E_PROGRESS_BAR_MG_COLOR]);
    }
  }

  if (playerid == INVALID_PLAYER_ID) {
    TextDrawColor(Text: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID], set);
  } else {
    PlayerTextDrawColor(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_FG_TD_ID], set);
  }
  return true;
}

stock bool: SetProgressBarMgColor(ProgressBar: id, set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_MG_COLOR] = set;

  new playerid = GET_PROGRESS_BAR_PLAYER_ID(id);

  if (playerid == INVALID_PLAYER_ID) {
    TextDrawColor(Text: ProgressBarData[_: id][E_PROGRESS_BAR_MG_TD_ID], set);
  } else {
    PlayerTextDrawColor(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_MG_TD_ID], set);
  }
  return true;
}

stock bool: SetProgressBarBgColor(ProgressBar: id, set) {
  if (!IsValidProgressBar(id)) {
    return false;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_BG_COLOR] = set;

  new playerid = GET_PROGRESS_BAR_PLAYER_ID(id);

  if (playerid == INVALID_PLAYER_ID) {
    TextDrawColor(Text: ProgressBarData[_: id][E_PROGRESS_BAR_BG_TD_ID], set);
  } else {
    PlayerTextDrawColor(playerid, PlayerText: ProgressBarData[_: id][E_PROGRESS_BAR_BG_TD_ID], set);
  }
  return true;
}

stock FlashProgressBar(ProgressBar: id) {
  if (!IsValidProgressBar(id)) {
    return 0;
  }

  if (ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID]) {
    return -1;
  }

  ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID] = repeat FlashProgressBarTimer(_: id);
  return 1;
}

stock StopFlashProgressBar(ProgressBar: id) {
  if (!IsValidProgressBar(id)) {
    return 0;
  }

  if (!ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID]) {
    return -1;
  }

  stop ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID];
  ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID] = Timer: 0;

  ShowProgressBar(id);
  return 1;
}

stock bool: IsProgressBarFlashing(ProgressBar: id) {
  return IsValidProgressBar(id) && !!ProgressBarData[_: id][E_PROGRESS_BAR_FLASH_TIMER_ID];
}

stock static GetProgressBarFreeSlot(playerid = INVALID_PLAYER_ID) {
  new start,
    end;

  if (playerid == INVALID_PLAYER_ID) {
    end = MAX_PROGRESS_BARS;
  } else {
    start = MAX_PROGRESS_BARS + (MAX_PLAYER_PROGRESS_BARS * playerid);
    end = start + MAX_PLAYER_PROGRESS_BARS;
  }

  for (;;) {
    if (!(start < end-- && Iter_Contains(ProgressBar, end))) {
      break;
    }
  }
  return start > end ? cellmin : end;
}

stock static DestroyAllProgressBars() {
  foreach (new i : ProgressBar) {
    DestroyProgressBar(ProgressBar: i);
  }
}

stock static CreateTextDrawBox(color, Float: x, Float: y, Float: sizex, Float: sizey, playerid = INVALID_PLAYER_ID) {
  new id = INVALID_TEXT_DRAW;

  if (playerid == INVALID_PLAYER_ID) {
    id = _: TextDrawCreate(x, y, !"LD_SPAC:white");

    TextDrawFont(Text: id, TEXT_DRAW_FONT_SPRITE_DRAW);
    TextDrawColor(Text: id, color);
    TextDrawTextSize(Text: id, sizex, sizey);
  } else {
    id = _: CreatePlayerTextDraw(playerid, x, y, !"LD_SPAC:white");

    PlayerTextDrawFont(playerid, PlayerText: id, TEXT_DRAW_FONT_SPRITE_DRAW);
    PlayerTextDrawColor(playerid, PlayerText: id, color);
    PlayerTextDrawTextSize(playerid, PlayerText: id, sizex, sizey);
  }
  return id;
}

stock static Float: pb_floatclamp(Float: value, Float: min, Float: max) {
  return value < min ? min : value > max ? max : value;
}

timer FlashProgressBarTimer[100](id) {
  if (ShowProgressBar(ProgressBar: id) == -1) {
    HideProgressBar(ProgressBar: id);
  }
}

hook OnScriptExit() {
  DestroyAllProgressBars();
}
