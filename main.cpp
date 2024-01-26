#define MAIN
#include "stdafx.h"
#include "resource.h"
#include "sysControl.h"
#include "DlgReporteDoctoSeguroAfirme.h"
#include "CargarDLL.h"
#include "gnwproto.hpp"
#include "password.hpp"
#include "wtienda.hpp"
#include "DialogoML.h"


//Variables
CString sServer,sTienda,sCaja,sEmpleado,sLink,sArea,sMuestraMsg,sNumCtas,sCliente,sFactura1,sFactura2,sCantidadDeSeguros1,sCantidadDeSeguros2;
int iTienda;


int CA0068( char *cInput1,char *cInput2 )
{
	
	//char cIpTiendaLocal[17];
	CString sSqlTxt, sDato,sLink;
	char cServer[15];
	int iFlag = 0;
	bool bContinuar=true;
	char cMensajeOut[MAX_BUFFER_XML]={0};

	char cIpTiendaLocal[25]	= { 0 }, cIpCartera[25]={0}, cSql[250]={0};
	int iLink;
	long lNumeroEmpleado = 0L;

	SParametros cParametros;

	memset( &cParametros, 0, sizeof( SParametros ) );
	memcpy( &cParametros, cInput1, sizeof( SParametros ) );

	iLink  = cParametros.iLink;
	

	memset( cServer,0,sizeof(cServer) );
	CDlgReporteDoctoSeguroAfirme dlg;

	if ( checarLink( iLink ) )
	{
		sServer =cParametros.sServer;
		dlg.sServer = sServer;
		sprintf(cIpTiendaLocal, "%s", sServer);
		sprintf(cServer, "%s", sServer);
        
		sTienda.Format( "%d", cParametros.iTienda);
		dlg.sTienda = sTienda;
		iTienda = atoi(sTienda);

		sEmpleado.Format( "%ld", cParametros.lEmpleado);
		dlg.sEmpleado = sEmpleado;

		sCaja.Format( "%d", cParametros.iCajaActual);
		dlg.sCaja = sCaja;
		dlg.iCaja = atoi(sCaja);

		sMuestraMsg.Format( "%d", cParametros.iMuestraMsg);
		dlg.sMuestraMsg = sMuestraMsg;
		dlg.iMuestraMsg = atoi(sMuestraMsg);			

		sCliente.Format( "%ld", cParametros.lCliente);
		dlg.lCliente = atol(sCliente);

		sFactura1.Format( "%ld", cParametros.lCodigo1);
		dlg.lFactura1 = atol(sFactura1);

		sFactura2.Format( "%ld", cParametros.lCodigo2);
		dlg.lFactura2 = atol(sFactura2);			

		//if ( abrirConexion(cIpTiendaLocal, cIpTiendaLocal, iTienda) == true )
		if( abrirConexionBD(&odbcTiendaNumero, 0, cIpTiendaLocal, cIpTiendaLocal, CONECTA_TIENDANUMERO, iTienda))
		{
			if (consultarIpServidor(&odbcTiendaNumero, cIpCartera, SERV_CARTERA, cSql))
			//if ( abrirConexionCartera(&odbc) == true )
			{
				if( abrirConexionBD(&odbcCartera,SERV_CARTERA, cIpCartera, cIpCartera, CONECTA_CARTERA))
				{
					dlg.iFinLinea = finLinea( &odbcTiendaNumero, 'C', dlg.iCaja, bContinuar, dlg.cSqlTxt, true ); 
					if( bContinuar == true )
					{
						dlg.iTipoImpresora = tipoImpresora( &odbcTiendaNumero, 'C', dlg.iCaja, bContinuar,dlg.cSqlTxt, true ); 
						if( bContinuar == false )
						{
							obtenerMensaje("CA0068.XML",MENSAJE_0001,cMensajeOut);
							AfxMessageBox( cMensajeOut );
						}
						else
						{
							dlg.DoModal();
						}
					}
					else
					{
						obtenerMensaje("CA0068.XML",MENSAJE_0002,cMensajeOut);
						AfxMessageBox( cMensajeOut );
					}
				cerrarConexionBD(&odbcCartera);
				}
			cerrarConexionBD(&odbcTiendaNumero);
		    }
    	}
	}
	return 1;
}

