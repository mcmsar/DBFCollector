//=============================================================================
// Tools.c
//=============================================================================
//
//  Written by Barry W. Hill
//
//=============================================================================

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "CioColor.h"
#include "Tools.h"
#pragma warning(disable : 4996)


extern U32 i, j;
//extern U16 saved_x, saved_y;
//extern char kbchar, datebuf[16], timebuf[16];



//=============================================================================
// Barry's Windows Programming Tools
//==============================================================================
void CursorVisible(BOOL CVState)
{
  HANDLE MainConsole;
  CONSOLE_CURSOR_INFO CursorInfo;

  // Get a HANDLE to the Console Window
  MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  
  // Get the Info
  GetConsoleCursorInfo(MainConsole, &CursorInfo);
  // CursorInfo.dwSize = ;  //Not Changing This Info 
  CursorInfo.bVisible = 0; 
  
  // Set the Info
  SetConsoleCursorInfo(MainConsole, &CursorInfo);
}


//==============================================================================
void PositionCursor(U16 X, U16 Y)
{
  HANDLE MainConsole;
  COORD Position = {0,0};

  // Set X as the X-COORD
  Position.X = X;

  // Set Y as the Y-COORD
  Position.Y = Y;

  // Get a HANDLE to the Console Window
  MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Now Put The Cursor there
  SetConsoleCursorPosition(MainConsole, Position);
}


//==============================================================================
void ClrScr(void)
{
  HANDLE MainConsole;
  COORD coordScreen = {0,0};
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;

  // Get a HANDLE to the Console Window
  MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Get Console Information
  GetConsoleScreenBufferInfo(MainConsole, &csbi );

  // Figure Console Size
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // Fill Console with spaces
  FillConsoleOutputCharacter(MainConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );

  // Get Console Information
  GetConsoleScreenBufferInfo(MainConsole, &csbi );

  // Fill Console with Current Attributes
  FillConsoleOutputAttribute(MainConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );

  // Send the Cursor Home
  SetConsoleCursorPosition(MainConsole, coordScreen );
  return;
}


//==============================================================================
void kbflush(void)
{
  while(kbhit())  // If there is a key in the buffer
  {
    getch();      // Get IT
  }
}


//==============================================================================
char wait_for_key(void)
{
  kbflush();                     // Empty KB Buffer
  do{}while( !kbhit() );         // Wait for a Key Press
  return(toupper( getch() ));    // Return the toupper of the key
}


//==============================================================================
char prompt_for_key(char *message)
{
  printf("%s", message);        // Display the Message
  kbflush();                     // Empty KB Buffer
  do{Sleep(10);}while( !kbhit() );         // Wait for a Key Press
  return(toupper( getch() ));    // Return the toupper of the key
}


//==============================================================================
char anykey(void)
{
  printf("\n  Press AnyKey to Continue...."); // Prompt for AnyKey
  kbflush();                                    // Empty KB Buffer
  do{Sleep(10);}while( !kbhit() );         // Wait for a Key Press
  return(toupper( getch() ));    // Return the toupper of the key
}


//==============================================================================
void print_time(void)
{
//  _strdate(datebuf);                                // Get Current Date
//  _strtime(timebuf);                                // Get Current Time
//  printf("Date: %s  Time: %s", datebuf, timebuf ); // Display them
}


//==============================================================================
void save_cursor(void)
{
  HANDLE MainConsole;
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  // Get a HANDLE to the Console Window
  MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  // Get Console Information
  GetConsoleScreenBufferInfo(MainConsole, &csbi );

  // Figure Console Size
//  saved_x = csbi.dwCursorPosition.X;
//  saved_y = csbi.dwCursorPosition.Y;

  return;
}


//==============================================================================
void restore_cursor(void)
{
//  PositionCursor(saved_x, saved_y);
}


//==============================================================================
BOOL VersionDetect(void)
{

   OSVERSIONINFOEX osvi;
   BOOL bOsVersionInfoEx;

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   if( !(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)) )
   {
      // If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.

      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      if (! GetVersionEx ( (OSVERSIONINFO *) &osvi) ) 
         return FALSE;
   }

   switch (osvi.dwPlatformId)
   {
      case VER_PLATFORM_WIN32_NT:

      // Test for the product.

         if ( osvi.dwMajorVersion <= 4 )
           printf( "Microsoft Windows NT ");
         if ( osvi.dwMajorVersion == 5 )
            printf ("Microsoft Windows 2000 ");

      // Display version, service pack (if any), and build number.

         printf ("version %d.%d %s (Build %d)\n",
            osvi.dwMajorVersion,
            osvi.dwMinorVersion,
            osvi.szCSDVersion,
            osvi.dwBuildNumber & 0xFFFF);

         break;

      case VER_PLATFORM_WIN32_WINDOWS:

         if ((osvi.dwMajorVersion > 4) || 
            ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion > 0)))
         {
             printf ("Microsoft Windows 98 ");
         } 
         else printf ("Microsoft Windows 95 ");

         break;

      case VER_PLATFORM_WIN32s:

         printf ("Microsoft Win32s ");
         break;
   }
   return TRUE; 
}


