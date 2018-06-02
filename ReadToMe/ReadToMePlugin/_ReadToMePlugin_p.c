

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "_ReadToMePlugin.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct __ReadToMePlugin_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } _ReadToMePlugin_MIDL_TYPE_FORMAT_STRING;

typedef struct __ReadToMePlugin_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } _ReadToMePlugin_MIDL_PROC_FORMAT_STRING;

typedef struct __ReadToMePlugin_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } _ReadToMePlugin_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const _ReadToMePlugin_MIDL_TYPE_FORMAT_STRING _ReadToMePlugin__MIDL_TypeFormatString;
extern const _ReadToMePlugin_MIDL_PROC_FORMAT_STRING _ReadToMePlugin__MIDL_ProcFormatString;
extern const _ReadToMePlugin_MIDL_EXPR_FORMAT_STRING _ReadToMePlugin__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IReadToMe_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IReadToMe_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IHtmlEvenHandler_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IHtmlEvenHandler_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMyBrowserEvents_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMyBrowserEvents_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const _ReadToMePlugin_MIDL_PROC_FORMAT_STRING _ReadToMePlugin__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const _ReadToMePlugin_MIDL_TYPE_FORMAT_STRING _ReadToMePlugin__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IReadToMe, ver. 0.0,
   GUID={0x6A7C0940,0xD1F2,0x4343,{0xAB,0xB9,0x58,0xAB,0x66,0x9E,0x9E,0x4F}} */

#pragma code_seg(".orpc")
static const unsigned short IReadToMe_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IReadToMe_ProxyInfo =
    {
    &Object_StubDesc,
    _ReadToMePlugin__MIDL_ProcFormatString.Format,
    &IReadToMe_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IReadToMe_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _ReadToMePlugin__MIDL_ProcFormatString.Format,
    &IReadToMe_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IReadToMeProxyVtbl = 
{
    0,
    &IID_IReadToMe,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IReadToMe_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IReadToMeStubVtbl =
{
    &IID_IReadToMe,
    &IReadToMe_ServerInfo,
    7,
    &IReadToMe_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IHtmlEvenHandler, ver. 0.0,
   GUID={0xD0F58ABF,0x0B8E,0x4888,{0xB9,0x7F,0x27,0xFA,0x76,0xFF,0x7E,0x44}} */

#pragma code_seg(".orpc")
static const unsigned short IHtmlEvenHandler_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IHtmlEvenHandler_ProxyInfo =
    {
    &Object_StubDesc,
    _ReadToMePlugin__MIDL_ProcFormatString.Format,
    &IHtmlEvenHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IHtmlEvenHandler_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _ReadToMePlugin__MIDL_ProcFormatString.Format,
    &IHtmlEvenHandler_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IHtmlEvenHandlerProxyVtbl = 
{
    0,
    &IID_IHtmlEvenHandler,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IHtmlEvenHandler_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IHtmlEvenHandlerStubVtbl =
{
    &IID_IHtmlEvenHandler,
    &IHtmlEvenHandler_ServerInfo,
    7,
    &IHtmlEvenHandler_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMyBrowserEvents, ver. 0.0,
   GUID={0xF06319D4,0xC694,0x4E50,{0x8A,0xEB,0x45,0xCD,0xAC,0xDA,0x37,0xA4}} */

#pragma code_seg(".orpc")
static const unsigned short IMyBrowserEvents_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IMyBrowserEvents_ProxyInfo =
    {
    &Object_StubDesc,
    _ReadToMePlugin__MIDL_ProcFormatString.Format,
    &IMyBrowserEvents_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMyBrowserEvents_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _ReadToMePlugin__MIDL_ProcFormatString.Format,
    &IMyBrowserEvents_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IMyBrowserEventsProxyVtbl = 
{
    0,
    &IID_IMyBrowserEvents,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IMyBrowserEvents_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IMyBrowserEventsStubVtbl =
{
    &IID_IMyBrowserEvents,
    &IMyBrowserEvents_ServerInfo,
    7,
    &IMyBrowserEvents_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    _ReadToMePlugin__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x70001f4, /* MIDL Version 7.0.500 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * __ReadToMePlugin_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IReadToMeProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IHtmlEvenHandlerProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMyBrowserEventsProxyVtbl,
    0
};

const CInterfaceStubVtbl * __ReadToMePlugin_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IReadToMeStubVtbl,
    ( CInterfaceStubVtbl *) &_IHtmlEvenHandlerStubVtbl,
    ( CInterfaceStubVtbl *) &_IMyBrowserEventsStubVtbl,
    0
};

PCInterfaceName const __ReadToMePlugin_InterfaceNamesList[] = 
{
    "IReadToMe",
    "IHtmlEvenHandler",
    "IMyBrowserEvents",
    0
};

const IID *  __ReadToMePlugin_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define __ReadToMePlugin_CHECK_IID(n)	IID_GENERIC_CHECK_IID( __ReadToMePlugin, pIID, n)

int __stdcall __ReadToMePlugin_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( __ReadToMePlugin, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( __ReadToMePlugin, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( __ReadToMePlugin, 3, *pIndex )
    
}

const ExtendedProxyFileInfo _ReadToMePlugin_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & __ReadToMePlugin_ProxyVtblList,
    (PCInterfaceStubVtblList *) & __ReadToMePlugin_StubVtblList,
    (const PCInterfaceName * ) & __ReadToMePlugin_InterfaceNamesList,
    (const IID ** ) & __ReadToMePlugin_BaseIIDList,
    & __ReadToMePlugin_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

