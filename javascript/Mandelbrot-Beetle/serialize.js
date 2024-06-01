/***********************************************************************
MANDELBROT BEETLE

Plot the "Mandelbrot Beetle" Fractal

Language: Javascript

DATABASE SERIALIZATION

Technology: Javascript+jQuery
Connection to the MyJSON repository that stores the project database.
REST API is used for the connection via the PUT and GET protocols

Developed by:

	- Yacsha
    - AndyLaTuquita 

Web: www.theworldofchaos.com   

HISTORY...

 >> Version 2 - 01-VI-2024
    - Improvedment: The Interface is translated from Spanish to English
    - Improvedment: Minor changes to description and credits

>> Version 1 - 05-VIII-2019
	- First version in Spanish

***********************************************************************/

// Conexión con repositorio MyJSON.com que guarda la base de datos
// del proyecto de manera permanente en el siguiente link

// ***********************************************************
// NOTICE (01-VI-2024):
// myjson.com closed in 2020, so the functionality of
// serializing to an online server is not currently working,
// but if you manage to access a server similar to myjson.com,
// you can put the link to your repository in this place, so
// that the Rest-APIs for serialization work with this new link
// ***********************************************************
var uriRepositorio = "https://api.myjson.com/bins/7i873";

function SerializarBD(){
    
    // Se usa protocolo PUT

    var bd = [];
    bd.push( bdTablaUsuario );
    bd.push( bdTablaFractal );

    var bdJSON = JSON.stringify(bd);    
 
    // Guarda JSON
   $.ajax({
        url:uriRepositorio,
        type:"PUT",
        data:bdJSON,
        contentType:"application/json; charset=utf-8",
        dataType:"json",
        success: function(data, textStatus, jqXHR){
        
        }
    });
}

function DesSerializarBD(){

    // Se usa protocolo GET

     // Carga JSON
    $.get(uriRepositorio, function (data, textStatus, jqXHR) {
          
        bdTablaUsuario = data[0];
        bdTablaFractal = data[1];

    });
}