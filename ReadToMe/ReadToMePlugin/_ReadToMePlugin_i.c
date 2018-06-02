

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Aug 26 22:27:12 2008
 */
/* Compiler settings for _ReadToMePlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

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

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IReadToMe,0x6A7C0940,0xD1F2,0x4343,0xAB,0xB9,0x58,0xAB,0x66,0x9E,0x9E,0x4F);


MIDL_DEFINE_GUID(IID, IID_IHtmlEvenHandler,0xD0F58ABF,0x0B8E,0x4888,0xB9,0x7F,0x27,0xFA,0x76,0xFF,0x7E,0x44);


MIDL_DEFINE_GUID(IID, IID_IMyBrowserEvents,0xF06319D4,0xC694,0x4E50,0x8A,0xEB,0x45,0xCD,0xAC,0xDA,0x37,0xA4);


MIDL_DEFINE_GUID(IID, LIBID_ReadToMePlugin,0x9BA94845,0x6AAB,0x4BBB,0x9E,0x0F,0x3B,0xE2,0x2B,0x8C,0x1A,0xFB);


MIDL_DEFINE_GUID(CLSID, CLSID_CReadToMe,0x1FFFE263,0x3C8E,0x4DD8,0x9B,0xAA,0x36,0x99,0x8D,0x29,0x56,0x1E);


MIDL_DEFINE_GUID(CLSID, CLSID_CHtmlEvenHandler,0xE6A7F2CD,0xF0DF,0x4C78,0x87,0xE9,0x60,0x51,0x6B,0xCF,0x6A,0xFA);


MIDL_DEFINE_GUID(CLSID, CLSID_CMyBrowserEvents,0x51A96B6A,0x8D5E,0x4BA3,0x95,0x3C,0x4F,0xE6,0xEE,0xC0,0xEF,0x65);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



