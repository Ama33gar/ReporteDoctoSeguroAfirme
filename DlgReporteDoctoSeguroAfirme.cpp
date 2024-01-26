// DlgReporteDoctoSeguroAfirme.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "sysControl.h"

//#include "ReporteDoctoSeguroAfirme.h"
#include "DlgReporteDoctoSeguroAfirme.h"
#include ".\dlgreportedoctoseguroafirme.h"

#include "C_FormasPCL.hpp"
#include "gnwproto.hpp"
#include "wtienda.hpp"
#include "folios.hpp"

#include "CGrabarDocumentoSeguro.hpp"
#include "CGrabarDocumentoSeguro2.hpp"
#include "CGrabarDocumentoSeguro2X.hpp"
#include "CConsultarCiudadGnDominio.hpp"
#include "CFolioCoppel.hpp"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

/*class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()
*/

// CDlgReporteDoctoSeguroAfirme dialog



CDlgReporteDoctoSeguroAfirme::CDlgReporteDoctoSeguroAfirme(CWnd* pParent /*=NULL*/)
	: CDialogoML(CDlgReporteDoctoSeguroAfirme::IDD, pParent)
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgReporteDoctoSeguroAfirme::DoDataExchange(CDataExchange* pDX)
{
	CDialogoML::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_imprimir);
	DDX_Control(pDX, IDCANCEL, m_cancelar);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK5, m_check5);
	DDX_Control(pDX, IDC_CHECK6, m_check6);
	DDX_Control(pDX, IDC_CHECK7, m_check7);
	DDX_Control(pDX, IDC_CHECK8, m_check8);
	DDX_Control(pDX, IDC_CHECK9, m_check9);	
	DDX_Control(pDX, IDC_FOLIOSEGURO, m_folioSeguro);
}

BEGIN_MESSAGE_MAP(CDlgReporteDoctoSeguroAfirme, CDialogoML)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnBnClickedCheck9)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgReporteDoctoSeguroAfirme message handlers

