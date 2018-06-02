/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Sep 21 10:58:37 2002
 */
/* Compiler settings for C:\MYAPPDEV\Stevesprogs\MP3\ID3Tag\id3lib-3.8.0\id3com\id3com.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


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

#ifndef __id3com_h__
#define __id3com_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IID3ComField_FWD_DEFINED__
#define __IID3ComField_FWD_DEFINED__
typedef interface IID3ComField IID3ComField;
#endif 	/* __IID3ComField_FWD_DEFINED__ */


#ifndef __IID3ComFrame_FWD_DEFINED__
#define __IID3ComFrame_FWD_DEFINED__
typedef interface IID3ComFrame IID3ComFrame;
#endif 	/* __IID3ComFrame_FWD_DEFINED__ */


#ifndef __IID3ComTag_FWD_DEFINED__
#define __IID3ComTag_FWD_DEFINED__
typedef interface IID3ComTag IID3ComTag;
#endif 	/* __IID3ComTag_FWD_DEFINED__ */


#ifndef __ID3ComTag_FWD_DEFINED__
#define __ID3ComTag_FWD_DEFINED__

#ifdef __cplusplus
typedef class ID3ComTag ID3ComTag;
#else
typedef struct ID3ComTag ID3ComTag;
#endif /* __cplusplus */

#endif 	/* __ID3ComTag_FWD_DEFINED__ */


#ifndef __ID3ComFrame_FWD_DEFINED__
#define __ID3ComFrame_FWD_DEFINED__

#ifdef __cplusplus
typedef class ID3ComFrame ID3ComFrame;
#else
typedef struct ID3ComFrame ID3ComFrame;
#endif /* __cplusplus */

#endif 	/* __ID3ComFrame_FWD_DEFINED__ */


#ifndef __ID3ComField_FWD_DEFINED__
#define __ID3ComField_FWD_DEFINED__

#ifdef __cplusplus
typedef class ID3ComField ID3ComField;
#else
typedef struct ID3ComField ID3ComField;
#endif /* __cplusplus */

#endif 	/* __ID3ComField_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_id3com_0000 */
/* [local] */ 

