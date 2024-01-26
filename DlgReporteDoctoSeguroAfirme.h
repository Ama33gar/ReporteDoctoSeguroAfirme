// DlgReporteDoctoSeguroAfirme.h : header file
//

#pragma once
#include "afxwin.h"
#include "DialogoML.h"

#define MENSAJE_1001	1
#define MENSAJE_1002	2
#define MENSAJE_1003	3
#define MENSAJE_1004	4

#define REPORTE_1001	1
#define REPORTE_1002	2
#define REPORTE_1003	3
#define REPORTE_1004	4
#define REPORTE_1005	5
#define REPORTE_1006	6
#define REPORTE_1007	7
#define REPORTE_1008	8
#define REPORTE_1009	9
#define REPORTE_1010	10
#define REPORTE_1011	11
#define REPORTE_1012	12
#define REPORTE_1013	13
#define REPORTE_1014	14
#define REPORTE_1015	15
#define REPORTE_1016	16
#define REPORTE_1017	17
#define REPORTE_1018	18
#define REPORTE_1019	19
#define REPORTE_1020	20
#define REPORTE_1021	21

// CDlgReporteDoctoSeguroAfirme dialog
class CDlgReporteDoctoSeguroAfirme : public CDialogoML
{
// Construction
public:
	CDlgReporteDoctoSeguroAfirme(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DLGREPORTEDOCTOSEGUROAFIRME };

// Variables
	CString sServer,sTienda,sCaja,sEmpleado,sLink,sArea,sMuestraMsg,sNumCtas;
	int iControles,iFoco;    
    bool bShiftTab;
	long lFacturaG,lFactura1,lFactura2,lCliente,lFolioSeguro,lEmpleado;
	int iCaja,iMuestraMsg, iDiaActual,iMesActual,iAnioActual,iCiudad,
		iFinLinea,iTipoImpresora;	
	int iNumCtas,iFlag,iCantidadDeSeguros1,iCantidadDeSeguros2;	
	char cSqlTxt[255];

	//Funciones
	bool validarClick(int nTmpFocus);
	void asignarFoco();	
	bool validarControl(char *cCadena);
	bool validarControles(void);
	bool boton();
	void imprimeReciboDocumentos( long lFolioSeguro, long lCliente );
	void grabarDocumentosSeguro( long lCliente, long lFolioSeguro );
	bool transaccionGrabarDocumentosSeguro();
	long obtenerFolio(int iTipoFolio,int iIncrementarFolio);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CStatic m_barraMsj, m_textoMsj;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton m_imprimir;
	CButton m_cancelar;
	CButton m_check1;
	CButton m_check2;
	CButton m_check3;
	CButton m_check4;
	CButton m_check5;
	CButton m_check6;
	CButton m_check7;
	CButton m_check8;
	CButton m_check9;	
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();	
	CEdit m_folioSeguro;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOk();
};