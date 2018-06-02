

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FTPPlugin_h__
#define __FTPPlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IIEFTPPlugin_FWD_DEFINED__
#define __IIEFTPPlugin_FWD_DEFINED__
typedef interface IIEFTPPlugin IIEFTPPlugin;
#endif 	/* __IIEFTPPlugin_FWD_DEFINED__ */


#ifndef __IEFTPPlugin_FWD_DEFINED__
#define __IEFTPPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class IEFTPPlugin IEFTPPlugin;
#else
typedef struct IEFTPPlugin IEFTPPlugin;
#endif /* __cplusplus */

#endif 	/* __IEFTPPlugin_FWD_DEFINED__ */


#ifndef __IIEEventHandler_FWD_DEFINED__
#define __IIEEventHandler_FWD_DEFINED__
typedef interface IIEEventHandler IIEEventHandler;
#endif 	/* __IIEEventHandler_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IIEFTPPlugin_INTERFACE_DEFINED__
#define __IIEFTPPlugin_INTERFACE_DEFINED__

/* interface IIEFTPPlugin */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IIEFTPPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("551844CA-B5A5-46CB-B28F-A979831ACA0C")
    IIEFTPPlugin : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IIEFTPPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIEFTPPlugin * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIEFTPPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIEFTPPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIEFTPPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIEFTPPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIEFTPPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIEFTPPlugin * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIEFTPPluginVtbl;

    interface IIEFTPPlugin
    {
        CONST_VTBL struct IIEFTPPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIEFTPPlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIEFTPPlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIEFTPPlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIEFTPPlugin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIEFTPPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIEFTPPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIEFTPPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIEFTPPlugin_INTERFACE_DEFINED__ */



#ifndef __FTPPluginLib_LIBRARY_DEFINED__
#define __FTPPluginLib_LIBRARY_DEFINED__

/* library FTPPluginLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_FTPPluginLib;

EXTERN_C const CLSID CLSID_IEFTPPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("DF9A8ABF-A30C-4240-9BFE-E03E7EADC816")
IEFTPPlugin;
#endif
#endif /* __FTPPluginLib_LIBRARY_DEFINED__ */

#ifndef __IIEEventHandler_INTERFACE_DEFINED__
#define __IIEEventHandler_INTERFACE_DEFINED__

/* interface IIEEventHandler */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IIEEventHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("911E0834-CFC0-43b6-9AC5-FB4397D6EBD7")
    IIEEventHandler : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IIEEventHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIEEventHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIEEventHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIEEventHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IIEEventHandler * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IIEEventHandler * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IIEEventHandler * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IIEEventHandler * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IIEEventHandlerVtbl;

    interface IIEEventHandler
    {
        CONST_VTBL struct IIEEventHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIEEventHandler_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIEEventHandler_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIEEventHandler_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIEEventHandler_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIEEventHandler_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIEEventHandler_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIEEventHandler_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIEEventHandler_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