typedef /* [public][public][public][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_id3com_0000_0001
    {	ID3_FIELD_NOFIELD	= 0,
	ID3_FIELD_TEXTENC	= ID3_FIELD_NOFIELD + 1,
	ID3_FIELD_TEXT	= ID3_FIELD_TEXTENC + 1,
	ID3_FIELD_URL	= ID3_FIELD_TEXT + 1,
	ID3_FIELD_DATA	= ID3_FIELD_URL + 1,
	ID3_FIELD_DESCRIPTION	= ID3_FIELD_DATA + 1,
	ID3_FIELD_OWNER	= ID3_FIELD_DESCRIPTION + 1,
	ID3_FIELD_EMAIL	= ID3_FIELD_OWNER + 1,
	ID3_FIELD_RATING	= ID3_FIELD_EMAIL + 1,
	ID3_FIELD_FILENAME	= ID3_FIELD_RATING + 1,
	ID3_FIELD_LANGUAGE	= ID3_FIELD_FILENAME + 1,
	ID3_FIELD_PICTURETYPE	= ID3_FIELD_LANGUAGE + 1,
	ID3_FIELD_IMAGEFORMAT	= ID3_FIELD_PICTURETYPE + 1,
	ID3_FIELD_MIMETYPE	= ID3_FIELD_IMAGEFORMAT + 1,
	ID3_FIELD_COUNTER	= ID3_FIELD_MIMETYPE + 1,
	ID3_FIELD_SYMBOL	= ID3_FIELD_COUNTER + 1,
	ID3_FIELD_VOLUMEADJ	= ID3_FIELD_SYMBOL + 1,
	ID3_FIELD_NUMBITS	= ID3_FIELD_VOLUMEADJ + 1,
	ID3_FIELD_VOLCHGRIGHT	= ID3_FIELD_NUMBITS + 1,
	ID3_FIELD_VOLCHGLEFT	= ID3_FIELD_VOLCHGRIGHT + 1,
	ID3_FIELD_PEAKVOLRIGHT	= ID3_FIELD_VOLCHGLEFT + 1,
	ID3_FIELD_PEAKVOLLEFT	= ID3_FIELD_PEAKVOLRIGHT + 1,
	ID3_FIELD_LASTFIELDID	= ID3_FIELD_PEAKVOLLEFT + 1
    }	eID3FieldTypes;

typedef /* [public][public][public][public][public][public][helpstring][uuid] */ 
enum __MIDL___MIDL_itf_id3com_0000_0002
    {	ID3_NOFRAME	= 0,
	ID3_AUDIOCRYPTO	= ID3_NOFRAME + 1,
	ID3_PICTURE	= ID3_AUDIOCRYPTO + 1,
	ID3_COMMENT	= ID3_PICTURE + 1,
	ID3_COMMERCIAL	= ID3_COMMENT + 1,
	ID3_CRYPTOREG	= ID3_COMMERCIAL + 1,
	ID3_EQUALIZATION	= ID3_CRYPTOREG + 1,
	ID3_EVENTTIMING	= ID3_EQUALIZATION + 1,
	ID3_GENERALOBJECT	= ID3_EVENTTIMING + 1,
	ID3_GROUPINGREG	= ID3_GENERALOBJECT + 1,
	ID3_INVOLVEDPEOPLE	= ID3_GROUPINGREG + 1,
	ID3_LINKEDINFO	= ID3_INVOLVEDPEOPLE + 1,
	ID3_CDID	= ID3_LINKEDINFO + 1,
	ID3_MPEGLOOKUP	= ID3_CDID + 1,
	ID3_OWNERSHIP	= ID3_MPEGLOOKUP + 1,
	ID3_PRIVATE	= ID3_OWNERSHIP + 1,
	ID3_PLAYCOUNTER	= ID3_PRIVATE + 1,
	ID3_POPULARIMETER	= ID3_PLAYCOUNTER + 1,
	ID3_POSITIONSYNC	= ID3_POPULARIMETER + 1,
	ID3_BUFFERSIZE	= ID3_POSITIONSYNC + 1,
	ID3_VOLUMEADJ	= ID3_BUFFERSIZE + 1,
	ID3_REVERB	= ID3_VOLUMEADJ + 1,
	ID3_SYNCEDLYRICS	= ID3_REVERB + 1,
	ID3_SYNCEDTEMPO	= ID3_SYNCEDLYRICS + 1,
	ID3_ALBUM	= ID3_SYNCEDTEMPO + 1,
	ID3_BPM	= ID3_ALBUM + 1,
	ID3_COMPOSER	= ID3_BPM + 1,
	ID3_CONTENTTYPE	= ID3_COMPOSER + 1,
	ID3_COPYRIGHT	= ID3_CONTENTTYPE + 1,
	ID3_DATE	= ID3_COPYRIGHT + 1,
	ID3_PLAYLISTDELAY	= ID3_DATE + 1,
	ID3_ENCODEDBY	= ID3_PLAYLISTDELAY + 1,
	ID3_LYRICIST	= ID3_ENCODEDBY + 1,
	ID3_FILETYPE	= ID3_LYRICIST + 1,
	ID3_TIME	= ID3_FILETYPE + 1,
	ID3_CONTENTGROUP	= ID3_TIME + 1,
	ID3_TITLE	= ID3_CONTENTGROUP + 1,
	ID3_SUBTITLE	= ID3_TITLE + 1,
	ID3_INITIALKEY	= ID3_SUBTITLE + 1,
	ID3_LANGUAGE	= ID3_INITIALKEY + 1,
	ID3_SONGLEN	= ID3_LANGUAGE + 1,
	ID3_MEDIATYPE	= ID3_SONGLEN + 1,
	ID3_ORIGALBUM	= ID3_MEDIATYPE + 1,
	ID3_ORIGFILENAME	= ID3_ORIGALBUM + 1,
	ID3_ORIGLYRICIST	= ID3_ORIGFILENAME + 1,
	ID3_ORIGARTIST	= ID3_ORIGLYRICIST + 1,
	ID3_ORIGYEAR	= ID3_ORIGARTIST + 1,
	ID3_FILEOWNER	= ID3_ORIGYEAR + 1,
	ID3_LEADARTIST	= ID3_FILEOWNER + 1,
	ID3_BAND	= ID3_LEADARTIST + 1,
	ID3_CONDUCTOR	= ID3_BAND + 1,
	ID3_MIXARTIST	= ID3_CONDUCTOR + 1,
	ID3_PARTINSET	= ID3_MIXARTIST + 1,
	ID3_PUBLISHER	= ID3_PARTINSET + 1,
	ID3_TRACKNUM	= ID3_PUBLISHER + 1,
	ID3_RECORDINGDATES	= ID3_TRACKNUM + 1,
	ID3_NETRADIOSTATION	= ID3_RECORDINGDATES + 1,
	ID3_NETRADIOOWNER	= ID3_NETRADIOSTATION + 1,
	ID3_SIZE	= ID3_NETRADIOOWNER + 1,
	ID3_ISRC	= ID3_SIZE + 1,
	ID3_ENCODERSETTINGS	= ID3_ISRC + 1,
	ID3_USERTEXT	= ID3_ENCODERSETTINGS + 1,
	ID3_YEAR	= ID3_USERTEXT + 1,
	ID3_UNIQUEFILEID	= ID3_YEAR + 1,
	ID3_TERMSOFUSE	= ID3_UNIQUEFILEID + 1,
	ID3_UNSYNCEDLYRICS	= ID3_TERMSOFUSE + 1,
	ID3_WWWCOMMERCIALINFO	= ID3_UNSYNCEDLYRICS + 1,
	ID3_WWWCOPYRIGHT	= ID3_WWWCOMMERCIALINFO + 1,
	ID3_WWWAUDIOFILE	= ID3_WWWCOPYRIGHT + 1,
	ID3_WWWARTIST	= ID3_WWWAUDIOFILE + 1,
	ID3_WWWAUDIOSOURCE	= ID3_WWWARTIST + 1,
	ID3_WWWRADIOPAGE	= ID3_WWWAUDIOSOURCE + 1,
	ID3_WWWPAYMENT	= ID3_WWWRADIOPAGE + 1,
	ID3_WWWPUBLISHER	= ID3_WWWPAYMENT + 1,
	ID3_WWWUSER	= ID3_WWWPUBLISHER + 1,
	ID3_METACRYPTO	= ID3_WWWUSER + 1
    }	eID3FrameTypes;



