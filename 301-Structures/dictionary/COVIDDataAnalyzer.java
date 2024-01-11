package covid;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

/**
 * @author <Your Name Here>
 */
public class COVIDDataAnalyzer
{
	// You will need to define attributes to manage the data here!
	List<COVIDData> data;
	Map<String, List<COVIDData>> dataByCountry;
	Map<String, Long> casesByContinent;
	Map<String, List<String>> countriesByContinent;
	Map<String, Long> populationByCountry;
	
	/**
	 * Read the data in the know WHO format from the specified file
	 * @param filename the name of the file to read
	 * @return a list of COVIDData objects read from the file
	 * @throws ParseException 
	 */
	@SuppressWarnings("deprecation")
	public List<COVIDData> readFile(String filename) throws IOException, ParseException
	{
		List<COVIDData> data = new ArrayList<>();
		COVIDData dataObj;
		Scanner s = new Scanner(new File(filename));
		s.nextLine();
		while(s.hasNextLine()) {
			String[] lineArr = s.nextLine().split(",");
			dataObj = new COVIDData(new Date(Integer.parseInt(lineArr[3])-1900,Integer.parseInt(lineArr[2])-1,Integer.parseInt(lineArr[1])),Long.parseLong(lineArr[4]),Long.parseLong(lineArr[5]),lineArr[6],Long.parseLong(lineArr[9]),lineArr[10]);
			data.add(dataObj);
		}
		//Maps init
		dataByCountry = new TreeMap<String, List<COVIDData>>();
		casesByContinent = new TreeMap<String, Long>();
		populationByCountry = new TreeMap<String, Long>();
		countriesByContinent = new TreeMap<String, List<String>>();
		for(COVIDData obj : data) {
			//dataByCountry
			if(dataByCountry.containsKey(obj.getCountry())) {
				dataByCountry.get(obj.getCountry()).add(obj);
			}
			else {
				dataByCountry.put(obj.getCountry(), new ArrayList<COVIDData>());
				dataByCountry.get(obj.getCountry()).add(obj);
			}
			//casesByContinent
			if(casesByContinent.containsKey(obj.getContinent())) {
				casesByContinent.replace(obj.getContinent(), casesByContinent.get(obj.getContinent())+obj.getCases());
			}
			else {
				casesByContinent.put(obj.getContinent(), obj.getCases());
			}
			//countriesByContinent;
			if(!countriesByContinent.containsKey(obj.getContinent())){
				countriesByContinent.put(obj.getContinent(), new ArrayList<String>());
				countriesByContinent.get(obj.getContinent()).add(obj.getCountry());
			}
			else if(!countriesByContinent.get(obj.getContinent()).contains(obj.getCountry())) {
				countriesByContinent.get(obj.getContinent()).add(obj.getCountry());
			}
			else 

			//populationByCountry
			if(!populationByCountry.containsKey(obj.getCountry())) {
				populationByCountry.put(obj.getCountry(), obj.getPopulation());
			}
		}
		return data;
	}
	
	/**
	 * Create a new report filtered to the specified country and stored in the specified
	 * file.  The new file should use the following format
	 * <country>, <continent>, <population>, <day>, <month>, <year>, <cases>, <deaths>
	 * @param country - The country to report upon
	 * @param toFilename - The destination filename to save the report
	 * @throws IOException 
	 */
	@SuppressWarnings("deprecation")
	public void generateReport(String country, String toFilename) throws IOException
	{
		FileWriter w = new FileWriter(toFilename, true);
		List<COVIDData> lst = dataByCountry.get(country);
		for(int i=0; i<lst.size(); i++) {
			COVIDData data = lst.get(i);
			StringBuilder line = new StringBuilder();
			line.append(country+", ");
			line.append(data.getContinent()+", ");
			line.append(data.getPopulation()+", ");
			line.append(data.getDay().getDate()+", ");
			line.append(data.getDay().getMonth()+1+", ");
			line.append(data.getDay().getYear()+1900+", ");
			line.append(data.getCases()+", ");
			line.append(data.getDeaths()+", ");
			w.write(line+"\r\n");
		}
		w.close();
	}
	
	
	/**
	 * Retrieve the number of cases on each continent
	 * @return a map with the key of the continent name and the 
	 *  value the total number of cases on that continent
	 */
	public long getCasesForContinent(String continent)
	{
		long cases = casesByContinent.get(continent);
		return cases;
	}

	/**
	 * Retrieve the population of a continent
	 * @param continent - the target
	 * @return a map with the key of the continent name and the 
	 *  value the population of that continent
	 */
	public long getPopulationForContinent(String continent)
	{
		long population = 0;
		for(String country : countriesByContinent.get(continent)) {
			population += populationByCountry.get(country);
		}
		return population;
	}	
	
	/**
	 * Retrieve all the countries on a continent
	 * @param continent - the target
	 * @return a list of countries
	 */
	public Collection<String> getCountriesOnContinent(String continent)
	{
		return countriesByContinent.get(continent);
	}
}