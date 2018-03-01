function insc(){
	var nom = document.getElementById("nom");
	if(nom.value.length<=2)
		document.getElementById("infonom").innerHTML="il faut plus de 2 cars";
	else
		document.getElementById("infonom").innerHTML="ok";
	
	var pre = document.getElementById("pre");
	if(pre.value.length<=2)
		document.getElementById("infopre").innerHTML="il faut plus de 2 cars";
	else
		document.getElementById("infopre").innerHTML="ok";
		
	var key = document.getElementById("key");
	if(key.value.length<=6)
		document.getElementById("infokey").innerHTML="il faut plus de 6 cars";
	else
		document.getElementById("infokey").innerHTML="ok";
	
	var pay = document.getElementById("pays");
	if(pay.value=="v0")
		document.getElementById("infopays").innerHTML="il faut choisir un pays";
	else
		document.getElementById("infopays").innerHTML="ok";
	
	


}




function re(){
	var nom = document.getElementById("nom");
	nom.value=""
	var pre = document.getElementById("pre");
	pre.value=""
	var key = document.getElementById("key");
	key.value=""
	var pay = document.getElementById("pays");
	pay.value=="v0"
	document.getElementById("infonom").innerHTML="";
	document.getElementById("infopre").innerHTML="";
	document.getElementById("infokey").innerHTML="";
	document.getElementById("infopays").innerHTML="";
}