public class Database(){
	private List<Integer> lst;

	public Database(){
		lst=new ArrayList<Interger>();
	}  



	//recu un id,retourne si il est deja connecté.
	//si non,l'ajoute dans la liste
	public boolean idrec(int id){
		int i;
		for(i:lst){
			if(i==id)
				return true;
		}
		lst.add(id);
		return false;
	}

	public void deconnect(int id){
		int i;
		for(i=0;i<lst.size();i++){
			if(lst.get(i)==id){
				lst.remove(i)
				return ;
			}
		}
	}


	
}