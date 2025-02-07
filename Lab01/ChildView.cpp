
// ChildView.cpp: реализация класса CChildView
//

#include "header.h"
#include "Lab02.h"
#include "ChildView.h"
#include "TestBMP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{		
}

CChildView::~CChildView()
{
}

// Реализация карты сообщений
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()													// сообщение ЛКМ нажата
	ON_WM_LBUTTONUP()													// сообщение ЛКМ отпущена
	// сообщения меню выбора
	ON_COMMAND(ID_FILE_LOAD, &CChildView::OnFileLoad)					// загрузка файла
	ON_COMMAND(ID_FILE_LOADINPOINT, &CChildView::OnFileLoadInPoint)		// загрузка файла в указанное место
	ON_COMMAND(ID_FILE_SSAVE, &CChildView::OnFileSave)					// сохранение области
	ON_COMMAND(ID_FILE_CLEAR, &CChildView::OnFileClear)					// очистка окна

END_MESSAGE_MAP()



// Обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // контекст устройства для рисования

	if (theApp.index == 1)				// если изображение загружено, происходит отображение изображения
		ShowBitMap(theApp.hwnd, theApp.hBit, theApp.From.x, theApp.From.y);		// вывод изображения
}

void CChildView::OnLButtonDown(UINT flags, CPoint point)						// фиксация точки при нажатии ЛКМ
{
	theApp.From = point;
}


void CChildView::OnLButtonUp(UINT flags, CPoint point)							// фиксация точки при отпускании ЛКМ
{
	theApp.To = point;
}

 
void CChildView::OnFileLoad()													// загрузка файла по умолчанию
{
	theApp.index = 1;
	theApp.From.x = define_X;	// координаты левого верхнего угла изображения в окне вывода
	theApp.From.y = define_Y;
	theApp.LoadImageBMP(theApp.From);
}


void CChildView::OnFileLoadInPoint()											// загрузка файла в указанное место
{
	theApp.index = 1;
	theApp.LoadImageBMP(theApp.From);
}


void CChildView::OnFileSave()													// запись указанной области изображения в файл
{
	theApp.SaveArea();

}

void CChildView::OnFileClear()													//очистка области
{
	theApp.index = 0;
	Invalidate();
}