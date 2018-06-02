

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sun Nov 05 19:29:03 2006
 */
/* Compiler settings for .\FTPPlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
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

MIDL_DEFINE_GUID(IID, IID_IIEFTPPlugin,0x551844CA,0xB5A5,0x46CB,0xB2,0x8F,0xA9,0x79,0x83,0x1A,0xCA,0x0C);


MIDL_DEFINE_GUID(IID, LIBID_FTPPluginLib,0xC11D7BDB,0xD9D0,0x45C4,0xBA,0x83,0xA2,0x3D,0xAB,0xDA,0x24,0x2D);


MIDL_DEFINE_GUID(CLSID, CLSID_IEFTPPlugin,0xDF9A8ABF,0xA30C,0x4240,0x9B,0xFE,0xE0,0x3E,0x7E,0xAD,0xC8,0x16);


MIDL_DEFINE_GUID(IID, IID_IIEEventHandler,0x911E0834,0xCFC0,0x43b6,0x9A,0xC5,0xFB,0x43,0x97,0xD6,0xEB,0xD7);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



