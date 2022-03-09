import java.util.ArrayList;
import java.util.LinkedList;
import java.lang.Math;

public class CengHashTable {
	public class Bucket {
		public int localDepth;
		public LinkedList<CengPoke> entries = new LinkedList<CengPoke>();

		Bucket(int depth){
			this.localDepth = depth;
		}
	}
	public int globalDepth;
	public int bSize;
	public ArrayList<Bucket> dir;

	public CengHashTable()
	{
		this.bSize = CengPokeKeeper.getBucketSize();
		globalDepth = 0;

		dir = new ArrayList<>();
		dir.add(new Bucket(0));

	}

	private String HashHelper(Integer key){
		int hashMod = CengPokeKeeper.getHashMod();
		int count = (int) ((Math.log(hashMod) / Math.log(2)));
		int len;
		String binary;

		key = key % hashMod;
		binary = Integer.toBinaryString(key);
		len = binary.length();
		for(int i = 0; i < count - len; i++){
			binary = "0" + binary;
		}
		if(globalDepth == count) return binary;

		return binary;
	}

	private int Hash(Integer key)
	{
		if(globalDepth == 0) return 0;
		String binary = HashHelper(key);
		return Integer.parseInt(binary.substring(0,globalDepth),2);
	}

	public void deletePoke(Integer pokeKey)
	{
		int key = Hash(pokeKey);
		int emptyBuckets = 0;
		Bucket bucket = dir.get(key);
		for(int i = 0; i < bucket.entries.size(); i++){
			CengPoke temp = bucket.entries.get(i);
			if(temp.pokeKey() == pokeKey){
				bucket.entries.remove(i);
				break;
			}
		}
		LinkedList<CengPoke> temp = dir.get(0).entries;
		if(temp.isEmpty()) {
			emptyBuckets++;
		}
		for (Bucket value : dir) {
			if (value.entries != temp) {
				temp = value.entries;
				if (temp.isEmpty()) {
					emptyBuckets++;
				}
			}
		}

		System.out.println("\"delete\": {");
		System.out.println("\t\"emptyBucketNum\": " + emptyBuckets);
		System.out.println("}");
	}

	public void addPoke(CengPoke poke)
	{			
		int bucketno = Hash(poke.pokeKey());
		dir.get(bucketno).entries.add(poke);
		if(dir.get(bucketno).entries.size() > bSize){
			split(bucketno);
		}
	}

	private void split(Integer bucket)
	{
		LinkedList<CengPoke> temp = new LinkedList<>(dir.get(bucket).entries);
		boolean isdoubled = false;
		dir.get(bucket).localDepth++;
		int ldepth = dir.get(bucket).localDepth;
		dir.get(bucket).entries.clear();

		if(ldepth > globalDepth) {
			doubledir();
			isdoubled = true;
		}

		if(isdoubled) {
			dir.set(2*bucket,new Bucket(ldepth));
			dir.set(2*bucket+1,new Bucket(ldepth));
		}
		else{
			if(bucket % 2 == 0){
				dir.set(bucket,new Bucket(ldepth));
				dir.set(bucket+1,new Bucket(ldepth));
			}
			else{
				dir.set(bucket,new Bucket(ldepth));
			}
		}

		for(CengPoke entry: temp){
			addPoke(entry);
		}
	}

	private void doubledir(){
		ArrayList<Bucket> newdir = new ArrayList<Bucket>();
		int size = dir.size();
		for(int i = 0; i < size*2; i++) newdir.add(new Bucket(-1));
		for(int i = 0; i < size; i++){
			newdir.set(2*i,dir.get(i));
			newdir.set((2*i)+1,dir.get(i));
		}
		globalDepth++;
		dir = newdir;
	}