extern RPC_IF_HANDLE __MIDL_itf_id3com_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_id3com_0000_v0_0_s_ifspec;

#ifndef __IID3ComField_INTERFACE_DEFINED__
#define __IID3ComField_INTERFACE_DEFINED__

/* interface IID3ComField */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IID3ComField;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A513A24E-C749-11D3-841C-0008C782A257")
    IID3ComField : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [in] */ long ItemNum,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ long ItemNum,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Long( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Long( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyDataToFile( 
            BSTR FileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyDataFromFile( 
            BSTR FileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumTextItems( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Binary( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Binary( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IID3ComFieldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IID3ComField __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IID3ComField __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IID3ComField __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Text )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ long ItemNum,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Text )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ long ItemNum,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Long )( 
            IID3ComField __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Long )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IID3ComField __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyDataToFile )( 
            IID3ComField __RPC_FAR * This,
            BSTR FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyDataFromFile )( 
            IID3ComField __RPC_FAR * This,
            BSTR FileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumTextItems )( 
            IID3ComField __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Binary )( 
            IID3ComField __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Binary )( 
            IID3ComField __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IID3ComFieldVtbl;

    interface IID3ComField
    {
        CONST_VTBL struct IID3ComFieldVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IID3ComField_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IID3ComField_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IID3ComField_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IID3ComField_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IID3ComField_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IID3ComField_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IID3ComField_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IID3ComField_get_Text(This,ItemNum,pVal)	\
    (This)->lpVtbl -> get_Text(This,ItemNum,pVal)

#define IID3ComField_put_Text(This,ItemNum,newVal)	\
    (This)->lpVtbl -> put_Text(This,ItemNum,newVal)

#define IID3ComField_get_Long(This,pVal)	\
    (This)->lpVtbl -> get_Long(This,pVal)

#define IID3ComField_put_Long(This,newVal)	\
    (This)->lpVtbl -> put_Long(This,newVal)

#define IID3ComField_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IID3ComField_CopyDataToFile(This,FileName)	\
    (This)->lpVtbl -> CopyDataToFile(This,FileName)

#define IID3ComField_CopyDataFromFile(This,FileName)	\
    (This)->lpVtbl -> CopyDataFromFile(This,FileName)

#define IID3ComField_get_NumTextItems(This,pVal)	\
    (This)->lpVtbl -> get_NumTextItems(This,pVal)

#define IID3ComField_get_Binary(This,pVal)	\
    (This)->lpVtbl -> get_Binary(This,pVal)

#define IID3ComField_put_Binary(This,newVal)	\
    (This)->lpVtbl -> put_Binary(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComField_get_Text_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [in] */ long ItemNum,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComField_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComField_put_Text_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [in] */ long ItemNum,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComField_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComField_get_Long_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IID3ComField_get_Long_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComField_put_Long_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IID3ComField_put_Long_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComField_Clear_Proxy( 
    IID3ComField __RPC_FAR * This);


void __RPC_STUB IID3ComField_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComField_CopyDataToFile_Proxy( 
    IID3ComField __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB IID3ComField_CopyDataToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComField_CopyDataFromFile_Proxy( 
    IID3ComField __RPC_FAR * This,
    BSTR FileName);


void __RPC_STUB IID3ComField_CopyDataFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComField_get_NumTextItems_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IID3ComField_get_NumTextItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComField_get_Binary_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComField_get_Binary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComField_put_Binary_Proxy( 
    IID3ComField __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComField_put_Binary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IID3ComField_INTERFACE_DEFINED__ */


#ifndef __IID3ComFrame_INTERFACE_DEFINED__
#define __IID3ComFrame_INTERFACE_DEFINED__

/* interface IID3ComFrame */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IID3ComFrame;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AEBA98BE-C36C-11D3-841B-0008C782A257")
    IID3ComFrame : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Field( 
            /* [in] */ eID3FieldTypes FieldType,
            /* [retval][out] */ IID3ComField __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ eID3FrameTypes __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ eID3FrameTypes newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Compressed( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Compressed( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IID3ComFrameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IID3ComFrame __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IID3ComFrame __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IID3ComFrame __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Field )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ eID3FieldTypes FieldType,
            /* [retval][out] */ IID3ComField __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IID3ComFrame __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            IID3ComFrame __RPC_FAR * This,
            /* [retval][out] */ eID3FrameTypes __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ID )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ eID3FrameTypes newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameName )( 
            IID3ComFrame __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Compressed )( 
            IID3ComFrame __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Compressed )( 
            IID3ComFrame __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IID3ComFrameVtbl;

    interface IID3ComFrame
    {
        CONST_VTBL struct IID3ComFrameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IID3ComFrame_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IID3ComFrame_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IID3ComFrame_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IID3ComFrame_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IID3ComFrame_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IID3ComFrame_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IID3ComFrame_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IID3ComFrame_get_Field(This,FieldType,pVal)	\
    (This)->lpVtbl -> get_Field(This,FieldType,pVal)

#define IID3ComFrame_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IID3ComFrame_get_ID(This,pVal)	\
    (This)->lpVtbl -> get_ID(This,pVal)

#define IID3ComFrame_put_ID(This,newVal)	\
    (This)->lpVtbl -> put_ID(This,newVal)

#define IID3ComFrame_get_FrameName(This,pVal)	\
    (This)->lpVtbl -> get_FrameName(This,pVal)

#define IID3ComFrame_get_Compressed(This,pVal)	\
    (This)->lpVtbl -> get_Compressed(This,pVal)

#define IID3ComFrame_put_Compressed(This,newVal)	\
    (This)->lpVtbl -> put_Compressed(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_get_Field_Proxy( 
    IID3ComFrame __RPC_FAR * This,
    /* [in] */ eID3FieldTypes FieldType,
    /* [retval][out] */ IID3ComField __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IID3ComFrame_get_Field_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_Clear_Proxy( 
    IID3ComFrame __RPC_FAR * This);


void __RPC_STUB IID3ComFrame_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_get_ID_Proxy( 
    IID3ComFrame __RPC_FAR * This,
    /* [retval][out] */ eID3FrameTypes __RPC_FAR *pVal);


void __RPC_STUB IID3ComFrame_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_put_ID_Proxy( 
    IID3ComFrame __RPC_FAR * This,
    /* [in] */ eID3FrameTypes newVal);


void __RPC_STUB IID3ComFrame_put_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_get_FrameName_Proxy( 
    IID3ComFrame __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComFrame_get_FrameName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_get_Compressed_Proxy( 
    IID3ComFrame __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IID3ComFrame_get_Compressed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComFrame_put_Compressed_Proxy( 
    IID3ComFrame __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IID3ComFrame_put_Compressed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IID3ComFrame_INTERFACE_DEFINED__ */


#ifndef __IID3ComTag_INTERFACE_DEFINED__
#define __IID3ComTag_INTERFACE_DEFINED__

/* interface IID3ComTag */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IID3ComTag;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AEBA98BC-C36C-11D3-841B-0008C782A257")
    IID3ComTag : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Link( 
            BSTR __RPC_FAR *FileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasChanged( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindFrame( 
            /* [in] */ eID3FrameTypes FrameID,
            /* [defaultvalue][in] */ VARIANT_BOOL CreateNewIfNotFound,
            /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long FrameNum,
            /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveV1Tag( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StripV1Tag( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveV2Tag( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StripV2Tag( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Artist( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Artist( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Album( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Album( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Title( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Comment( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Comment( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Genre( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Genre( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Year( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Year( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Track( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Track( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastPlayed( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LastPlayed( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasV1Tag( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasV2Tag( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasLyrics( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindFrameString( 
            /* [in] */ eID3FrameTypes FrameID,
            /* [in] */ eID3FieldTypes FieldType,
            /* [in] */ BSTR FindString,
            /* [defaultvalue][in] */ VARIANT_BOOL CreateNewIfNotFound,
            /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PlayCount( 
            /* [in] */ BSTR EMailAddress,
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PlayCount( 
            /* [in] */ BSTR EMailAddress,
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Popularity( 
            /* [in] */ BSTR EMailAddress,
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Popularity( 
            /* [in] */ BSTR EMailAddress,
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TagCreated( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TagCreated( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PercentVolumeAdjust( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PercentVolumeAdjust( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Padding( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UnSync( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VersionString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveFrame( 
            /* [in] */ eID3FrameTypes FrameID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveFrameByNum( 
            /* [in] */ long FrameNum) = 0;
        
        virtual /* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pRetVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IID3ComTagVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IID3ComTag __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IID3ComTag __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IID3ComTag __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Link )( 
            IID3ComTag __RPC_FAR * This,
            BSTR __RPC_FAR *FileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IID3ComTag __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasChanged )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFrame )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ eID3FrameTypes FrameID,
            /* [defaultvalue][in] */ VARIANT_BOOL CreateNewIfNotFound,
            /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ long FrameNum,
            /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveV1Tag )( 
            IID3ComTag __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StripV1Tag )( 
            IID3ComTag __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveV2Tag )( 
            IID3ComTag __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StripV2Tag )( 
            IID3ComTag __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Artist )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Artist )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Album )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Album )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Title )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Comment )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Comment )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Genre )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Genre )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Year )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Year )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Track )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Track )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastPlayed )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LastPlayed )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasV1Tag )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasV2Tag )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasLyrics )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFrameString )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ eID3FrameTypes FrameID,
            /* [in] */ eID3FieldTypes FieldType,
            /* [in] */ BSTR FindString,
            /* [defaultvalue][in] */ VARIANT_BOOL CreateNewIfNotFound,
            /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PlayCount )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR EMailAddress,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PlayCount )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR EMailAddress,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Popularity )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR EMailAddress,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Popularity )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ BSTR EMailAddress,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TagCreated )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TagCreated )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PercentVolumeAdjust )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PercentVolumeAdjust )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Padding )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UnSync )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VersionString )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveFrame )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ eID3FrameTypes FrameID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveFrameByNum )( 
            IID3ComTag __RPC_FAR * This,
            /* [in] */ long FrameNum);
        
        /* [restricted][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IID3ComTag __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pRetVal);
        
        END_INTERFACE
    } IID3ComTagVtbl;

    interface IID3ComTag
    {
        CONST_VTBL struct IID3ComTagVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IID3ComTag_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IID3ComTag_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IID3ComTag_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IID3ComTag_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IID3ComTag_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IID3ComTag_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IID3ComTag_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IID3ComTag_Link(This,FileName)	\
    (This)->lpVtbl -> Link(This,FileName)

#define IID3ComTag_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IID3ComTag_get_HasChanged(This,pVal)	\
    (This)->lpVtbl -> get_HasChanged(This,pVal)

#define IID3ComTag_FindFrame(This,FrameID,CreateNewIfNotFound,pVal)	\
    (This)->lpVtbl -> FindFrame(This,FrameID,CreateNewIfNotFound,pVal)

#define IID3ComTag_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IID3ComTag_get_Item(This,FrameNum,pVal)	\
    (This)->lpVtbl -> get_Item(This,FrameNum,pVal)

#define IID3ComTag_SaveV1Tag(This)	\
    (This)->lpVtbl -> SaveV1Tag(This)

#define IID3ComTag_StripV1Tag(This)	\
    (This)->lpVtbl -> StripV1Tag(This)

#define IID3ComTag_SaveV2Tag(This)	\
    (This)->lpVtbl -> SaveV2Tag(This)

#define IID3ComTag_StripV2Tag(This)	\
    (This)->lpVtbl -> StripV2Tag(This)

#define IID3ComTag_get_Artist(This,pVal)	\
    (This)->lpVtbl -> get_Artist(This,pVal)

#define IID3ComTag_put_Artist(This,newVal)	\
    (This)->lpVtbl -> put_Artist(This,newVal)

#define IID3ComTag_get_Album(This,pVal)	\
    (This)->lpVtbl -> get_Album(This,pVal)

#define IID3ComTag_put_Album(This,newVal)	\
    (This)->lpVtbl -> put_Album(This,newVal)

#define IID3ComTag_get_Title(This,pVal)	\
    (This)->lpVtbl -> get_Title(This,pVal)

#define IID3ComTag_put_Title(This,newVal)	\
    (This)->lpVtbl -> put_Title(This,newVal)

#define IID3ComTag_get_Comment(This,pVal)	\
    (This)->lpVtbl -> get_Comment(This,pVal)

#define IID3ComTag_put_Comment(This,newVal)	\
    (This)->lpVtbl -> put_Comment(This,newVal)

#define IID3ComTag_get_Genre(This,pVal)	\
    (This)->lpVtbl -> get_Genre(This,pVal)

#define IID3ComTag_put_Genre(This,newVal)	\
    (This)->lpVtbl -> put_Genre(This,newVal)

#define IID3ComTag_get_Year(This,pVal)	\
    (This)->lpVtbl -> get_Year(This,pVal)

#define IID3ComTag_put_Year(This,newVal)	\
    (This)->lpVtbl -> put_Year(This,newVal)

#define IID3ComTag_get_Track(This,pVal)	\
    (This)->lpVtbl -> get_Track(This,pVal)

#define IID3ComTag_put_Track(This,newVal)	\
    (This)->lpVtbl -> put_Track(This,newVal)

#define IID3ComTag_get_LastPlayed(This,pVal)	\
    (This)->lpVtbl -> get_LastPlayed(This,pVal)

#define IID3ComTag_put_LastPlayed(This,newVal)	\
    (This)->lpVtbl -> put_LastPlayed(This,newVal)

#define IID3ComTag_get_HasV1Tag(This,pVal)	\
    (This)->lpVtbl -> get_HasV1Tag(This,pVal)

#define IID3ComTag_get_HasV2Tag(This,pVal)	\
    (This)->lpVtbl -> get_HasV2Tag(This,pVal)

#define IID3ComTag_get_HasLyrics(This,pVal)	\
    (This)->lpVtbl -> get_HasLyrics(This,pVal)

#define IID3ComTag_FindFrameString(This,FrameID,FieldType,FindString,CreateNewIfNotFound,pVal)	\
    (This)->lpVtbl -> FindFrameString(This,FrameID,FieldType,FindString,CreateNewIfNotFound,pVal)

#define IID3ComTag_get_PlayCount(This,EMailAddress,pVal)	\
    (This)->lpVtbl -> get_PlayCount(This,EMailAddress,pVal)

#define IID3ComTag_put_PlayCount(This,EMailAddress,newVal)	\
    (This)->lpVtbl -> put_PlayCount(This,EMailAddress,newVal)

#define IID3ComTag_get_Popularity(This,EMailAddress,pVal)	\
    (This)->lpVtbl -> get_Popularity(This,EMailAddress,pVal)

#define IID3ComTag_put_Popularity(This,EMailAddress,newVal)	\
    (This)->lpVtbl -> put_Popularity(This,EMailAddress,newVal)

#define IID3ComTag_get_TagCreated(This,pVal)	\
    (This)->lpVtbl -> get_TagCreated(This,pVal)

#define IID3ComTag_put_TagCreated(This,newVal)	\
    (This)->lpVtbl -> put_TagCreated(This,newVal)

#define IID3ComTag_get_PercentVolumeAdjust(This,pVal)	\
    (This)->lpVtbl -> get_PercentVolumeAdjust(This,pVal)

#define IID3ComTag_put_PercentVolumeAdjust(This,newVal)	\
    (This)->lpVtbl -> put_PercentVolumeAdjust(This,newVal)

#define IID3ComTag_put_Padding(This,newVal)	\
    (This)->lpVtbl -> put_Padding(This,newVal)

#define IID3ComTag_put_UnSync(This,newVal)	\
    (This)->lpVtbl -> put_UnSync(This,newVal)

#define IID3ComTag_get_VersionString(This,pVal)	\
    (This)->lpVtbl -> get_VersionString(This,pVal)

#define IID3ComTag_RemoveFrame(This,FrameID)	\
    (This)->lpVtbl -> RemoveFrame(This,FrameID)

#define IID3ComTag_RemoveFrameByNum(This,FrameNum)	\
    (This)->lpVtbl -> RemoveFrameByNum(This,FrameNum)

#define IID3ComTag_get__NewEnum(This,pRetVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pRetVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_Link_Proxy( 
    IID3ComTag __RPC_FAR * This,
    BSTR __RPC_FAR *FileName);


void __RPC_STUB IID3ComTag_Link_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_Clear_Proxy( 
    IID3ComTag __RPC_FAR * This);


void __RPC_STUB IID3ComTag_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_HasChanged_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_HasChanged_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_FindFrame_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ eID3FrameTypes FrameID,
    /* [defaultvalue][in] */ VARIANT_BOOL CreateNewIfNotFound,
    /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_FindFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Count_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Item_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ long FrameNum,
    /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_SaveV1Tag_Proxy( 
    IID3ComTag __RPC_FAR * This);


void __RPC_STUB IID3ComTag_SaveV1Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_StripV1Tag_Proxy( 
    IID3ComTag __RPC_FAR * This);


void __RPC_STUB IID3ComTag_StripV1Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_SaveV2Tag_Proxy( 
    IID3ComTag __RPC_FAR * This);


void __RPC_STUB IID3ComTag_SaveV2Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_StripV2Tag_Proxy( 
    IID3ComTag __RPC_FAR * This);


void __RPC_STUB IID3ComTag_StripV2Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Artist_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Artist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Artist_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComTag_put_Artist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Album_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Album_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Album_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComTag_put_Album_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Title_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Title_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComTag_put_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Comment_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Comment_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComTag_put_Comment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Genre_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Genre_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Genre_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IID3ComTag_put_Genre_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Year_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Year_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Year_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IID3ComTag_put_Year_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Track_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Track_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Track_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IID3ComTag_put_Track_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_LastPlayed_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_LastPlayed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_LastPlayed_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IID3ComTag_put_LastPlayed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_HasV1Tag_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_HasV1Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_HasV2Tag_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_HasV2Tag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_HasLyrics_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_HasLyrics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_FindFrameString_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ eID3FrameTypes FrameID,
    /* [in] */ eID3FieldTypes FieldType,
    /* [in] */ BSTR FindString,
    /* [defaultvalue][in] */ VARIANT_BOOL CreateNewIfNotFound,
    /* [retval][out] */ IID3ComFrame __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_FindFrameString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_PlayCount_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR EMailAddress,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_PlayCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_PlayCount_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR EMailAddress,
    /* [in] */ long newVal);


void __RPC_STUB IID3ComTag_put_PlayCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_Popularity_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR EMailAddress,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_Popularity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Popularity_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ BSTR EMailAddress,
    /* [in] */ short newVal);


void __RPC_STUB IID3ComTag_put_Popularity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_TagCreated_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_TagCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_TagCreated_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IID3ComTag_put_TagCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_PercentVolumeAdjust_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_PercentVolumeAdjust_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_PercentVolumeAdjust_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IID3ComTag_put_PercentVolumeAdjust_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_Padding_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IID3ComTag_put_Padding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IID3ComTag_put_UnSync_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IID3ComTag_put_UnSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get_VersionString_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IID3ComTag_get_VersionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_RemoveFrame_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ eID3FrameTypes FrameID);


void __RPC_STUB IID3ComTag_RemoveFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IID3ComTag_RemoveFrameByNum_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [in] */ long FrameNum);


void __RPC_STUB IID3ComTag_RemoveFrameByNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id][propget] */ HRESULT STDMETHODCALLTYPE IID3ComTag_get__NewEnum_Proxy( 
    IID3ComTag __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pRetVal);


void __RPC_STUB IID3ComTag_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IID3ComTag_INTERFACE_DEFINED__ */



#ifndef __ID3COM_LIBRARY_DEFINED__
#define __ID3COM_LIBRARY_DEFINED__

/* library ID3COM */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ID3COM;

EXTERN_C const CLSID CLSID_ID3ComTag;

#ifdef __cplusplus

class DECLSPEC_UUID("AEBA98BD-C36C-11D3-841B-0008C782A257")
ID3ComTag;
#endif

EXTERN_C const CLSID CLSID_ID3ComFrame;

#ifdef __cplusplus

class DECLSPEC_UUID("AEBA98BF-C36C-11D3-841B-0008C782A257")
ID3ComFrame;
#endif

EXTERN_C const CLSID CLSID_ID3ComField;

#ifdef __cplusplus

class DECLSPEC_UUID("A513A24F-C749-11D3-841C-0008C782A257")
ID3ComField;
#endif
#endif /* __ID3COM_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
