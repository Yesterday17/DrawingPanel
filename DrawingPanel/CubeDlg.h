#pragma once

class POJOCube {
public:
	POJOCube();
	void Draw(CDC* pDC, CPoint offset);

	float scale = 1.0;

	// 顶点
	float CubeVerts[8][4] = {
		{0,0,0,1},{100,0,0,1},{100,100,0,1},{0,100,0,1},
		{0,0,100,1},{100,0,100,1},{100,100,100,1},{0,100,100,1}
	};
	// 面
	int CubeFaces[6][4] = {
		{0,1,2,3},{4,7,6,5},{0,3,7,4},{5,6,2,1},{3,2,6,7},{5,1,0,4}
	};
	float TransformMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0}, {0,0,0,1} };
	// 缩放
	float ScaleMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0}, {0,0,0,1} };
	// 旋转
	float RotateMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0}, {0,0,0,1} };
	float ProjMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0}, {0,0,0,1} };

	// 单位矩阵，不允许修改
	float IdentityMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
};

// CubeDlg 对话框

class CCubeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCubeDlg)

public:
	CCubeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CCubeDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWCUBE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	void MultiplyMatrixTo(const float mul[][4], float to[][4]);
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); 
	BOOL CCubeDlg::PreTranslateMessage(MSG* pMsg);
	bool OnKeyDown(UINT nChar);
	afx_msg void OnBnClickedRadioParallel();

	POJOCube cube;
	int pX;
	int pY;
	int pZ;
	BOOL rParrel;
	CEdit pxEdit;
	CEdit pyEdit;
	CEdit pzEdit;
	CButton pSubmit;
	afx_msg void OnClickedButtonPerspective();
	afx_msg void OnBnClickedButtonReset();
};
