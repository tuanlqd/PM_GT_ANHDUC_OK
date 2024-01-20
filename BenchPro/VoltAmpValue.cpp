#include "pch.h"
#include "VoltAmpValue.h"

//#define CS_PI 3.141592653589793238
//#define CS_DEGREES_PER_RADIAN 0.01745329251994329576923690768489
//#define CS_RADIANS_PER_DEGREE 57.295779513082320876798154814105  
//// CImagePrieviewStatic
//IMPLEMENT_DYNAMIC(VoltAmpValue, CStatic)
//
//VoltAmpValue::VoltAmpValue() : CStatic()
//{
//	m_graphics = (Graphics*)NULL;
//	m_dVolt = 30.0;
//	m_dAmp = 8.0;
//
//	m_DBBitmap = NULL;
//	m_DBGraphics = NULL;
//
//	
//
//	m_fontValue = NULL;
//
//	m_pthGrBrush = NULL;
//	m_solidBrushBLACK = NULL;
//	m_solidBrushBLUE = NULL;
//	m_solidBrushGREEN = NULL;
//	
//}
//
//VoltAmpValue::~VoltAmpValue()
//{
//	delete m_graphics;
//	if (m_DBBitmap)
//		delete m_DBBitmap;
//	if (m_DBGraphics)
//		delete m_DBGraphics;
//	
//
//	if (m_fontValue)
//		delete m_fontValue;
//	if (m_pthGrBrush)
//		delete m_pthGrBrush;
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
//BOOL VoltAmpValue::Create()
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
//		FontFamily fontFamilyTextValue(L"Digital-7");
//		m_fontValue = new Gdiplus::Font(&fontFamilyTextValue, 48, FontStyleBold, UnitPixel);
//
//		m_solidBrushBLACK = new SolidBrush(Color(255, 0, 0, 0));
//		//m_solidBrushBLACK = new SolidBrush(Color(255, 185, 122, 87));
//		//m_solidBrushBLACK = new SolidBrush(Color(255, 63, 72, 204));
//		m_solidBrushBLUE = new SolidBrush(Color(255, 255, 0, 0));
//		m_solidBrushGREEN = new SolidBrush(Color(255, 0, 255, 0));
//		
//
//		return TRUE;
//	}
//	return FALSE;
//}
//void VoltAmpValue::setValues(const double dVolt, const double dAmp)
//{
//	m_dVolt = dVolt;
//	m_dAmp = fabs(dAmp);
//}
//
//void VoltAmpValue::DrawItem(LPDRAWITEMSTRUCT	/*lpDrawItemStruct*/)
//{
//	if (m_graphics == NULL)
//		return;
//	RectF destRect(REAL(m_rect.left), REAL(m_rect.top), REAL(m_rect.Width()), REAL(m_rect.Height())),
//		srcRect;
//
//	m_DBGraphics->FillRectangle(m_solidBrushBLACK, destRect);
//	//m_DBGraphics->DrawRectangle(m_penBLUE, destRect);
//
//	PointF      pointVolt(0, 0);
//	bool isSign = m_dVolt < 0.0;
//	double dTemp = fabs(m_dVolt);
//
//
//	if (dTemp >= 0 && dTemp < 10.0)
//	{
//		if(isSign)
//			swprintf(m_wsValue, 64, _T("- %.3lf Volt"), dTemp);
//		else
//			swprintf(m_wsValue, 64, _T("+ %.3lf Volt"), dTemp);
//	}
//	else
//	{
//		if (isSign)
//			swprintf(m_wsValue, 64, _T("-%.3lf Volt"), dTemp);
//		else
//			swprintf(m_wsValue, 64, _T("+%.3lf Volt"), dTemp);
//	}
//	m_DBGraphics->DrawString(m_wsValue, -1, m_fontValue, pointVolt, m_solidBrushGREEN);
//	pointVolt.Y += 40;
//	swprintf(m_wsValue, 64, _T("   %.3lf Ampe"), m_dAmp);
//	m_DBGraphics->DrawString(m_wsValue, -1, m_fontValue, pointVolt, m_solidBrushBLUE);
//	m_graphics->DrawImage(m_DBBitmap, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
//}
//
//BEGIN_MESSAGE_MAP(VoltAmpValue, CStatic)
//END_MESSAGE_MAP()
//
//// CImagePrieviewStatic message handlers
