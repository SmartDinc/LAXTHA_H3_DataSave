// TEST_LXSMWD12Doc.cpp : implementation of the CTEST_LXSMWD12Doc class
//

#include "stdafx.h"
#include "TEST_LXSMWD12.h"

#include "TEST_LXSMWD12Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12Doc

IMPLEMENT_DYNCREATE(CTEST_LXSMWD12Doc, CDocument)

BEGIN_MESSAGE_MAP(CTEST_LXSMWD12Doc, CDocument)
	//{{AFX_MSG_MAP(CTEST_LXSMWD12Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12Doc construction/destruction

CTEST_LXSMWD12Doc::CTEST_LXSMWD12Doc()
{
	// TODO: add one-time construction code here

}

CTEST_LXSMWD12Doc::~CTEST_LXSMWD12Doc()
{
}

BOOL CTEST_LXSMWD12Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12Doc serialization

void CTEST_LXSMWD12Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12Doc diagnostics

#ifdef _DEBUG
void CTEST_LXSMWD12Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTEST_LXSMWD12Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTEST_LXSMWD12Doc commands
