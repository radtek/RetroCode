

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef ___ReadToMePlugin_h__
#define ___ReadToMePlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IReadToMe_FWD_DEFINED__
#define __IReadToMe_FWD_DEFINED__
typedef interface IReadToMe IReadToMe;
#endif 	/* __IReadToMe_FWD_DEFINED__ */


#ifndef __IHtmlEvenHandler_FWD_DEFINED__
#define __IHtmlEvenHandler_FWD_DEFINED__
typedef interface IHtmlEvenHandler IHtmlEvenHandler;
#endif 	/* __IHtmlEvenHandler_FWD_DEFINED__ */


#ifndef __IMyBrowserEvents_FWD_DEFINED__
#define __IMyBrowserEvents_FWD_DEFINED__
typedef interface IMyBrowserEvents IMyBrowserEvents;
#endif 	/* __IMyBrowserEvents_FWD_DEFINED__ */


#ifndef __CReadToMe_FWD_DEFINED__
#define __CReadToMe_FWD_DEFINED__

#ifdef __cplusplus
typedef class CReadToMe CReadToMe;
#else
typedef struct CReadToMe CReadToMe;
#endif /* __cplusplus */

#endif 	/* __CReadToMe_FWD_DEFINED__ */


#ifndef __CHtmlEvenHandler_FWD_DEFINED__
#define __CHtmlEvenHandler_FWD_DEFINED__

#ifdef __cplusplus
typedef class CHtmlEvenHandler CHtmlEvenHandler;
#else
typedef struct CHtmlEvenHandler CHtmlEvenHandler;
#endif /* __cplusplus */

#endif 	/* __CHtmlEvenHandler_FWD_DEFINED__ */


#ifndef __CMyBrowserEvents_FWD_DEFINED__
#define __CMyBrowserEvents_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMyBrowserEvents CMyBrowserEvents;
#else
typedef struct CMyBrowserEvents CMyBrowserEvents;
#endif /* __cplusplus */

#endif 	/* __CMyBrowserEvents_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"
#include "shldisp.h"
#include "shobjidl.h"
#include "sapi.h"
#include "sapiddk.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IReadToMe_INTERFACE_DEFINED__
#define __IReadToMe_INTERFACE_DEFINED__

/* interface IReadToMe */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IReadToMe;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A7C0940-D1F2-4343-ABB9-58AB669E9E4F")
    IReadToMe : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IReadToMeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IReadToMe * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IReadToMe * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IReadToMe * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IReadToMe * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IReadToMe * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IReadToMe * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IReadToMe * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IReadToMeVtbl;

    interface IReadToMe
    {
        CONST_VTBL struct IReadToMeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReadToMe_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IReadToMe_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IReadToMe_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IReadToMe_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IReadToMe_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IReadToMe_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IReadToMe_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IReadToMe_INTERFACE_DEFINED__ */


#ifndef __IHtmlEvenHandler_INTERFACE_DEFINED__
#define __IHtmlEvenHandler_INTERFACE_DEFINED__

/* interface IHtmlEvenHandler */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHtmlEvenHandler;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0F58ABF-0B8E-4888-B97F-27FA76FF7E44")
    IHtmlEvenHandler : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IHtmlEvenHandlerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHtmlEvenHandler * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHtmlEvenHandler * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHtmlEvenHandler * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IHtmlEvenHandler * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IHtmlEvenHandler * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IHtmlEvenHandler * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IHtmlEvenHandler * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IHtmlEvenHandlerVtbl;

    interface IHtmlEvenHandler
    {
        CONST_VTBL struct IHtmlEvenHandlerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHtmlEvenHandler_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHtmlEvenHandler_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHtmlEvenHandler_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHtmlEvenHandler_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IHtmlEvenHandler_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IHtmlEvenHandler_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IHtmlEvenHandler_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHtmlEvenHandler_INTERFACE_DEFINED__ */


#ifndef __IMyBrowserEvents_INTERFACE_DEFINED__
#define __IMyBrowserEvents_INTERFACE_DEFINED__

/* interface IMyBrowserEvents */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMyBrowserEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F06319D4-C694-4E50-8AEB-45CDACDA37A4")
    IMyBrowserEvents : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMyBrowserEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyBrowserEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyBrowserEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMyBrowserEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMyBrowserEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMyBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMyBrowserEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMyBrowserEventsVtbl;

    interface IMyBrowserEvents
    {
        CONST_VTBL struct IMyBrowserEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyBrowserEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMyBrowserEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMyBrowserEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMyBrowserEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMyBrowserEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMyBrowserEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMyBrowserEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyBrowserEvents_INTERFACE_DEFINED__ */



#ifndef __ReadToMePlugin_LIBRARY_DEFINED__
#define __ReadToMePlugin_LIBRARY_DEFINED__

/* library ReadToMePlugin */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_ReadToMePlugin;

EXTERN_C const CLSID CLSID_CReadToMe;

#ifdef __cplusplus

class DECLSPEC_UUID("1FFFE263-3C8E-4DD8-9BAA-36998D29561E")
CReadToMe;
#endif

EXTERN_C const CLSID CLSID_CHtmlEvenHandler;

#ifdef __cplusplus

class DECLSPEC_UUID("E6A7F2CD-F0DF-4C78-87E9-60516BCF6AFA")
CHtmlEvenHandler;
#endif

EXTERN_C const CLSID CLSID_CMyBrowserEvents;

#ifdef __cplusplus

class DECLSPEC_UUID("51A96B6A-8D5E-4BA3-953C-4FE6EEC0EF65")
CMyBrowserEvents;
#endif
#endif /* __ReadToMePlugin_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


