#pragma once

#include "conecta.hpp"
#include "general.hpp"


	//Identificador de dialogos para el archivo XML
	#define DIALOGO_REPORTEDOCTOSEGUROAFIRME	1
	
	#define MENSAJE_0001	1
	#define MENSAJE_0002	2
	
	#ifdef MAIN
		C_ODBC odbcTiendaNumero;
		C_ODBC odbcCartera;
	#else
		extern C_ODBC odbcTiendaNumero;
		extern C_ODBC odbcCartera;
	#endif




// Abrir Conexion -> if ( abrirConexionBD( &odbcTiendaNumero, cIpTiendaLocal, cIpTiendaLocal, CONECTA_TIENDANUMERO, iTienda ) )
// Cerrar Conexion -> cerrarConexionBD( &odbcTiendaNumero );

// Borrar del proyecto el #include "ctrlglob.hpp" de todos los fuentes y agregar este fuente a su proyecto.
// Borrar la carpeta que incluya las conexiones.