BOOL CDlgReporteDoctoSeguroAfirme::OnInitDialog()
{
	CDialogoML::OnInitDialog();

	char cMensajeOut[MAX_BUFFER_XML]={0};

	if( cargarXML( "CA0068.XML", DIALOGO_REPORTEDOCTOSEGUROAFIRME ) )
	{

		agregarControl( IDD_DLGREPORTEDOCTOSEGUROAFIRME, this, CTRL_DIALOGO );
		agregarControl( IDC_STATIC_FOLIO );
		agregarControl( IDC_STATIC_SELECCIONE );
		agregarControl( IDC_CHECK1 );
		agregarControl( IDC_CHECK2 );
		agregarControl( IDC_CHECK3 );
		agregarControl( IDC_CHECK4 );
		agregarControl( IDC_CHECK5 );
		agregarControl( IDC_CHECK6 );
		agregarControl( IDC_CHECK7 );
		agregarControl( IDC_CHECK8 );
		agregarControl( IDC_CHECK9 );

		// Add "About..." menu item to system menu.

		// IDM_ABOUTBOX must be in the system command range.
		/*ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
		ASSERT(IDM_ABOUTBOX < 0xF000);

		CMenu* pSysMenu = GetSystemMenu(FALSE);
		if (pSysMenu != NULL)
		{
			CString strAboutMenu;
			strAboutMenu.LoadString(IDS_ABOUTBOX);
			if (!strAboutMenu.IsEmpty())
			{
				pSysMenu->AppendMenu(MF_SEPARATOR);
				pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			}
		}*/

		// Set the icon for this dialog.  The framework does this automatically
		//  when the application's main window is not a dialog
		SetIcon(m_hIcon, TRUE);			// Set big icon
		SetIcon(m_hIcon, FALSE);		// Set small icon

		// TODO: Add extra initialization here
		char cFecha[30],cConsulta[1002],cNombreCiudad[20];

		memset(cFecha,0,sizeof(cFecha));
		memset(cNombreCiudad,0,sizeof(cNombreCiudad));

		ShowWindow(SW_SHOWMAXIMIZED);
		crearMensaje( this, m_barraMsj, m_textoMsj );
		obtenerMensaje (MENSAJE_1001,cMensajeOut);
		ponerMensaje( this, m_barraMsj, m_textoMsj, cMensajeOut );

		iControles = 9;
		iFoco = 0;
		iFlag = 0;
		m_folioSeguro.LimitText(6);
		lFolioSeguro = 0;
		
		if ( !obtenerFechaGnDominio( &odbcTiendaNumero, cFecha, iDiaActual, iMesActual, iAnioActual, cConsulta ) )
		{
			CDialogoML::OnCancel();
		}
		else
		{
			//CConsultarCiudadGnDominio consultarCiudadGnDominioSQL(&odbc);

			//if ( !consultarCiudad( atoi(sTienda), iCiudad, cNombreCiudad, consultarCiudadGnDominioSQL ) )	//gnwConsultarCiudad.cpp
			if ( !consultarCiudad( atoi(sTienda), iCiudad, cNombreCiudad, &odbcTiendaNumero ) )
			{
				CDialogoML::OnCancel();
			}
		}
	}
	else
	{
		CString sError;
        sError.Format( "%s", obtenerError() );
        AfxMessageBox( sError, MB_ICONERROR );
        OnCancel();
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgReporteDoctoSeguroAfirme::OnSysCommand(UINT nID, LPARAM lParam)
{
	/*if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else*/
	{
		CDialogoML::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDlgReporteDoctoSeguroAfirme::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogoML::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgReporteDoctoSeguroAfirme::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDlgReporteDoctoSeguroAfirme::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
    
char cPaso[80];
    bShiftTab = false;	
 
	/*if (iFoco != 1 && WM_LBUTTONDOWN && m_grid1.bFocoGrid == true)
	{
		iFoco=1;
		asignarFoco();
	}
	*/

	if(pMsg->message == WM_SYSKEYDOWN) // Teclas virtuales 
	{  
		//if (GetKeyState(VK_MENU) & 0x8000 || pMsg->wParam == VK_F10)
		if ( GetKeyState(VK_MENU) & 0x8000 )//ELIMINO  ALT  
		{
				pMsg->wParam = VK_SHIFT;  
				return TRUE;
		}
	}

	if(pMsg->message == WM_SYSKEYDOWN) // Teclas virtuales 
	{  
		if ( pMsg->wParam == VK_F10 )
			pMsg->wParam = VK_SHIFT;
		{
			if ( validarControles() )
			{
				OnBnClickedOk();
			}
		}
	}
	
	if ( pMsg->message == WM_KEYDOWN )
	{
		if ( pMsg->wParam == VK_LEFT || pMsg->wParam == VK_UP )
		{
			iFoco--;
			if ( iFoco < 0 )
				iFoco = 0;
			asignarFoco();
		}

		if ( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_TAB || pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT )
		{
			if ( !boton() )
			{
				if ( iFoco <= iControles) //numero de controles
				{
					if ( validarControl(cPaso) )
					{
						if ( (iFoco == 0 ) && ( pMsg->wParam == VK_RETURN ) )
						{	
							iFoco = 0;								
						}

						iFoco++;
						asignarFoco();							
					}
					else
					{
						if ( !bShiftTab )
						{
							AfxMessageBox(cPaso);
						}
					}
					return TRUE; 
				}
				else
				{
					if ( pMsg->wParam != VK_RETURN )
					{
						iFoco++;
						asignarFoco();
					}
					else
					{
						asignarFoco();
					}
					return TRUE;
				}
			}
			else
			{
				if ( pMsg->wParam == VK_RETURN )
				{
					switch (iFoco)
					{
						case 11:
							OnBnClickedOk();
							break;
						case 10:								
							CDialogoML::OnCancel();
							break;															
						default:
							break;
					}
					return TRUE;
				}
				iFoco++;
				asignarFoco();
				//return TRUE;
			}
		}
		else
		{
			if ( pMsg->wParam == VK_TAB && GetKeyState(VK_SHIFT) & 0x8000 )
			{
				bShiftTab = true;
			}
			else
			{
				switch ( pMsg->wParam )
				{																			
					case VK_F10:
						OnBnClickedOk();
						break;						
					case VK_ESCAPE:
						CDialogoML::OnCancel();						
						break;						
					default:
						break;
				}
			}
		}
	}	

	return CDialogoML::PreTranslateMessage(pMsg);
}

bool CDlgReporteDoctoSeguroAfirme::validarClick(int nTmpFocus)
{
CString msg;
int nElementoTmp, i;
bool bRegresa = true;
char cPaso[80];
	
	memset(cPaso,0,sizeof(cPaso));

    if (iFoco < nTmpFocus)
    {
        // validar control anterior
        if (!validarControl(cPaso))
        {
            asignarFoco();
            if (iFoco != iControles)//numero de controles para los que se quieren se vea el mensaje de error
            {
                if ( !bShiftTab )
                {
                    AfxMessageBox(cPaso);
                }
            }
            bRegresa = false;
        }
        else
        {
            nElementoTmp = iFoco;
            iFoco = nTmpFocus;
            for (i=0; i<=nTmpFocus; i++)
            {
                iFoco = i;
                //valida hacia abajo los controles
                if (!validarControl(cPaso))
                {
                    break;
                }
            }
            asignarFoco();
        }
    }
    else
    {
        iFoco = nTmpFocus;
    }
	return bRegresa;
}

void CDlgReporteDoctoSeguroAfirme::asignarFoco()
{
    switch ( iFoco )
    {		
		case 0:			
			m_folioSeguro.SetFocus();
            break;
		case 1:			
			m_check1.SetFocus();
            break;
		case 2:
			m_check2.SetFocus();
            break;
		case 3:
			m_check3.SetFocus();				
            break;	
		case 4:
			m_check4.SetFocus();
            break;	
		case 5:
			m_check5.SetFocus();
            break;	
		case 6:
			m_check6.SetFocus();
            break;
		case 7:
			m_check7.SetFocus();
            break;
		case 8:
			m_check8.SetFocus();
            break;
		case 9:
			m_check9.SetFocus();
            break;
	/*	case 10:
			m_cancelar.SetFocus();
            break;
		case 11:
			m_imprimir.SetFocus();
            break;*/
		case 10:
			iFoco = 0;  
			m_folioSeguro.SetFocus();
            break;		
       default:
            break;
	}
}

bool CDlgReporteDoctoSeguroAfirme::validarControl( char *cCadena )
{
bool bValorRegresa = true;
CString sTexto;
char cMensajeOut[MAX_BUFFER_XML]={0};

CString sFolioSeguro;

    switch (iFoco)
    {       
		case 0 :
				m_folioSeguro.GetWindowText( sFolioSeguro );
				lFolioSeguro = atol(sFolioSeguro);

				if ( lFolioSeguro == 999999 )
				{
					memset(cCadena,' ',80);
					obtenerMensaje(MENSAJE_1002,cMensajeOut);
					memcpy(cCadena,cMensajeOut,16);
					cCadena[16]=0;
					m_folioSeguro.SetSel(0,6);
					bValorRegresa = false;
				}
				else if (lFolioSeguro == 0 )
				{
					memset(cCadena,' ',80);
					obtenerMensaje(MENSAJE_1003,cMensajeOut);
					memcpy(cCadena,cMensajeOut,32);
					cCadena[32]=0;
					m_folioSeguro.SetSel(0,6);
					bValorRegresa = false;
				}
				else if ( lFolioSeguro == lFactura1 )
				{
					lFacturaG = lFactura1;
					iFlag = 1;
				}
				else if ( lFolioSeguro == lFactura2 )
				{
					lFacturaG = lFactura2;
					iFlag = 1;
				}
				else
				{
					memset(cCadena,' ',80);
					obtenerMensaje(MENSAJE_1004,cMensajeOut);
					memcpy(cCadena,cMensajeOut,41);
					cCadena[41]=0;
					m_folioSeguro.SetSel(0,6);
					bValorRegresa = false;
				}
				break;

		default:
            break;
    }

    return bValorRegresa;
}

bool CDlgReporteDoctoSeguroAfirme::validarControles(void)
{
bool bValorRegresa = false;
int i, iFocoAnt;
bool bandera = true;	
char cPaso[80];
	
	memset(cPaso,0,sizeof(cPaso));

	iFocoAnt = iFoco;

    for (i=0; i < iControles; i++)
    {
        iFoco = i;
        bandera = validarControl(cPaso);
        if (!bandera)
        {
            AfxMessageBox(cPaso);
            asignarFoco();
            break;
        }
    }

    if ( bandera )
    {
		bValorRegresa = true;
    }

    iFoco = iFocoAnt;
	asignarFoco();

	return bValorRegresa;
}

bool CDlgReporteDoctoSeguroAfirme::boton()
{
    CWnd *pWnd = GetFocus();
    bool bValorRegresa = false;

    switch(pWnd->GetDlgCtrlID())
    {       
        case IDOK:
            bValorRegresa = true;
            break;
		case IDCANCEL:
            bValorRegresa = true;
            break;		
    }
    return bValorRegresa;;

}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck1()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck2()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck3()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck4()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck5()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck6()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck7()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck8()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedCheck9()
{
	// TODO: Add your control notification handler code here
}

void CDlgReporteDoctoSeguroAfirme::OnBnClickedOk()
{
CWaitCursor cursor;
	//imprimeReciboDocumentos( lFactura, lFolioSeguro, lCliente, iCantidadDeSeguros );
	imprimeReciboDocumentos( lFolioSeguro, lCliente );
	OnOK();
}

//void CDlgReporteDoctoSeguroAfirme::imprimeReciboDocumentos( long lFactura, long lFolioSeguro, long lCliente, int iCantidadDeSeguros )
void CDlgReporteDoctoSeguroAfirme::imprimeReciboDocumentos( long lFolioSeguro, long lCliente )
{
int iLinea=0; 
int iCheck1,iCheck2,iCheck3,iCheck4,iCheck5,iCheck6,iCheck7,iCheck8,iCheck9;
char cTextoOut[MAX_BUFFER_XML]={0};
	
	iCheck1 = m_check1.GetCheck();//Contrato original último recibo pago.
	iCheck2 = m_check2.GetCheck();//Acta de nacimiento asegurado.
	iCheck3 = m_check3.GetCheck();//Acta de defunción original.
	iCheck4 = m_check4.GetCheck();//Declaraciones de aseguradora.
	iCheck5 = m_check5.GetCheck();//Expendiente clínico certificado de defunción.
	iCheck6 = m_check6.GetCheck();//Acta ministerio público.
	iCheck7 = m_check7.GetCheck();//Acta original beneficiarios identificación.
	iCheck8 = m_check8.GetCheck();//Actas original identificación tutor.
	iCheck9 = m_check9.GetCheck();//Acta notariada patria potestad.	

	C_FormasPCL hoja(33,270,"LPT1",iFinLinea, iTipoImpresora );	

    hoja.poner(COMPACTAR,0,0);
	obtenerTexto(REPORTE_1001,cTextoOut);
    hoja.poner(cTextoOut,iLinea,0);
    iLinea+=2;

    //Contrato original último recibo pago.
	if ( iCheck1 == 1 )
    {
		obtenerTexto(REPORTE_1002,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1003,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Acta de nacimiento asegurado.
	if ( iCheck2 == 1 )
    {
		obtenerTexto(REPORTE_1004,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1005,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Acta de defunción original.
	if ( iCheck3 == 1 )
    {
		obtenerTexto(REPORTE_1006,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1007,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Declaraciones de aseguradora.
	if ( iCheck4 == 1 )
    {
		obtenerTexto(REPORTE_1008,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1009,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Expendiente clínico certificado de defunción.
	if ( iCheck5 == 1 )
    {
		obtenerTexto(REPORTE_1010,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1011,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Acta ministerio público.
	if ( iCheck6 == 1 )
    {
		obtenerTexto(REPORTE_1012,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1013,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Acta original beneficiarios identificación.
	if ( iCheck7 == 1 )
    {
		obtenerTexto(REPORTE_1014,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1015,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Actas original identificación tutor.
	if ( iCheck8 == 1 )
    {
		obtenerTexto(REPORTE_1016,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1017,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    //Acta notariada patria potestad.
	if ( iCheck9 == 1 )
    {
		obtenerTexto(REPORTE_1018,cTextoOut);
        hoja.poner(cTextoOut,iLinea,1);
		obtenerTexto(REPORTE_1019,cTextoOut);
        hoja.poner(cTextoOut,iLinea,100);
        iLinea++;
    }

    hoja.poner("----------------------",11,50);
	obtenerTexto(REPORTE_1020,cTextoOut);
    hoja.poner(cTextoOut,12,50);   

    hoja.poner(OCTAVOS,21,0);
    hoja.poner(COMPACTAR,21,5);

	grabarDocumentosSeguro( lCliente, lFolioSeguro );

	if ( !transaccionGrabarDocumentosSeguro() )
	{
		obtenerTexto(REPORTE_1021,cTextoOut);
		AfxMessageBox(cTextoOut);
		CDialogoML::OnCancel();
	}
	else
	{
		hoja.imprimir();
	}
}

void CDlgReporteDoctoSeguroAfirme::grabarDocumentosSeguro( long lCliente, long lFolioSeguro )//Checar para que se usaba el pcuentas_cliente->registro_cliente                                      
{
long lRecibo=0L;
int iCantidadSeguros=1;
char cTexto[10],cRespuesta[10];

CString sSqlTxt,sTexto;
char cIPDestino[22],cConsulta[1002],cIPCacarmov[15];

    memset(cTexto,0,10);
    memset(cRespuesta,0,10);

    sSqlTxt.Format("SELECT folio, cliente, cantidadseguros FROM crseguros WHERE cliente = %ld", lCliente);

	CGrabarDocumentoSeguro grabarDocumentoSeguroSQL(&odbcCartera);

	if ( !grabarDocumentoSeguroSQL.Exec(sSqlTxt) )
	{
		//Se obtiene el error
		sServer.Trim();		
		sprintf(cIPDestino,"%s",sServer);
		cIPDestino[15] = 0;
		sSqlTxt.Trim();		
		sprintf(cConsulta,"%s",sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		grabarDocumentoSeguroSQL.odbc->GetLastError(grabarDocumentoSeguroSQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIPDestino, "ReporteDoctoSeguroAfirme", "CDlgReporteDoctoSeguroAfirme", "grabarDocumentoSeguro", cConsulta,lEmpleado,"Error #3128",grabarDocumentoSeguroSQL.odbc,iMuestraMsg);
		CDialogoML::OnCancel();
	}
	else
	{
		grabarDocumentoSeguroSQL.activarCols();
		
		if ( grabarDocumentoSeguroSQL.leer() )
		{
			if ( grabarDocumentoSeguroSQL.folio == lFolioSeguro &&
				grabarDocumentoSeguroSQL.cliente == lCliente )
			{
				iCantidadSeguros = grabarDocumentoSeguroSQL.cantidadseguros;
			}
		}
	}

	CGrabarDocumentoSeguro2X grabarDocumentoSeguro2SQL(&odbcTiendaNumero);
	
	sSqlTxt.Format("CREATE TEMPORARY TABLE tmpcacarmov ( clavelocal char(1) DEFAULT ' '::bpchar,"
														 "clave char(1) DEFAULT ' '::bpchar,"
														 "tipomovimiento char(1) DEFAULT ' '::bpchar,"
														 "cantidadseguros int2 DEFAULT 0,"
														 "cliente int4 DEFAULT 0,"
														 "movtoseguro char(1) DEFAULT ' '::bpchar,"
														 "tienda int2 DEFAULT 0,"
														 "ciudad int2 DEFAULT 0,"
														 "caja int2 DEFAULT 0,"
														 "fecha date DEFAULT timenow(),"
														 "folio int4 DEFAULT 0,"
														 "recibo int4 DEFAULT 0 ,"
														 "ipcarteracliente char(15) DEFAULT ' '::bpchar) WITHOUT OIDS; ");   	

	if ( !grabarDocumentoSeguro2SQL.Exec(sSqlTxt) )
	{
		//Se obtiene el error
		sServer.Trim();		
		sprintf(cIPDestino,"%s",sServer);
		cIPDestino[15] = 0;
		sSqlTxt.Trim();		
		sprintf(cConsulta,"%s",sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		grabarDocumentoSeguro2SQL.odbc->GetLastError(grabarDocumentoSeguro2SQL.GetHstmt());
		grabarMensajeError( "M", iCaja, cIPDestino, "EntradaDevolucionCobranza", "CDlgEntradaDevolucionCobranza", "altaUdi", cConsulta,lEmpleado,"Error #3130",grabarDocumentoSeguro2SQL.odbc,iMuestraMsg);
		CDialogoML::OnCancel();
	}
	else
	{
		grabarDocumentoSeguro2SQL.Commit();		
	}	

	grabarDocumentoSeguro2SQL.activarCols();
	grabarDocumentoSeguro2SQL.prepararInsert("tmpcacarmov");
   
	memcpy(&grabarDocumentoSeguro2SQL.clavelocal,"1",1);
	grabarDocumentoSeguro2SQL.clavelocal[1] = 0;

    if ( lCliente == -1 )
	{	
		memcpy(&grabarDocumentoSeguro2SQL.clavelocal,"2",1);
		grabarDocumentoSeguro2SQL.clavelocal[1] = 0;
	}
    
	memcpy(&grabarDocumentoSeguro2SQL.clave,"G",1);
	grabarDocumentoSeguro2SQL.clave[1] = 0;
    
	memcpy(&grabarDocumentoSeguro2SQL.tipomovimiento,"3",1);
	grabarDocumentoSeguro2SQL.tipomovimiento[1] = 0;

    grabarDocumentoSeguro2SQL.cantidadseguros = short int(iCantidadSeguros);

	grabarDocumentoSeguro2SQL.cliente = lCliente;    
        
	memcpy(&grabarDocumentoSeguro2SQL.movtoseguro," ",1);//tienda_compra
	grabarDocumentoSeguro2SQL.movtoseguro[1] = 0;
    
	grabarDocumentoSeguro2SQL.tienda = (short int) atoi(sTienda);
        
	grabarDocumentoSeguro2SQL.ciudad = short int(iCiudad);
	grabarDocumentoSeguro2SQL.caja = short int(iCaja);        
    
	grabarDocumentoSeguro2SQL.fecha.ponerFecha(iDiaActual,iMesActual,iAnioActual);
    
    grabarDocumentoSeguro2SQL.folio = lFolioSeguro;
    
	lRecibo = obtenerFolio( FOLIOC_RECIBO, 0 ) + 1;//Se obtiene el folio sin incrementarlo y se suma 1 para simular el incremento.
    
	grabarDocumentoSeguro2SQL.recibo = lRecibo;
	
	sServer.Trim();		
	sprintf(cIPCacarmov,"%s",sServer);
	cIPCacarmov[15] = 0;
	
    memcpy(&grabarDocumentoSeguro2SQL.ipcarteracliente ,sServer,15);
	//grabarDocumentoSeguro2SQL.ipcarteracliente[15] = 0;


	if ( !grabarDocumentoSeguro2SQL.Insert() )
	{
		//Se obtiene el error
		sServer.Trim();		
		sprintf(cIPDestino,"%s",sServer);
		cIPDestino[15] = 0;
		sSqlTxt.Trim();		
		sprintf(cConsulta,"%s",sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		grabarDocumentoSeguro2SQL.odbc->GetLastError(grabarDocumentoSeguro2SQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIPDestino, "ReporteDoctoSeguroAfirme", "CDlgReporteDoctoSeguroAfirme", "grabarDocumentoSeguro", cConsulta,lEmpleado,"Error #3131",grabarDocumentoSeguro2SQL.odbc,iMuestraMsg);
		CDialogoML::OnCancel();
	}
	else
	{
		grabarDocumentoSeguro2SQL.Commit();
	}	
}

bool CDlgReporteDoctoSeguroAfirme::transaccionGrabarDocumentosSeguro()
{
char cIPDestino[22],cConsulta[1002];
CString sSqlTxt;
bool bFlagEjecuto=true;

	sSqlTxt.Format("SELECT cagrabardocumentosseguro('%d')",iCaja);

	CGrabarDocumentoSeguro2X grabarDocumentoSeguro2SQL(&odbcTiendaNumero);		

	if ( !grabarDocumentoSeguro2SQL.Exec(sSqlTxt) )
	{
		//Se obtiene el error
		sServer.Trim();			
		sprintf(cIPDestino,"%s",sServer);
		cIPDestino[15] = 0;
		sSqlTxt.Trim();			
		sprintf(cConsulta,"%s",sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		grabarDocumentoSeguro2SQL.odbc->GetLastError(grabarDocumentoSeguro2SQL.GetHstmt());
		grabarMensajeError( "C", iCaja, cIPDestino, "ReporteDoctoSeguroAfirme", "CDlgReporteDoctoSeguroAfirme", "transaccionGrabarDocumentosSeguro", cConsulta,lEmpleado,"ERROR #3132",grabarDocumentoSeguro2SQL.odbc,iMuestraMsg);
		bFlagEjecuto = false;
		CDialogoML::OnCancel();
	}
	return bFlagEjecuto;
}  

long CDlgReporteDoctoSeguroAfirme::obtenerFolio(int iTipoFolio,int iIncrementarFolio)
{
CString sSqlTxt;
long lFolio=0L;
char cIPDestino[22],cConsulta[1002];

	memset(cIPDestino,0,sizeof(cIPDestino));
	memset(cConsulta,0,sizeof(cConsulta));
	
	sSqlTxt.Format("SELECT gnincrementarfolio('C', '%d', '%d', '%d' ) ", iCaja, iTipoFolio, iIncrementarFolio );	

	CFolioCoppel  folioCoppelSQL(&odbcTiendaNumero);

	if( !folioCoppelSQL.Exec( sSqlTxt ) )
	{		
		//Se obtiene el error
		sServer.Trim();		
		sprintf(cIPDestino,"%s",sServer);
		cIPDestino[15] = 0;
		sSqlTxt.Trim();		
		sprintf(cConsulta,"%s",sSqlTxt);
		cConsulta[ sSqlTxt.GetLength() ] = 0;

		folioCoppelSQL.odbc->GetLastError(folioCoppelSQL.GetHstmt());
		grabarMensajeError( "M", iCaja, cIPDestino, "ReporteDoctoSeguroAfirme", "CDlgReporteDoctoSeguroAfirme", "obtenerFolio", cConsulta,lEmpleado,"Error #3133",folioCoppelSQL.odbc,iMuestraMsg);
		CDialogoML::OnCancel();
	}
	else
	{
		folioCoppelSQL.activarCols();
		if ( folioCoppelSQL.Leer() )
		{
			lFolio = (long)folioCoppelSQL.folio;		
		}
	}
	return lFolio;
}