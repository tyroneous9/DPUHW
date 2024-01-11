package automata;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Comparator;
import java.util.HashSet;
import java.util.Set;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.TransformerException;

import org.xml.sax.SAXException;

import automata.Automaton.AutomatonBuilder;
import automata.Test.TestException;

public class TestPA1<DetAut extends Automaton> {
	private AutomatonBuilder<DetAut> detbuilder;
	
	public TestPA1 (AutomatonBuilder<DetAut> detbuilder_) {
		    detbuilder = detbuilder_;
	}

  private <AnyAut extends Automaton>
      void testAutIO (AnyAut A, File f) throws IOException, TestException {
    for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replace (".xml", "-in.txt"))))
      if (!A.accepts (s))
        throw new TestException ("word " + s + " wrongly rejected");

    for (String s : Files.readAllLines (Paths.get (f.getAbsolutePath ().replace (".xml", "-out.txt"))))
      if (A.accepts (s))
        throw new TestException ("word " + s + " wrongly accepted");
  }

  private void testFile (File f, boolean complete) throws TestException {
    try {
      DetAut A = XML.fromXMLFile (f.getAbsolutePath (), detbuilder);

      if (!A.isDeterministic ())
        throw new TestException ("automaton does not appear to be deterministic or works on wrong alphabet.");

      // Test accepted/rejected words.
      testAutIO (A, f);

      // Test that the automaton can be reconstructed.
      ByteArrayOutputStream outxml = new ByteArrayOutputStream ();
      XML.toXML (A, outxml);
      ByteArrayInputStream inxml = new ByteArrayInputStream (outxml.toByteArray ());
      DetAut B = XML.fromXML (inxml, detbuilder);
      if (!A.equals (B))
        throw new TestException ("failed to be put into XML and back.");

      // For the bonus phase.
      if (!complete) {
        int nstates = A.getStates ().size () + 1;
        for (int i = nstates / 2; i < nstates; ++i) {
          Set<String> allstates = new HashSet<> (A.getStates ());

          if (A.isComplete ())
            throw new TestException ("wrongly marked as complete.");
          A.complete ();
          if (!A.isComplete ())
            throw new TestException ("automaton is incomplete after completion");
          if (!A.isDeterministic ())
            throw new TestException (
                "completed automaton does not appear to be deterministic or works on wrong alphabet.");

          // Check that it still accepts/rejects the same words if we just completed the
          // original automaton.
          if (i == 0)
            testAutIO (A, f);

          // Check that exactly one state was added.
          if (A.getStates ().stream ().filter (s -> !allstates.contains (s)).count () != 1)
            throw new TestException ("# of sink state added is "+nstates);
          // Add a new state, making the automaton incomplete.
          String newstate = A.getStates ().stream ().max (Comparator.comparingInt (String::length)).orElse ("") + "0";
          A.addState (newstate);
        }
      }
    } catch (ParserConfigurationException | SAXException | IOException | TransformerException e) {
      StringWriter sw = new StringWriter ();
      e.printStackTrace (new PrintWriter (sw));
      throw new TestException ("FATAL: " + sw.toString ());
    }
  }

  public void runTests () {
    int totalTests = 0;
    int passedTests = 0;
    File dir = new File ("test/resources/");
    File[] files = dir.listFiles ( (d, name) -> name.startsWith ("aut-") &&
        name.endsWith (".xml"));

    for (File f : files) {
      totalTests++;
      if (Test.runTest(f.getName(), () -> {
    	  testFile (f, true);
    	  return null;
      }, 1) == 1.)
        passedTests++;
    }

    // Bonus phase
    files = dir.listFiles ( (d, name) -> name.startsWith ("incomplete-aut-") &&
        name.endsWith (".xml"));

    System.err.println ("BONUS EXERCISE");
    for (File f : files) {
    	if (Test.runTest(f.getName(), () -> {
    		testFile (f, false);
    		return null;
    	}, 1) == 1.)
    		passedTests++;
    }

    System.err.println ("SCORE: " + passedTests + "/" + totalTests);
  }
  
  static public void main (String[] args) {
	  TestPA1<DetAutomaton> t1 = new TestPA1<> (s -> new DetAutomaton (s));
	  t1.runTests ();
	  System.exit (0);
  }
}
