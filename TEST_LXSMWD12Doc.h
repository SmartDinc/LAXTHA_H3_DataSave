// TEST_LXSMWD12Doc.h : interface of the CTEST_LXSMWD12Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_LXSMWD12DOC_H__43F647EB_8B62_4BDF_8A1E_444B8DBCD89C__INCLUDED_)
#define AFX_TEST_LXSMWD12DOC_H__43F647EB_8B62_4BDF_8A1E_444B8DBCD89C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTEST_LXSMWD12Doc : public CDocument
{
protected: // create from serialization only
	CTEST_LXSMWD12Doc();
	DECLARE_DYNCREATE(CTEST_LXSMWD12Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTEST_LXSMWD12Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTEST_LXSMWD12Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTEST_LXSMWD12Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_LXSMWD12DOC_H__43F647EB_8B62_4BDF_8A1E_444B8DBCD89C__INCLUDED_)
