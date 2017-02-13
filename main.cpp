#define _WIN32_IE 0X301
#define _WIN32_WINNT 0X0500
#include "resource.h"
#include <windows.h>
#include<commctrl.h>
#include<sstream>
#include<math.h>
#include<fstream>

#define CLOCK 3
#define HOURHAND 2
#define MINHAND 1
#define SECHAND 0
#define p2i (6.2851)

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "WindowsApp";
POINT ptHour[4]={-10,0,0,-60,10,0,0,15};
POINT ptMin[4]={-10,0,0,-100,10,0,0,15};
POINT ptSec[2]={0,0,0,-90};
POINT ptClock[1]={0,-100};
POINT ptTempSec[2],ptTempMin[4],ptTempHour[4],ptTempClock[1];

int xCentre,yCentre;
int AlarmHour,AlarmMinute;

HINSTANCE hinstance;

void CreateChildAlarm(int x, int y)
{
HWND hwndChild;    
    hwndChild = CreateWindowEx (
              WS_EX_TOPMOST,                   /* Extended possibilites for variation */
           "AlarmClass",         /* Classname */
           "Alarm",       /* Title Text */
           WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_BORDER, /* default window */
           x,       /* Windows decides the position */
           y,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           200,                 /* and height in pixels */
           NULL,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hinstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           ); 
           
    ShowWindow(hwndChild,SW_SHOW);
}



int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
    INITCOMMONCONTROLSEX icc;
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
hinstance=hThisInstance;
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_ICON));
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_ICON));
    wincl.hCursor = LoadCursor (hinstance, MAKEINTRESOURCE(IDC_CURSOR));
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(1,1,255));//GetStockObject(BLACK_BRUSH);
 
 icc.dwSize=sizeof(icc);
 icc.dwICC=ICC_WIN95_CLASSES;
 InitCommonControlsEx(&icc);
             
             
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;
    
        /*window for alarm*/
        wincl.hInstance = hinstance;
        wincl.lpszClassName = "AlarmClass";
        wincl.lpfnWndProc = ChildProcedure;      /* This function is called by windows */
        wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
        wincl.cbSize = sizeof (WNDCLASSEX);
                        
        /* Use default icon and mouse-pointer */
        wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName =NULL;                 /* No menu */
        wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
        wincl.cbWndExtra = 0;                      /* structure or the window instance */
        /* Use Windows's default color as the background of the window */
       wincl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
       RegisterClassEx (&wincl);

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           WS_EX_TOPMOST|WS_EX_TOOLWINDOW|WS_EX_LAYERED,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Analog Clock",       /* Title Text */
           WS_POPUP|WS_CLIPCHILDREN, /* default window */
           1110,       /* Windows decides the position */
           440,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           280,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
           

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
     UpdateWindow(hwnd);
    SetLayeredWindowAttributes(hwnd,RGB(1,1,255),150,1);
    /* Run the message loop. It will run until GetMessage() returns 0 */
           
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

void Rotate(int Hand,int Angle)
{int i;
switch(Hand)
{case SECHAND:
  ptTempSec[1].x=(int)(ptSec[1].x*cos(Angle*p2i/360) + ptSec[1].y*sin(Angle*p2i/360));
  ptTempSec[1].y=(int)(ptSec[1].y*cos(Angle*p2i/360) - ptSec[1].x*sin(Angle*p2i/360));
  ptTempSec[1].x+=xCentre;
  ptTempSec[1].y+=yCentre;
  break;
 case MINHAND:
      for(i=0;i<4;i++)
      {ptTempMin[i].x=(int)(ptMin[i].x*cos(Angle*p2i/360) + ptMin[i].y*sin(Angle*p2i/360));
      ptTempMin[i].y=(int)(ptMin[i].y*cos(Angle*p2i/360) - ptMin[i].x*sin(Angle*p2i/360));
      ptTempMin[i].x+=xCentre;
      ptTempMin[i].y+=yCentre;
      }
      break;
 case HOURHAND:
      for(i=0;i<4;i++)
      {ptTempHour[i].x=(int)(ptHour[i].x*cos(Angle*p2i/360) + ptHour[i].y*sin(Angle*p2i/360));
      ptTempHour[i].y=(int)(ptHour[i].y*cos(Angle*p2i/360) - ptHour[i].x*sin(Angle*p2i/360));
      ptTempHour[i].x+=xCentre;
      ptTempHour[i].y+=yCentre;
      }
      break;
 case CLOCK:
    ptTempClock[0].x=(int)(ptClock[0].x*cos(Angle*p2i/360) + ptClock[0].y*sin(Angle*p2i/360));  
    ptTempClock[0].y=(int)(ptClock[0].y*cos(Angle*p2i/360) - ptClock[0].x*sin(Angle*p2i/360));  
    ptTempClock[0].x+=xCentre;
    ptTempClock[0].y+=yCentre;
    break;
}
}

