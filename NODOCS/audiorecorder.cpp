#include <commdlg.h>
#include <mmsystem.h>
#include <fstream>
#include <cstdlib>

using namespace std;
//Globals for sound wave visualisation
int number, length, byte_samp, byte_sec, bit_samp;
static int samplerate = 11025;
const int NUMPTS = 11025 * 10;
bool mono = 1;
bool PLAY = 0;
errno_t wavfile;
char * filename;
int s_rate = 11025;
double limit = 10000.0;
FILE * stream;
/* Declare Windows procedure */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
/* Declare procedures */
int readSample(int number, bool leftchannel);
void SaveWavFile(char *Filename, PWAVEHDR WaveHeader);
void Wav(char *c, HWND hWnd);
/* Make the class name into a global variable */
char szAppName[ ] = "Recorder";

// **********
// Windows Main Functions
// - Programm starts here
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd; /* Window Handler */
    MSG messages; /* Saves Messages to the application */
    WNDCLASSEX wincl; /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName J= szAppName;
    wincl.lpfnWndProc = WindowProcedure; /* this function is called by windows */
    wincl.style = CS_DBCLKS;             /* catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = "APP_MENU";
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    /* Use windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    
    /* Register the window class, and if it fails quit the program */
    if(!RegisterClassEx (&wincl)){return 0;}

    /* The class is registered, let's create the programm */
    hwnd = CreateWindowEx(
        0, /* extended possibilites for variation */
        szAppName, /* Classname */
        szAppName, /* Title text */
        WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX, /* default window */
        CW_USEDEFAULT, /* Windows decides the position */
        CW_USEDEFAULT, /* where the window ends up on the screen */
        430, /* window width */
        300, /* window height */
        HWND_DESKTOP, /* the window is a child-window to desktop */
        NULL, /* use class menu */
        hThisInstance, /* Program Instance handler */
        NULL /* No window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, cmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while(GetMessage(&messages, NULL, 0, 0))
    {
        /* translate virtual-key messages into character messages */
        TranslateMessage(&messages)
        /* send message to WindowProcedure */
        DispatchMessage(&message);
    }

    /* The program return value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/* This function is called by the Windows function DispatchMessage() */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM, wParam, LPARAM lParam)
{
    static HWND REcButton;
    static HWND PlyButton;
    static HWND StpButton;
    static HMENU hMenu;
    static HPEN hPen;
    static BOOL bRecording, bPlaying, bEnding, bTerminating;
    static DWORD dwDataLength, dwRepetitions = 1;
    static HWAVEIN hWaveIn;
    static hWaveOut;
    static PBYTE pBuffer1, pBuffer2, pSaveBuffer, pNewBuffer;
    static PWAVEHDR pWaveHdr1, pWaveHdr2;
    static TCHAR szOpenError[] = TEXT("Error opening waveform audio!");
    static TCHAR szMemError[] =  TEXT("Error allocating memory!");
    static WAVEFORMATEX waveform;

    hMenu = GetMenu(hwnd);
    HDC hDC;
    POINT pt[NUM];
    BOOL fSuccess = 0;

    switch(message)         /* handle the message */
    {
    case WM_CREATE:
        RecButton = CreateWindow(TEXT("button"),"RECORD",WS_VISIBLE|WS_CHILD|ES_LEFT|1,7,175,100,25,hwnd,(HMENU) IDC_RECORD,((LPCREATESTRUCT) lParam)->hInstance,NULL);
        PlyButton = CreateWindow(TEXT("button"),"PLAY"  ,WS_VISIBLE|WS_CHILD|ES_LEFT|1,7,175,100,25,hwnd,(HMENU) IDC_PLAY  ,((LPCREATESTRUCT) lParam)->hInstance,NULL);
        StpButton = CreateWindow(TEXT("button"),"STOP"  ,WS_VISIBLE|WS_CHILD|ES_LEFT|1,7,175,100,25,hwnd,(HMENU) IDC_STOP  ,((LPCREATESTRUCT) lParam)->hInstance,NULL);

        EnableWindow(PlyButton, 0);
        EnableWindow(StpButton, 0);

        pWaveHdr1 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
        pWaveHdr2 = reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));
        //Allocate memory for save buffer
        pSaveBuffer = reinterpret_cast<PBYTE>(malloc(1));

        return 0;
    case WM_PAINT:
        PAINTSTRUCT ps;
        hDC = BeginPaint(hwnd, &ps);

        if(hDC)
        {
            RECT rc;
            rc.top = 35;
            rc.left = 0;
            rc.bottom = 145;
            rc.right = 425;
            FillRect(hDC,&rc,(HBRUSH)(COLOR_WINDOW+2));
            if(PLAY==TRUE)
            {
                FillRect(hDC,&rc,(HBRUSH)(COLOR_WINDOW+2));
                hPen = CreatePen(PS_SOLID,1,RGB(0,200,0));
                SelectObject(hDC,hPen);
                SetMapMode(hDC,MM_ISOTROPIC);
                SetWindowExtEx(hDC, 400, 300, NULL);
                SetViewPortExtEx(hDC,200,180,NULL);
                SetViewPortOrgEx(hdc,0,0,NULL);
                
                int sample=0;
                int i=1;
                int num = 60000;
                sample = readSample(i,1);
                //scale the sample
                pt[i].x = i/20;
                pt[i].y = (int)((sample)*1.5);
                MoveToEx(hDC,pt[i].x,pt[i].y,NULL);
                while(i<num && sample!=(int)0xefffffff)
                {
                    // scale the sample
                    pt[i].x = i/20;
                    pt[i].y = (int) ((sample)*1.5);
                    LineTo(hDC, pt[i].x,pt[i].y);
                    i++;
                    sample = readSample(i,1);
                }
            }
            DeleteObject(hPen);
            DeleteDC(hDC);
            EndPaint(hwnd,&ps);
        }
        return 0;
        case MM_WIM_OPEN:
            // Shrink down the save buffer
            pSaveBuffer = reinterpret_cast<PBYTE>(realloc(pSaveBuffer,1));
            //add the buffes
            waveInAddBuffer(hWaveIn, PWaveHdr1,sizeof(waveHDR));
            waveInAddBuffer(hWaveIn, PWaveHdr2,sizeof(waveHDR));
    
            // Begin sampling
    
            bRecording = 1;
            bEnding = 0;
            dwDataLength = 0;
            waveInStart(hWaveIn);
            return 1;
        case MM_WIM_DATA:
            // Reallocate save buffer memory
            pNewBuffer = reinterpret_cast<PBYTE>(realloc(pSaveBuffer,dwDataLength + ((PWAVEHDR) lParam)->dwBytesRecorded));
            if(pNewBuffer == NULL)
            {
                waveInClose(hWaveIn);
                MessageBox(hwnd, szMemError, szAppName, MB_ICONEXCLAMATION | MB_OK);
                return 1;
            }
    
            pSaveBuffer = pNewBuffer;
            CopyMemory(pSaveBuffer+dwDatalength,((PWAVEHDR) lParam)->lpData,((PWAVEHDR) lParam) -> dwBytesRecorded);
            dwDataLength += ((PWAVEHDR) lParam)->dwBytesRecorded;
            if(bEnding)
            {
                waveInClose(hWaveIn);
                return 1;
            }
    
            //send out a new buffer
            waveInAddBuffer(hWaveIn, (PWAVEHDR) lParam, sizeof(WAVEHDR));
            return 1;
        case MM_WIM_CLOSE:
            // Free the buffer memory
    
            waveInUnprepareHeader(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
            waveInUnprepareHeader(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));
            free(pBuffer1);
            free(pBuffer2);
    
            // enable and disable buttons
            if(dwDataLength > 0)
            {
                EnableWindow(PlyButton, 1);
            }
            bRecording = 0;
            if(bTerminating){SendMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0L);}
            
            return 1;
        case MM_WOM_OPEN:
            //set up header
            pWaveHdr1->lpData           = reinterpret_cast<CHAR*>(pSaveBuffer);
            pWaveHdr1->dwBufferLength   = dwDataLength;
            pWaveHdr1->dwBytesRecorded  = 0;
            pWaveHdr1->dwUser           = 0;
            pWaveHdr1->dwFlags          = WHDR_BEGINLOOP | WHDR_ENDLOOP;
            pWaveHdr1->dwLoops          = dwRepetitions;
            pWaveHdr1->lpNext           = NULL;
            pWaveHdr1->reversed         = 0;

            // prepare and write
            waveOutPrepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
            waveOutWrite(hWaveOut, pWavehdr1, sizeof(WAVEHDR));

            bEnding = 0;
            bPlaying = 1;
            return 1;
        case MM_WOM_DONE:
            waveOutUnprepareHader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
            waveOutClose(hWaveOut);
            EnableWindow(PlyButton, TRUE);
    }
}

