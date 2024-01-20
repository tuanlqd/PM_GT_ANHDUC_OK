#include "pch.h"
#include "GUIStaticText.h"

//// CImagePrieviewStatic
//IMPLEMENT_DYNAMIC(GUIStaticText, CStatic)
//
//GUIStaticText::GUIStaticText() : CStatic()
//{
//	m_graphics = (Graphics*)NULL;
//	
//	m_DBBitmap = NULL;
//	m_DBGraphics = NULL;
//
//
//
//	m_fontTIMES = NULL;
//
//	m_solidBrushDialog = NULL;
//	m_solidBrushBLACK = NULL;
//	m_solidBrushBLUE = NULL;
//	m_solidBrushGREEN = NULL;
//	swprintf(m_wsValue, 64, _T("%s"), L"TRẠM NGUỒN DƯƠNG 1");
//
//}
//
//GUIStaticText::~GUIStaticText()
//{
//	delete m_graphics;
//	if (m_DBBitmap)
//		delete m_DBBitmap;
//	if (m_DBGraphics)
//		delete m_DBGraphics;
//
//
//	if (m_fontTIMES)
//		delete m_fontTIMES;
//	if (m_solidBrushDialog)
//		delete m_solidBrushDialog;
//	if (m_solidBrushBLACK)
//		delete m_solidBrushBLACK;
//	if (m_solidBrushBLUE)
//		delete m_solidBrushBLUE;
//	if (m_solidBrushGREEN)
//		delete m_solidBrushGREEN;
//
//}
//
//
//BOOL GUIStaticText::Create()
//{
//	if (GetSafeHwnd() != HWND(NULL))
//	{
//		m_graphics = new Graphics(GetSafeHwnd());
//		GetClientRect(&m_rect);
//		m_DBBitmap = new Bitmap(m_rect.right, m_rect.bottom);
//		m_DBGraphics = Graphics::FromImage(m_DBBitmap);
//
//
//
//		FontFamily fontFamily(L"Times New Roman");
//		m_fontTIMES = new Gdiplus::Font(&fontFamily, 23, FontStyleBold, UnitPixel);
//				
//
//		m_solidBrushBLACK = new SolidBrush(Color(255, 0, 0, 0));
//		m_solidBrushBLUE = new SolidBrush(Color(255, 0, 0, 255));
//		m_solidBrushGREEN = new SolidBrush(Color(255, 0, 255, 0));
//		m_solidBrushDialog = new SolidBrush(Color(255, 240, 240, 240));
//
//
//		return TRUE;
//	}
//	return FALSE;
//}
//
//
//void GUIStaticText::DrawItem(LPDRAWITEMSTRUCT	/*lpDrawItemStruct*/)
//{
//	if (m_graphics == NULL)
//		return;
//	RectF destRect(REAL(m_rect.left), REAL(m_rect.top), REAL(m_rect.Width()), REAL(m_rect.Height()));
//
//	m_DBGraphics->FillRectangle(m_solidBrushDialog, destRect);
//	
//	StringFormat stringFormat;
//	// Center-justify each line of text.
//	stringFormat.SetAlignment(StringAlignmentCenter);
//	// Center the block of text (top to bottom) in the rectangle.
//	stringFormat.SetLineAlignment(StringAlignmentCenter);
//
//	m_DBGraphics->DrawString(m_wsValue, -1, m_fontTIMES, destRect, &stringFormat, m_solidBrushBLACK);
//
//
//	//m_DBGraphics->DrawString(m_wsValue, -1, m_fontTIMES, pointVolt, m_solidBrushBLACK);
//
//	m_graphics->DrawImage(m_DBBitmap, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
//}
//void GUIStaticText::setText(unsigned char fontSize, const std::wstring& strCaption)
//{
//	swprintf(m_wsValue, 64, _T("%s"), strCaption.c_str());
//	if (m_fontTIMES)
//		delete m_fontTIMES;
//	//FontFamily fontFamily(L"Times New Roman");
//	FontFamily fontFamily(L"Calibri");
//	m_fontTIMES = new Gdiplus::Font(&fontFamily, fontSize, FontStyleBold, UnitPixel);
//}
//BEGIN_MESSAGE_MAP(GUIStaticText, CStatic)
//END_MESSAGE_MAP()
//
//// CImagePrieviewStatic message handlers
