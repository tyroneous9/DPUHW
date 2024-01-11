package Autocomplete;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JTextField;


public class AutocompleteGUI {
	
	public static void main(String[] args) throws FileNotFoundException {
		
		// read in the terms from a file
    	File file = new File("movies.txt");
        Scanner reader = new Scanner(file);
        int n = Integer.parseInt(reader.nextLine());
        Term[] terms = new Term[n];
        for(int i=0; i<n; i++) {
        	String[] elements = reader.nextLine().split("	");
        	String query = elements[0];
        	long weight = Long.parseLong(elements[1]);
        	terms[i] = new Term(query, weight);
        }
        reader.close();
		
    	Autocomplete movies  = new Autocomplete(terms);

	    JFrame f = new JFrame("Top Movies");
	    f.setSize(300, 200);
	    f.setLocation(200,200);
	    final JTextArea textArea = new JTextArea(10, 40);
	    
	    final JTextField entry = new JTextField("Enter your query here");
	    
	    f.getContentPane().add(BorderLayout.NORTH,entry);
	    f.getContentPane().add(BorderLayout.CENTER, textArea);
	    final JButton button = new JButton("Search");
	    f.getContentPane().add(BorderLayout.SOUTH, button);
	    button.addActionListener(new ActionListener() {

	        @Override
	        public void actionPerformed(ActionEvent e) {
			try {
	        		textArea.setText(null);
		        	String query = entry.getText().toLowerCase();
		        	query = query.substring(0, 1).toUpperCase() + query.substring(1);
		        	
	        		Term[] matches = movies.allMatches(query);
		            for(Term t : matches) {
		            	textArea.append(t.query + " - " + String.valueOf(t.weight) + "\n");
		            }
	        	}
	        	catch (Exception x){
	        		textArea.append("No results found");
	        	}
	        }
	    });

	    f.setVisible(true);

	  }
	
}