//==============================================================================
void SetColors(U16 ConsoleColor)
{
  HANDLE MainConsole;

  OSVERSIONINFOEX osvi;
  BOOL bOsVersionInfoEx;

  ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
  osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

  if(!(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)))
  {
    osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    GetVersionEx ( (OSVERSIONINFO *) &osvi);
  }

  if(osvi.dwPlatformId != VER_PLATFORM_WIN32_NT)
  {          
    // Get a HANDLE to the Console Window
    MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(MainConsole, ConsoleColor);
  }
}


//==============================================================================
char dsp_time_scan_for_key(void)
{
  save_cursor();
  do
  {
    print_time();
    restore_cursor();
  }while (!kbhit());
  return(toupper( getch() ));    // Return the toupper of the key
}


//==============================================================================
void print_passed(void)
{
  SetColors(Color_Passed);
  printf("Passed");
  SetColors(Color_Normal);
}


//==============================================================================
void print_failed(void)
{
  SetColors(Color_Failed);
  printf("Failed");
  SetColors(Color_Normal);
}


//==============================================================================
void Busy_Signal(int speed)
{
  U16 BS_x, BS_y;
  U32 BSLoop;
  HANDLE MainConsole;
  CONSOLE_SCREEN_BUFFER_INFO csbi;

  // Get a HANDLE to the Console Window
  MainConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  // Get Console Information
  GetConsoleScreenBufferInfo(MainConsole, &csbi );
  // Save Cursor Position
  BS_x = csbi.dwCursorPosition.X;
  BS_y = csbi.dwCursorPosition.Y;
  
  for(BSLoop = speed;BSLoop>0x0000;BSLoop--)
  {
    PositionCursor(70, 2);
    SetColors(BSColor0);
    printf("*\b");
    Sleep(2);

    PositionCursor(70, 2);
    SetColors(BSColor1);
    printf("|");
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor2);
    printf("/"); 
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor3);
    printf("-");  
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor4);
    printf("\\");  
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor5);
    printf("|");  
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor6);
    printf("/");  
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor7);
    printf("-");  
    Sleep(2);
  
    PositionCursor(70, 2);
    SetColors(BSColor8);
    printf("\\");  
    Sleep(2);
  
  }

  PositionCursor(70, 2);
  printf(" ");
  SetColors(Color_Normal);
  PositionCursor(BS_x, BS_y);

}



