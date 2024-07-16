/***********************************************************************
MANDELBROT BEETLE

Plot the "Mandelbrot Beetle" Fractal

Language: Javascript

DATABASE

Technology:
 - Local in-memory Array database of native javascript dictionaries
 - The serialization of the DB is done with API-REST see more info
   in serialize.js
   
Developed by:

	- JOSE LUIS DE LA CRUZ LAZARO (Yacsha)
    - AndyLaTuquita 
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 01-VI-2024
    - Improvedment: The Interface is translated from Spanish to English
    - Improvedment: Minor changes to description and credits

>> Version 1 - 05-VIII-2019
	- First version in Spanish

***********************************************************************/

// Base de datos in-memory
var bdTablaUsuario = [];
var bdTablaFractal = [];

function RegistrarUsuario( nombre, clave )
{
    var nLastId = bdTablaUsuario.length+1;

    var registro = { IdUsuario: nLastId, nombreUsuario: nombre, contrasenia:  clave };

    bdTablaUsuario.push(registro );

    SerializarBD();

    return nLastId;
}

function ValidarUsuario( nombre,  clave ) {

    var i, nDatos = bdTablaUsuario.length;

    for( i=0; i<nDatos; i++ ){

        var registro = bdTablaUsuario[i];

        if( registro.nombreUsuario==nombre &&  registro.contrasenia==clave )
            return registro.IdUsuario;
    }

    return 0;
}

function GuardarFractal( nIdUsuario,  sNombre,  sDescripcion,  dXmin,  dXmax,  dYmin,  dYmax) {

    var nLastId = bdTablaFractal.length+1;

    var registro = { IdFractal: nLastId, IdUsuario: nIdUsuario, nombreFractal: sNombre, descripcion: sDescripcion, xMin: dXmin, xMax: dXmax, yMin: dYmin, yMax: dYmax };

    bdTablaFractal.push(registro );

    SerializarBD();

    return nLastId;
}


function ListarFractales( nIdUsuario, vFractales){

    var i, nDatos = bdTablaFractal.length;

    for( i=0; i<nDatos; i++ ){

        var registro = bdTablaFractal[i];

        if(registro.IdUsuario== nIdUsuario)
            vFractales.push(registro);
    }
}

