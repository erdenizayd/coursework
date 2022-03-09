import java.io.*;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class CengPokeParser {

	public static ArrayList<CengPoke> parsePokeFile(String filename)
	{
		ArrayList<CengPoke> pokeList = new ArrayList<CengPoke>();

		// You need to parse the input file in order to use GUI tables.
		// TODO: Parse the input file, and convert them into CengPokes

		return pokeList;
	}
	
	public static void startParsingCommandLine() throws IOException
	{
		// TODO: Start listening and parsing command line -System.in-.
		// There are 5 commands:
		// 1) quit : End the app. Print nothing, call nothing.
		// 2) add : Parse and create the poke, and call CengPokeKeeper.addPoke(newlyCreatedPoke).
		// 3) search : Parse the pokeKey, and call CengPokeKeeper.searchPoke(parsedKey).
		// 4) delete: Parse the pokeKey, and call CengPokeKeeper.removePoke(parsedKey).
		// 5) print : Print the whole hash table with the corresponding buckets, call CengPokeKeeper.printEverything().

		// Commands (quit, add, search, print) are case-insensitive.
		InputStreamReader inp = new InputStreamReader(System.in, "UTF-8");
		BufferedReader buff = new BufferedReader(inp);
		while(true){
			String input = buff.readLine();
			if(input.startsWith("quit")) break;
			if(input.startsWith("add")){
				String[] token = input.split("\t");
				int pkey = Integer.parseInt(token[1]);
				String pname = token[2];
				String ppower = token[3];
				String ptype = token[4];
				CengPoke newpoke = new CengPoke(pkey,pname,ppower,ptype);
				CengPokeKeeper.addPoke(newpoke);

			}
			if(input.startsWith("search")){
				String[] token = input.split("\t");
				int pkey = Integer.parseInt(token[1]);
				CengPokeKeeper.searchPoke(pkey);
			}
			if(input.startsWith("delete")){
				String[] token = input.split("\t");
				int pkey = Integer.parseInt(token[1]);
				CengPokeKeeper.deletePoke(pkey);
			}
			if(input.startsWith("print")){
				CengPokeKeeper.printEverything();
			}
		}
	}
}
