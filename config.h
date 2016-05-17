/* See LICENSE file for copyright and license details. */
#include "gaplessgrid.c"
#include "maximize.c" // Really shitty hack for borderpx
#pragma once

//TODO: global var for togglability of swallowing
//canswallow=1 to look at rules
//canswallow=0 ignores rules and disables swallowing
//this is toggled by keybinding

/* appearance */
static const char *fonts[] = {
	"Source Code Pro for Powerline:Semibold:size=11:antialias=true:hinting=true",
	"Symbola:size=11",
    "Sans:size=11",
    "VL Gothic:size=11",
    "WenQuanYi Micro Hei:size=11"
};
static const char dmenufont[]       = "Source Code Pro for Powerline-11";
static const char normbordercolor[] = "#444444";
static const char normbgcolor[]     = "#222222";
static const char normfgcolor[]     = "#bbbbbb";
static const char selbordercolor[]  = "#005577";
static const char selbgcolor[]      = "#005577";
static const char selfgcolor[]      = "#eeeeee";
static const char floatnormbordercolor[] = "#005577";
static const char floatselbordercolor[]  = "#005577";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 5;       /* snap pixel */
static const unsigned int minwsz    = 20;       /* Minimal heigt of a client for smfact */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

#define NUMCOLORS         6
static const char colors[NUMCOLORS][MAXCOLORS][8] = {
  // border   foreground  background
  { "#817cde", "#657b83", "#1b1b1b" },  // normal
  { "#00ccff", "#eee8d5", "#7f62b3" },  // selected
  { "#dc322f", "#002b36", "#b58900" },  // urgent
  { "#073642", "#839496", "#073642" },  // lightgrey on brightblack
  { "#073642", "#073642", "#002b36" },  // brightblack on black
  { "#073642", "#002b36", "#073642" },  // black on brightblack
  // add more here
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance    title       tags mask iscentered isfloating isterminal noswallow   monitor */
	{ "Gimp",       NULL,       NULL,       0,        1,         1,         0,         1,        -1 },
	{ "Pidgin",     NULL,       NULL,       1 << 6,   0,         0,         0,         0,        -1 },
	{ "Skype",      NULL,       NULL,       1 << 6,   0,         0,         0,         0,         1 },
	{ "Thunderbird",NULL,       NULL,       1 << 5,   0,         0,         0,         0,        -1 },
	{ "Firefox",    NULL,       NULL,       1 << 1,   0,         0,         0,         1,        -1 },
	{ "mpv",        NULL,       NULL,       0,        1,         1,         0,         1,        -1 },
	{ "VirtualBox", NULL,       NULL,       0,        0,         1,         0,         0,        -1 },
	{ "feh",        NULL,       NULL,       0,        1,         1,         0,         1,        -1 },
	{ "imageviewer",NULL,       NULL,       0,        1,         1,         0,         1,         1 },
	{ "qBittorrent",NULL,       NULL,       1,        0,         0,         0,         0,         0 },
	{ "URxvt",     "urxvt",     NULL,       0,        0,         0,         1,         1,         0 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const float smfact    = 0.55; /* factor of tiled clients [0.00..0.95] */
// static const int nmaster      = 1;    #<{(| number of clients in master area |)}>#
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "###",      gaplessgrid},
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPER  Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ SUPER,                        KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ SUPER|ShiftMask,              KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ SUPER,                        XK_p,      spawn,          {.v = dmenucmd } },
	// { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ SUPER,                        XK_b,      togglebar,      {0} },
	{ SUPER,                        XK_j,      focusstack,     {.i = +1 } },
	{ SUPER,                        XK_k,      focusstack,     {.i = -1 } },
	{ SUPER,                        XK_i,      incnmaster,     {.i = +1 } },
	{ SUPER,                        XK_d,      incnmaster,     {.i = -1 } },
	{ SUPER,                        XK_h,      setmfact,       {.f = -0.02} },
	{ SUPER,                        XK_l,      setmfact,       {.f = +0.02} },
	{ SUPER|ShiftMask,              XK_h,      setsmfact,      {.f = +0.02} },
	{ SUPER|ShiftMask,              XK_l,      setsmfact,      {.f = -0.02} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ SUPER|ShiftMask,              XK_w,      killclient,     {0} },
	{ SUPER,                        XK_t,      setlayout,      {.v = &layouts[0]} },
	{ SUPER,                        XK_f,      setlayout,      {.v = &layouts[1]} },
	{ SUPER,                        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ SUPER,                        XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ SUPER|ShiftMask,              XK_space,  togglefloating, {0} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ SUPER,                        XK_comma,  focusmon,       {.i = -1 } },
	{ SUPER,                        XK_period, focusmon,       {.i = +1 } },
	{ SUPER|ShiftMask,              XK_comma,  tagmon,         {.i = -1 } },
	{ SUPER|ShiftMask,              XK_period, tagmon,         {.i = +1 } },
	{ SUPER|ControlMask|ShiftMask,  XK_h,      togglehorizontalmax, {0} },
	{ SUPER|ControlMask|ShiftMask,  XK_l,      togglehorizontalmax, {0} },
	{ SUPER|ControlMask|ShiftMask,  XK_j,      toggleverticalmax,   {0} },
	{ SUPER|ControlMask|ShiftMask,  XK_k,      toggleverticalmax,   {0} },
	{ SUPER|ShiftMask,              XK_f,      togglemaximize,      {0} },
	{ SUPER|ShiftMask,              XK_t,      togglefloatborders,  {0} },
	{ SUPER|ShiftMask,              XK_s,      togglesticky,        {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         SUPER,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,          Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