//start of wave visualisation process
int readSample(int number, bool leftchannel)
{
    /*
        Reads sample number, returns it as an int , if this.mono==false we look at the leftchannel bool to determine which to return

        number is in the range [0,length/byte_samp]

        returns 0xefffffff on failure
    */

   if(number>=0 && number<lenght/byte_samp)
   {
       // got to the beginning of the file
       rewind(stream);

       // we start reading at sample_number * sample_size + header length

       int offset = number * 1 + 44;

       // unless this is a stereo file and the rightchannel is requested.
       if(!mono && !leftchannel)
       {
           offset += byte_samp/2;
       }

       //read this many bytes;
       int amount;
       amount = byte_samp;

       fseek(stream,offset,SEEK_CUR);
       short sample = 0;
       fread((void *)&sample,1,amount,stream);

       return sample;
   }
   else
   {
       // return 0xefffffff if failed
       return (int)0xefffffff;
   }
}

// read the temporary wav file
void Wav(char *c, HWND hWnd)
{
    filename = new char[strlen(c)+1];
    strcpy_s(filename,strlen(c)+1,c);
    //open filepointer readonly
    wavfile = fopen_s(&stream,filename,"r");
    if(stream==NULL)
    {
        MessageBox(hWnd,"Could not open" + (char)filename,"Error",MB_OK);
    }
    else
    {
        // declare a char buff to stroe some values in
        char *buff = new char[5];
        buff[4]='\0';
        //read the first 4 bytes
        fread((void *)buff,1,4,stream);
        // the first four bytes should be 'RIFF'
        if(strcmp((char *)buff,"RIFF")==0)
        {
            //read bytes 8,9,10 and 11
            fseek(stream,4,SEEK_CUR);
            fread((void *)buff,1,4,stream);
            // this should read "WAVE"
            if(strcmp((char *)buff,"WAVE")==0)
            {
                // read byte 12,13,14,15
                fread((void *)buff,1,4,stream);
                //this should read "fmt "
                if(strcmp((char *)buff,"fmt ")==0)
                {
                    fseek(stream,20,SEEK_CUR);
                    // final one read byte 36,37,38,39
                    fread((void *)buff,1,4,stream);
                    if(strcmp((char *)buff,"data")==0)
                    {
                        // now we know it is a wav file, rewind the stream
                        rewind(stream);
                        // is it mono or stereo?
                        fseek(stream,22,SEEK_CUR);
                        fread((void *)buff,1,2,stream);
                        if(buff[0]==0x02)
                        {
                            mono=false;
                        }
                        else
                        {
                            mono=true;
                        }
                        //read the sample rate
                        fread((void *)&s_rate,1,4,stream);
                        fread((void *)&byte_sec,1,4,stream);
                        byte_samp = 0;
                        fread((void *)&byte_samp,1,2,stream);
                        bit_samp = 0;
                        fread((void *)&bit_samp,1,2,stream);
                        fseek(stream,4,SEEK_CUR);
                        fread((void *)&length,1,4,stream);
                    }
                }
            }
        }
        delete buff;
    }
}