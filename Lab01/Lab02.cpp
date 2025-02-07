
// Lab02.cpp: определяет поведение классов для приложения.
//

#include "header.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Lab02.h"
#include "MainFrm.h"
#include "TestBMP.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab01App

BEGIN_MESSAGE_MAP(CLab01App, CWinApp)
END_MESSAGE_MAP()

// Clab2App construction

void CLab01App::LoadImageBMP(CPoint point)								// загрузка изображения
{
	CFileDialog fileDialog((BOOL)TRUE);							//объект класса выбора файла
	int result = fileDialog.DoModal();							//запустить диалоговое окно
	if (result == IDOK)											//если файл выбран
	{
		AfxMessageBox(fileDialog.GetPathName());				// показать полный путь
		CWnd *cwnd = AfxGetMainWnd();							// получить указатель на активное главное окно приложения
		hwnd = cwnd->GetSafeHwnd();								// Возвращает дескриптор окна m_hWnd или NULL если указатель thisNULL.
		hBit = (HBITMAP)LoadImage(NULL, fileDialog.GetPathName().GetBuffer(), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);		//загрузка изображения
		ShowBitMap(hwnd, hBit, point.x, point.y);				//вывод изображения
	}
}

void CLab01App::SaveArea()												// сохранение области изображения
{
	CFileDialog fileDialog((BOOL)FALSE, NULL, L"area.bmp");		//объект класса выбора файла
	int result = fileDialog.DoModal();							//запустить диалоговое окно
	if (result == IDOK)											//если файл выбран
	{
		CWnd *cwnd = AfxGetMainWnd();
		HWND hwnd = cwnd->GetSafeHwnd();
		RECT r;													//r – область в окне, куда выводится изображение
		if (From.x < To.x) {
			r.left = From.x;
			r.right = To.x;
			r.top = From.y;
			r.bottom = To.y;
		}
		else {
			r.left = To.x;
			r.right = From.x;
			r.top = To.y;
			r.bottom = From.y;
		}
		ClientToBmp(hwnd, r, (char*)fileDialog.GetPathName().GetBuffer());	// сохранение области изображения

	}
}










// Создание CLab01App

CLab01App::CLab01App() noexcept
{
	index = 0;

	SetAppID(_T("Lab01.AppID.NoVersion"));
}

// Единственный объект CLab01App

CLab01App theApp;


// Инициализация CLab01App

BOOL CLab01App::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));


	// Чтобы создать главное окно, этот код создает новый объект окна
	// рамки, а затем задает его как объект основного окна приложения
	CFrameWnd* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	// создайте и загрузите рамку с его ресурсами
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, nullptr,
		nullptr);


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;




	// Одно и только одно окно было инициализировано, поэтому отобразите и обновите его
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CLab01App::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}

// Обработчики сообщений CLab01App


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CLab01App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Обработчики сообщений CLab01App