	public void searchPoke(Integer pokeKey)
	{
		int key = Hash(pokeKey);
		Bucket bucket = dir.get(key);
		boolean contains = false;
		CengPoke poke = null;

		for(int i = 0; i < bucket.entries.size(); i++){
			if(bucket.entries.get(i).pokeKey() == pokeKey){
				contains = true;
				poke = bucket.entries.get(i);
				break;
			}
		}
		if(contains){
			int count = 0;
			System.out.println("\"search\": {");
			for(int i = 0; i < dir.size(); i++){
				if(dir.get(i) == bucket){
					
					String hashpref = Integer.toBinaryString(i);
					if(hashpref.length() < globalDepth) {
						int len = hashpref.length();
						for(int k = 0; k < (globalDepth - len); k++){
							hashpref = "0" + hashpref;
						}
					}
					if(count > 0) System.out.print(",\n");
					count++;
					System.out.println("\t\"row\": {");
					System.out.println("\t\t\"hashPref\": " + hashpref + ",");
					System.out.println("\t\t\"bucket\": {");
					System.out.println("\t\t\t\"hashLength\": " + dir.get(i).localDepth + ",");
					System.out.println("\t\t\t\"pokes\": [");
					for (int j = 0; j < dir.get(i).entries.size(); j++){
						printPoke(dir.get(i).entries.get(j));
						if(j != dir.get(i).entries.size() - 1) System.out.println("\t\t\t\t},");
						else System.out.println("\t\t\t\t}");
					}
					System.out.println("\t\t\t]");
					System.out.println("\t\t}");
					System.out.print("\t}");
					}
			
		}
		System.out.print("\n");
		System.out.println("}");
		}
		else{
			System.out.println("\"search\": {");
			System.out.println("}");
		}
	
	}
	
	public void print()
	{
		System.out.println("\"table\": {");
		for(int i = 0; i < dir.size(); i++){
			printRow(i);
		}
		System.out.println("}");
	}

	private void printRow(int i){
		String hashpref = Integer.toBinaryString(i);
		if(hashpref.length() < globalDepth) {
			int len = hashpref.length();
			for(int k = 0; k < (globalDepth - len); k++){
				hashpref = "0" + hashpref;
			}
		}

		System.out.println("\t\"row\": {");
		System.out.println("\t\t\"hashPref\": " + hashpref + ",");
		System.out.println("\t\t\"bucket\": {");
		System.out.println("\t\t\t\"hashLength\": " + dir.get(i).localDepth + ",");
		System.out.println("\t\t\t\"pokes\": [");
		for (int j = 0; j < dir.get(i).entries.size(); j++){
			printPoke(dir.get(i).entries.get(j));
			if(j != dir.get(i).entries.size() - 1) System.out.println("\t\t\t\t},");
			else System.out.println("\t\t\t\t}");
		}
		System.out.println("\t\t\t]");
		System.out.println("\t\t}");
		if(i != dir.size() - 1) System.out.println("\t},");
		else System.out.println("\t}");
	}

	private void printPoke(CengPoke poke){
		System.out.println("\t\t\t\t\"poke\": {");
		System.out.println("\t\t\t\t\t\"hash\": " + HashHelper(poke.pokeKey()) + ",");
		System.out.println("\t\t\t\t\t\"pokeKey\": " + poke.pokeKey() + ",");
		System.out.println("\t\t\t\t\t\"pokeName\": " + poke.pokeName() + ",");
		System.out.println("\t\t\t\t\t\"pokePower\": " + poke.pokePower() + ",");
		System.out.println("\t\t\t\t\t\"pokeType\": " + poke.pokeType());
	}
	// GUI-Based Methods
	// These methods are required by GUI to work properly.
	
	public int prefixBitCount()
	{
		// TODO: Return table's hash prefix length.
		return 0;
	}
	
	public int rowCount()
	{
		// TODO: Return the count of HashRows in table.
		return 0;
	}
	
	public CengHashRow rowAtIndex(int index)
	{
		// TODO: Return corresponding hashRow at index.
		return null;
	}
	
	// Own Methods
}
