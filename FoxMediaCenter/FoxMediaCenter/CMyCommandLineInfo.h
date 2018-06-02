// CCommandLineInfo override class

class CMyCommandLineInfo : public CCommandLineInfo
{
public:
	CMyCommandLineInfo();
	~CMyCommandLineInfo();

	CStringArray m_straFiles;
	virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};