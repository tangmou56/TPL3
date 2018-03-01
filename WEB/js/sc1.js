function moyt(t){
	var sum=t.reduce((p,c)=>c+=p);
	var moy=sum/t.length;
	return moy;

}



function affiche_tableau(t){
	 document.write("<p>"+t+"</p>");


}

function affiche_moyenne(t){ 

	var sum=t.reduce((p,c)=>c+=p);
	var moy=sum/t.length;

	document.write("<p>moy="+moy+"</p>");


}

function occurrences(x,t){
	document.write("<p>occ="+t[x]+"</p>");


}

function onteulamoyenne(t){
	var nb=0;
	var moy=moyt(t);
	for(i in t){
		if(t[i]>=moy)
			nb+=1;
	}
	document.write("<p>nb pers="+nb+"</p>");


}

function recherche(x,t){ 
	for(i in t){
		if(t[i]==x){
			document.write("<p>present</p>");
			return ;
		}
	}
	document.write("<p>non present</p>");


}

var notes=[13,11,9,4,18,3,11,17,10];



affiche_tableau(notes); 
affiche_moyenne(notes);
occurrences(2,notes)
onteulamoyenne(notes);
recherche(3,notes);