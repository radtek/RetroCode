/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Sep 21 10:58:37 2002
 */
/* Compiler settings for C:\MYAPPDEV\Stevesprogs\MP3\ID3Tag\id3lib-3.8.0\id3com\id3com.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IID3ComField = {0xA513A24E,0xC749,0x11D3,{0x84,0x1C,0x00,0x08,0xC7,0x82,0xA2,0x57}};


const IID IID_IID3ComFrame = {0xAEBA98BE,0xC36C,0x11D3,{0x84,0x1B,0x00,0x08,0xC7,0x82,0xA2,0x57}};


const IID IID_IID3ComTag = {0xAEBA98BC,0xC36C,0x11D3,{0x84,0x1B,0x00,0x08,0xC7,0x82,0xA2,0x57}};


const IID LIBID_ID3COM = {0xAEBA98B0,0xC36C,0x11D3,{0x84,0x1B,0x00,0x08,0xC7,0x82,0xA2,0x57}};


const CLSID CLSID_ID3ComTag = {0xAEBA98BD,0xC36C,0x11D3,{0x84,0x1B,0x00,0x08,0xC7,0x82,0xA2,0x57}};


const CLSID CLSID_ID3ComFrame = {0xAEBA98BF,0xC36C,0x11D3,{0x84,0x1B,0x00,0x08,0xC7,0x82,0xA2,0x57}};


const CLSID CLSID_ID3ComField = {0xA513A24F,0xC749,0x11D3,{0x84,0x1C,0x00,0x08,0xC7,0x82,0xA2,0x57}};


#ifdef __cplusplus
}
#endif

