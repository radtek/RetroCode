For conditions of distribution and use, see the copyright notice in License.txt
Please read the documentation instead of this documment (it may be difficult to read
it due to formatting tags for an automatic documentation generation).
If you do not have it, download it from	http://software.artpol.com.pl

/** \mainpage ZipArchive library documentation

\section secGen General Information

<I><B>
ZipArchive library				<BR>
</B>
</I>

\b Version: 1.6.5		<BR>
\b Date:	24-July-2001


This library allows creating ZIP files in the compatible way with WinZip and
PKZIP version 2.5 and higher.


<B> \ref pageSyst "Platforms supported": </B>
- Windows 9x\NT\2000 (MFC and STL) - \ref sectVisual "Microsoft Visual C++ 6.0",
\ref sectBorl "Borland C++"

\author Tadeusz Dracz		<BR>
E-Mail: 
\htmlonly
<a href="mailto:tdracz@artpol.com.pl"> tdracz@artpol.com.pl</a>
\endhtmlonly
<BR>
Web Site:
\htmlonly
<A HREF="http://software.artpol.com.pl" target="_blank">http://software.artpol.com.pl</A>
\endhtmlonly

This library uses 
\htmlonly
<A HREF="http://www.freesoftware.com/pub/infozip/zlib/" target="_blank">the zlib library </A>
\endhtmlonly
by Jean-loup Gailly and Mark Adler to perform inflate and deflate operations.

\section sectFeat Features Summary:
- work in a compatible way with PKZIP and WinZip (apart from \ref TDSpan "TD disk spanning mode" which is specific to this library)
- create, modify and extract zip archives
- create and extract multi-disk archives (on non-removable disks as well)
- password encryption and decryption supported
- possibility to create or extract self-extracting archives
- compression and decompression to/from memory
- using callback functions
	- to provide easy disk change in a multi-disk archives
	- for the progress control when adding or extracting files
- testing files inside archive
- wide characters supported	
- easy interface
- easy transfer to other system platforms
- speedy
- well documented
- full source code and a sample application provided

\section secQl Quick Links

\par 
\ref pageGen
\par
\ref pageSyst
\par
\ref pageFaq
\par
\ref pageTroubles
\par
\ref pageHist 
\par
\ref pageLic 
\par
\ref pageSubsc


 */

/**
 
	\page pageSyst Compilation & Integration

	\section secCompil Compiling for different implementations and platforms

	The files required for all the library versions are located in the program 
	root directory. You also need to copy additional files to the library 
	root directory from the two more subfolders. Depending on the configuration 
	these files are located in:

	
	\subsection winMFC Windows MFC
		\e \windows and \e \mfc <BR>
		You can just execute \e !copy from Win-MFC.bat batch file.

	\subsection winSTL Windows STL
		\e \windows and \e \stl <BR>
		You can just execute \e !copy from !copy from Win-STL.bat batch file.

	\section sectVisual Visual C++ : integrating with the project
	
	To add ZipArchive library functionality into your project you need to link 
	the library to the project. You can do this in at least two ways 
	(in both cases you need to include ZipArchive.h header in your sources).

	\subsection subsM1 Method 1

	Add \e ZipArchive.lib with the proper path e.g. <EM> ..\ZipArchive\debug\ZipArchive.lib </EM> to <EM> Project Settings->Link->Input->Object/library modules </EM> 
	and add ZipArchive library directory to the preprocessor searches (<EM> Project Settings -> C++ -> Preprocessor -> Additional include directories </EM>).

	\subsection subsM2 Method 2 (simpler)
	Insert Zip project into workspace and set project dependencies: your project dependent on ZipArchive project
	(<EM> Project -> Dependencies </EM> and then on the dialog that will appear
	you select your project name from the combo box and check the box next to ZipArchive project name). 
	When you use this method, you link configurations in your project with
	configurations in the ZipArchive project that have the same name in both projects. So if you need to use 
	for example "Static Release" configuration from ZipArchive project, you need to create one with the same name
	in your application project and make sure that your project uses MFC library and run-time library in same way
	(<em> Project->Settings->General->Microsoft Fundation Classes </em> and <EM> Project->Settings-> c/c++ ->Code Generation->Use run-time library </EM>).

	In case you experience linking problems, please see the section \ref secLink.

	\section sectBorl Borland C++ compatibility
	The library contains a project files for Borland C++ 5.0.
	They were created using Visual C++ Project Conversion Utility (VCTOBPR.EXE).
	You can start it with the command <I> Tools->Visual C++ Project Conversion Utility </I>.
	- The project \e ZipArchive.bpr was converted from a Release configuration
	of the MFC version of the library (\e ZipArchive.dsp).
	- The project \e ZipArchive_no_MFC.bpr was converted from a Release configuration
	of the non MFC version of the library (\e ZipArchive_no_MFC.dsp).

	\note Be sure to create \e Release subfolder before compiling one of these projects,
	 otherwise you'll get a write error.

	In case the projects provided don't work for you, you can create your own. You need to copy 
	to the root directory appropriate files for \ref winMFC "MFC" or \ref winSTL "STL" versions. 
	You may use the Borland project conversion utility.

	
	\subsection subExample Compiling the sample application
	There is a Borland C++ project provided with the sample application \c TesZipDlg. <BR>
	To compile it you need compiled MFC version of ZipArchive library.

	\note Be sure to create \e Release subfolder first, otherwise you'll get 
	a write error.
	
	Add the library (\e ZipArchive.lib ) to the project (<I>Project->Add To Project</I>) and compile.

*/