void DrawClock(HDC hdc)
{int i,Radius;
HBRUSH hBrush;
HFONT hfont;
LOGFONT f={0};
char clk[2];
hBrush=CreateSolidBrush(RGB(100,50,255));
SelectObject(hdc,hBrush);
SelectObject(hdc,GetStockObject(NULL_PEN));
   for(i=0;i<60;i++)
   {
    if(i%5==0)Radius=0;
    else Radius=3;
    Rotate(CLOCK,i*6);
    Ellipse(hdc,ptTempClock[0].x-Radius,ptTempClock[0].y-Radius,ptTempClock[0].x+Radius,ptTempClock[0].y+Radius);
  }
  DeleteObject(hBrush);
 strcpy(f.lfFaceName,"Arial Black");
 f.lfHeight=18;
 f.lfPitchAndFamily=FIXED_PITCH;
 hfont=CreateFontIndirect(&f);
 SetTextColor(hdc,RGB(100,50,255));
 SetBkMode(hdc,TRANSPARENT);
 SelectObject(hdc,hfont);
  Radius=7;
  for(i=1;i<13;i++)
  {Rotate(CLOCK,-i*30);
  sprintf(clk,"%d",i);
  if(i<10)
  TextOut(hdc,ptTempClock[0].x-Radius,ptTempClock[0].y-Radius,&clk[0],1);
  else TextOut(hdc,ptTempClock[0].x-Radius,ptTempClock[0].y-Radius,&clk[0],2);
  }
  DeleteObject(hfont);
}

void DrawHands(HDC hdc)
{HBRUSH hBrush;
HPEN hPen;
hBrush=CreateSolidBrush(RGB(100,100,100));
SelectObject(hdc,hBrush);
SelectObject(hdc,GetStockObject(NULL_PEN));
Polygon(hdc,ptTempHour,4);
DeleteObject(hBrush);
hBrush=CreateSolidBrush(RGB(150,150,200));
SelectObject(hdc,hBrush);
SelectObject(hdc,GetStockObject(NULL_PEN));
Polygon(hdc,ptTempMin,4);
DeleteObject(hBrush);
hBrush=CreateSolidBrush(RGB(0,0,255));
SelectObject(hdc,hBrush);
SelectObject(hdc,GetStockObject(NULL_PEN));
Ellipse(hdc,xCentre-5,yCentre-5,xCentre+5,yCentre+5);
DeleteObject(hBrush);
hPen=CreatePen(PS_SOLID,2,RGB(0,0,255));
SelectObject(hdc,hPen);
MoveToEx(hdc,xCentre,yCentre,NULL);
LineTo(hdc,ptTempSec[1].x,ptTempSec[1].y);
DeleteObject(hPen);
}

void PrintTime(HDC hdc,SYSTEMTIME st)
{HFONT hfont;
LOGFONT f={0};
char time[10];
     strcpy(f.lfFaceName,"Blackout 2 AM");
             f.lfHeight=17;
             f.lfPitchAndFamily=FIXED_PITCH;
             hfont=CreateFontIndirect(&f);
             SetTextColor(hdc,RGB(255,0,0));
             SetBkMode(hdc,TRANSPARENT);
             SelectObject(hdc,hfont);
             sprintf(time,"%d%d:%d%d:%d%d",st.wHour/10,st.wHour%10,st.wMinute/10,st.wMinute%10,st.wSecond/10,st.wSecond%10);
             TextOut(hdc,xCentre-25,yCentre+40,&time[0],8);
             DeleteObject(hfont);
             strcpy(f.lfFaceName,"Times New Roman");
             f.lfHeight=17;
             hfont=CreateFontIndirect(&f);
             SelectObject(hdc,hfont);
             switch(st.wDayOfWeek)
             {case 0:
             TextOut(hdc,xCentre-25,yCentre-60,"Sunday",6);
             break;
             case 1:
             TextOut(hdc,xCentre-25,yCentre-60,"Monday",6);
             break;
             case 2:
             TextOut(hdc,xCentre-25,yCentre-60,"Tuesday",7);
             break;
             case 3:
             TextOut(hdc,xCentre-25,yCentre-60,"Wednesday",9);
             break;
             case 4:
             TextOut(hdc,xCentre-25,yCentre-60,"Thursday",8);
             break;
             case 5:
             TextOut(hdc,xCentre-25,yCentre-60,"Friday",6);
             break;
             case 6:
             TextOut(hdc,xCentre-25,yCentre-60,"Saturday",8);
             break;
             }
             sprintf(time,"%d%d-%d%d-%d",st.wDay/10,st.wDay%10,st.wMonth/10,st.wMonth%10,st.wYear);
             TextOut(hdc,xCentre-30,yCentre-40,&time[0],10);
             DeleteObject(hfont);
}

