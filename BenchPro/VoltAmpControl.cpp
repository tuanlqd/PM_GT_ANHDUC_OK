#include "pch.h"
#include "VoltAmpControl.h"
//#define CS_PI 3.141592653589793238
//#define CS_DEGREES_PER_RADIAN 0.01745329251994329576923690768489
//#define CS_RADIANS_PER_DEGREE 57.295779513082320876798154814105  
//// CImagePrieviewStatic
//IMPLEMENT_DYNAMIC(VoltAmpControl, CStatic)
//
//VoltAmpControl::VoltAmpControl() : CStatic()
//{
//	m_graphics = (Graphics*)NULL;
//	m_dValue = 0.0;
//	m_dAngle = 120.0 * CS_DEGREES_PER_RADIAN;
//
//	m_DBBitmap = NULL;
//	m_DBGraphics = NULL;
//
//	m_penBLACK = NULL;
//
//	m_fontTIMES = NULL;
//
//	m_fontValue = NULL;
//
//	m_pthGrBrush = NULL;
//	m_solidBrushBLACK = NULL;
//	m_solidBrushBLUE = NULL;
//	m_solidBrushGREEN = NULL;
//	m_solidBrushDialog = NULL;
//
//	SetMode(CS_MODE_VOLT_POS);
//}
//
//
//VoltAmpControl::~VoltAmpControl()
//{
//	delete m_graphics;
//	if (m_DBBitmap)
//		delete m_DBBitmap;
//	if (m_DBGraphics)
//		delete m_DBGraphics;
//	if (m_penBLACK)
//		delete m_penBLACK;
//
//	if (m_fontTIMES)
//		delete m_fontTIMES;
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
//	if (m_solidBrushDialog)
//		delete m_solidBrushDialog;
//	if (m_penBLUE)
//		delete m_penBLUE;
//}
//void VoltAmpControl::SetMode(const EMODE_SIMULATE& mode)
//{
//	m_mode = mode;
//	if (m_mode == CS_MODE_VOLT_POS)
//	{
//		m_maxValue = 30.0;
//		m_dUnit = 1;
//		m_dTickMark = 5;
//	}
//	else if (m_mode == CS_MODE_VOLT_NEG)
//	{
//		m_maxValue = -30.0;
//		m_dUnit = 1;
//		m_dTickMark = 5;
//	}
//	else if (m_mode == CS_MODE_AMP_NEG || m_mode == CS_MODE_AMP_POS)
//	{
//		m_maxValue = 8.0;
//		m_dUnit = 0.25;
//		m_dTickMark = 1;
//	}		
//}
//
//BOOL VoltAmpControl::Create()
//{
//	if (GetSafeHwnd() != HWND(NULL))
//	{
//		m_graphics = new Graphics(GetSafeHwnd());
//		GetClientRect(&m_rect);
//		m_DBBitmap = new Bitmap(m_rect.right, m_rect.bottom);
//		m_DBGraphics = Graphics::FromImage(m_DBBitmap);
//
//		m_penBLACK = new Pen(Color(255, 0, 0, 0), 1);
//		m_penBLUE = new Pen(Color(255, 0, 0, 255), 2);
//
//		FontFamily fontFamily(L"Times New Roman");
//		m_fontTIMES = new Gdiplus::Font(&fontFamily, 12, FontStyleRegular, UnitPixel);
//
//
//		FontFamily fontFamilyTextValue(L"Digital-7");
//		m_fontValue = new Gdiplus::Font(&fontFamilyTextValue, 28, FontStyleBold, UnitPixel);
//
//		m_solidBrushBLACK = new SolidBrush(Color(255, 0, 0, 0));
//		m_solidBrushBLUE = new SolidBrush(Color(255, 0, 0, 255));
//		m_solidBrushGREEN = new SolidBrush(Color(255, 0, 255, 0));
//		m_solidBrushDialog = new SolidBrush(Color(255, 240, 240, 240));
//
//
//		// Create a path that consists of a single ellipse.
//
//		m_radius = __min(m_rect.Width(), m_rect.Height()) / 2.0;
//
//		m_center.X = m_radius;
//		m_center.Y = m_radius;
//		m_radius -= 40;
//		PointF topCircle;
//		topCircle.X = m_center.X - m_radius;
//		topCircle.Y = m_center.Y - m_radius;
//
//		GraphicsPath path;
//		path.AddEllipse(topCircle.X, topCircle.Y, 2 * m_radius, 2 * m_radius);
//
//		// Use the path to construct a brush.
//		m_pthGrBrush = new PathGradientBrush(&path);
//
//		// Set the color at the center of the path to blue.
//		m_pthGrBrush->SetCenterColor(Color(0, 255, 255, 255));
//
//		// Set the color along the entire boundary of the path to aqua.
//		Color colors[] = { Color(255, 150, 150, 150) };
//		int count = 1;
//		m_pthGrBrush->SetSurroundColors(colors, &count);
//
//		return TRUE;
//	}
//	return FALSE;
//}
//
//void VoltAmpControl::SetFilename(LPCTSTR szFilename)
//{
//#ifndef	_UNICODE
//	USES_CONVERSION;
//#endif
//
//	ASSERT(szFilename);
//	ASSERT(AfxIsValidString(szFilename));
//
//	TRACE("%s\n", szFilename);
//
//#ifndef	_UNICODE
//	wcscpy(m_wsFilename, A2W(szFilename));
//#else
//	wcscpy_s(m_wsFilename, szFilename);
//#endif
//	Invalidate();
//}
//
//void VoltAmpControl::DrawItem(LPDRAWITEMSTRUCT	/*lpDrawItemStruct*/)
//{
//	if (m_graphics == NULL)
//		return;
//	RectF destRect(REAL(m_rect.left), REAL(m_rect.top), REAL(m_rect.Width()), REAL(m_rect.Height()));
//	// clear rect
//	m_DBGraphics->FillRectangle(m_solidBrushDialog, destRect);
//	// bounding rect
//	m_DBGraphics->DrawRectangle(m_penBLUE, destRect);
//	// name control
//	PointF      pointVolt(0, 0);
//	if (m_mode == CS_MODE_VOLT_POS || m_mode == CS_MODE_VOLT_NEG)
//		m_DBGraphics->DrawString(_T("Volt"), -1, m_fontValue, pointVolt, m_solidBrushBLACK);
//	else
//		m_DBGraphics->DrawString(_T("Ampe"), -1, m_fontValue, pointVolt, m_solidBrushBLACK);
//	// circle control
//	RectF rectCircle(m_center.X - m_radius, m_center.Y - m_radius, m_radius * 2, m_radius * 2);
//	m_DBGraphics->FillEllipse(m_pthGrBrush, rectCircle);
//	// tick mark
//	double startAngle1 = 120;
//	double endAngle1 = 360;
//	double startAngle2 = 0;
//	double endAngle2 = 60;
//	double deltaAngle = (endAngle1 - startAngle1) + (endAngle2 - startAngle2);
//
//	double stepAngle = deltaAngle / (fabs(m_maxValue) / m_dUnit);
//	bool isSign = m_maxValue < 0.0;
//	double dTmp = startAngle1;
//	unsigned short tickCount = 0;
//	Point pFrom, pTo;
//	double dAngleValue, dsin, dcos;
//	double dradius1 = m_radius + 5;
//	double dradius2 = m_radius + 10;
//	double dradius3 = m_radius + 20;
//
//	unsigned int tickRange = m_dTickMark / m_dUnit;
//
//	PointF      pointF(30.0f, 12.0f);
//	RectF layoutRect(0, 0, 100, 50);
//	RectF boundRect;
//
//	wchar_t strBuff[64];
//
//	while (dTmp < endAngle1)
//	{
//		dAngleValue = dTmp * CS_DEGREES_PER_RADIAN;
//		dsin = sin(dAngleValue);
//		dcos = cos(dAngleValue);
//
//		pFrom.X = m_center.X + dradius1 * dcos;
//		pFrom.Y = m_center.Y + dradius1 * dsin;
//		pTo.X = m_center.X + dradius2 * dcos;
//		pTo.Y = m_center.Y + dradius2 * dsin;
//		m_DBGraphics->DrawLine(m_penBLACK, pFrom, pTo);
//		if (tickCount % tickRange == 0)
//		{
//			pointF.X = m_center.X + dradius3 * dcos;
//			pointF.Y = m_center.Y + dradius3 * dsin;
//
//			if (!isSign)
//				swprintf(strBuff, 64, _T("%.0lf"), tickCount * m_dUnit);
//			else
//				swprintf(strBuff, 64, _T("%.0lf"), m_maxValue+tickCount * m_dUnit);
//
//			m_DBGraphics->ResetTransform();
//			m_DBGraphics->TranslateTransform(pointF.X, pointF.Y);
//			m_DBGraphics->RotateTransform(dAngleValue);
//			m_DBGraphics->TranslateTransform(-pointF.X, -pointF.Y);
//			// Measure the string.
//			m_DBGraphics->MeasureString(strBuff, wcslen(strBuff), m_fontTIMES, layoutRect, &boundRect);
//			pointF.X -= boundRect.Width / 2;
//			pointF.Y -= boundRect.Height / 2;
//			m_DBGraphics->DrawString(strBuff, -1, m_fontTIMES, pointF, m_solidBrushBLACK);
//			m_DBGraphics->ResetTransform();
//		}
//		dTmp += stepAngle;
//		tickCount++;
//	}
//	dTmp = startAngle2;
//	while (dTmp <= endAngle2)
//	{
//		dAngleValue = dTmp * CS_DEGREES_PER_RADIAN;
//		dsin = sin(dAngleValue);
//		dcos = cos(dAngleValue);
//
//		pFrom.X = m_center.X + dradius1 * dcos;
//		pFrom.Y = m_center.Y + dradius1 * dsin;
//		pTo.X = m_center.X + dradius2 * dcos;
//		pTo.Y = m_center.Y + dradius2 * dsin;
//		m_DBGraphics->DrawLine(m_penBLACK, pFrom, pTo);
//		if (tickCount % tickRange == 0)
//		{
//			pointF.X = m_center.X + dradius3 * dcos;
//			pointF.Y = m_center.Y + dradius3 * dsin;
//
//			if (!isSign)
//				swprintf(strBuff, 64, _T("%.0lf"), tickCount * m_dUnit);
//			else
//				swprintf(strBuff, 64, _T("%.0lf"), m_maxValue+tickCount * m_dUnit);
//
//			m_DBGraphics->ResetTransform();
//			m_DBGraphics->TranslateTransform(pointF.X, pointF.Y);
//			m_DBGraphics->RotateTransform(dAngleValue);
//			m_DBGraphics->TranslateTransform(-pointF.X, -pointF.Y);
//			// Measure the string.
//			m_DBGraphics->MeasureString(strBuff, wcslen(strBuff), m_fontTIMES, layoutRect, &boundRect);
//			pointF.X -= boundRect.Width / 2;
//			pointF.Y -= boundRect.Height / 2;
//			m_DBGraphics->DrawString(strBuff, -1, m_fontTIMES, pointF, m_solidBrushBLACK);
//			m_DBGraphics->ResetTransform();
//		}
//		dTmp += stepAngle;
//		tickCount++;
//	}
//	// draw value
//	PointF pCenterValue, pTopValue;
//	double radiusValue = 7;
//	
//		pCenterValue.X = (m_radius - radiusValue) * cos(m_dAngle) + m_center.X;
//		pCenterValue.Y = (m_radius - radiusValue) * sin(m_dAngle) + m_center.Y;
//	
//
//	pTopValue.X = pCenterValue.X - radiusValue;
//	pTopValue.Y = pCenterValue.Y - radiusValue;
//
//
//	m_DBGraphics->FillEllipse(m_solidBrushGREEN, pTopValue.X, pTopValue.Y, 2 * radiusValue, 2 * radiusValue);
//
//	pointF.X = 0;
//	pointF.Y = m_rect.Height() - 26;
//	if (m_mode == CS_MODE_AMP_NEG || m_mode == CS_MODE_AMP_POS)
//	{
//		swprintf(strBuff, 64, _T("%.3lf"), abs(m_dValue));
//	    OnChangeValue(abs(m_dValue));
//	}
//	else
//	{
//		if (!isSign)
//		{
//		   swprintf(strBuff, 64, _T("%.3lf"), m_dValue);
//		   OnChangeValue(abs(m_dValue));
//		}
//		else
//		{
//			swprintf(strBuff, 64, _T("%.3lf"), m_maxValue - m_dValue);
//			OnChangeValue(m_maxValue - m_dValue);
//		}
//	}
//	m_DBGraphics->DrawString(strBuff, -1, m_fontValue, pointF, m_solidBrushBLUE);
//	m_graphics->DrawImage(m_DBBitmap, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
//}
//
//BEGIN_MESSAGE_MAP(VoltAmpControl, CStatic)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_RBUTTONDOWN()
//	ON_WM_MOUSEWHEEL()
//END_MESSAGE_MAP()
//
//// CImagePrieviewStatic message handlers
//
//
//void VoltAmpControl::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	double dx = point.x - m_center.X;
//	double dy = point.y - m_center.Y;
//	double dAngleRad = atan2(dy, dx);
//	double dAngle = dAngleRad * CS_RADIANS_PER_DEGREE;
//
//	if (dAngle < 0.0)
//		dAngle += 360;
//	bool isValid = false;
//
//	if (dAngle >= 90 && dAngle < 120)
//	{
//		dAngle = 120;
//		dAngleRad = 120 * CS_DEGREES_PER_RADIAN;
//	}
//
//	if (dAngle >= 60 && dAngle < 90)
//	{
//		dAngle = 60;
//		dAngleRad = 60 * CS_DEGREES_PER_RADIAN;
//	}
//
//	if (dAngle >= 120 && dAngle <= 360)
//	{
//		m_dValue = (dAngle - 120.0) * (m_maxValue / 300.0);
//		m_dAngle = dAngleRad;
//		isValid = true;
//	}
//	else if (dAngle >= 0 && dAngle <= 60)
//	{
//		m_dValue = dAngle * (m_maxValue / 300.0) + (240 * (m_maxValue / 300.0));
//		m_dAngle = dAngleRad;
//		isValid = true;
//	}
//	if (isValid)
//	{
//		this->Invalidate(false);
//		//CString strMess;
//		//strMess.Format(_T("%.2lf"), m_dValue);
//		//AfxMessageBox(strMess);
//	}
//	CStatic::OnLButtonDown(nFlags, point);
//}
//void VoltAmpControl::SetValue(double dValue)
//{	   
//	   if(m_mode== CS_MODE_VOLT_POS || m_mode== CS_MODE_AMP_POS)
//		{
//				double angle = dValue * 300 / m_maxValue;
//				double anngleX=120+ angle;
//				if(anngleX>=360)
//					anngleX -=360;
//				m_dAngle = anngleX* CS_DEGREES_PER_RADIAN;
//				m_dValue= dValue;
//		}
//	   if (m_mode == CS_MODE_VOLT_NEG || m_mode == CS_MODE_AMP_NEG)
//	   {
//		   double angle = dValue * 300 / fabs(m_maxValue);
//		   double anngleX = 420 + angle;
//		   if (anngleX >= 360)
//			   anngleX -= 360;
//		   m_dAngle = anngleX * CS_DEGREES_PER_RADIAN;
//		   m_dValue = m_maxValue-dValue;
//	   }
//
//}
//
//void VoltAmpControl::OnRButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//	// 0.001 volt -> 0.00375 do 
//	double tmpAngle = m_dAngle * CS_RADIANS_PER_DEGREE;
//	bool isValid = false;
//	if (tmpAngle < 0.0)
//		tmpAngle += 360;
//
//	double dStep = 0.0375;
//	if (m_mode == CS_MODE_VOLT_POS || m_mode == CS_MODE_VOLT_NEG)
//		dStep /= 10.0;
//
//	if (tmpAngle >= 120 && tmpAngle <= 360)
//	{
//		tmpAngle -= dStep;
//		if (tmpAngle < 120)
//			tmpAngle = 120;
//
//		m_dValue = (tmpAngle - 120.0) * (m_maxValue / 300.0);
//		m_dAngle = tmpAngle * CS_DEGREES_PER_RADIAN;
//		isValid = true;
//	}
//	else if (tmpAngle >= 0 && tmpAngle <= 60)
//	{
//		tmpAngle -= dStep;
//		if (tmpAngle < 0)
//			tmpAngle = 0;
//		m_dValue = tmpAngle * (m_maxValue / 300.0) + (240 * (m_maxValue / 300.0));
//		m_dAngle = tmpAngle * CS_DEGREES_PER_RADIAN;
//		isValid = true;
//	}
//	if (isValid)
//		this->Invalidate(false);
//	CStatic::OnRButtonDown(nFlags, point);
//}
//
//
//BOOL VoltAmpControl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO: Add your message handler code here and/or call default
//	double deltaVolt = zDelta * 0.000375 / 1.2;
//	if (m_mode == CS_MODE_VOLT_POS || m_mode == CS_MODE_VOLT_NEG)
//		deltaVolt /= 10.0;
//
//	double dAngle = m_dAngle * CS_RADIANS_PER_DEGREE;
//	dAngle += deltaVolt;
//	double dAngleRad;
//
//	if (dAngle < 0.0)
//		dAngle += 360;
//	if (dAngle > 360)
//		dAngle -= 360;
//	bool isValid = false;
//	dAngleRad = dAngle * CS_DEGREES_PER_RADIAN;
//
//	if (dAngle >= 90 && dAngle < 120)
//	{
//		dAngle = 120;
//		dAngleRad = 120 * CS_DEGREES_PER_RADIAN;
//	}
//
//	if (dAngle >= 60 && dAngle < 90)
//	{
//		dAngle = 60;
//		dAngleRad = 60 * CS_DEGREES_PER_RADIAN;
//	}
//
//	if (dAngle >= 120 && dAngle <= 360)
//	{
//		m_dValue = (dAngle - 120.0) * (m_maxValue / 300.0);
//		m_dAngle = dAngleRad;
//		isValid = true;
//	}
//	else if (dAngle >= 0 && dAngle <= 60)
//	{
//		m_dValue = dAngle * (m_maxValue / 300.0) + (240 * (m_maxValue / 300.0));
//		m_dAngle = dAngleRad;
//		isValid = true;
//	}
//	if (isValid)
//		this->Invalidate(false);
//
//	return CStatic::OnMouseWheel(nFlags, zDelta, pt);
//}
