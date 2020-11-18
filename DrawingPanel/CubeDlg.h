#pragma once

class POJOCube {
public:
	float scale = 1.0;

	float TransformMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0}, {0,0,0,1} };
	float RotateMatrix[4][4] = { {1,0,0,0},{0,1,0,0},{0,0,1,0}, {0,0,0,1} };

	void Draw(CDC* pDC);
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
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	POJOCube cube;

private:
	void RePaint();
};