void VoicePlayBack(SYSTEMTIME st)
{int i,s;
//sndPlaySound("SoundFiles//TheTimeIs.wav",SND_SYNC);
PlaySound(MAKEINTRESOURCE(IDW_WAVE_TTI),hinstance,SND_RESOURCE|SND_SYNC);

     switch(st.wHour)
     {case 0:
     case 12:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_12),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 1:
     case 13:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_1),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 2:
     case 14:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_2),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 3:
     case 15:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_3),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 4:
     case 16:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_4),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 5:
     case 17:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_5),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 6:
     case 18:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_6),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 7:
     case 19:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_7),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 8:
     case 20:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_8),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 9:
     case 21:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_9),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 10:
     case 22:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_10),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 11:
     case 23:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_11),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     }
for(i=0;i<2;i++)
{if(i==0 && st.wMinute>19)s=(st.wMinute/10)*10;
else if(st.wMinute>19) s=st.wMinute%10;
     else {s=st.wMinute;i=1;}
      switch(s)
     {
     case 1:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_1),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 2:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_2),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 3:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_3),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 4:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_4),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 5:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_5),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 6:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_6),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 7:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_7),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 8:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_8),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 9:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_9),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 10:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_10),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 11:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_11),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 12:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_12),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 13:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_13),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 14:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_14),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 15:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_15),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 16:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_16),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 17:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_17),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 18:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_18),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 19:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_19),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 20:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_20),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 30:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_30),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 40:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_40),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     case 50:
     PlaySound(MAKEINTRESOURCE(IDW_WAVE_50),hinstance,SND_RESOURCE|SND_SYNC);
     break;
     }
}
     Sleep(10);
     if(st.wHour<12)PlaySound(MAKEINTRESOURCE(IDW_WAVE_AM),hinstance,SND_RESOURCE|SND_SYNC);
     else PlaySound(MAKEINTRESOURCE(IDW_WAVE_PM),hinstance,SND_RESOURCE|SND_SYNC);
}
/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static SYSTEMTIME st;
static HWND hwndAlarmButton;
HDC hdc;
static RECT rc;
HFONT hfont;
LOGFONT f={0};
static BOOL BeepFlag;
ifstream fin;
static BOOL hold;
static int xDiff,yDiff;
static POINT pt;
                
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
             hwndAlarmButton= CreateWindow (TEXT("button"),"Alarm",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,100,205,50,20,hwnd,(HMENU)1,((LPCREATESTRUCT)lParam)->hInstance,NULL);
             GetClientRect(hwnd,&rc);
             xCentre=(rc.right-rc.left)/2;
             yCentre=(rc.bottom-rc.top)/2;
             SetTimer(hwnd,1,1000,NULL);
             BeepFlag=~BeepFlag;
             fin.open("AlarmValue.bin");
             fin>>AlarmHour;
             fin>>AlarmMinute;
             fin.close();
             //SendMessage(hwndCheck,BM_SETCHECK,1,0);
             //sndPlaySound("SoundFiles//TheClockIsSynchronised.wav",SND_ASYNC);
             break;
       case WM_COMMAND:
             switch(LOWORD(wParam))
             {case 1:
             GetClientRect(hwnd,&rc);
             pt.x=rc.left; pt.y=rc.top;
             ClientToScreen(hwnd,&pt);
             CreateChildAlarm(pt.x-100,pt.y);
             }
             break;
       case WM_LBUTTONDBLCLK:
            VoicePlayBack(st);
            break;
        /*case WM_CTLCOLORBTN:
             //Beep(1000,500);
             //SelectObject((HDC)wParam,GetStockObject(BLACK_BRUSH));
             
             //DeleteObject((HBRUSH)SetClassLong((HWND)lParam,GCL_HBRBACKGROUND,(LONG)GetStockObject(BLACK_BRUSH)));
             SetBkColor((HDC)wParam,TRANSPARENT);
             SetTextColor((HDC)wParam,RGB(255,255,255));
             return (LRESULT)GetStockObject(BLACK_BRUSH+1);
             break;*/
        case WM_SIZE:
             GetClientRect(hwnd,&rc);
             xCentre=(rc.right-rc.left)/2;
             yCentre=(rc.bottom-rc.top)/2;
             break;
       case WM_TIMER:
             if(BeepFlag)PlaySound(MAKEINTRESOURCE(IDW_WAVE_TICK),hinstance,SND_RESOURCE|SND_NOSTOP|SND_ASYNC);
             InvalidateRect(hwnd,NULL,TRUE);
             break;
       case WM_CHAR:
            if(wParam==32 || wParam==13)
            BeepFlag=~BeepFlag;
            break;
        case WM_LBUTTONDOWN:
    		SetCapture(hwnd);
			xDiff=LOWORD(lParam);
			yDiff=HIWORD(lParam);
			hold=1;
			break;
		case WM_LBUTTONUP:
			hold=0;
			break;
		case WM_MOUSEMOVE:
			pt.x=LOWORD(lParam);
			pt.y=HIWORD(lParam);
			ClientToScreen(hwnd,&pt);
			if(hold)
			MoveWindow(hwnd,pt.x-xDiff,pt.y-yDiff,250,280,FALSE);
			ReleaseCapture();
			break;
        case WM_PAINT:
             DefWindowProc (hwnd, message, wParam, lParam);
             hdc=GetDC(hwnd);
             GetLocalTime(&st);
             Rotate(SECHAND,-st.wSecond*6);
             Rotate(MINHAND,-st.wMinute*6);
             Rotate(HOURHAND,-(st.wHour*30+(180*st.wMinute)/360));
             DrawClock(hdc);
             DrawHands(hdc);
        strcpy(f.lfFaceName,"Monotype Corsiva");
        f.lfHeight=28;
        f.lfPitchAndFamily=FIXED_PITCH;
        hfont=CreateFontIndirect(&f);
        SetBkMode(hdc,TRANSPARENT);
        SetTextColor(hdc,RGB(200,100,0));
        SelectObject(hdc,hfont);
             TextOut(hdc,xCentre-30,yCentre+10,"Saifee",6);
             DeleteObject(hfont);
             PrintTime(hdc,st);
             ReleaseDC(hwnd,hdc);
             if(st.wMinute==0 && st.wSecond==0)
             PlaySound(MAKEINTRESOURCE(IDW_WAVE_PERHOUR),hinstance,SND_RESOURCE|SND_SYNC);
             if(st.wHour==AlarmHour && st.wMinute==AlarmMinute && st.wSecond==0)
             PlaySound(MAKEINTRESOURCE(IDW_WAVE_ALARM),hinstance,SND_RESOURCE|SND_ASYNC);
             
             break;
        case WM_DESTROY:
            KillTimer(hwnd,1);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void FillListBox(HWND hwndListBox[])
{
 int i;
 char value[3];
 for(i=0;i<24;i++)
 {sprintf(value,"%d",i);
 SendMessage(hwndListBox[0],LB_INSERTSTRING,i,(LPARAM)value);
 }
 for(i=0;i<60;i++)
 {sprintf(value,"%d",i);
 SendMessage(hwndListBox[1],LB_INSERTSTRING,i,(LPARAM)value);
 }
 
}


