//*********************************************************
//* MANDELBROT BEETLE                                     *
//* Diagrama el Fractal  del "Escarabajo de Mandelbrot"   *
//* Lenguaje: Javascript                                  *
//*                                                       *
//* INTERFAZ                                              *
//*                                                       *
//* Fecha: 05-Agosto-2019                                 *
//* Autors: Yacsha and AndyLaTuquita                      *
//* Web: www.theworldofchaos.com                          *
//*********************************************************

var out = null;// = document.getElementById('out');
var m_sNombre = "";
var m_nIdUsuario = 0;

window.onload = function() {
    out = document.getElementById('out'); 
    
    // Reacciona a los eventos del teclado
    function OnKeyDown(event) {
        var key = event.keyCode;

        if( canvas.style.visibility=="visible" &&
            (key==13 || key ==27) ){
            CerrarCanvas();
        }        
    }
    document.addEventListener('keydown', OnKeyDown, false);


    // Desserializa la base de datos
    DesSerializarBD();

    Login();
};

function Login()
{ 
    cls(); //limpia la pantalla       

    println("Welcome to the 'FRACTAL MANDELBROT BEETLE' Plotter");
    println("MENU");
    printlnURL("1. Login", "ILogin()");
    printlnURL("2. Register", "IRegistrarUsuario()");
    printlnURL("3. Exit", "Salir()");
   
    println("Choose an option");
}


function ILogin()
{
    var sClave;

    cls(); //limpia la pantalla
    println("Login<br>");
    m_sNombre  = prompt("Enter your name");
    sClave = prompt("Enter your password");
    
    m_nIdUsuario = ValidarUsuario(m_sNombre, sClave);
    
    if (m_nIdUsuario==0) {
   
        println("<br>Invalid username or password<br>");
        pausa("Login()");        
    } else {        
        InterfazPrincipal();
    }
}

function InterfazPrincipal()
{
   
    cls(); //limpia la pantalla

    println("Welcome " + m_sNombre  + "<br>");
    println("Select an option:<br>");
    printlnURL("1. Plot new fractal", "GraficarFractal(true)");
    printlnURL("2. Plot your favorite fractals", "InterfazPrincipal_GraficarFractal()");
    printlnURL("3. Logout", "Salir()");

    println("Choose an option");  
}

function InterfazPrincipal_GraficarFractal()
{
    ListarFractales1();

}

function IRegistrarUsuario() 
{
    var sClave;	

    cls(); //limpia la pantalla
    println("User Registration<br>");
    m_sNombre = prompt("Enter your name");
    sClave = prompt("Enter your password");
   
    var cOp = confirm("Save (Yes 'Y' or No 'N')");
    
    if (cOp){

        m_nIdUsuario = RegistrarUsuario(m_sNombre,sClave);
        InterfazPrincipal();	
    } else {
        Login();
    }

}

function GraficarFractal( bMostrarInstrucciones) {

    if ( bMostrarInstrucciones ) {
        
        cls();//limpia la pantalla
        println("INSTRUCTIONS:<br>");
        println("...The 'Mandelbrot Beetle' fractal will then be graphed in a new window");
        println("The Beetle is a theoretically 'infinite' zoom image, dare you find the limits!...<br>");
        println("1. Use left click to zoom in and right click to zoom out<br>");
        println("2. Press the ENTER key, ESC key or the Save BUTTON to finish and save your current image to favorite fractals<br>");



        println("Have you read the instructions? (", false);
        printlnURL("Yes", "GraficarFractal_Display()", false);
        println(" or ", false);
        printlnURL("No", "InterfazPrincipal()", false);
        println(")");


    }else {
        GraficarFractal_Display();
    }
}

function GraficarFractal2( dXmin, dXmax, dYmin, dYmax )
{  

    PlanoComplejo.xmin = dXmin;
    PlanoComplejo.xmax = dXmax;
    PlanoComplejo.ymin = dYmin;
    PlanoComplejo.ymax = dYmax;

    GraficarFractal(false);				
    
}

function GraficarFractal_Display(){

    cls();//limpia la pantalla

    Display();    
}

function GuardarFractal1() {

    var sNombreFractal;
    var sDescripcion;	

    cls();//limpia la pantalla

    var cOp = confirm("Do you want to save the fractal to favorites?");

    if (cOp){
   
    println("Save the fractal:");
   
    sNombreFractal = prompt("Enter the name of the fractal:");
   
    sDescripcion = prompt("Enter a description for your fractal:");
   
    GuardarFractal(m_nIdUsuario, sNombreFractal, sDescripcion, PlanoComplejo.xmin, PlanoComplejo.xmax, PlanoComplejo.ymin, PlanoComplejo.ymax);
   
    println("<br>Your fractal has been saved in the database...<br>");
   
    }
   
    pausa("InterfazPrincipal()");

}


function ListarFractales1() {

    var vFractales = [];
    
    var mFractal = null;

    ListarFractales( m_nIdUsuario, vFractales);

    var i, nFractales = vFractales.length;

    cls(); //limpia la pantalla

    if (nFractales == 0) {

        println("There are no favorite fractals, please create a new one with the 'Plot new fractal' option");
        mFractal = null;
    }
    else {

        for (i = 0; i < nFractales; i++) {
            mFractal = vFractales[i];            
            
            printlnURL( pad(i+1,2) + ". " + mFractal.nombreFractal, "GraficarFractal2(" +mFractal.xMin +","+mFractal.xMax+","+ mFractal.yMin+","+mFractal.yMax +  ")", false );
            println( " : '"+ mFractal.descripcion +  "'");				
        }
        
        println("<br>Choose an option");      
    }	

    pausa("InterfazPrincipal()");

    return mFractal;
}

function ListarFractales_Opcion(vFractales) {
    mFractal = vFractales.get(nOp - 1);	
}


function Salir()
{ 
    cls(); //limpia la pantalla       

    println("<br>Thank you for using Mandelbrot Beetle...");
    pausa("Login()"); 

    SerializarBD();
}


function println( texto, bImprimirLn=true ){
    out.innerHTML += texto     
    if(bImprimirLn )
        out.innerHTML +="<br>";
}

function printlnURL( texto, jsFuncionDestinoURL, bImprimirLn=true  ){
    
    println("<a onclick='" + jsFuncionDestinoURL + "' href='javascript:void(0);'>" + texto + "</a>", bImprimirLn);
}

function cls(){
    out.innerHTML = "";
}

function cls(){
    out.innerHTML = "";
}

function pausa( jsFuncionDestinoURL ){
    printlnURL("Press HERE to continue . . .", jsFuncionDestinoURL );
}

function pad(num, size) {
    var s = num+"";
    while (s.length < size) s = "0" + s;
    return s;
}

