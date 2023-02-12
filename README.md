# Xource

Xource is an open-source reimplementation of Valve's Source engine.

This project does **NOT** support Valve's SDK. (sorry modders)

# Tasks

At least make it as Quake engine ;)

- [x] CVar

- [ ] Console

- [ ] Filesystem (partially)

- [ ] BSP (partially)

- [ ] GL Renderer

- [ ] Software Renderer

- [ ] Sound

- [ ] Shader and material system

- [ ] Scripts

- [ ] Map compilers

# Source history

```pikchr
# Variables
linewid = 4px # left/right
lineht  = 5mm # up/down
ovalwid = 3.5cm
ovalht  = 7mm

# History
Legacy: [
  Q: [
    text "Quake 1" "(1996)"
    arrow
    text "GoldSrc" "(1998)"
  ]
  down
  oval wid Q.wid+5mm ht Q.ht+2mm at Q
  arrow

  # Source engine itself
  oval "SE 1999-2003"
  move to last.s
  oval "Source 2004"
  arrow
  oval "Source 2006 (ep1)"
  arrow

  # Branching
  S2007ob: oval "SE 2007 (Orange Box)"

  arrow from S2007ob.w left 1cm <->
  oval "Source 2008-9 (l4d)"
  arrow down from last.s
  S2009: oval "Source 2009 (ep3)"
  right
  move 5mm
  S2007mp: oval "Source 2007 (MP)"
  move same
  S2007: oval "Source 2007"
  arrow from S2007ob.s to S2007mp.n
  arrow from S2007ob.e to S2007.n
  arrow from S2007ob.w to S2009.ne
  down

  arrow from S2007.s down
  arrow from S2007mp.s down

  arrow dashed from S2009.s down 2mm \
    then to S2007mp.sw-(0,6mm)
  arrow dashed from S2009.s down 2mm \
    then right until even with S2007
]
box dashed behind Legacy color red fill yellow \
  at Legacy wid Legacy.wid+2mm ht Legacy.ht
down
text "Legacy" with .nw at Legacy.nw
move to Legacy.s

# Modern
S2010: oval "Source 2010 (aswarm)"
arrow
oval "Source 2011 (Portal 2)"
arrow
oval "Source 2012 (CS:GO)"

# Working crutch
move to Legacy.s
move right ovalwid + 5mm
down
S2013: oval "Source 2013"

arrow from S2013.s left 1cm down 5mm
text "MultiPlayer"

arrow from S2013.s right 1cm down 5mm
text "SinglePlayer"
```