LRESULT CALLBACK ChildProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static HWND hwndListBox[3],hwndButton;
int i;
HDC hdc;
ofstream f;
    switch (message)                  /* handle the messages */
    {
     case WM_CREATE:
        for(i=0;i<2;i++)
         hwndListBox[i]= CreateWindow("listbox",NULL,WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_NOTIFY|LBS_STANDARD,0,0,0,0,hwnd,(HMENU)i+2,hinstance,NULL);
         hwndButton=CreateWindow("button","Save",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,10,40,40,20,hwnd,(HMENU)5,hinstance,NULL);
         FillListBox(hwndListBox);
         SendMessage(hwndListBox[0],LB_SETCURSEL,AlarmHour,1);
         SendMessage(hwndListBox[1],LB_SETCURSEL,AlarmMinute,1);
         for(i=0;i<3;i++)
         {
         SendMessage(hwndListBox[0],WM_VSCROLL,SB_LINEUP,0);
         SendMessage(hwndListBox[1],WM_VSCROLL,SB_LINEUP,0);
         }
         break;
    case WM_COMMAND:
         switch(LOWORD(wParam))
         {case 5:
            f.open("AlarmValue.bin");
            i=SendMessage(hwndListBox[0],LB_GETCURSEL,0,0);
            f<<i<<"\n";
            AlarmHour=i;
            i=SendMessage(hwndListBox[1],LB_GETCURSEL,0,0);
            f<<i;
            f.close();
            AlarmMinute=i;
            SendMessage(hwnd,WM_CLOSE,0,0);
            break;
         }
         break;
    case WM_PAINT:
          for(i=0;i<2;i++)
          MoveWindow(hwndListBox[i],i*70+10,10,50,100,FALSE);
          MoveWindow(hwndButton,170,30,40,20,FALSE);
          hdc=GetDC(hwnd);
          TextOut(hdc,10,110,"Hour",4);
          TextOut(hdc,80,110,"Minute",6);
          ReleaseDC(hwnd,hdc);
          DefWindowProc(hwnd,message,wParam,lParam);
          break;
     default:
      return DefWindowProc(hwnd,message,wParam,lParam);
    }
        return 0;
}