/**
\page pageTroubles Troubleshooting

\section secLink Linking problems (Visual C++)

When you experience linking errors (mostly \e LNK2005) you need to make sure that
 the library and your program are both using single-threaded or both
 multithreaded (or multithreaded DLL) run-time library. The option <EM> Project->Settings-> c/c++ ->Code Generation->Use run-time library </EM> 
 should be set to the same value in the ZipArchive library and the program 
 project options. Make sure that you link appriopriate configurations (Release against Release, Debug against Debug...)
 and that you're using MFC library in the same way (shared, static or not using) in those configurations.

\section secImploded Cannot extract the file

The common reason is that the data is compressed using \e imploded method (usualy with old archivers).
The only methods supported by the zlib library are \e deflation which is the most commonly used by archivers and \e storing 
which is not a compression method at all. You can check whether there lays the problem by setting
a breakpoint at CZipFileHeader::Read and checking at the end of the function the value of \e m_uMethod field. 
It should be 0 (stored) or 8 (deflated); otherwise you will not be able to extract the file.


*/

/**

\page pageGen General Information

\par
\ref sectCompress
\par
\ref sectSpan
\par
\ref sectPass 
\par
\ref sectSE 
\par
\ref sectExc 
\par


 

\section sectCompress Compression and decompression

There are some functions defined for fast operations on archive: CZipArchive::AddNewFile,
 CZipArchive::ExtractFile, CZipArchive::DeleteFile, CZipArchive::TestFile. 
 You only need to call functions CZipArchive::Open - before and CZipArchive::Close - after using them.
Remember to call CZipArchive::Close function when you finish working with CZipArchive class.

\section sectSpan Multi-disk archives

This library supports two kinds of multi-disk archives:

- Disk spanning performed in the compatible way with all other main zip programs. It means that the archive can only be created on a removable device, the size of the volume is auto-detected and the label is written to the disk. To use this kind of disk spanning you need to define a static callback function for changing disks and set it with CZipArchive::SetSpanCallback function.
- Disk spanning performed in the internal mode, called in the sources TDSpan mode. This allows creating multi-disk archives also on non-removable devices and with user-defined volume size. There is no need to set callback function in this mode.

These two disk spanning modes create volumes with compatible internal structure. It means that you can easily convert the volumes created in one mode to the other one by renaming the files (in TDSpan mode each volume but last has a number as an extension). To convert the archive from TD to PKZIP compatible archive, copy each file to the removable media, giving them the extension ".zip". You should also label each disk with the appropriate label starting from "pkback# 001".

There is a limited functions set available during work with multi-disk archives. Only adding is allowed when creating an archive and only extracting and testing when opening an existing one. Deleting files from these archives isn't allowed in any of these cases.

Class CZipArchive uses write buffer to make write operations extremely fast. You can change its size with CZipArchive::SetAdvanced function. While creating a multi-disk archive, set the size of the buffer to the maximum size of the volume  for the best performance.

The popular archivers such as PKZIP and WinZip cannot operate on archive in TDSpan mode. You need to convert them to PKZIP span mode (have a look above). Remember about copying the files to the removable media (it does not comply with Winzip, which can extract a multi-disk archive from any media but only from the fixed location on the drive).

\section sectPass Password encryption and decryption

This library supports creating and extracting of the password protected archives. There are several issues you should be aware of when using this feature. To set the password for the file to be added or extracted call the function CZipArchive::SetPassword with the password as the argument. To clear the password call this function without arguments or with an empty string argument. The function has no effect on a closed archive and on the currently opened file (whether new or existing) inside archive. During opening an archive the password is cleared and it is not changed if the file inside archive is opened. You can set different passwords for different files inside the same archive, but remember to set it BEFORE opening the file. You cannot use ASCII characters with codes above 127 in a password, if you do so, the function CZipArchive::SetPassword returns false and the password is cleared. If the password is cleared, no encryption or decryption take place.
You can find out what files are password encrypted by calling CZipArchive::GetFileInfo which fills the structure CZipFileHeader with data, and then the method CZipFileHeader::IsEncrypted. If it returns true, the file needs a password to extract.
The successful extraction of the encrypted file doesn't always mean that the password is correct. CZipArchive doesn't check for a crc if m_info.m_uUncomprLeft is not zero in the function CZipArchive::CloseFile. In some cases bad password causes that this value is not zero, so you have to check also for the return value of this function (it returns -1 in this case). You can also check the size of the extracted file since it is smaller than it should be.

\section sectSE Self extract support

The library automatically detects self-extracting archives. This is the simplest self-extract code :

\code
//Windows code

int APIENTRY WinMain(HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
{
	CZipArchive zip;

	// get the path of the executable
	TCHAR szBuff[_MAX_PATH];
	if (!::GetModuleFileName(hInstance, szBuff, _MAX_PATH))
		return -1;

	CString szDest;
	// ...
	// add some code here to get the destination directory from the user 
	// for example:
	// CBrowseForFolder bf;
	//   bf.strTitle = _T("Select directory to extract files");
	//   if (!bf.GetFolder(szDest))
	//       return -1;
	//
	// class CBrowseForFolder is included in the sample application project
	// remember about including the header!
	zip.Open(szBuff, CZipArchive::openReadOnly); 
	// openReadOnly mode is necessary for self extract archives
	for (WORD i = 0; i < zip.GetNoEntries(); i++)
		zip.ExtractFile(i, szDest);

	zip.Close();
	return 0;
	// this code will not work for the encrypted archives since it is needed
	// to get the password from the user ( a small addition to the 
	// existing code I suppose )
}

\endcode

After compiling it and appending a zip archive to it (e.g. with the DOS command: <EM> copy /b SelfExtract.exe + ZipFile.zip FinalFile.exe </EM>) we have a self extracting archive.


\section sectExc Exceptions

The library throws the following exceptions in the MFC version (inherited from CException): CMemoryException*, CFileExeption* and CZipException*. The first two don't need an explanation. The last is thrown when some internal error occurs. Handling them may be done in the following way:

\code

try
{
	// ...
	// some operations on the ZipArchive library
}
catch (CException* e)
{
	if (e->IsKindOf( RUNTIME_CLASS( CZipException )))
	{
		CZipException* p = (CZipException*) e;
		//... and so on 
	}
	else if (e->IsKindOf( RUNTIME_CLASS( CFileException )))
	{
		CFileException* p = (CFileException*) e;
		//... and so on 
	} 
	else
	{
		// the only possibility is a memory exception I suppose
		//... and so on 
	}
	e->Delete();
}


\endcode


In the STL version the library throws exceptions inherited from std::exception. In this case you should catch std::exception object (not a pointer to it).


*/

/**
\page pageSubsc ZipArchive Newsletter

To be notified about ZipArchive library updates, enter your
e-mail into the input field below and press \e Subscribe! button.

\htmlonly

<form method="post" action="http://software.artpol.com.pl/cgi-bin/subscribe.cgi">
<input type="hidden" name="op" value="add">
<input type="hidden" name="list" value="ZipArchive">
<input type="text" name="email" value="">
<input type="submit" value="Subscribe!">
</form>


<H4>Privacy Policy of the ZipArchvie library Newsletter List</h4>
<UL>
 <li> The information you provide, will never be made available to any third party company. 
 <li> Only the Web Master of the Artpol Software site will have an access to the mailing list.
 <li> If at anytime you wish to be removed from the mailing list, you can do it by 
following the link that you will receive with every newsletter.
</UL>

\endhtmlonly

*/