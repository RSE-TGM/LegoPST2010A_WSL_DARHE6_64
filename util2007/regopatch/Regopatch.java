import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Regopatch
{
	
	private File dir;
	private String oldKKS = null;
	private String newKKS = null;

	/**
	 * Costruttore 
	 * 
	 * @param file file da modificare
	 */
	public Regopatch(File file)
	{
		refactor(file);

	}
	
	/**
	 * Costruttore 
	 * 
	 * @param file file da modificare
	 */
	public Regopatch(String dir)
	{
		this.dir = new File (dir);
	}

	public Regopatch(String dir,String oldKKS,String newKKS)
	{
		this.dir = new File (dir);
		this.oldKKS = oldKKS;
		this.newKKS = newKKS;
	}
	
	public void refactorAll ()
	{
		if (dir != null && dir.exists())
		{
			Set<File> files = new HashSet<File> ();
			getPageFiles(dir, files);
			for (File file : files)
			{
				refactor(file);
			}
		}
		else
		{
			System.out.println("Directory files non esistente!");
		}
	}
	
	private void refactor(File file)
	{
		try
		{
			System.out.println("File in modifica ----> " + file.getName());
			//chiavi oggetti in modifica
			List<KeyClass> keys = new ArrayList<KeyClass>();
			List<String> fileRead = readFile(file);
			for (String line : fileRead)
			{
				if (line.indexOf(".") > 0)
				{
					String keyFlat = line.substring(0, line.indexOf("."));
					String key = keyFlat + ".paginaStazioni";
					if (line.startsWith(key) && !keys.contains(key))
					{
						String val = getValue(line);
						if (!val.trim().equals("") && !val.trim().equalsIgnoreCase("kks"))
						{
							KeyClass kc = new KeyClass(keyFlat, key, val);
							keys.add(kc);
							// System.out.println("modification : " +
							// kc.toString());
						}
					}
				}
			}
			// aggiorna i valori
			List<String> toWrite = cloneRead(fileRead);
			for (KeyClass kc : keys)
			{
				for (int ix = 0; ix < fileRead.size(); ix++)
				{
					String line = fileRead.get(ix);
					if (line.startsWith(kc.getKeyFlat())
							&& !line.startsWith(kc.getKeyObject()))
					{
						if (line.indexOf("KKS") >= 0)
						{
							// System.out.println("pre : " + line);
							line = line.replaceAll("KKS", kc.getKeyValue());
							toWrite.set(ix, line);
							// System.out.println("post : " + line);
						}
					}
				}
			}
			//crea copia di backup del file in modifica
			File bck = new File(file.getAbsolutePath() + ".bck");
			copyFile(file, bck);
			//salva modifiche
			saveFile(toWrite, file.getAbsolutePath());
			System.out.println("File " + file.getName() + " aggiornato correttamente!");
		}
		catch (IOException e)
		{
			System.out.println(e);
		}
	}
	
	public void modify ()
	{
		System.out.println("File in modifica ----> " + dir.getName());
		List<String> toWrite  = new  ArrayList<String> ();
		try
		{
			List<String> fileRead = readFile(dir);
			for (String line : fileRead)
			{
				if (line.indexOf(oldKKS) >= 0)
				{
					line = line.replaceAll(oldKKS, newKKS);
				}
				toWrite.add(line);
			}
			//crea backup
			File bck = new File(dir.getAbsolutePath() + ".bck");
			copyFile(dir, bck);
			//salva modifiche
			saveFile(toWrite, dir.getAbsolutePath());
			System.out.println("File " + dir.getName() + " aggiornato correttamente!");
		}
		catch (IOException e)
		{
			System.out.println(e);
		}
		
	}

	/**
	 * Clona il flie per le modifiche
	 * 
	 * @param fileRead lista del file sequenziale
	 * @return file clonato
	 */
	private List<String> cloneRead(List<String> fileRead)
	{
		List<String> toWrite = new ArrayList<String>();
		for (String string : fileRead)
		{
			toWrite.add(string);
		}
		return toWrite;
	}

	/**
	 *  copia file 
	 *  
	 * @param source
	 * @param target
	 * @throws FileNotFoundException
	 * @throws IOException
	 */
	public void copyFile(File source, File target)
			throws FileNotFoundException, IOException
	{
		if (source.getAbsolutePath().equals(target.getAbsolutePath()))
		{
			return;
		}
		FileInputStream in = new FileInputStream(source);
		target.getParentFile().mkdirs();
		FileOutputStream out = new FileOutputStream(target);
		copyFile(in, out);
	}

	private void copyFile(FileInputStream in, FileOutputStream out)
			throws IOException
	{
		int l = 0;
		byte[] b = new byte[8192];
		while ((l = in.read(b)) > -1)
		{
			out.write(b, 0, l);
		}
		out.flush();
		out.close();
		in.close();
	}

	/**
	 * Torna il kks introdotto dall'utente
	 * @param line
	 * @return
	 */
	private String getValue(String line)
	{
		String tmp = line;
		String val = "";
		int posIn = tmp.indexOf("_");
		if (posIn > 0)
		{
			tmp = tmp.substring(posIn + 1);
			int posEnd = tmp.indexOf("_");
			if (posEnd > 0)
			{
				val = line.substring(posIn + 1, posIn + posEnd + 1);
			}
		}
		return val;
	}

	private void getPageFiles (File dir,Set<File> files)
	{
		File [] f = dir.listFiles();
		if (f != null)
		{
			for (int i = 0; i < f.length;i++)
			{
				File mf = f[i];
				if (mf.isFile() && mf.getName().toLowerCase().endsWith(".pag"))
				{
					files.add(mf);
				}
			}
		}
	}
	
	/**
	 * Salva il file
	 * 
	 * @param fileRead
	 * @param pathName
	 * @throws FileNotFoundException
	 */
	public void saveFile(List<String> fileRead, String pathName)
			throws FileNotFoundException
	{
		PrintStream ps = new PrintStream(pathName);
		for (String line : fileRead)
		{
			ps.print(line + "\n");
		}
		ps.flush();
		ps.close();
	}

	/**
	 * Legge il file
	 * 
	 * @param f
	 * @return
	 * @throws IOException
	 */
	public List<String> readFile(File f) throws IOException
	{
		List<String> fil = new ArrayList<String>();
		String ms = "";
		BufferedReader io = new BufferedReader(new FileReader(f));
		while ((ms = io.readLine()) != null)
		{
			fil.add(ms);
		}
		io.close();
		return fil;
	}

	public static void main(String[] args)
	{
		if (args != null && args.length == 0)
		{
			System.out.println("Usage:\n -f nomefile \n -all dir \n -m nomefile oldkks newkks");
			System.exit(0);
		}
		String par = args[0];
		if (par.equals("-all"))
		{
			if (args.length < 2)
			{
				System.out.println("Usage:\n -f nomefile \n -all dir \n -m nomefile oldkks newkks");
				System.exit(0);
			}
			Regopatch rp =new Regopatch (args[1]);
			rp.refactorAll();
		}
		if (par.equals("-f"))
		{
			if (args.length < 2)
			{
				System.out.println("Usage:\n -f nomefile \n -all \n");
				System.exit(0);
			}
			File f = new File(args[1]);
			if (!f.exists())
			{
				System.out.println("File '" + args[1] + "' non esistente!");
				System.exit(0);
			}
			new Regopatch(f);
		}
		if (par.equals("-m"))
		{
			if (args.length < 3)
			{
				System.out.println("Usage:\n -f nomefile \n -all dir \n -m nomefile oldkks newkks");
				System.exit(0);
			}
			System.out.println("Funzione non acora abilitata!");
			System.exit(0);
			//Regopatch rp = new Regopatch (args[0],args[1],args[2]);
			//TODO da verificare se fare un controllo + accurato!
			//rp.modify();
		}
	}

	class KeyClass
	{
		private String keyFlat = null;

		private String keyObject = null;

		private String keyValue = null;

		public KeyClass(String keyFlat, String keyObject, String keyValue)
		{
			this.keyFlat = keyFlat;
			this.keyObject = keyObject;
			this.keyValue = keyValue;
		}

		public String getKeyFlat()
		{
			return keyFlat;
		}

		public String getKeyObject()
		{
			return keyObject;
		}

		public String getKeyValue()
		{
			return keyValue;
		}

		public String toString()
		{
			return keyFlat + " - " + keyValue;
		}

	}
}
