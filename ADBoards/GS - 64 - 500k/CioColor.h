#ifndef  cio_colors                              /* IF CIO COLORS NOT DEFINED */

  #define  TEXT_BLACK            0x00
  #define  TEXT_BLUE             0x01
  #define  TEXT_GREEN            0x02
  #define  TEXT_CYAN             0x03
  #define  TEXT_RED              0x04
  #define  TEXT_MAGENTA          0x05
  #define  TEXT_BROWN            0x06
  #define  TEXT_LIGHTGRAY        0x07
  #define  TEXT_DARKGRAY         0x08
  #define  TEXT_LIGHTBLUE        0x09
  #define  TEXT_LIGHTGREEN       0x0A
  #define  TEXT_LIGHTCYAN        0x0B
  #define  TEXT_LIGHTRED         0x0C
  #define  TEXT_LIGHTMAGENTA     0x0D
  #define  TEXT_YELLOW           0x0E
  #define  TEXT_WHITE            0x0F
  #define  BCKGND_BLACK          0x00
  #define  BCKGND_BLUE           0x10
  #define  BCKGND_GREEN          0x20
  #define  BCKGND_CYAN           0x30
  #define  BCKGND_RED            0x40
  #define  BCKGND_MAGENTA        0x50
  #define  BCKGND_BROWN          0x60
  #define  BCKGND_LIGHTGRAY      0x70
  #define  BCKGND_DARKGRAY       0x80
  #define  BCKGND_LIGHTBLUE      0x90
  #define  BCKGND_LIGHTGREEN     0xA0
  #define  BCKGND_LIGHTCYAN      0xB0
  #define  BCKGND_LIGHTRED       0xC0
  #define  BCKGND_LIGHTMAGENTA   0xD0
  #define  BCKGND_YELLOW         0xE0
  #define  BCKGND_WHITE          0xF0

  #define  Color_Normal          0x07  /* TEXT_LIGHTGRAY  BCKGND_BLACK        */
  #define  Color_Menu_UnSelected 0x07  /* TEXT_LIGHTGRAY  BCKGND_BLACK        */
  #define  Color_Menu_Selected   0x0F  /* TEXT_WHITE      BCKGND_BLACK        */
  #define  Color_Title           0x0F  /* TEXT_WHITE      BCKGND_BLACK        */
  #define  Color_Header          0x0F  /* TEXT_WHITE      BCKGND_BLACK        */
  #define  Color_Passed          0x0F  /* TEXT_WHITE      BCKGND_BLACK        */
  #define  Color_Warning         0x0E  /* TEXT_YELLOW     BCKGND_BLACK        */
  #define  Color_Failed          0x04  /* TEXT_RED        BCKGND_BLACK        */

  #define  BSColor0              0x03  /* Busy Signal Color                   */
  #define  BSColor1              0x04  /* Busy Signal Color                   */
  #define  BSColor2              0x05  /* Busy Signal Color                   */
  #define  BSColor3              0x07  /* Busy Signal Color                   */
  #define  BSColor4              0x09  /* Busy Signal Color                   */
  #define  BSColor5              0x0A  /* Busy Signal Color                   */
  #define  BSColor6              0x0B  /* Busy Signal Color                   */
  #define  BSColor7              0x0C  /* Busy Signal Color                   */
  #define  BSColor8              0x0D  /* Busy Signal Color                   */
  #define  BSColor9              0x0E  /* Busy Signal Color                   */

  #define  cio_colors         Defined  /* SHOW CIO COLORS DEFINED             */

#endif                                 /* END IF NOT DEFINED                  */
