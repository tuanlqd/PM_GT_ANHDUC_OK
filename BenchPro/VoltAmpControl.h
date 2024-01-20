#pragma once
#include "pch.h"
//enum EMODE_SIMULATE
//{
//	CS_MODE_VOLT_POS,
//	CS_MODE_VOLT_NEG,
//	CS_MODE_AMP_POS,
//	CS_MODE_AMP_NEG
//};
//// CImagePrieviewStatic
//class VoltAmpControl : public CStatic
//{
//	DECLARE_DYNAMIC(VoltAmpControl)
//public:
//	VoltAmpControl();
//	virtual			~VoltAmpControl();
//
//	virtual	BOOL	Create();
//	virtual	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
//
//	void			SetFilename(LPCTSTR	szFilename);
//	void SetMode(const EMODE_SIMULATE& mode);
//	void SetValue(double dValue);
//	virtual void OnChangeValue(double dValue){};
//protected:
//	WCHAR			m_wsFilename[_MAX_PATH];
//	Graphics* m_graphics;
//
//	Bitmap* m_DBBitmap;
//	Graphics* m_DBGraphics;
//
//	double m_dValue;
//	double m_dAngle;
//
//	Pen* m_penBLACK;
//	Gdiplus::Font* m_fontTIMES;
//	Gdiplus::Font* m_fontValue;
//	Pen* m_penBLUE;
//
//	PathGradientBrush* m_pthGrBrush;
//	SolidBrush* m_solidBrushBLACK;
//	SolidBrush* m_solidBrushBLUE;
//	SolidBrush* m_solidBrushGREEN;
//	SolidBrush* m_solidBrushDialog;
//
//	CRect m_rect;
//	PointF m_center;
//	double m_radius;
//	EMODE_SIMULATE m_mode;
//	double m_maxValue, m_dUnit, m_dTickMark;
//	
//
//	DECLARE_MESSAGE_MAP()
//public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
//	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
//};
//