//==============================================================================
void ShowAPIError(U32 APIReturnCode)
{
  ClrScr();
  printf("\n  An Error has Occured in the API for the Device Driver.");
  printf("\n  Below is all the information that was available about ");
  printf("\n  the encountered Error.                             \n ");

  switch (APIReturnCode)
  {
    case ApiConfigAccessFailed:
      printf("\n  Return Code  %d  = ApiConfigAccessFailed\n", APIReturnCode);
      break;
    case ApiDmaChannelInvalid:
      printf("\n  Return Code  %d  = ApiDmaChannelInvalid\n", APIReturnCode);
      break;
    case ApiDmaChannelUnavailable:
      printf("\n  Return Code  %d  = ApiDmaChannelUnavailable\n", APIReturnCode);
      break;
    case ApiDmaCommandInvalid:
      printf("\n  Return Code  %d  = ApiDmaCommandInvalid\n", APIReturnCode);
      break;
    case ApiDmaDone:
      printf("\n  Return Code  %d  = ApiDmaDone\n", APIReturnCode);
      break;
    case ApiDmaInProgress:
      printf("\n  Return Code  %d  = ApiDmaInProgress\n", APIReturnCode);
      break;
    case ApiDmaInvalidChannelPriority:
      printf("\n  Return Code  %d  = ApiDmaInvalidChannelPriority\n", APIReturnCode);
      break;
    case ApiDmaPaused:
      printf("\n  Return Code  %d  = ApiDmaPaused\n", APIReturnCode);
      break;
    case ApiFailed:
      printf("\n  Return Code  %d  = ApiFailed\n", APIReturnCode);
      break;
    case ApiInsufficientResources:
      printf("\n  Return Code  %d  = ApiInsufficientResources\n", APIReturnCode);
      break;
    case ApiInvalidAccessType:
      printf("\n  Return Code  %d  = ApiInvalidAccessType\n", APIReturnCode);
      break;
    case ApiInvalidAddress:
      printf("\n  Return Code  %d  = ApiInvalidAddress\n", APIReturnCode);
      break;
    case ApiInvalidDeviceInfo:
      printf("\n  Return Code  %d  = ApiInvalidDeviceInfo\n", APIReturnCode);
      break;
    case ApiInvalidHandle:
      printf("\n  Return Code  %d  = ApiInvalidHandle\n", APIReturnCode);
      break;
    case ApiInvalidPowerState:
      printf("\n  Return Code  %d  = ApiInvalidPowerState\n", APIReturnCode);
      break;
    case ApiInvalidSize:
      printf("\n  Return Code  %d  = ApiInvalidSize\n", APIReturnCode);
      break;
    case ApiNoActiveDriver:
      printf("\n  Return Code  %d  = ApiNoActiveDriver\n", APIReturnCode);
      break;
    case ApiNullParam:
      printf("\n  Return Code  %d  = ApiNullParam\n", APIReturnCode);
      break;
    case ApiPowerDown:
      printf("\n  Return Code  %d  = ApiPowerDown\n", APIReturnCode);
      break;
	case ApiInvalidBoardNumber:
      printf("\n  Return Code  %d  = ApiInvalidBoardNumber\n", APIReturnCode);
      break;
	case ApiInvalidDMANumWords:
      printf("\n  Return Code  %d  = ApiInvalidDMANumWords\n", APIReturnCode);
      break;
    case ApiUnsupportedFunction:
      printf("\n  Return Code  %d  = ApiUnsupportedFunction\n", APIReturnCode);
      break;
    case ApiInvalidDriverVersion:
      printf("\n  Return Code  %d  = ApiInvalidDriverVersion\n", APIReturnCode);
      break;
    case ApiInvalidOffset:
      printf("\n  Return Code  %d  = ApiInvalidOffset\n", APIReturnCode);
      break;
    case ApiInvalidData:
      printf("\n  Return Code  %d  = ApiInvalidData\n", APIReturnCode);
      break;
    case ApiInvalidIndex:
      printf("\n  Return Code  %d  = ApiInvalidIndex\n", APIReturnCode);
      break;
    case ApiInvalidIopSpace:
      printf("\n  Return Code  %d  = ApiInvalidIopSpace\n", APIReturnCode);
      break;
    case ApiInvalidPciSpace:
      printf("\n  Return Code  %d  = ApiInvalidPciSpace\n", APIReturnCode);
      break;
    case ApiInvalidBusIndex:
      printf("\n  Return Code  %d  = ApiInvalidBusIndex\n", APIReturnCode);
      break;
    case ApiWaitTimeout:
      printf("\n  Return Code  %d  = ApiWaitTimeout\n", APIReturnCode);
      break;
    case ApiWaitCanceled:
      printf("\n  Return Code  %d  = ApiWaitCanceled\n", APIReturnCode);
      break;
    case ApiDmaSglPagesGetError:
      printf("\n  Return Code  %d  = ApiDmaSglPagesGetError\n", APIReturnCode);
      break;
    case ApiDmaSglPagesLockError:
      printf("\n  Return Code  %d  = ApiDmaSglPagesLockError\n", APIReturnCode);
      break;
    case ApiMuFifoEmpty:
      printf("\n  Return Code  %d  = ApiMuFifoEmpty\n", APIReturnCode);
      break;
    case ApiMuFifoFull:
      printf("\n  Return Code  %d  = ApiMuFifoFull\n", APIReturnCode);
      break;
    case ApiHSNotSupported:
      printf("\n  Return Code  %d  = ApiHSNotSupported\n", APIReturnCode);
      break;
    case ApiVPDNotSupported:
      printf("\n  Return Code  %d  = ApiVPDNotSupported\n", APIReturnCode);
      break;
    case ApiDeviceInUse:
      printf("\n  Return Code  %d  = ApiDeviceInUse\n", APIReturnCode);
      break;
    case ApiDmaNotReady:
      printf("\n  Return Code  %d  = ApiDmaNotReady\n", APIReturnCode);
      break;
    default:
      printf("\n  Return Code  %d  Is not Listed as a valid return code. \n", APIReturnCode);
      break;
  }
  anykey();
}














